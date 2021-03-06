"""
Datastores are an easy way to keep an app's per-user data -- like
settings, bookmarks, or game state -- in sync across multiple devices
and operating systems.  Datastores are simple embedded databases,
which are synced to Dropbox.

This reference details the full set of classes needed when working
with datastores.  You can also read the Datastore API tutorial for a
detailed example of how to use them.

Unlike the client-side datastore APIs (for e.g. iOS, Android and
JavaScript), the Python datastore API does not implement automatic
conflict resolution.  Instead, if commit() fails, you must start over.
You can use the transaction() method for this, which allows you to
retry the transaction several times before giving up.

The Python API is not thread-safe.  If you want to use the same
Datastore object from multiple threads you should manage your own
locking.
"""

__all__ = ['DatastoreError', 'DatastoreNotFoundError', 'DatastoreConflictError',
           'DatastoreManager', 'DatastoreInfo', 'Datastore', 'Table', 'Record',
           'Date', 'Bytes', 'List',
           ]

import array
import base64
import collections
import datetime
import hashlib
import json
import math
import re
import sys
import time
import uuid

from .rest import RESTSocketError, ErrorResponse

# The port to Python 3 is not yet finished.
PY3 = sys.version_info[0] == 3

# Polyfill a few things for Bytes().
if PY3:  # pragma: no cover
    buffer = memoryview
    basestring = str
    long = int
else:
    bytearray = bytes


def _dbase64_encode(b):
    """Internal helper to encode bytes using our base64 variant.

    This is like urlsafe base64 encode but strips the trailing '='
    padding.  Also, it returns a string, not a bytes object.
    """
    bb = base64.urlsafe_b64encode(b)
    ss = str(bb.decode('ascii'))
    s = ss.rstrip('=')  # Remove padding.
    return s


def _dbase64_decode(s):
    """Internal helper to decode bytes using our base64 variant.

    This is the inverse of _dbase64_encode(), taking a string,
    returning bytes.
    """
    ss = s + '=' * (4 - len(s) % 4)  # Add padding back.
    bb = ss.encode('ascii')
    b = base64.urlsafe_b64decode(bb)
    return b


class DatastoreError(Exception):
    """Exception raised when the server returns a JSON error dict.

    This is the base class for more specific exception classes.
    """

    _resp__doc__ = """
        The JSON dict that was returned by the server.
        """

    def __init__(self, message, resp=None):
        super(DatastoreError, self).__init__(message)
        self.resp = resp


class DatastoreNotFoundError(DatastoreError):
    """Exception raised when attempting to open a non-existent datastore.

    Derives from :class:`DatastoreError`.
    """


class DatastoreConflictError(DatastoreError):
    """Exception raised when the server reports a conflict.

    Derives from :class:`DatastoreError`.
    """


class _DatastoreOperations(object):
    """Low-level datastore operations.

    The methods here map 1:1 to endpoints in the HTTP API.

    Also, the parameter names exactly match the HTTP protocol, and the
    return value is the JSON dict returned by the request.

    The exception is create_datastore(), which takes no parameters and
    adds the generated datastore ID to the JSON dict.

    Exceptions that may be raised:

    - :class:`dropbox.rest.ErrorResponse` if the server returned an
      error
    - :class:`dropbox.rest.HTTPSocketError` if there was a
      network problem
    - :class:`DatastoreNotFoundError` if a specified datastore
      does not exist
    - :class:`DatastoreConflictError` if the server reports a write
      conflict
    - :class:`DatastoreError` if an unanticipated JSON response is
      received
    """

    def __init__(self, client):
        self._client = client

    def _check_not_found(self, resp):
        if 'notfound' in resp:
            raise DatastoreNotFoundError(resp, resp['notfound'])
        return resp

    def _check_rev(self, resp):
        resp = self._check_not_found(resp)
        if 'rev' not in resp:
            raise DatastoreError('rev missing from response: %r' % (resp,), resp)
        return resp

    def _check_handle(self, resp):
        resp = self._check_rev(resp)
        if 'handle' not in resp:
            raise DatastoreError('handle missing from response: %r' % (resp,), resp)
        return resp

    def _check_ok(self, resp):
        resp = self._check_not_found(resp)
        if 'ok' not in resp:
            raise DatastoreError('ok missing from response: %r' % (resp,), resp)
        return resp

    def _check_conflict(self, resp):
        if 'conflict' in resp:
            raise DatastoreConflictError(resp['conflict'], resp)
        resp = self._check_rev(resp)
        return resp

    def _check_list_datastores(self, resp):
        if 'datastores' not in resp or 'token' not in resp:
            raise DatastoreError('token or datastores missing from response: %r' % (resp,),
                                 resp)
        return resp

    def _check_get_snapshot(self, resp):
        resp = self._check_rev(resp)
        if 'rows' not in resp:
            raise DatastoreError('rows missing from response: %r' % (resp,), resp)
        return resp

    def _check_await(self, resp):
        # Nothing to do here -- it may or may not have keys 'list_datastores' and 'get_deltas'.
        return resp

    def _check_get_deltas(self, resp):
        resp = self._check_not_found(resp)
        # If there are no new deltas the response is empty.
        if resp and 'deltas' not in resp:
            raise DatastoreError('deltas missing from response: %r' % (resp,), resp)
        return resp

    def get_datastore(self, dsid):
        url, params, headers = self._client.request('/datastores/get_datastore',
                                                    {'dsid': dsid}, method='GET')
        resp = self._client.rest_client.GET(url, headers)
        return self._check_handle(resp)

    def get_or_create_datastore(self, dsid):
        url, params, headers = self._client.request('/datastores/get_or_create_datastore',
                                                    {'dsid': dsid})
        resp = self._client.rest_client.POST(url, params, headers)
        return self._check_handle(resp)

    def create_datastore(self):
        # NOTE: This generates a dsid locally and adds it to the returned response.
        # Start with 32 random bytes so the encoded key will be at least 32 characters in length.
        bkey = uuid.uuid4().bytes + uuid.uuid4().bytes
        key = _dbase64_encode(bkey)
        # Use the sha256 of the *encoded* key.
        keyhash = hashlib.sha256(key.encode('ascii')).digest()
        dsid = '.' + _dbase64_encode(keyhash)
        url, params, headers = self._client.request('/datastores/create_datastore',
                                                    {'dsid': dsid, 'key': key})
        resp = self._client.rest_client.POST(url, params, headers)
        resp = self._check_handle(resp)
        if 'dsid' not in resp:
            resp['dsid'] = dsid
        return resp

    def delete_datastore(self, handle):
        url, params, headers = self._client.request('/datastores/delete_datastore',
                                                    {'handle': handle})
        resp = self._client.rest_client.POST(url, params, headers)
        return self._check_ok(resp)

    def list_datastores(self):
        url, params, headers = self._client.request('/datastores/list_datastores', method='GET')
        resp = self._client.rest_client.GET(url, headers)
        return self._check_list_datastores(resp)

    def get_snapshot(self, handle):
        url, params, headers = self._client.request('/datastores/get_snapshot',
                                                    {'handle': handle}, method='GET')
        resp = self._client.rest_client.GET(url, headers)
        return self._check_get_snapshot(resp)

    def get_deltas(self, handle, rev):
        url, params, headers = self._client.request('/datastores/get_deltas',
                                                    {'handle': handle, 'rev': rev},
                                                    method='GET')
        resp = self._client.rest_client.GET(url, headers)
        return self._check_get_deltas(resp)

    def put_deltas(self, handle, rev, changes, nonce=None):
        args = {'handle': handle,
                'rev': str(rev),
                'changes': json.dumps(changes),
                }
        if nonce:
            args['nonce'] = nonce
        url, params, headers = self._client.request('/datastores/put_delta', args)
        resp = self._client.rest_client.POST(url, params, headers)
        return self._check_conflict(resp)

    def await(self, token=None, cursors=None):
        params = {}
        if token:
            params['list_datastores'] = json.dumps({'token': token})
        if cursors:
            params['get_deltas'] = json.dumps({'cursors': cursors})
        url, params, headers = self._client.request('/datastores/await', params, method='GET')
        resp = self._client.rest_client.GET(url, headers)
        return self._check_await(resp)


