Public Class Read_current
    Public Sub New(ByVal f As User_interface) 'constructor runs at start
        _frm = f 'need an instance of form to allow operation of Invoke
        Dim readthread As Threading.Thread = New Threading.Thread(AddressOf read)
        readthread.Start()  'see if have data to read using worker thread
    End Sub
    Private _frm As User_interface  'need instance of mainform to give invoke a handler
    Private Sub read()
        Dim sample As Integer = 0  'the received sample
        Try
            Dim com8 As IO.Ports.SerialPort = My.Computer.Ports.OpenSerialPort("com8", 9600)

            com8.ReadTimeout = 20000  'should respond in 10 seconds
            Try
                Upload_stored.display_data(Upload_stored.rx_number) = Upload_stored.software_dcoffset - CInt(com8.ReadLine) '* Upload_stored.software_scalefactor ' get rid of cr lf
                Upload_stored.time_saved = DateTime.Now  'remember the time last sample stored
                _frm.Invoke(New messdelegate(AddressOf showmessage)) 'register sample
            Catch ex As TimeoutException
                MsgBox("we have lost the circuit") 'board will respond within 60 secs
            End Try
            com8.Write("SSSSSS")  'arduino board command for next sample
            com8.Dispose()
        Catch ex As Exception
        End Try  'dispose of com8 and catch any exceptions
    End Sub
    Delegate Sub messdelegate() 'a delegate will run on the main window thread
    Private Sub showmessage() 'this runs on the main window thread because control not thread safe
        Upload_stored.rx_number = Upload_stored.rx_number + 1  'register sample
        If Upload_stored.rx_number = 1439 Then Upload_stored.rx_number = 0 'reset value***and save full sample
        If Display_files.show_current Then
            Dim d As New Display
            d.display_now = Upload_stored.display_data
            d.dt = Upload_stored.displaytime
            d.show_now()
            _frm.Label2.Text = "Current temperature = " & (Upload_stored.display_data(Upload_stored.rx_number - 1) * Upload_stored.software_nominal).ToString("n1")
        End If
        _frm.Timer1.Enabled = True 'OK lets check for another sample
    End Sub
End Class
