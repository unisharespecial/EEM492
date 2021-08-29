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
    public partial class WebForm8 : System.Web.UI.Page
    {
        SqlConnection con = new SqlConnection("Server=.\\SQLEXPRESS;Database=BITIRME_PROJE;Trusted_Connection=yes");
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void btnOEkle_Click(object sender, EventArgs e)
        {
            if (txtOAd.Text == "" || txtOSoyad.Text == "" || txtOOgrenciNo.Text == "" || txtOBolum.Text == "")
            {
                String msj;
                msj = "Boş bırakmayınız!";

                ClientScript.RegisterStartupScript(this.GetType(), "myalert", "alert('" + msj + "');", true);
            }
            else
            {
                SqlCommand Ogrenci = new SqlCommand("[PasifOgrenciKayıt]", con);
                Ogrenci.Parameters.AddWithValue("@Ad", txtOAd.Text);
                Ogrenci.Parameters.AddWithValue("@Soyad", txtOSoyad.Text);
                Ogrenci.Parameters.AddWithValue("@OgrenciNo", txtOOgrenciNo.Text);
                Ogrenci.Parameters.AddWithValue("@Bolum", txtOBolum.Text);

                con.Open();
                Ogrenci.ExecuteNonQuery();
                con.Close();
    
            }
        }

        protected void btnAEkle_Click(object sender, EventArgs e)
        {
            if (txtAAd.Text == "" || txtASoyad.Text == "" || txtAEmail.Text == "" || txtAUnvan.Text == "")
            {
                String msj;
                msj = "Boş bırakmayınız!";

                ClientScript.RegisterStartupScript(this.GetType(), "myalert", "alert('" + msj + "');", true);
            }
            else
            {
                SqlCommand Akademisyen = new SqlCommand("[AktifAkademisyenKayıt]", con);
                Akademisyen.Parameters.AddWithValue("@Ad", txtAAd.Text);
                Akademisyen.Parameters.AddWithValue("@Soyad", txtASoyad.Text);
                Akademisyen.Parameters.AddWithValue("@Email", txtAEmail.Text);
                Akademisyen.Parameters.AddWithValue("@Unvan", txtAUnvan.Text);
                Random AkademisyenSifre = new Random();
                int AkademikSifre = AkademisyenSifre.Next(100000,999999);

                //MailMessageEventArgs
                //MailMessageEventArgs msj = new MailMessageEventArgs("get"));
                Response.Redirect("Giris.aspx");
                MailMessage Mail = new MailMessage();
                Mail.From = new MailAddress("sdksck@gmail.com");
                Mail.To.Add(txtAEmail.Text + "@baskent.edu.tr");
                Mail.Subject = "Kullanıcı Şifresi";
                Mail.Body = "Kullanıcı Şifreniz:" + AkademikSifre;
                SmtpClient smpt = new SmtpClient();
                smpt.Credentials = new NetworkCredential("20894643@mail.baskent.edu.tr", "pars1667");
                smpt.Send(Mail);
                con.Open();
                Akademisyen.ExecuteNonQuery();
                con.Close();
            }
        }

        protected void btnAPasif_Click(object sender, EventArgs e)
        {
            if (txtAEmail.Text == "")
            {
                String msj;
                msj = "E-mail'i boş bırakmayınız!";

                ClientScript.RegisterStartupScript(this.GetType(), "myalert", "alert('" + msj + "');", true);
            }
            else
            {
                SqlCommand AkademisyenPasif = new SqlCommand("[AktifAkademisyenSil]", con);
                AkademisyenPasif.Parameters.AddWithValue("@Email", txtAEmail.Text);
                con.Open();
                AkademisyenPasif.ExecuteNonQuery();
                con.Close();
            }
        }
    }
}