class DatastoreManager(object):
    """A manager for datastores.

    In order to work with datastores you must first create an instance
    of this class, passing its constructor a
    :class:`dropbox.client.DropboxClient` instance.

    The methods here let you open or create datastores and retrieve
    the list of datastores.

    This class has no state except for a reference to the
    :class:`dropbox.client.DropboxClient`, which itself is threadsafe.
    """

    DEFAULT_DATASTORE_ID = 'default'  #: The default datastore ID.
    _DEFAULT_DATASTORE_ID__doc__ = """
        The default datastore ID used by :meth:`open_default_datastore()`.
        """

    def __init__(self, client):
        """Construct a ``DatastoreManager`` using a :class:`dropbox.client.DropboxClient`."""
        self._dsops = _DatastoreOperations(client)

    def __repr__(self):
        return '%s(%r)' % (self.__class__.__name__, self._dsops._client if self._dsops else None)

    def close(self):
        # This doesn't do anything to the _DatastoreOperations object.
        self._dsops = None

    def get_client(self):
        """Return the :class:`dropbox.client.DropboxClient` object used."""
        return self._dsops._client

    def open_default_datastore(self):
        """Open the default datastore for this account, creating it if needed.

        This is a shorthand for :meth:`open_or_create_datastore`\(:const:`DEFAULT_DATASTORE_ID`).

        Returns
            A :class:`Datastore` instance.
        """
        return self.open_or_create_datastore(self.DEFAULT_DATASTORE_ID)

    def open_datastore(self, id):
        """Open an existing datastore given its ID (a string).

        Returns
            A :class:`Datastore` instance.
        """
        resp = self._dsops.get_datastore(id)
        return self._datastore_from_response(resp, id)

    def open_or_create_datastore(self, id):
        """Open a local datastore, creating it if it does not yet exist.

        The ID must not start with a dot.

        Returns
            A :class:`Datastore` instance.
        """
        resp = self._dsops.get_or_create_datastore(id)
        return self._datastore_from_response(resp, id)

    def open_datastore_from_info(self, dsinfo):
        """Open an existing datastore given a :class:`DatastoreInfo`."""
        return self._datastore_from_args(id=dsinfo.id, handle=dsinfo.handle, rev=dsinfo.rev)

    def create_datastore(self):
        """Create a new datastore with a randomly assigned ID.

        The assigned ID will start with a dot.

        Returns
            A :class:`Datastore` instance.
        """
        resp = self._dsops.create_datastore()
        return self._datastore_from_response(resp, resp['dsid'])

    def delete_datastore(self, id):
        """Delete a datastore given its ID."""
        resp = self._dsops.get_datastore(id)
        self._dsops.delete_datastore(resp['handle'])

    def _datastore_from_response(self, resp, id):
        return self._datastore_from_args(id=id, handle=resp['handle'], rev=resp['rev'])

    def _datastore_from_args(self, id, handle, rev):
        ds = Datastore(self, id=id, handle=handle)
        if rev > 0:
            ds.load_snapshot()
        return ds

    def list_datastores(self):
        """List the existing datastores for this account.

        Returns
            A list of :class:`DatastoreInfo` objects.
        """
        resp = self._dsops.list_datastores()
        return [_make_dsinfo(item) for item in resp['datastores']]

    def await(self, token=None, datastores=None):
        """Wait until certain changes occur.

        This methods implements a flexible and efficient long-polling
        mechanism that can be used to be notified of changes to
        specific datastores and/or to the list of datastores itself
        (for the current account).

        Parameters
          token
            An optional token that represents a hash of the list of
            datastores, computed by the server.  If this parameter is
            present and non-empty, ``await()`` will return when the
            list of datastores has changed in a way that would cause a
            different token to be computed, such as when a datastore
            is created or deleted.  The token should be obtained from
            the previous ``await()`` call; as a special case, the
            value ``'.'`` forces the call to return immediately with a
            fresh token (as does any outdated token).

          datastores
            An optional list of :class:`Datastore` instances.  The
            list represents currently open datastores for which you
            are interested in receiving updates.  If this parameter is
            present and non-empty, ``await()`` will return whenever a
            new revision is available for any of those datastores.

        The call also returns after a certain amount of time passes
        without activity.  The timeout is controlled by the server; it
        is currently approximately one minute.

        Returns
            A ``(token, dsinfos, deltamap)`` tuple.

            The ``token`` value is a new token, or the value of the
            ``token`` parameter if there are no changes to the list of
            datastores.  You should pass this to the next ``await()``
            call.

            The ``dsinfos`` value is the full list of
            :class:`DatastoreInfo` objects (as returned by
            :meth:`list_datastores()`) if there is a new token,
            otherwise ``None``.

            The ``deltamap`` value is either a mapping indicating
            which of the given datastores were changed, or ``None`` if
            there are no changes to datastores to report.  If it is a
            mapping, each key is a :meth:`Datastore`, and the
            corresponding value is either a non-empty list of deltas,
            or ``None`` if that datastore is deleted or is otherwise
            invalid.

        Unlike :meth:`Datastore.load_deltas()`, ``await()`` does not
        apply the deltas returned in ``deltamap`` to the respective
        datastores; that is the caller's responsibility.  For
        example::

            for ds, deltas in deltamap.items():
                if deltas is not None:
                    ds.apply_deltas(deltas)
                else:
                    # ds has been deleted
        """
        cursors = None
        if datastores is not None:
            cursors = {}
            for ds in datastores:
                cursors[ds._handle] = ds._rev
        resp = self._dsops.await(token=token, cursors=cursors)
        dsinfos = None
        deltamap = None
        if 'list_datastores' in resp:
            subresp = resp['list_datastores']
            token = subresp['token']
            dsinfos = [_make_dsinfo(item) for item in subresp['datastores']]
        if 'get_deltas' in resp:
            subresp = resp['get_deltas']
            rawmap = subresp['deltas']
            deltamap = {}
            for ds in datastores:
                if ds._handle in rawmap:
                    deltamap[ds] = rawmap[ds._handle]
        return token, dsinfos, deltamap


DatastoreInfo = collections.namedtuple('DatastoreInfo', 'id handle rev title mtime')

# Dummy class for docstrings, see doco.py.
class _DatastoreInfo__doc__(object):
    """A read-only record of information about a :class:`Datastore`.

    Instances of this class are returned by
    :meth:`DatastoreManager.list_datastores()`.

    They can be passed to
    :meth:`DatastoreManager.open_datastore_from_info()`.
    """
    _id__doc__ = """The datastore ID (a string)."""
    # handle and rev are internal and should remain undocumented.
    # title and mtime are future features, undocumented for now.


def _make_dsinfo(item):
    title = mtime = None
    info = item.get('info')
    if info:
        title = info.get('title')
        raw_mtime = info.get('mtime')
        if raw_mtime is not None:
            mtime = Date.from_json(raw_mtime)
    return DatastoreInfo(id=item['dsid'], handle=item['handle'], rev=item['rev'],
                         title=title, mtime=mtime)


