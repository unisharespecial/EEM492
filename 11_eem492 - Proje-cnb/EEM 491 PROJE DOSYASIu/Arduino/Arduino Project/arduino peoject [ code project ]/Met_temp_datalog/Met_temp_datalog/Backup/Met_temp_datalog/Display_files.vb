Imports System.IO
Public Class Display_files
    Public Shared user_folder As String = My.Computer.FileSystem.SpecialDirectories.MyMusic & "\met_samples\"
    Public Shared show_current As Boolean = True  'the current samples are displayed
    Private displayed_time As Integer = 0  'the number of the displayed file
    Public Sub read_files(ByVal way As Boolean)
        show_current = False  'while using files dont show current
        Try  'only can work if folder and files pesent
            Dim files() = My.Computer.FileSystem.GetFiles(user_folder).ToArray 'array of all file names
            Dim display_now = New [Int16](1439) {}
            If way Then   'we count up
                displayed_time += 1
                If displayed_time = files.Length Then
                    displayed_time = 0  'reset display
                End If
            Else  'we count down
                displayed_time -= 1
                If displayed_time < 0 Then
                    displayed_time = files.Length - 1   'reset display
                End If
            End If
            Dim st As Stream = File.Open(files(displayed_time), FileMode.Open, FileAccess.Read) 'get access to file
            Dim sample_n = My.Computer.FileSystem.GetFileInfo(files(displayed_time)).Length / 2 - 1
            Using br As New BinaryReader(st)
                For i = 0 To sample_n  'read the number of samples in tyhe stored file
                    display_now(i) = br.ReadInt16
                Next
            End Using
            Dim starttime As TimeSpan = TimeSpan.FromMinutes(sample_n) 'get sample start time
            Dim rt As String = files(displayed_time).Substring(files(displayed_time).Length - 27, 27).Replace("-", "/")
            rt = rt.Substring(rt.IndexOf("\") + 1)
            Dim sts As DateTime = rt.Replace(".", ":")  'fix up the stored time
            Dim dt = (sts.Subtract(starttime)).ToString("t") 'just need short time
            Dim yt = (sts.Subtract(starttime)).ToString("d MMM yyyy")
            Dim d As New Display
            d.display_now = display_now
            d.dt = dt
            d.show_now()
            User_interface.Label2.Text = "data sampled at:    " & dt & "  " & yt
        Catch ex As Exception  'no message just leave out
        End Try
    End Sub
    Public Sub current()
        Dim d As New Display
        d.display_now = Upload_stored.display_data
        d.dt = Upload_stored.displaytime
        d.show_now()
        User_interface.Label2.Text = "Current temperature = " & (Upload_stored.display_data(Upload_stored.rx_number - 1) * Upload_stored.software_nominal).ToString("n1")
        show_current = True 'we now show current samples
    End Sub
End Class
