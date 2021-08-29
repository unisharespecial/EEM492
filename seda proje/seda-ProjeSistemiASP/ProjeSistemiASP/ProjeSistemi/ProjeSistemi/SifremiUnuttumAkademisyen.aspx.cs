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
    public partial class WebForm11 : System.Web.UI.Page
    {
        SqlConnection con = new SqlConnection("Server=.\\SQLEXPRESS;Database=BITIRME_PROJE;Trusted_Connection=yes");
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void btnGonder_Click(object sender, EventArgs e)
        {
            if ( txtEmail.Text == "")
            {
                String msj;
                msj = "Boş bırakmayınız!";

                ClientScript.RegisterStartupScript(this.GetType(), "myalert", "alert('" + msj + "');", true);
                txtEmail.Text = "";
                txtEmail.Focus();
            }
            else
            {
                SqlCommand Ogrenci = new SqlCommand("[AkademikSifreSorgu]", con);
                Ogrenci.Parameters.AddWithValue("@Email", txtEmail.Text);
                con.Open();
                string sifre = Ogrenci.ExecuteScalar().ToString();
                con.Close();

                //MailMessageEventArgs
                //MailMessageEventArgs msj = new MailMessageEventArgs("get"));
                Response.Redirect("Giris.aspx");
                MailMessage Mail = new MailMessage();
                Mail.From = new MailAddress("sdksck@gmail.com");
                Mail.To.Add(txtEmail.Text + "@baskent.edu.tr");
                Mail.Subject = "Kullanıcı Şifresi";
                Mail.Body = "Kullanıcı Şifreniz:" + sifre;
                SmtpClient smpt = new SmtpClient();
                smpt.Credentials = new NetworkCredential("20894643@mail.baskent.edu.tr", "pars1667");
                smpt.Send(Mail);
            }
        }
    }
}