_DBASE64_VALID_CHARS = '-_A-Za-z0-9'
_VALID_NAMED_DSID_RE = r'[a-z0-9_-]([a-z0-9._-]{0,30}[a-z0-9_-])?'
_VALID_UNNAMED_DSID_RE = r'\.[%s]{1,100}' % _DBASE64_VALID_CHARS
_VALID_DSID_RE = r'\A(%s|%s)\Z' % (_VALID_NAMED_DSID_RE, _VALID_UNNAMED_DSID_RE)


class Datastore(object):
    """An object representing a datastore.

    A datastore holds a set of tables identified by table IDs, each of
    which holds a set of records identified by record IDs.  A record
    holds a set of field values identified by field names.  The
    ``Datastore`` object keeps a snapshot of the current content (all
    tables, records and fields) in memory and supports simple queries.

    Changes to a datastore are made through methods on the
    :class:`Table` and :class:`Record` classes, as well as the
    :class:`List` class (which represents a composite field value).

    Changes are not immediately sent to the server.  Instead, the
    datastore keeps a list of changes in memory; these are sent to the
    server by the :meth:`commit()` method.  The :meth:`load_deltas()`
    method retrieves new changes from the server and incorporates them
    into the current snapshot.  Those changes that have not yet been
    sent to the server can be undone using the :meth:`rollback()`
    method.  Finally, the :meth:`transaction()` method combines the
    functionality of these into a more powerful operation that can
    retry sets of changes specified by a callback function.

    **Do not instantiate this class directly**.  Use the methods on
    :class:`DatastoreManager` instead.
    """

    def __init__(self, manager, id=None, handle=None):
        self._manager = manager
        self._id = id
        self._handle = handle
        self._rev = 0
        self._tables = {}
        self._changes = []

    def __repr__(self):
        return 'Datastore(<rev=%d>, id=%r, handle=%r)' % (self._rev, self._id, self._handle)

    @staticmethod
    def is_valid_id(id):
        """A helper method to check for a valid datastore ID.

        There are actually two types of datastore IDs, which (for want
        of better terminology) are called local IDs and global IDs.

        Local datastores are created with
        :meth:`DatastoreManager.open_default_datastore()` or
        :meth:`DatastoreManager.open_or_create_datastore()`,
        and the app has control over the name.
        Valid local datastore IDs are 1-32 characters long and
        may contain the following characters: ``a-z 0-9 . - _`` .
        However the first and last character cannot be dots.  Note
        that upper case is not allowed.

        Global datastores are created with
        :meth:`DatastoreManager.create_datastore()`; the
        name is a dot followed by a random-looking sequence of
        characters assigned by the SDK.  Valid global datastore IDs
        are a dot followed by 1-100 dbase64 characters (which are
        ``a-z A-Z 0-9 - _``).  Note that upper case *is* allowed.

        The :meth:`DatastoreManager.open_datastore()` and
        :meth:DatastoreManager.open_datastore_from_info()`` methods
        can open either type of datastores.
        """
        return bool(re.match(_VALID_DSID_RE, id))

    def get_id(self):
        """Return the ID of this datastore (a string)."""
        return self._id

    def get_manager(self):
        """Return the :class:`DatastoreManager` to which this datastore belongs."""
        return self._manager

    def get_mtime(self):
        return self._get_info_field('mtime')

    def get_title(self):
        return self._get_info_field('title')

    def set_title(self, title):
        if title is not None and not isinstance(title, basestring):
            raise TypeError('Title must be a string, not %s' % type(title).__name__)
        self._set_info_field('title', title)

    def _set_mtime(self):
        now = time.time()
        mtime = Date(now)
        self._set_info_field('mtime', mtime)

    def _get_info_field(self, field):
        info_table = self.get_table(':info')
        info_record = info_table.get('info')
        if info_record is None:
            return None
        return info_record.get(field)

    def _set_info_field(self, field, value):
        info_table = self.get_table(':info')
        info_record = info_table.get_or_insert('info')
        info_record.set(field, value)

    def load_snapshot(self):
        """Load the datastore with a snapshot retrieved from the server.

        All previously loaded content of the datastore is discarded,
        including pending changes.

        This is automatically called by all of the ``open_*()``
        methods, so there is normally no reason to call this.
        """
        resp = self._manager._dsops.get_snapshot(self._handle)
        rev = resp['rev']
        rows = resp['rows']
        self._rev = 0
        self._tables = {}
        self._changes = []
        for row in rows:
            tid = row['tid']
            recordid = row['rowid']
            data = dict((field, _value_from_json(v)) for field, v in row['data'].items())
            table = self.get_table(tid)
            record = Record(table, recordid, data)
            table._records[recordid] = record
        self._rev = rev

    def await_deltas(self):
        """Wait for and incorporate changes to this datastore.

        It is an error to call this method if the datastore has
        pending changes.

        Returns
            A dict mapping table IDs to lists of records,
            see :meth:`apply_deltas()`.
        """
        if self._changes:
            raise DatastoreError('Cannot call await_deltas() with pending changes')
        resp = self._manager._dsops.await(cursors={self._handle: self._rev})
        if 'get_deltas' not in resp:
            return {}
        subresp = resp['get_deltas']
        if self._handle not in subresp['deltas']:
            return {}
        myresp = subresp['deltas'][self._handle]
        myresp = self._manager._dsops._check_not_found(myresp)
        deltas = myresp.get('deltas')
        return self.apply_deltas(deltas)

    def load_deltas(self):
        """Load new changes retrieved from the server into the datastore.

        All previously loaded content is preserved, unless explicitly
        deleted or modified by one of the loaded changes.

        It is an error to call this method if the datastore has
        pending changes.

        Calling ``ds.load_deltas()`` is equivalent to::

            deltas = ds.fetch_deltas()
            ds.apply_deltas(deltas)

        Returns
            A dict mapping table IDs to lists of records,
            see :meth:`apply_deltas()`.
        """
        if self._changes:
            raise DatastoreError('Cannot call load_deltas() with pending changes')
        deltas = self.fetch_deltas()
        return self.apply_deltas(deltas)

    def fetch_deltas(self):
        """Retrieve new changes from the server without applying them.

        This is one of the building blocks of :meth:`load_deltas()`;
        you probably want to use that instead.

        Returns
            A list of deltas suitable to be passed directly to
            :meth:`apply_deltas()`.
        """
        resp = self._manager._dsops.get_deltas(self._handle, self._rev)
        return resp.get('deltas')

    def apply_deltas(self, deltas):
        """Apply deltas retrieved by some other means.

        It is an error to call this method if the datastore has
        pending changes.

        The deltas should be received from the server.  Normally this
        is called internally by :meth:`await_deltas()` or
        :meth:`load_deltas()`.

        Returns
            A dict mapping table IDs to lists of records,
            indicating the records that were inserted, updated or deleted
            by the loaded deltas.
        """
        if self._changes:
            raise DatastoreError('Cannot call apply_deltas() with pending changes')
        if deltas is None:
            return {}
        raw_changed_records = {}
        for delta in deltas:
            rev = delta['rev']
            changes = delta['changes']
            if rev != self._rev:
                # Either the server sent us bad data or our state is mixed up.
                raise DatastoreError('Revision out of sequence (expected %d, actual %d)' %
                                     (self._rev, rev))
            for c in changes:
               ch = _Change.from_json(c)
               record = self._apply_change(ch)
               tid = record.get_table().get_id()
               rid = record.get_id()
               raw_changed_records[tid, rid] = record
            self._rev = rev + 1
        changed_records = {}
        for tid, rid in sorted(raw_changed_records):
            record = raw_changed_records[tid, rid]
            if tid in changed_records:
                changed_records[tid].append(record)
            else:
                changed_records[tid] = [record]
        return changed_records

    def get_table(self, tid):
        """Get a :class:`Table` object with the given table ID."""
        t = self._tables.get(tid)
        if t is None:
            t = Table(self, tid)
            self._tables[tid] = t
        return t

    def list_table_ids(self):
        """List the non-empty tables for this datastore.

        Returns
            A set of strings table IDs (strings).
        """
        tids = set()
        for tid, table in self._tables.items():
            if table._records:
                tids.add(tid)
        return tids

    def rollback(self):
        """Discard all pending changes since the last successful :meth:`commit()`."""
        while self._changes:
            ch = self._changes.pop()
            inv = ch.invert()
            self._apply_change(inv)

    def commit(self):
        """Attempt to commit all pending changes.

        Pending changes are all mutations to a datastore made through
        :meth:`Table.insert()`, :meth:`Record.set()` and similar
        methods (inluding mutating :class:`List` methods).

        To upload pending changes to the server you must use
        :meth:`commit()`, or :meth:`transaction()`, which calls it.

        This method raises :class:`DatastoreConflictError` when the
        server detects a conflict and refuses to accept the changes.
        The proper response to this exception is to call
        :meth:`rollback()`, then :meth:`load_deltas()`, and then retry
        the transaction from the top, or give up and report an error
        to the user.  (The :meth:`transaction()` method implements
        this higher-level control flow.)

        If there are any changes, this method adds a change that
        updates the datastore's mtime.  If there are no changes, this
        method is a no-op (and no empty delta will be sent to the
        server).
        """
        if not self._changes:
            return
        self._set_mtime()
        changes = [ch.to_json() for ch in self._changes]
        nonce = _new_uuid()
        resp = self._manager._dsops.put_deltas(self._handle, self._rev, changes, nonce)
        self._rev = resp['rev']
        self._changes = []

    def transaction(self, callback, *args, **kwds):
        """transaction(callback, *args, max_tries=1)

        Call a callback function and commit changes, with retries.

        When multiple clients try to update a datastore concurrently,
        it is possible for :meth:`commit()` to raise
        :class:`DatastoreConflictError`, indicating a conflict.  This
        function handles the details of handling such failures and
        retrying the updates.  You pass it a callback function which
        will be called repeatedly until :meth:`commit()` succeeds, or
        the maximum number of tries is reached.

        The keyword-only parameter ``max_tries`` specifies how many
        times the callback is called before giving up.  The default is
        1, i.e. call it only once; the recommended value is 4.

        Generally, if you plan to modify a datastore, you should do
        all your reads and writes in a transaction.  On entry, there
        should be no pending changes.

        Example::

            def do_stuff(record_id):
                record = tasks_table.get(record_id)
                user_count = record.get('user_count')
                record.update(user_count=user_count+1)

            datastore.transaction(do_stuff, some_record_id, max_tries=4)

        Extra positional arguments are passed on to the callback
        function.  On success, the return value of the callback is
        returned.

        When a commit attempt fails, uncommitted changes are rolled
        back using :meth:`rollback()`, and new changes are retrieved
        from the server and loaded into the datastore using
        :meth:`load_deltas()`.  This is done before checking whether
        we are out of tries.

        When giving up, :meth:`DatastoreError` is raised.

        When any other exception occurs (either in the callback or in
        the commit), uncommitted changes are rolled back and the last
        exception is re-raised.
        """
        # Hack: max_tries is a keyword-only parameter.
        max_tries = kwds.pop('max_tries', 1)
        if kwds:
            raise TypeError('Unexpected kwargs %r' % (kwds,))
        if max_tries < 1:
            raise ValueError('max_tries must be >= 1')
        # Note that catching BaseException is generally not advised.
        if self._changes:
            raise DatastoreError('There should be no pending changes')
        for _ in range(max_tries):
            try:
                rv = callback(*args)
            except Exception:
                # The callback failed; give up completely.
                self.rollback()
                raise
            try:
                self.commit()
            except DatastoreConflictError:
                # It's a conflict; update content and maybe try again.
                self.rollback()
                # If loading deltas fails, that's too bad.
                self.load_deltas()
            except Exception:
                # Some other error; give up completely.
                self.rollback()
                raise
            else:
                # Success!
                return rv
        # We ran out of tries.  But we've loaded new deltas.
        if max_tries == 1:
            raise DatastoreError('Failed to commit; set max_tries to a value > 1 to retry')
        else:
            raise DatastoreError('Failed to commit %d times in a row' % (max_tries,))

    # NOTE: The asserts below can only fire if the server sends bogus data.

    def _apply_change(self, change):
        op = change.op
        tid = change.tid
        recordid = change.recordid
        data = change.data
        table = self.get_table(tid)
        if op == INSERT:
            assert recordid not in table._records, repr((tid, recordid))
            record = Record(table, recordid, data)
            table._records[recordid] = record
        elif op == DELETE:
            record = table._records.pop(recordid, None)
            change.undo = dict(record._fields)
            record._fields = None
        elif op == UPDATE:
            record = table._records[recordid]
            fields = dict(record._fields)
            undo = {}
            for field, val in data.items():
                undo[field] = record._fields.get(field)
                assert _is_op(val), repr(val)
                op = val[0]
                if op == ValuePut:
                    fields[field] = val[1]
                elif op == ValueDelete:
                    # Silently ignore deletions for non-existing fields.
                    if field in data:
                        del fields[field]
                elif _is_listop(val):
                    fields[field] = self._apply_listop(fields.get(field), val)
                else:
                    assert False, repr((field, val))  # pragma: no cover
            record._fields = fields
            change.undo = undo
        else:
            assert False, repr(change)  # pragma: no cover
        return record

    def _apply_listop(self, oldval, val):
        op = val[0]
        if op == ListCreate:
            assert oldval is None or oldval == (), repr(oldval)
            return ()
        assert isinstance(oldval, tuple), repr(oldval)
        if op == ListPut:
            index, newval = val[1:]
            return oldval[:index] + (newval,) + oldval[index+1:]
        if op == ListInsert:
            index, newval = val[1:]
            return oldval[:index] + (newval,) + oldval[index:]
        if op == ListDelete:
            index = val[1]
            return oldval[:index] + oldval[index+1:]
        if op == ListMove:
            return _list_move(oldval, *val[1:])
        assert False, repr(val)  # pragma: no cover

    def close(self):
        """Close the datastore.

        The datastore should not be used after this call.

        All pending changes are lost.
        """
        # Make essential stuff fail.
        self._manager = None
        self._changes = None


