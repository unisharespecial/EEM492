Public Class User_interface

    Private display As New Display_files

    Private Sub User_interface_FormClosing(ByVal sender As Object, ByVal e As System.Windows.Forms.FormClosingEventArgs) Handles Me.FormClosing
        Dim d As New Upload_stored
        d.save()
    End Sub

    Private Sub User_interface_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        Dim d As New Upload_stored
        d.load()
    End Sub

    Private Sub Timer1_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer1.Tick
        Timer1.Enabled = False 'disable until this sample is read
        Dim c As New Read_current(Me) 'must pass form to constructor
    End Sub

    Private Sub Previous_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Previous.Click
        display.read_files(False)
    End Sub

    Private Sub Dispnext_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Dispnext.Click
        display.read_files(True)
    End Sub

    Private Sub Current_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Current.Click
        display.current()
    End Sub

End Class
