Imports System.IO
Public Class showstart
#Region "system variables"
    Private cd = My.Computer.FileSystem.CurrentDirectory & "\met_data_log"
    Private upload As String = ""
    Private startblock As Long = 0   'the first block in sd card to use
    Private currentblock As Long = 0  'the next available sd block in arduino
    Private totalblock As Long = 0   'total sectors to upload from sd card
    Private lastblock As Long = 0 'the last file in met_data_log
    Private com8 As IO.Ports.SerialPort  'the serial port to Arduino
    Private ram_samples(255) As Int32 'tempory store for the arduino ram samples
    Private ram_number As Integer = 0  'the number of ram samples
    Private button_clicked As Boolean = False 'signal to send sector number
#End Region
    Private Sub showstart_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        ProgressBar1.Visible = False
        Label1.Visible = False
        Label4.Visible = False
        Label5.Visible = False
        TextBox1.Visible = False
        Button1.Visible = False
        Label6.Visible = False
        Label4.Visible = False
        Button2.Visible = False  'start with everthing off
        If Not My.Computer.FileSystem.DirectoryExists(cd) Then
            My.Computer.FileSystem.CreateDirectory(cd)
        End If  'this could be the first run or the folder has been deleted
        If Not My.Computer.FileSystem.FileExists(cd & "\archive") Then
            Dim str As Stream = File.Open(cd & "\archive", FileMode.Create, FileAccess.Write)
            Dim bwr As New BinaryWriter(str)  'to send samples to stream
            Dim archiveblock As Int64 = 0
            bwr.Write(archiveblock) 'write a int64 =0 to file the first archived file
            str.Close()  'create the file
            bwr.Close()   'sends all samples to file
        End If
        While My.Computer.FileSystem.FileExists(cd & "\" & lastblock)
            lastblock += 1 'find the next block
        End While
        Label3.Text = "there are " & lastblock & " sectors of data in memory"
        Dim readthread = New Threading.Thread(AddressOf read)
        readthread.Start()  'thread runs to upload all data
    End Sub
    Private Sub read()
        Try
            System.Threading.Thread.CurrentThread.Priority = Threading.ThreadPriority.Highest 'dont need any interuptions during upload
            com8 = My.Computer.Ports.OpenSerialPort("com8", 9600)
            com8.ReadTimeout = 22000  'if any read takes longer end process
            com8.WriteTimeout = 1000  'must be less or fails
            Dim date_stamp = DateTime.Now 'time we add to the saved uploaded file
            Dim date_stamp_start As DateTime 'the time we started to upload
            Try
                Do  'check data from arduino until process is complete
                    upload = com8.ReadLine
                    upload = upload.Substring(0, upload.Length - 1) 'remove audinos last char
                    If upload = "sensors" Then  'arduino has been restarted
                        Dim rs1 = CInt(com8.ReadLine)  'remove numbers from stream
                        Dim rs2 = CInt(com8.ReadLine)
                        Dim rs3 = CInt(com8.ReadLine)  'and save for missed samples
                        Dim ramaddress = CInt(com8.ReadLine)
                        currentblock = CInt(com8.ReadLine)
                        'the lastblock must be =< current block or we have major problem
                        If lastblock > currentblock Then
                            MsgBox("we have a major problem." & vbNewLine & _
                                   "more sectors stored on computer than available on sd card" & vbNewLine _
                                   & "restart arduino and fix problem")
                            upload = "close form" 'must close form on forms thread
                            Invoke(New messdelegate(AddressOf showmessage))
                        End If  'to many stored sectors
                        totalblock = currentblock - lastblock
                        com8.WriteLine("u" & lastblock) 'we want to upload from this block
                        Do   'upload all ram
                            upload = com8.ReadLine
                            If upload.Substring(0, upload.Length - 1) = "r" Then
                                date_stamp = date_stamp.Subtract(TimeSpan.FromSeconds(ram_number * 10 / 3))
                                Exit Do  'we have all ram samples
                            End If
                            ram_samples(ram_number) = CInt(upload)  'arduino sends ram samples
                            ram_number += 1
                        Loop  'upload all ram
                        Dim str As Stream = File.Open(cd & "\ram", FileMode.Create, FileAccess.Write)
                        Dim bwr As New BinaryWriter(str)  'to send samples to stream
                        For i = 0 To ram_number - 1 'all ram samples
                            bwr.Write(ram_samples(i))  'send all the samples to disk
                        Next  'write ram file
                        bwr.Close()   'sends all samples to file
                        str.Close()
                        Dim sd_samples(255) As Int32  'tempory store for the arduino sd block samples
                        Dim j = lastblock
                        date_stamp = date_stamp.Subtract(TimeSpan.FromSeconds((currentblock - lastblock - 1) * 850))
                        'this gets the start time of first sector in the upload
                        date_stamp_start = DateTime.Now  'remember when started
                        If j = currentblock Then com8.ReadLine() 'get rid of "e" at end of upload
                        While Not j = currentblock  'upload all sectores
                            Dim sd_number = 0  'counter for upload sd block
                            Do   'upload sector
                                upload = com8.ReadLine
                                If upload.Substring(0, upload.Length - 1) = "e" Then
                                    Exit Do   'we have all the sd block samples
                                End If
                                sd_samples(sd_number) = CInt(upload)  'arduino sends ram samples
                                sd_number += 1  'get next
                                If sd_number = 256 Then Exit Do 'we have done one block
                            Loop  'sector upload
                            Dim save_sd = cd & "\" & j
                            j += 1
                            Dim st As Stream = File.Open(save_sd, FileMode.Create, FileAccess.Write)
                            Dim bw As New BinaryWriter(st)  'to send samples to stream
                            For i = 0 To 255  'all old samples
                                bw.Write(sd_samples(i))  'send all the samples
                            Next  'sector stored in file
                            bw.Write(date_stamp.ToString("F"))  'add date to file
                            date_stamp = date_stamp.Add(TimeSpan.FromSeconds(850))
                            bw.Close()   'sends all samples to file
                            st.Close()
                            lastblock = j 'we have uploaded one sector
                            upload = "uploading"
                            Invoke(New messdelegate(AddressOf showmessage))
                        End While  'have blocks to upload
                        Dim missed_samples = CInt((DateTime.Now - date_stamp_start).TotalSeconds / 10)
                        If missed_samples > 0 Then  'we have missed samples during upload so fill in
                            Dim strf As Stream = File.Open(cd & "\ram", FileMode.Append, FileAccess.Write)
                            Dim bwrf As New BinaryWriter(strf)  'to send sample to stream
                            For i = 0 To missed_samples  'use the lst sample in ram
                                bwrf.Write(rs1)  'send the sample to disk
                                bwrf.Write(rs2)  'send the sample to disk
                                bwrf.Write(rs3)  'send the sample to disk
                            Next
                            bwrf.Close()   'sends all samples to file
                            strf.Close()
                        End If  'have missed samples
                        upload = "close form" 'must close form on forms thread
                        Invoke(New messdelegate(AddressOf showmessage))
                    End If  'the upload was "sensors"
                    If upload = "ready" Then  'arduino has been restarted
                        currentblock = CInt(com8.ReadLine)  'this is next block to write to
                        If lastblock > currentblock Then
                            MsgBox("we have a major problem." & vbNewLine & _
                                   "more sectors stored on computer than available on sd card" & vbNewLine _
                                   & "restart arduino and fix problem")
                            upload = "close form" 'must close form on forms thread
                            Invoke(New messdelegate(AddressOf showmessage))
                        End If  'to many stored sectors
                        If button_clicked Then
                            com8.WriteLine(startblock)  'send the sector to store data
                            If Not startblock = currentblock Then 'user changes sd sector number
                                Dim str As Stream = File.Open(cd & "\ram", FileMode.Create, FileAccess.Write)
                                str.Close()  'must put empty ram file to show that we are connected
                                upload = "close form" 'must close form on forms thread
                                Invoke(New messdelegate(AddressOf showmessage))
                            End If 'start sector changed user must do arrangements
                            If currentblock - lastblock > 0 Then  'oldsectors to upload
                                Dim sd_stored(255) As Int32  'tempory store 
                                If My.Computer.FileSystem.FileExists(cd & "\" & lastblock - 1) Then
                                    Dim st As Stream = File.Open(cd & "\" & lastblock - 1, FileMode.Open, FileAccess.Read)
                                    Dim br As New BinaryReader(st)  'to get samples from stream
                                    For i = 0 To 255  'all old samples
                                        sd_stored(i) = br.ReadInt32()
                                    Next
                                    date_stamp = CDate(br.ReadString) 'get the time from the file
                                    date_stamp = date_stamp.Add(TimeSpan.FromSeconds(850 * (currentblock - lastblock))) 'from the beginning of the sectors
                                    br.Close()   'sends all samples to file
                                    st.Close()
                                    upload = "old_sector_upload"
                                    Invoke(New messdelegate(AddressOf showmessage))
                                End If  'get datetime from old sectors
                            Else  'no files to upload just close form
                                Dim str As Stream = File.Open(cd & "\ram", FileMode.Create, FileAccess.Write)
                                str.Close()  'must put empty ram file to show that we are connected
                                upload = "close form" 'must close form on forms thread
                                Invoke(New messdelegate(AddressOf showmessage))
                            End If 'old sectors to upload
                        End If 'the continue from sector has been selected
                        Invoke(New messdelegate(AddressOf showmessage)) 'use the upload value
                    End If  'upload was "ready"
                    If (upload = "readsderror") Or (upload = "writesderror") Then
                        Dim sderror = CInt(com8.ReadLine)  'this is the error value
                        Invoke(New messdelegate(AddressOf showmessage)) 'use the upload value
                    End If  'upload was error
                    If Not ((upload = "readsderror") Or (upload = "writesderror") _
                            Or (upload = "ready") Or (upload = "old_sector_upload")) Then
                        upload = "we cannot connect to Arduino"
                        Invoke(New messdelegate(AddressOf showmessage)) 'use the upload value
                    End If  'we are not getting correct arduino data
                Loop  'check data from arduino until process is complete
            Catch ex1 As Exception
                upload = "close form" 'must close form on forms thread
                Invoke(New messdelegate(AddressOf showmessage)) 'an exception during upload
            End Try
        Catch ex As Exception
            If ex.Message = "Access to the port 'com8' is denied." _
            Or ex.Message = "The port 'com8' does not exist." _
            Or ex.Message = "The operation has timed out." Then
                upload = "we cannot connect to Arduino"
                Invoke(New messdelegate(AddressOf showmessage))
            End If
        End Try  'dispose of com8 and catch any exceptions
    End Sub
    Delegate Sub messdelegate() 'a delegate will run on the main window thread
    Private Sub showmessage() 'this runs on the main window thread because control not thread safe        
        If upload = "close form" Then
            com8.Dispose()
            Me.Close()
        End If
        If upload = "we cannot connect to Arduino" Then
            Label5.Text = "no access to port or we cannot connect to Arduino"
            Label5.Visible = True
            Button2.Visible = True 'continue program button
        End If
        If upload = "ready" Then  'arduino has been restarted
            Label4.Visible = True
            Label5.Visible = True
            TextBox1.Visible = True
            Button1.Visible = True  'continue from this sector button
            Label4.Text = "last sector stored on card " & currentblock - 1
            TextBox1.Text = currentblock
            startblock = currentblock
            Label7.Text = "there are " & currentblock - lastblock & " old sectors to upload"
        End If
        If (upload = "readsderror") Or (upload = "writesderror") Then
            Label6.Visible = True
            Label6.Text = "sd card has failed"
            Button2.Visible = True  'continue program button
        End If
        If upload = "uploading" Then
            ProgressBar1.Visible = True
            ProgressBar1.Value = 100 + 100 * (lastblock - currentblock) / totalblock
            Label1.Visible = True
            Label1.Text = "uploading " & currentblock - lastblock & " sectors from Arduino"
            Label3.Text = "there are " & lastblock & " sectors of data in memory"
        End If
        If upload = "old_sector_upload" Then
            Label1.Visible = True
            Label1.Text = "waiting to upload old sectors"
        End If
    End Sub
    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click
        button_clicked = True  'continue from this sector button
    End Sub
    Private Sub Button2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button2.Click
        Try  'if com8 exists must dispose here 
            com8.Dispose()
        Catch ex As Exception
        End Try
        Me.Close()   'continue program button
    End Sub
    Private Sub TextBox1_TextChanged(ByVal sender As Object, ByVal e As System.EventArgs) Handles TextBox1.TextChanged
        Try
            startblock = TextBox1.Text
        Catch ex As Exception
            MsgBox("must be a valid sector number")
        End Try
    End Sub
End Class