_VALID_ID_RE = r'([a-zA-Z0-9_\-/.+=]{1,32}|:[a-zA-Z0-9_\-/.+=]{1,31})\Z'


class Table(object):
    """An object representing a table in a datastore.

    You need a ``Table`` in order to query or modify the content of the datastore.

    **Do not instantiate this class directly**.  Use
    :meth:`Datastore.get_table()` instead.  Calls with the same ID will return
    the same object.
    """

    def __init__(self, datastore, tid):
        self._datastore = datastore
        self._tid = tid
        self._records = {}

    def __repr__(self):
        return 'Table(<%s>, %r)' % (self._datastore._id, self._tid)

    @staticmethod
    def is_valid_id(id):
        """A helper method to check for a valid table ID.

        Valid table IDs are 1-32 characters long and may contain the
        following characters: ``a-z A-Z 0-9 _ - / . + =`` .  Reserved
        IDs start with a colon followed by 1-31 characters from that set.
        """
        return bool(re.match(_VALID_ID_RE, id))

    def get_id(self):
        """Return the ID of this table (a string)."""
        return self._tid

    def get_datastore(self):
        """Return the :class:`Datastore` to which this table belongs."""
        return self._datastore

    def get(self, recordid):
        """Return the record with the given record ID.

        If no such record exists, return None.
        """
        return self._records.get(recordid)

    def get_or_insert(self, recordid, **fields):
        """Return the record with the given record ID, or create it.

        If a record with the given record ID already exists, it is
        returned, and the keyword arguments are ignored.  If no such
        record exists, this inserts a record with the given record ID,
        setting its fields from the keyword arguments.
        """
        if recordid in self._records:
            return self._records[recordid]
        else:
            return self._insert_with_id(recordid, fields)

    def insert(self, **fields):
        """Insert a new record into the table with a random record ID.

        Random record IDs are generated according to RFC 4122, using
        UUID version 4.  If used properly we guarantee that they are
        universally unique for the lifetime of the solar system.

        The new record's fields are set from the keyword arguments.
        """
        return self._insert_with_id(_new_uuid(), fields)

    def _insert_with_id(self, recordid, fields):
        for field, value in fields.items():
            if value is None:
                raise TypeError('Cannot set field %r to None in insert' % (field,))
            if isinstance(value, (List, list, tuple)):
                value = tuple(value)
            _typecheck_value(value, field)
            fields[field] = value
        self._datastore._changes.append(_Change(INSERT, self._tid, recordid, dict(fields)))
        record = Record(self, recordid, fields)
        self._records[recordid] = record
        return record

    def query(self, **kwds):
        """Query the records in the table.

        If called without arguments, this returns a list of all
        records in the table.

        If called with keyword arguments, each keyword argument
        specifies a required value for the corresponding field;
        only records that have the required field values for all
        keyword arguments are returned.

        The following example retrieves all records in the 'tasks'
        table that have a 'done' field whose type is ``bool`` and
        whose value is ``False``:

            results = tasks.query(done=False)

        For the purpose of queries, integers and floats are compared
        using the standard Python equality comparisons.
        """
        results = []
        for record in self._records.values():
            for field, value in kwds.items():
                if field not in record._fields:
                    break
                rfv = record._fields[field]
                if rfv != value:
                    break
                # If the values match but the type don't, the filter
                # fails unless both types are numeric.
                trfv = type(rfv)
                tv = type(value)
                if trfv is not tv and not set((trfv, tv)) <= set((int, long, float)):
                    break
            else:
                results.append(record)
        return results


