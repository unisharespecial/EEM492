Imports System.IO
Public Class Dump_files
    Private cd = My.Computer.FileSystem.CurrentDirectory & "\met_data_log"
    Private lastblock As Long = 0  'last block stored in folder
    Private startblock As Long = 0  'block to be displayed
    Private archiveblock As Int64 = 0  'block to be archived
    Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        If My.Computer.FileSystem.FileExists(cd & "\ram") Then
            Label1.Text = "ramfile exists"
            Button1.Visible = True
        Else
            Label1.Text = "ramfile does not exist"
            Button1.Visible = False
        End If
        While My.Computer.FileSystem.FileExists(cd & "\" & lastblock)
            lastblock += 1 'find the next block
        End While
        If lastblock > 0 Then
            Label2.Text = "sectors 0 to " & lastblock - 1 & " stored"
            Button2.Visible = True
            TextBox1.Visible = True
        End If
        If My.Computer.FileSystem.FileExists(cd & "\archive") Then
            Dim st As Stream = File.Open(cd & "\archive", FileMode.Open, FileAccess.Read)
            Dim br As New BinaryReader(st)  'to get samples from stream
            Try
                Do
                    archived.Text = archived.Text & br.ReadInt64() & vbNewLine
                Loop
            Catch ex As Exception  'exception of none left
            Finally
                br.Close()   'must close
                st.Close()
            End Try  'exit try when all read
        End If
    End Sub
    Private Sub TextBox1_TextChanged(ByVal sender As Object, ByVal e As System.EventArgs) Handles TextBox1.TextChanged
        Try
            startblock = TextBox1.Text
        Catch ex As Exception
            MsgBox("must be a valid sector number")
        End Try
    End Sub
    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click
        Dim working_buffer(25500) As Int32  'fill this buffer to use in display
        Label3.Text = "" 'clear display
        Try
            If My.Computer.FileSystem.FileExists(cd & "\ram") Then
                Dim st As Stream = File.Open(cd & "\ram", FileMode.Open, FileAccess.Read)
                Dim br As New BinaryReader(st)  'to get samples from stream
                Dim ram_number = 0  'the number of ram samples
                Try
                    For i = 0 To 25500  'Fill display buffer
                        ram_number = i
                        working_buffer(i) = br.ReadInt32() 'exception of none left
                    Next
                Catch ex As Exception
                Finally
                    br.Close()   'must close
                    st.Close()
                End Try  'exit try when all read
                For i = 0 To 1500
                    Dim j As Integer
                    Label3.Text &= (i * 16).ToString("d3") & "    "
                    For j = 0 To 15
                        If (i * 16 + j) >= ram_number Then Exit For
                        Label3.Text &= "  " & working_buffer(i * 16 + j).ToString("d4")
                    Next
                    If (i * 16 + j) >= ram_number Then Exit For
                    Label3.Text &= vbNewLine
                Next
            End If
        Catch ex As Exception
        End Try  'need if read thread has file        
    End Sub

    Private Sub Button2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button2.Click
        Dim sd_stored(255) As Int32  'tempory store 
        Dim display_start_time As DateTime
        Label3.Text = "" 'clear display
        If My.Computer.FileSystem.FileExists(cd & "\" & startblock) Then
            Dim st As Stream = File.Open(cd & "\" & startblock, FileMode.Open, FileAccess.Read)
            Dim br As New BinaryReader(st)  'to get samples from stream
            For i = 0 To 255  'all old samples
                sd_stored(i) = br.ReadInt32()
            Next
            display_start_time = CDate(br.ReadString) 'get the time from the file
            br.Close()   'sends all samples to file
            st.Close()
            For i = 0 To 15
                Label3.Text &= (i * 16).ToString("d3") & "    "
                For j = 0 To 15
                    Label3.Text &= "  " & sd_stored(i * 16 + j).ToString("d4")
                Next
                Label3.Text &= vbNewLine
            Next
            Label3.Text &= vbNewLine & vbNewLine _
            & "The datetime for this file is       " _
            & display_start_time.ToString("h:mm tt..d MMM yy")
        Else
            Label3.Text = "file does not exist"
        End If
    End Sub

    Private Sub Button3_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button3.Click       
        Try
            If Not TextBox1.Text = "" Then
                TextBox1.Text = CLng(TextBox1.Text) + 1
            End If
        Catch ex As Exception
            MsgBox("must be a valid sector number")
        End Try
    End Sub

    Private Sub Button4_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button4.Click      
        Try
            If TextBox1.Text >= 1 Then
                TextBox1.Text = CLng(TextBox1.Text) - 1
            End If
        Catch ex As Exception
            MsgBox("must be a valid sector number")
        End Try
    End Sub
    Private Sub TextBox2_TextChanged(ByVal sender As Object, ByVal e As System.EventArgs) Handles TextBox2.TextChanged
        Try
            archiveblock = TextBox2.Text
        Catch ex As Exception
            MsgBox("must be a valid sector number")
        End Try
    End Sub
    Private Sub Button5_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button5.Click
        If My.Computer.FileSystem.FileExists(cd & "\archive") Then
            Dim words() As String = archived.Text.Split(vbNewLine)
            Dim x = CLng((words.Length - 1))
            If archiveblock > CLng(words(words.Length - 2)) + 100 Then
                Dim str As Stream = File.Open(cd & "\archive", FileMode.Append, FileAccess.Write)
                Dim bwr As New BinaryWriter(str)  'to send samples to stream
                bwr.Write(archiveblock)  'send all the samples to disk
                bwr.Close()   'sends all samples to file
                str.Close()
            Else
                MsgBox("The archived block must be at least" & vbNewLine & _
                       "one day -that is 100 bigger than last")
            End If
            Dim st As Stream = File.Open(cd & "\archive", FileMode.Open, FileAccess.Read)
            Dim br As New BinaryReader(st)  'to get samples
            archived.Text = ""
            Try
                Do
                    archived.Text = archived.Text & (br.ReadInt64()) & vbNewLine
                Loop
            Catch ex As Exception  'exception of none left
            Finally
                br.Close()   'must close
                st.Close()
            End Try  'exit try when all read

        End If
    End Sub
    Private Sub clear_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles clear.Click
        Dim str As Stream = File.Open(cd & "\archive", FileMode.Create, FileAccess.Write)
        Dim bwr As New BinaryWriter(str)  'to send samples to stream
        Dim archiveblock As Int64 = 0
        bwr.Write(archiveblock) 'write a int64 =0 to file the first archived file
        str.Close()  'create the file
        bwr.Close()   'sends all samples to file
        Dim st As Stream = File.Open(cd & "\archive", FileMode.Open, FileAccess.Read)
        Dim br As New BinaryReader(st)  'to get samples
        archived.Text = ""
        Try
            Do
                archived.Text = archived.Text & (br.ReadInt64()) & vbNewLine
            Loop
        Catch ex As Exception  'exception of none left
        Finally
            br.Close()   'must close
            st.Close()
        End Try  'exit try when all read
    End Sub
End Class
