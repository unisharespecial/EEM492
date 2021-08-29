Imports System.Data.OleDb

Partial Class listele
    Inherits System.Web.UI.Page

    Protected Sub Button1_Click(ByVal sender As Object, ByVal e As System.EventArgs) Handles Button1.Click
        Dim sql As String = String.Empty
        Dim conn As New System.Data.OleDb.OleDbConnection()
        sql = "delete from detaylar"
        conn.ConnectionString = "Provider=Microsoft.Jet.OLEDB.4.0; DATA Source=" & AppDomain.CurrentDomain.BaseDirectory & "App_Data\veriler.mdb;Persist Security Info=False"
        Dim comm As New OleDbCommand(sql, conn)





        Try
            conn.Open()
            comm.ExecuteNonQuery()
            conn.Close()
            Response.Write("Temizlik Ok")
        Catch ex As Exception
            Response.Write("Temizlik NOk" & ex.Message)
        End Try

    End Sub

    Protected Sub form1_Load(ByVal sender As Object, ByVal e As System.EventArgs) Handles form1.Load
        If Not Page.IsPostBack Then
            Dim yetkili As String = Request.QueryString("yetkili")
            If yetkili = "Admin" Then
                Button1.Visible = True
            Else
                Button1.Visible = False
            End If
        End If

    End Sub
End Class