class Record(object):
    """An object representing a record in a table in a datastore.

    A record has a record ID and zero or more fields.

    A field value can be an atomic type or a list of atomic types.

    Atomic types are ``bool``, integer (``int`` or ``long``), ``float``, string
    (``unicode`` or 8-bit ``str``; the latter must be a valid UTF-8 string), or an
    instance of the special classes :class:`Date` or :class:`Bytes`.  Note that ``None`` is
    not a valid field value.

    **Do not instantiate this class directly**.  Use
    :meth:`Table.get()`, :meth:`Table.insert()`,
    :meth:`Table.get_or_insert()` or :meth:`Table.query()` instead.
    """

    def __init__(self, table, recordid, fields):
        self._table = table
        self._datastore = table._datastore
        self._recordid = recordid
        self._fields = fields

    def __repr__(self):
        if self._fields is None:
            return 'Record(<%s>, %r, <deleted>)' % (self._table._tid, self._recordid)
        else:
            return 'Record(<%s>, %r, %r)' % (self._table._tid, self._recordid, self._fields)

    def __eq__(self, other):
        if not isinstance(other, Record):
            return NotImplemented
        return (self._table is other._table and
                self._recordid == other._recordid and
                self._fields == other._fields)

    def __ne__(self, other):
        r = self.__eq__(other)
        if r is not NotImplemented:
            r = not r
        return r

    @staticmethod
    def is_valid_id(id):
        """A helper method to check for a valid record ID.

        Valid record IDs are 1-32 characters long and may contain the
        following characters: ``a-z A-Z 0-9 _ - / . + =`` .  Reserved
        IDs start with a colon followed by 1-31 characters from that set.
        """
        return bool(re.match(_VALID_ID_RE, id))

    @staticmethod
    def is_valid_field(field):
        """A helper method to check for a valid field name.

        Valid field names are 1-32 characters long and may contain the
        following characters: ``a-z A-Z 0-9 _ - / . + =`` .  Reserved
        field names start with a colon followed by 1-31 characters
        from that set.
        """
        return bool(re.match(_VALID_ID_RE, field))

    def get_id(self):
        """Return the ID of this record (a string)."""
        return self._recordid

    def get_table(self):
        """Return the :class:`Table` to which this record belongs."""
        return self._table

    def get(self, field):
        """Return the value of a field in the record.

        If the record does not have a field by that name, return ``None``.

        If the field value is a list, this returns a :class:`List` object;
        mutating that object will modify the field's value in the record.
        """
        if self._fields is None:
            return None
        v = self._fields.get(field)
        if isinstance(v, tuple):
            v = List(self, field)
        return v

    def set(self, field, value):
        """Set the value of a field in the record.

        Setting the value to ``None`` deletes the field.
        """
        self.update(**{field: value})

    def delete(self, field):
        """Delete the value of a field in the record.

        If the field does not exist this is a no-op.
        """
        self.update(**{field: None})

    def get_fields(self):
        """Return a dict mapping all the fields in the record to their values.

        Modifying the dict will not affect the record in the datastore.

        To enforce this, list values are returned as tuples.
        """
        if self.is_deleted():
            return {}
        return dict(self._fields)

    def update(self, **kwds):
        """Set the value of multiple fields in the record.

        For each keyword argument, the field by that name is set to
        the corresponding value, except that if the value is ``None``, the
        field is deleted.
        """
        if self.is_deleted():
            raise DatastoreError('Cannot update a deleted record')
        # If this assert triggers we're terribly confused.
        assert self._table._records.get(self._recordid) is self, repr(self)
        fields = dict(self._fields)
        data = {}
        undo = {}
        for field, value in kwds.items():
            if value is None:
                if field in fields:
                    undo[field] = fields.get(field)
                    del fields[field]
                    data[field] = [ValueDelete]
            else:
                undo[field] = fields.get(field)
                if isinstance(value, (List, list, tuple)):
                    value = tuple(value)
                _typecheck_value(value, field)
                fields[field] = value
                data[field] = [ValuePut, value]
        if data:
            change = _Change(UPDATE, self._table._tid, self._recordid, data=data, undo=undo)
            self._table._datastore._changes.append(change)
            self._fields = fields

    def delete_record(self):
        """Delete the record from the table.

        If the record is already marked as deleted, this is a no-op.

        A record marked as deleted cannot be re-inserted, cannot be
        modified, and no longer has any fields.  To check for a
        deleted record, use :meth:`is_deleted()`.
        """
        if self.is_deleted():
            return
        # If this assert triggers we're terribly confused.
        assert self._table._records.get(self._recordid) is self, repr(self)
        change = _Change(DELETE, self._table._tid, self._recordid, data=None, undo=self._fields)
        self._table._datastore._changes.append(change)
        del self._table._records[self._recordid]
        self._fields = None

    def get_or_create_list(self, field):
        """Get a list field, possibly setting it to an empty list.

        If the field exists, it must be a list.  If it does not exist,
        it is set to an empty list.  In either case, a :class:`List`
        object representing the field is returned.
        """
        if self.is_deleted():
            raise DatastoreError('Cannot update a deleted record')
        v = self._fields.get(field)
        if isinstance(v, tuple):
            return List(self, field)
        if v is not None:
            raise TypeError('Field %r already exists but is a %s instead of a list' %
                            (field, type(v).__name__))
        # Produce a ListCreate op.
        data = {field: _make_list_create()}
        change = _Change(UPDATE, self._table._tid, self._recordid, data=data, undo={field: None})
        self._table._datastore._changes.append(change)
        fields = dict(self._fields)
        fields[field] = ()
        self._fields = fields
        return List(self, field)

    def has(self, field):
        """Inquire whether the record has a given field.

        Return ``True`` if the field exists, ``False`` if not.
        """
        return self._fields is not None and field in self._fields

    def is_deleted(self):
        """Inquire whether the record is marked as deleted.

        Return ``True`` if the record has been deleted, ``False`` if not.
        """
        return self._fields is None


