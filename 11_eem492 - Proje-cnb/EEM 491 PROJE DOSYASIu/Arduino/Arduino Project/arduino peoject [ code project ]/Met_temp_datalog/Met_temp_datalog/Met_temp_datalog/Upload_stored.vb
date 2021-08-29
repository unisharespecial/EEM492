Imports System.IO
Public Class Upload_stored
    Public Shared display_data(1439) As Int16  'only 0 to 1023 possible
    Public Shared rx_number As Integer  'the number of air pressure samples
    Public Shared software_dcoffset As Int16 = 1324  'the offset to the sampled data
    Public Shared software_scalefactor As Decimal = 1.0 'sampled data scaling
    Public Shared software_nominal As Decimal = 0.039 'the nominal value of the sample
    Public Shared time_saved As DateTime = DateTime.Now  'the time the last sample is saved
    Public Shared displaytime As String = ""  'the time used on the current display
    Public Sub load()
        Try
            Dim com8 As IO.Ports.SerialPort = My.Computer.Ports.OpenSerialPort("com8", 9600)
            com8.ReadTimeout = 20000 'board will respond within 10 seconds
            com8.Write("U")  'arduino board command for upload on restart
            Try
                Dim addr_pointer As Integer = CInt(com8.ReadLine) ' get rid of cr lf
                If addr_pointer > 0 Then  'we have saved samples
                    For i = 0 To (addr_pointer / 2 - 1) 'read all stored samples
                        com8.ReadTimeout = 100  'if we dont get a new byte in 100 ms
                        Try
                            display_data(i) = software_dcoffset - CInt(com8.ReadLine) * software_scalefactor ' get rid of cr lf
                            rx_number += 1  'updata the sample buffer pointer
                        Catch ex As TimeoutException
                            MsgBox("we have lost the circuit")
                        End Try
                    Next
                End If
                com8.Write("SSSSSS")  'arduino board command for upload single samples
                User_interface.Timer1.Enabled = True  'start the sampling proces
                com8.Dispose()
            Catch ex As TimeoutException
                MsgBox("we dont have a circuit")
            End Try
        Catch ex As Exception
            MsgBox("we cant open port to download") 'cant connect to port
        End Try
        Dim starttime As TimeSpan = TimeSpan.FromMinutes(rx_number) 'get sample start time
        Dim backtime = time_saved.Subtract(starttime) 'by subtracting minutes in samples
        displaytime = backtime.ToString("t") 'just need short time
        Dim d As New Display
        d.display_now = display_data
        d.dt = displaytime
        d.show_now()
        User_interface.Label2.Text = "Current temperature = " & (display_data(rx_number - 1) * software_nominal).ToString("n1")
    End Sub
    Public Sub save()
        Dim rt As String = time_saved.ToString.Replace("/", "-")
        rt = rt.Replace(":", ".")  'cant have / and : in file name
        Dim save_current As String = Display_files.user_folder & rt
        If Not My.Computer.FileSystem.DirectoryExists(Display_files.user_folder) Then
            My.Computer.FileSystem.CreateDirectory(Display_files.user_folder) 'folder has gone missing
        End If
        Dim st As Stream = File.Open(save_current, FileMode.Create, FileAccess.Write)
        Dim bw As New BinaryWriter(st)  'to send samples to stream
        For i = 0 To rx_number - 1  'all old samples
            bw.Write(display_data(i))  'send all the samples
        Next
        bw.Close()   'sends all samples to file
        st.Close()
    End Sub
End Class
