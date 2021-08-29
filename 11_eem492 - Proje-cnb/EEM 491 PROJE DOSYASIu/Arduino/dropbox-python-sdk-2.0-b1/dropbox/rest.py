"""
A simple JSON REST request abstraction layer that is used by the
dropbox.client and dropbox.session modules. You shouldn't need to use this.
"""

import io
import pkg_resources
import socket
import ssl
import sys
import urllib

try:
    import json
except ImportError:
    import simplejson as json

try:
   import urllib3
except ImportError:
    raise ImportError('Dropbox python client requires urllib3.')


SDK_VERSION = "2.0-b1"

TRUSTED_CERT_FILE = pkg_resources.resource_filename(__name__, 'trusted-certs.crt')


class RESTResponse(io.IOBase):
    """
    Responses to requests can come in the form of RESTResponse. These are
    thin wrappers around the socket file descriptor.
    read() and close() are implemented.
    It is important to call close() to return the connection
    back to the connection pool to be reused. If a connection
    is not closed by the caller it may leak memory. The object makes a
    best-effort attempt upon destruction to call close(),
    but it's still best to explicitly call close()
    """

    def __init__(self, resp):
        # arg: A urllib3.HTTPResponse object
        self.urllib3_response = resp
        self.status = resp.status
        self.version = resp.version
        self.reason = resp.reason
        self.strict = resp.strict
        self.is_closed = False

    def __del__(self):
        # Attempt to close when ref-count goes to zero.
        self.close()

    # -----------------
    # Important methods
    # -----------------
    def read(self, amt=None):
        """
        Read data off the underlying socket

        Args:
            - ``amt``: Amount of data to read. Defaults to None, indicating to read
              everything

        Returns:
            - Data off the socket. If amt is not None, at most amt bytes are returned.
              An empty string when the socket has no data.

        Raises:
            - ValueError: If the RESTResponse has already been closed
        """
        if self.is_closed:
            raise ValueError('Response already closed')
        return self.urllib3_response.read(amt)

    BLOCKSIZE = 4 * 1024 * 1024 # 4MB at a time just because

    def close(self):
        """ Closes the underlying socket. """

        # Double closing is harmless
        if self.is_closed:
            return

        # Read any remaining crap off the socket before releasing the
        # connection. Buffer it just in case it's huge
        while self.read(RESTResponse.BLOCKSIZE):
            pass

        # Mark as closed and release the connection (exactly once)
        self.is_closed = True
        self.urllib3_response.release_conn()

    @property
    def closed(self):
        return self.is_closed


    # ---------------------------------
    # Backwards compat for HTTPResponse
    # ---------------------------------
    def getheaders(self):
        """ Returns a dictionary of the response headers """
        return self.urllib3_response.getheaders()

    def getheader(self, name, default=None):
        """ Returns a given response header """
        return self.urllib3_response.getheader(name, default)

    # Some compat functions showed up recently in urllib3
    try:
        urllib3.HTTPResponse.flush
        urllib3.HTTPResponse.fileno
        def fileno(self):
            return self.urllib3_response.fileno()
        def flush(self):
            return self.urllib3_response.flush()
    except AttributeError:
        pass

def create_connection(address):
    host, port = address
    err = None
    for res in socket.getaddrinfo(host, port, 0, socket.SOCK_STREAM):
        af, socktype, proto, canonname, sa = res
        sock = None
        try:
            sock = socket.socket(af, socktype, proto)
            sock.connect(sa)
            return sock

        except socket.error as e:
            err = e
            if sock is not None:
                sock.close()

    if err is not None:
        raise err
    else:
        raise socket.error("getaddrinfo returns an empty list")

def json_loadb(data):
    if sys.version_info >= (3,):
        data = data.decode('utf8')
    return json.loads(data)


class RESTClientObject(object):
    def __init__(self, max_reusable_connections=8, mock_urlopen=None):
        """
        Args:
            - ``max_reusable_connections``: max connections to keep alive in the pool
              ``mock_urlopen``: an optional alternate urlopen function for testing

        This class uses urllib3 to maintain a pool of connections. We attempt
        to grab an existing idle connection from the pool, otherwise we spin
        up a new connection. Once a connection is closed, it is reinserted
        into the pool (unless the pool is full)

        urllib3 also verifies certificates
        """
        self.mock_urlopen = mock_urlopen
        self.pool_manager = urllib3.PoolManager(
            num_pools = 4, # only a handful of hosts. api.dropbox.com, api-content.dropbox.com
            maxsize=max_reusable_connections,
            block=False,
            timeout=60.0, # long enough so datastores await doesn't get interrupted
            cert_reqs=ssl.CERT_REQUIRED,
            ca_certs=TRUSTED_CERT_FILE
        )

    def request(self, method, url, post_params=None, body=None, headers=None, raw_response=False):
        """ Performs a REST request. See RESTClient.request() for detailed description """

        post_params = post_params or {}
        headers = headers or {}
        headers['User-Agent'] = 'OfficialDropboxPythonSDK/' + SDK_VERSION

        if post_params:
            if body:
                raise ValueError("body parameter cannot be used with post_params parameter")
            body = urllib.urlencode(post_params)
            headers["Content-type"] = "application/x-www-form-urlencoded"

        # Handle StringIO instances, because urllib3 doesn't.
        if hasattr(body, 'getvalue'):
            body = str(body.getvalue())
            headers["Content-Length"] = len(body)

        try:
            # Grab a connection from the pool to make the request.
            # We return it to the pool when caller close() the response
            urlopen = self.mock_urlopen if self.mock_urlopen else self.pool_manager.urlopen
            r = urlopen(
                method=method,
                url=url,
                body=body,
                headers=headers,
                preload_content=False
            )
            r = RESTResponse(r) # wrap up the urllib3 response before proceeding
        except socket.error as e:
            raise RESTSocketError(url, e)
        except urllib3.exceptions.SSLError as e:
            raise RESTSocketError(url, "SSL certificate error: %s" % e)

        if r.status != 200:
            raise ErrorResponse(r, r.read())

        return self.process_response(r, raw_response)

    def process_response(self, r, raw_response):
        if raw_response:
            return r
        else:
            s = r.read()
            try:
                resp = json_loadb(s)
            except ValueError:
                raise ErrorResponse(r, s)
            r.close()

        return resp

    def GET(self, url, headers=None, raw_response=False):
        assert type(raw_response) == bool
        return self.request("GET", url, headers=headers, raw_response=raw_response)

    def POST(self, url, params=None, headers=None, raw_response=False):
        assert type(raw_response) == bool
        if params is None:
            params = {}

        return self.request("POST", url,
                            post_params=params, headers=headers, raw_response=raw_response)

    def PUT(self, url, body, headers=None, raw_response=False):
        assert type(raw_response) == bool
        return self.request("PUT", url, body=body, headers=headers, raw_response=raw_response)