class Date(object):
    """A simple immutable object representing a timestamp.

    Datastores store timestamps as milliseconds since the Epoch
    (1/1/1970) in UTC.

    To store a timestamp, you must set a field to a ``Date``
    object; if a field value is a timestamp, getting the value will
    return a ``Date``.

    To construct a ``Date``, pass the constructor a POSIX
    timestamp as returned by ``time.time()`` (and many other standard
    Python APIs).

    You can convert a ``Date`` back to a POSIX timestamp by
    calling ``float()`` or ``int()`` on it.  These conversions take
    care of the conversion between seconds and milliseconds;
    milliseconds map to fractions when converting to/from ``float``,
    and are truncated when converting to ``int``.

    
    You can also convert between Date and naive (``tzinfo``-less) ``datetime``
    objects using a choice of UTC or local time, using
    :meth:`to_datetime_utc()`, :meth:`from_datetime_utc()`,
    :meth:`to_datetime_local()`, and :meth:`from_datetime_local()`.
    Note that ``datetime`` objects using an explicit ``tzinfo`` field are not
    supported; if you need to work with those you must convert to/from
    naive ``datetime`` objects yourself.
    """

    def __init__(self, timestamp=None):
        """Construct a ``Date`` from a timestamp.

        The timestamp is an integer or float specifying seconds since
        the epoch.  It defaults to the current time.
        """
        if timestamp is None:
            timestamp = time.time()
        else:
            if not isinstance(timestamp, (float, int, long)):
                raise TypeError('Timestamp must be a float or integer, not %s' %
                                type(timestamp).__name__)
        self._timestamp = float(timestamp)

    def __repr__(self):
        dt = datetime.datetime.utcfromtimestamp(int(self._timestamp))
        ms = (self._timestamp * 1000) % 1000
        return 'Date<%s.%03d UTC>' % (str(dt), ms)

    def __float__(self):
        return self._timestamp

    def __int__(self):
        return int(self._timestamp)

    def __long__(self):
        return long(self._timestamp)

    def __eq__(self, other):
        if not isinstance(other, Date):
            return NotImplemented
        return self._timestamp == other._timestamp

    def __ne__(self, other):
        if not isinstance(other, Date):
            return NotImplemented
        return self._timestamp != other._timestamp

    def __lt__(self, other):
        if not isinstance(other, Date):
            return NotImplemented
        return self._timestamp < other._timestamp

    def __le__(self, other):
        if not isinstance(other, Date):
            return NotImplemented
        return self._timestamp <= other._timestamp

    def __gt__(self, other):
        if not isinstance(other, Date):
            return NotImplemented
        return self._timestamp > other._timestamp

    def __ge__(self, other):
        if not isinstance(other, Date):
            return NotImplemented
        return self._timestamp >= other._timestamp

    def to_datetime_utc(self):
        """Convert a ``Date`` to a ``datetime.datetime`` object in UTC.

        This sets the ``tzinfo`` field to ``None``.
        """
        return datetime.datetime.utcfromtimestamp(self._timestamp)

    @classmethod
    def from_datetime_utc(cls, dt):
        """Convert a ``datetime.datetime`` object in UTC to a ``Date``.

        The ``tzinfo`` field must be ``None``.
        """
        if dt.tzinfo is not None:
            raise TypeError('The argument datetime must not have a timezone')
        delta = dt - datetime.datetime.utcfromtimestamp(0)
        return cls(delta.days * 24*3600 + delta.seconds + delta.microseconds * 0.000001)

    def to_datetime_local(self):
        """Convert a ``Date`` to a ``datetime.datetime`` object in local time.

        This set the ``tzinfo`` field to ``None``.
        """
        return datetime.datetime.fromtimestamp(self._timestamp)

    @classmethod
    def from_datetime_local(cls, dt):
        """Convert a ``datetime.datetime`` object in UTC to a ``Date``.

        The ``tzinfo`` field must be ``None``.
        """
        if dt.tzinfo is not None:
            raise TypeError('The argument datetime must not have a timezone')
        # Keep the fraction separate because timetuple() doesn't store it.
        fraction = dt.microsecond * 0.000001
        return cls(time.mktime(dt.timetuple()) + fraction)

    # JSON encoding used by protocol.

    def to_json(self):
        return {TIMESTAMP: str(int(self._timestamp * 1000))}

    @classmethod
    def from_json(cls, j):
        # If this assert fires the server sent us bad data.
        assert (isinstance(j, dict) and
                list(j) == [TIMESTAMP] and
                isinstance(j[TIMESTAMP], basestring)), repr(j)
        timestamp = int(j[TIMESTAMP]) / 1000.0
        return cls(timestamp)


class Bytes(object):
    """A simple immutable object representing a binary string.

    Datastores transmit binary strings using a base64 encoding.

    Because Python 2 uses ambiguous representations of binary strings,
    you must wrap binary strings in this class in order to store them
    in a datastore.  8-bit strings not wrapped this way are assumed to
    represent text and must use the UTF-8 encoding.

    To construct a :class:`Bytes`, pass the constructor a ``str``
    instance, a ``buffer`` instance, or an ``array.array`` instance
    whose typecode indicate a one-byte-wide data type (i.e. ``'c'``, ``'b'``
    or ``'B'``).

    To convert a :class:`Bytes` to a raw byte string, call ``bytes()``
    on it.
    """

    def __init__(self, blob):
        """Construct a Bytes from an 8-bit string."""
        if not (isinstance(blob, (bytes, bytearray, buffer)) or
                isinstance(blob, array.array) and blob.typecode in ('c', 'b', 'B')):
            raise TypeError('Bytes must be a bytes-compatible type, not %s' %
                            type(blob).__name__)
        self._bytes = bytes(blob)  # Make a copy in case the argument is mutable.

    def __repr__(self):
        return 'Bytes(%r)' % self._bytes

    if PY3:  # pragma: no cover

        def __bytes__(self):
            return self._bytes

        def __str__(self):
            return repr(self)

    else:

        def __str__(self):
            return self._bytes

        def __unicode__(self):
            return repr(self)

    def __eq__(self, other):
        if isinstance(other, bytes):
            return self._bytes == other
        if isinstance(other, Bytes):
            return self._bytes == other._bytes
        return NotImplemented

    def __ne__(self, other):
        if isinstance(other, bytes):
            return self._bytes != other
        if isinstance(other, Bytes):
            return self._bytes != other._bytes
        return NotImplemented

    def __lt__(self, other):
        if isinstance(other, bytes):
            return self._bytes < other
        if isinstance(other, Bytes):
            return self._bytes < other._bytes
        return NotImplemented

    def __le__(self, other):
        if isinstance(other, bytes):
            return self._bytes <= other
        if isinstance(other, Bytes):
            return self._bytes <= other._bytes
        return NotImplemented

    def __gt__(self, other):
        if isinstance(other, bytes):
            return self._bytes > other
        if isinstance(other, Bytes):
            return self._bytes > other._bytes
        return NotImplemented

    def __ge__(self, other):
        if isinstance(other, bytes):
            return self._bytes >= other
        if isinstance(other, Bytes):
            return self._bytes >= other._bytes
        return NotImplemented

    # JSON encoding used by protocol.

    def to_json(self):
        s = _dbase64_encode(self._bytes)
        return {BLOB: s}

    @classmethod
    def from_json(cls, j):
        # If this assert fires the server sent us bad data.
        assert (isinstance(j, dict) and
                list(j) == [BLOB] and
                isinstance(j[BLOB], basestring)), repr(j)
        b = _dbase64_decode(j[BLOB])
        return cls(b)


