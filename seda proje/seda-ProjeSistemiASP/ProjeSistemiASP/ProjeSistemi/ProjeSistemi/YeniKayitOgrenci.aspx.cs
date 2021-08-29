using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using System.Data.SqlClient;
using System.Net.Mail;
using System.Net;



namespace ProjeSistemi
{
    public partial class WebForm5 : System.Web.UI.Page
    {
        SqlConnection con = new SqlConnection("Server=.\\SQLEXPRESS;Database=BITIRME_PROJE;Trusted_Connection=yes");
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void btnEkle_Click(object sender, EventArgs e)
        {
            if (txtAd.Text =="" || txtBolum.Text =="" || txtNo.Text =="" || txtSoyad.Text =="" )
            {
                String msj;
                msj = "Boş bırakmayınız!";

                ClientScript.RegisterStartupScript(this.GetType(), "myalert", "alert('" + msj + "');", true);
            }
            else
            {
                Random rnd = new Random();
                int yenisifre = rnd.Next(100000,999999);
                SqlCommand KayitEkle = new SqlCommand("[AktifOgrenciKayıt]", con);
                if (yenisifre != 0)
                {
                    KayitEkle.CommandType = CommandType.StoredProcedure;
                    KayitEkle.Parameters.AddWithValue("@Ad", txtAd.Text.ToUpper());
                    KayitEkle.Parameters.AddWithValue("@Soyad", txtSoyad.Text.ToUpper());
                    KayitEkle.Parameters.AddWithValue("@OgrenciNo", Convert.ToInt32(txtNo.Text));
                    KayitEkle.Parameters.AddWithValue("@Sifre", yenisifre);
                    KayitEkle.Parameters.AddWithValue("@Bolum", txtBolum.Text);

                    con.Open();
                    KayitEkle.ExecuteNonQuery();
                    con.Close();
                    //MailMessageEventArgs
                    //MailMessageEventArgs msj = new MailMessageEventArgs("get"));
                    Response.Redirect("Giris.aspx");
                    MailMessage Mail = new MailMessage();
                    Mail.From = new MailAddress("20894643@mail.baskent.edu.tr");
                    Mail.To.Add(txtNo.Text + "@mail.baskent.edu.tr");
                    Mail.Subject = "Kullanıcı Şifresi";
                    Mail.Body = "Kullanıcı Şifreniz:" + yenisifre;
                    SmtpClient smpt = new SmtpClient();
                    smpt.Credentials = new NetworkCredential("20894643@mail.baskent.edu.tr", "pars1667");
                    smpt.Send(Mail);
                }
            }
        }
    }
}