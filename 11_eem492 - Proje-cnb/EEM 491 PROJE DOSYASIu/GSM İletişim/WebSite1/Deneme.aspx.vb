Imports System.Data.OleDb
Imports System.Net

Partial Class _Default
    Inherits System.Web.UI.Page

    Protected Sub form1_Load(ByVal sender As Object, ByVal e As System.EventArgs) Handles form1.Load
        If Not Page.IsPostBack Then
            Dim id As String = Request.QueryString("id")
            Dim veri As String = Request.QueryString("veri")

            'Host Adı Alınır
            Dim parHostName As String = Dns.GetHostName()
            'Host Adına göre IP Listesi çekilir
            Dim ip As IPHostEntry = Dns.GetHostEntry(parHostName)
            'Ip Adresi bulunur ve bir değişkene atılır
            Dim ipAddress As String = ip.AddressList(0).ToString()
            'Sayfaya Ip adresi yazdırılır
            Response.Write("IP Adresiniz: " & ipAddress)
            Response.Write("<br>")
            Response.Write("Tarih Saat: " & DateTime.Now)


            
            If id <> "" And veri <> "" Then

                If kimlikno_check(id) = True Then
                    Response.Write(id)
                    Response.Write("<br>")
                    Response.Write(veri)

                    ' veriler istenen sartları saglıyorsa kayıt girilir

                    Dim sql As String = String.Empty
                    Dim conn As New System.Data.OleDb.OleDbConnection()
                    sql = "INSERT INTO detaylar(lokasyonid,problem,ip,kayitzamani) VALUES (@lokasyonid,@problem,@ip,@kayitzamani)"
                    conn.ConnectionString = "Provider=Microsoft.Jet.OLEDB.4.0; DATA Source=" & AppDomain.CurrentDomain.BaseDirectory & "App_Data\veriler.mdb;Persist Security Info=False"
                    Dim comm As New OleDbCommand(sql, conn)


                    comm.Parameters.Add("@lokasyonid", OleDbType.Char).Value = id
                    comm.Parameters.Add("@problem", OleDbType.Char).Value = veri
                    comm.Parameters.Add("@ip", OleDbType.Char).Value = ipAddress
                    comm.Parameters.Add("@kayitzamani", OleDbType.Date).Value = DateTime.Now


                    Try

                        If id.Contains("/") Or id.Contains("%") Or id.Contains("'") Or id.Contains("-") Or id.Contains("=") Or veri.Contains("/") Or veri.Contains("%") Or veri.Contains("'") Or veri.Contains("-") Or veri.Contains("=") Then
                            Exit Sub
                        End If


                        conn.Open()
                        comm.ExecuteNonQuery()
                        conn.Close()
                        Response.Write("<br>")
                        Response.Write("Kayıt Ok")

                    Catch ex As Exception
                        Response.Write("<br>")
                        Response.Write("Kayıt Nok")
                        Response.Write("<br>")
                        Response.Write(ex.Message)

                    End Try

                End If
            End If

        End If
    End Sub

    Shared Function kimlikno_check(ByVal tckimlikno As String) As Boolean
        If 11 <> tckimlikno.Length Then
            ' Girilen sayı 11 haneli olmak zorunda  
            Return False
        Else
            Dim toplam As Integer = 0

            For i As Integer = 0 To tckimlikno.Length - 2

                toplam += Convert.ToInt32(tckimlikno(i).ToString())
            Next

            If toplam.ToString()(1) = tckimlikno(10) Then
                Return True
            Else
                Return False
            End If
        End If
    End Function



    Protected Sub Button1_Click(ByVal sender As Object, ByVal e As System.EventArgs) Handles Button1.Click
        Response.Redirect("./listele.aspx")
    End Sub
End Class