class List(collections.MutableSequence):
    """A wrapper for a list value.

    When a field contains a list value, retrieving the field using
    :meth:`Record.get()` returns a ``List`` object.  This object
    behaves like a mutable sequence, but mutating it (e.g., replacing
    an item with a new value) will mutate the list value in the
    record.

    A ``List`` object knows the record and field to which it
    refers.  Multiple ``List`` objects may refer to the same record and
    field.

    ``List`` objects are compared by value (i.e., the sequence of
    items they contain, not the record and field to which they refer).
    They can also be compared to regular tuples and lists.

    Several methods available for regular lists are available for
    ``List`` objects, when in doubt, consult the documentation
    below.  Some methods unique to ``List`` objects also exist.

    Negative indices are supported in the usual fashion.

    **Do not instantiate this class directly**.  Use
    :meth:`Record.get()` or :meth:`Record.get_or_create_list()` instead.
    """

    def __init__(self, record, field):
        self._record = record
        self._field = field
        self._check()

    def __repr__(self):
        return 'List(<%s>, %r)' % (self._record.get_id(), self._field)

    def __eq__(self, other):
        if not isinstance(other, (List, list, tuple)):
            return NotImplemented
        return tuple(self) == tuple(other)

    def __ne__(self, other):
        if not isinstance(other, (List, list, tuple)):
            return NotImplemented
        return tuple(self) != tuple(other)

    def __lt__(self, other):
        if not isinstance(other, (List, list, tuple)):
            return NotImplemented
        return tuple(self) < tuple(other)

    def __le__(self, other):
        if not isinstance(other, (List, list, tuple)):
            return NotImplemented
        return tuple(self) <= tuple(other)

    def __gt__(self, other):
        if not isinstance(other, (List, list, tuple)):
            return NotImplemented
        return tuple(self) > tuple(other)

    def __ge__(self, other):
        if not isinstance(other, (List, list, tuple)):
            return NotImplemented
        return tuple(self) >= tuple(other)

    def get_record(self):
        """Return the :class:`Record` to which this ``List`` refers."""
        return self._record

    def get_field(self):
        """Return the field name (a string) to which this ``List`` refers."""
        return self._field

    def _check(self):
        if self._record.is_deleted():
            raise TypeError('Cannot use a List referring to a deleted record')
        v = self._record._fields.get(self._field)
        if not isinstance(v, tuple):
            raise TypeError('Cannot use a List referring to a non-list field')
        return v

    def __len__(self):
        v = self._check()
        return len(v)

    def __iter__(self):
        v = self._check()
        return iter(v)

    def __contains__(self, value):
        v = self._check()
        return value in v

    def __getitem__(self, index):
        v = self._check()
        return v[index]

    def __setitem__(self, index, value):
        if isinstance(index, slice):
            raise TypeError('Cannot set List slices')
        _typecheck_atom(value, self.get_field(), True)
        v = self._check()
        if index < 0:
            index += len(v)
        if not 0 <= index < len(v):
            raise IndexError
        v = v[:index] + (value,) + v[index+1:]
        self._update(v, _make_list_put(index, value))

    def __delitem__(self, index):
        if isinstance(index, slice):
            raise TypeError('Cannot delete List slices')
        v = self._check()
        if index < 0:
            index += len(v)
        if not 0 <= index < len(v):
            raise IndexError
        v = v[:index] + v[index+1:]
        self._update(v, _make_list_delete(index))

    def insert(self, index, value):
        """Insert a value into the list at a given index."""
        _typecheck_atom(value, self.get_field(), True)
        v = self._check()
        n = len(v)
        if index < 0:
            index += n
            if index < 0:
                index = 0
        elif index > n:
            index = n
        v = v[:index] + (value,) + v[index:]
        self._update(v, _make_list_insert(index, value))

    def append(self, value):
        """Append a value to the end of the list."""
        _typecheck_atom(value, self.get_field(), True)
        v = self._check()
        index = len(v)
        v = v + (value,)
        self._update(v, _make_list_insert(index, value))

    def move(self, index, newindex):
        """Move the list item at ``index`` to position ``newindex``.

        This is most easily explained as follows: first delete the
        item at position ``index``; then re-insert it at position
        ``newindex``.
        """
        v = self._check()
        n = len(v)
        if index < 0:
            index += n
        if not 0 <= index < len(v):
            raise IndexError
        if newindex < 0:
            newindex += n
        if not 0 <= newindex < len(v):
            raise IndexError
        v = _list_move(v, index, newindex)
        self._update(v, _make_list_move(index, newindex))

    def _update(self, v, op):
        record = self._record
        field = self._field
        change = _Change(UPDATE, record._table._tid, record._recordid,
                        data={field: op}, undo={field: record._fields.get(field)})
        record._datastore._changes.append(change)
        fields = dict(record._fields)
        fields[field] = v
        record._fields = fields


VALID_ATOM_TYPES = frozenset([
    int,
    bool,
    float,
    str,
    Date,
    Bytes,
    List,
    ] + ([] if PY3 else [long, unicode]))


def _typecheck_value(value, field):
    if isinstance(value, (List, list, tuple)):
        _typecheck_list(value, field)
    else:
        _typecheck_atom(value, field)


def _typecheck_list(value, field):
    for item in value:
        _typecheck_atom(item, field, is_list=True)


def _typecheck_atom(value, field, is_list=False):
    if type(value) not in VALID_ATOM_TYPES:
        if is_list:
            format = 'Type %s is not an acceptable list item type (field %r)'
        else:
            format = 'Type %s is not an acceptable value type (field %r)'
        raise TypeError(format % (type(value).__name__, field))


# Change ops.
INSERT, UPDATE, DELETE = 'I', 'U', 'D'