class RESTClient(object):
    """
    A class with all static methods to perform JSON REST requests that is used internally
    by the Dropbox Client API. It provides just enough gear to make requests
    and get responses as JSON data (when applicable). All requests happen over SSL.
    """

    IMPL = RESTClientObject()

    @classmethod
    def request(cls, *n, **kw):
        """Perform a REST request and parse the response.

        Args:
            - ``method``: An HTTP method (e.g. 'GET' or 'POST').
            - ``url``: The URL to make a request to.
            - ``post_params``: A dictionary of parameters to put in the body of the request.
              This option may not be used if the body parameter is given.
            - ``body``: The body of the request. Typically, this value will be a string.
              It may also be a file-like object in Python 2.6 and above. The body
              parameter may not be used with the post_params parameter.
            - ``headers``: A dictionary of headers to send with the request.
            - ``raw_response``: Whether to return a RESTReponse object. [default False]
              It's best enabled for requests that return large amounts of data that you
              would want to .read() incrementally rather than loading into memory. Also
              use this for calls where you need to read metadata like status or headers,
              or if the body is not JSON.

        Returns:
            - The JSON-decoded data from the server, unless raw_response is
              specified, in which case an RESTResponse object is returned instead.

        Raises:
            - dropbox.rest.ErrorResponse: The returned HTTP status is not 200, or the body was
              not parsed from JSON successfully.
            - dropbox.rest.RESTSocketError: A socket.error was raised while contacting Dropbox.
        """
        return cls.IMPL.request(*n, **kw)

    @classmethod
    def GET(cls, *n, **kw):
        """Perform a GET request using RESTClient.request"""
        return cls.IMPL.GET(*n, **kw)

    @classmethod
    def POST(cls, *n, **kw):
        """Perform a POST request using RESTClient.request"""
        return cls.IMPL.POST(*n, **kw)

    @classmethod
    def PUT(cls, *n, **kw):
        """Perform a PUT request using RESTClient.request"""
        return cls.IMPL.PUT(*n, **kw)


class RESTSocketError(socket.error):
    """A light wrapper for ``socket.error`` that adds some more information."""

    def __init__(self, host, e):
        msg = "Error connecting to \"%s\": %s" % (host, str(e))
        socket.error.__init__(self, msg)


# Dummy class for docstrings, see doco.py.
class _ErrorResponse__doc__(Exception):
    """Exception raised when :class:`DropboxClient` exeriences a problem.

    For example, this is raised when the server returns an unexpected
    non-200 HTTP response.
    """

    _status__doc__ = "HTTP response status (an int)."
    _reason__doc__ = "HTTP response reason (a string)."
    _body__doc__ = "HTTP response body (string or JSON dict)."
    _headers__doc__ = "HTTP response headers (a list of (header, value) tuples)."
    _error_msg__doc__ = "Error message for developer (optional)."
    _user_error_msg__doc__ = "Error message for end user (optional)."


class ErrorResponse(Exception):
    """
    Raised by dropbox.rest.RESTClient.request for requests that:

      - Return a non-200 HTTP response, or
      - Have a non-JSON response body, or
      - Have a malformed/missing header in the response.

    Most errors that Dropbox returns will have an error field that is unpacked and
    placed on the ErrorResponse exception. In some situations, a user_error field
    will also come back. Messages under user_error are worth showing to an end-user
    of your app, while other errors are likely only useful for you as the developer.
    """

    def __init__(self, http_resp, body):
        """
        Args
            ``http_resp``: The RESTResponse which errored
            ``body``: Body of the RESTResponse.
                      The reason we can't simply call http_resp.read() to
                      get the body, is that read() is not idempotent.
                      Since it can't be called more than once,
                      we have to pass the string body in separately
        """
        self.status = http_resp.status
        self.reason = http_resp.reason
        self.body = body
        self.headers = http_resp.getheaders()
        http_resp.close() # won't need this connection anymore

        try:
            self.body = json_loadb(self.body)
            self.error_msg = self.body.get('error')
            self.user_error_msg = self.body.get('user_error')
        except ValueError:
            self.error_msg = None
            self.user_error_msg = None

    def __str__(self):
        if self.user_error_msg and self.user_error_msg != self.error_msg:
            # one is translated and the other is English
            msg = "%s (%s)" % (self.user_error_msg, self.error_msg)
        elif self.error_msg:
            msg = self.error_msg
        elif not self.body:
            msg = self.reason
        else:
            msg = "Error parsing response body or headers: " +\
                  "Body - %s Headers - %s" % (self.body, self.headers)

        return "[%d] %s" % (self.status, repr(msg))