class _Change(object):

    REVERSED_OPS = {INSERT: DELETE, UPDATE: UPDATE, DELETE: INSERT}

    def __init__(self, op, tid, recordid, data=None, undo=None):
        assert op in (INSERT, UPDATE, DELETE), repr(op)
        assert isinstance(tid, basestring), repr(tid)
        assert isinstance(recordid, basestring), repr(recordid)
        if data is None:
            assert op == DELETE, repr(op)
        else:
            assert op != DELETE, repr(op)
            assert isinstance(data, dict), repr(data)
        if undo is not None:
            assert op != INSERT, repr(op)
            assert isinstance(undo, dict), repr(undo)
        self.op = op
        self.tid = tid
        self.recordid = recordid
        self.data = data
        self.undo = undo

    def __repr__(self):
        args = [self.op, self.tid, self.recordid]
        if self.data is not None or self.undo is not None:
            args.append(self.data)
            if self.undo is not None:
                args.append(self.undo)
        return '_Change(%s)' % (', '.join(map(repr, args)))

    def __eq__(self, other):
        if not isinstance(other, _Change):
            return NotImplemented
        return (self.op == other.op and
                self.tid == other.tid and
                self.recordid == other.recordid and
                self.data == other.data and
                self.undo == other.undo)

    def __ne__(self, other):
        eq = self.__eq__(other)
        if eq is not NotImplemented:
            eq = not eq
        return eq

    def without_undo(self):
        return _Change(self.op, self.tid, self.recordid, self.data)

    def invert(self):
        if self.op == UPDATE:
            newdata = {}
            newundo = {}
            for name, op in self.data.items():
                assert _is_op(op), repr((name, op))
                if _is_listop(op):
                    newdata[name], newundo[name] = self._invert_listop(name, op)
                else:
                    # Before and after are from op's POV.
                    before = self.undo.get(name)
                    opid = op[0]
                    if opid == ValuePut:
                        after = op[1]
                        if before is None:
                            newdata[name] = [ValueDelete]
                            newundo[name] = after
                        else:
                            newdata[name] = [ValuePut, before]
                            newundo[name] = after
                    elif opid == ValueDelete:
                        newdata[name] = [ValuePut, before]
                        newundo[name] = None
                    else:
                        assert False, repr((name, op))  # pragma: no cover
            return _Change(UPDATE, self.tid, self.recordid, newdata, newundo)
        else:
            return _Change(self.REVERSED_OPS[self.op], self.tid, self.recordid,
                           data=self.undo, undo=self.data)

    def _invert_listop(self, name, op):
        assert _is_listop(op), repr(op)
        # Before and after are from op's POV.
        before = self.undo[name]
        opid = op[0]
        if opid == ListCreate:
            after = ()
            invop = [ValueDelete]
            return invop, after
        index = op[1]
        assert isinstance(before, tuple), repr((name, before))
        if opid == ListPut:
            assert 0 <= index < len(before), repr((name, index, len(before)))
            opvalue = op[2]
            after = before[:index] + (opvalue,) + before[index+1:]
            invop = _make_list_put(index, before[index])
        elif opid == ListInsert:
            assert 0 <= index <= len(before), repr((name, index, len(before)))
            opvalue = op[2]
            after = before[:index] + (opvalue,) + before[index:]
            invop = _make_list_delete(index)
        elif opid == ListDelete:
            assert 0 <= index < len(before), repr((name, index, len(before)))
            after = before[:index] + before[index+1:]
            invop = _make_list_insert(index, before[index])
        elif opid == ListMove:
            assert 0 <= index < len(before), repr((name, index, len(before)))
            newindex = op[2]
            assert 0 <= newindex < len(before), repr((name, index, len(before)))
            after = _list_move(before, index, newindex)
            invop = _make_list_move(newindex, index)
        else:
            assert False, repr((name, op))  # pragma: no cover
        return invop, after

    @classmethod
    def from_json(cls, val):
        assert isinstance(val, list) and len(val) >= 3, repr(val)
        op, tid, recordid = val[:3]
        if op == INSERT:
            assert len(val) == 4, repr(val)
            data = dict((field, _value_from_json(v)) for field, v in val[3].items())
        elif op == UPDATE:
            assert len(val) == 4, repr(val)
            data = dict((field, _op_from_json(v)) for field, v in val[3].items())
        elif op == DELETE:
            assert len(val) == 3, repr(val)
            data = None
        else:
            assert False, repr(val)  # pragma: no cover
        return cls(op, tid, recordid, data)

    def to_json(self):
        # We never serialize the undo info.
        if self.op == INSERT:
            data = dict(self.data)
            for k, v in data.items():
                data[k] = _value_to_json(v)
            return [self.op, self.tid, self.recordid, data]
        if self.op == UPDATE:
            data = {}
            for k, v in self.data.items():
                assert _is_op(v), repr(v)
                data[k] = _op_to_json(v)
            return [self.op, self.tid, self.recordid, data]
        if self.op == DELETE:
            return [DELETE, self.tid, self.recordid]
        assert False, repr(self)  # pragma: no cover


# Field ops.
ValuePut, ValueDelete = VALUE_OPS = 'P', 'D'
ListCreate, ListPut, ListInsert, ListDelete, ListMove = LIST_OPS = 'LC', 'LP', 'LI', 'LD', 'LM'

# Sets of field ops.
VALUE_OPS = frozenset(VALUE_OPS)
LIST_OPS = frozenset(LIST_OPS)
ALL_OPS = VALUE_OPS | LIST_OPS

# Codes for encoding special values.
INTEGER = 'I'
NUMBER = 'N'
TIMESTAMP = 'T'
BLOB = 'B'

# Special floating point representations.
PLUS_INFINITY = {NUMBER: '+inf'}
MINUS_INFINITY = {NUMBER: '-inf'}
NOT_A_NUMBER = {NUMBER: 'nan'}

# Special floating point values.
INF_VALUE = 1e1000
NINF_VALUE = -INF_VALUE
NAN_VALUE = INF_VALUE / INF_VALUE


def _new_uuid():
    return base64.urlsafe_b64encode(uuid.uuid4().bytes).decode('ascii').rstrip('=')


def _value_from_json(v):
    if isinstance(v, (int, long)) and not isinstance(v, bool):
        return float(v)  # Plain JSON "numbers" are only used to encode floats.
    if isinstance(v, dict):
        assert len(v) == 1, repr(v)
        # This slightly awkward spelling is needed to support Python 2 and 3.
        key = next(iter(v))
        val = v[key]
        if key == INTEGER:
            return int(val)
        if key == NUMBER:
            if v == NOT_A_NUMBER:
                return NAN_VALUE
            if v == PLUS_INFINITY:
                return INF_VALUE
            if v == MINUS_INFINITY:
                return NINF_VALUE
            assert False, repr(v)  # pragma: no cover
        if key == TIMESTAMP:
            return Date.from_json(v)
        if key == BLOB:
            return Bytes.from_json(v)
        assert False, repr(v)  # pragma: no cover
    return v


def _value_to_json(v):
    if isinstance(v, (int, long)) and not isinstance(v, bool):
        return {INTEGER: str(v)}
    if isinstance(v, float):
        if math.isinf(v):
            if v > 0:
                return PLUS_INFINITY
            else:
                return MINUS_INFINITY
        if math.isnan(v):
            return NOT_A_NUMBER
    if isinstance(v, (Bytes, Date)):
        return v.to_json()
    return v


def _op_from_json(val):
    assert _is_op(val), repr(val)
    opid = val[0]
    if opid == ValuePut:
        return [opid, _value_from_json(val[1])]
    if opid in (ListPut, ListInsert):
        return [opid, val[1], _value_from_json(val[2])]
    return list(val)


def _op_to_json(val):
    assert _is_op(val), repr(val)
    opid = val[0]
    if opid == ValuePut:
        return [opid, _value_to_json(val[1])]
    if opid in (ListPut, ListInsert):
        return [opid, val[1], _value_to_json(val[2])]
    return list(val)


def _is_op(val):
    return isinstance(val, list) and val and val[0] in ALL_OPS


def _is_listop(val):
    return isinstance(val, list) and val and val[0] in LIST_OPS


def _list_move(old, index, newindex):
    if index <= newindex:
        return (old[:index] + old[index+1:newindex+1] +
                old[index:index+1] + old[newindex+1:])
    else:
        return(old[:newindex] + old[index:index+1] +
               old[newindex:index] + old[index+1:])


def _make_list_create():
    return [ListCreate]


def _make_list_put(index, value):
    return [ListPut, index, value]


def _make_list_insert(index, value):
    return [ListInsert, index, value]


def _make_list_delete(index):
    return [ListDelete, index]


def _make_list_move(index, newindex):
    return [ListMove, index, newindex]
