using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using System.Data.SqlClient;


namespace ProjeSistemi
{

    public partial class WebForm1 : System.Web.UI.Page
    {
        SqlConnection con = new SqlConnection("Server=.\\SQLEXPRESS;Database=BITIRME_PROJE;Trusted_Connection=yes");
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void btnAGiris_Click(object sender, EventArgs e)
        {
            if (txtAEmail.Text == "" || txtASifre.Text == "")
            {
                String msj;
                msj = "Boş bırakmayınız!";

                ClientScript.RegisterStartupScript(this.GetType(), "myalert", "alert('" + msj + "');", true);
            }
            else {
                    SqlCommand Akademisyen = new SqlCommand("[AkademikSifreSorgu]", con);
                    Akademisyen.Parameters.AddWithValue("@Email", txtAEmail.Text);
                    con.Open();
                    string sifre = Akademisyen.ExecuteScalar().ToString();
                    con.Close();
                    if (sifre == txtASifre.Text)
                    {
                        Response.Redirect("Akademisyen.aspx");
                    }
                    else {
                        String mesaj;
                        mesaj = "Şifre veya email yanlış !";

                        ClientScript.RegisterStartupScript(this.GetType(), "myalert", "alert('" + mesaj + "');", true);

                        txtAEmail.Text = "";
                        txtASifre.Text = "";
                        txtAEmail.Focus();
                     }
            }
        }

        protected void btnOGiris_Click(object sender, EventArgs e)
        {
                if (txtOEmail.Text == "" || txtOSifre.Text == "")
            {
                String msj;
                msj = "Boş bırakmayınız!";

                ClientScript.RegisterStartupScript(this.GetType(), "myalert", "alert('" + msj + "');", true);
            }
            else {
                SqlCommand Ogrenci = new SqlCommand("[OgrenciSifreSorgu]", con);
                Ogrenci.Parameters.AddWithValue("@Email", txtOEmail.Text);
                con.Open();
                string sifre = Ogrenci.ExecuteScalar().ToString();
                con.Close();
                if (sifre == txtOSifre.Text)
                {
                    Response.Redirect("OgrenciEkran.aspx");
                }
                else
                {
                    String mesaj;
                    mesaj = "Şifre veya email yanlış !";

                    ClientScript.RegisterStartupScript(this.GetType(), "myalert", "alert('" + mesaj + "');", true);

                    txtOEmail.Text = "";
                    txtOSifre.Text = "";
                    txtOEmail.Focus();
                }
            }
        }

        protected void btnYGiris_Click(object sender, EventArgs e)
        {
                if (txtYSifre.Text=="")
            {
                String msj;
                msj = "Boş bırakmayınız!";

                ClientScript.RegisterStartupScript(this.GetType(), "myalert", "alert('" + msj + "');", true);
            }
            else {

                if (txtYSifre.Text == "12345")
                {
                    Response.Redirect("YöneticiKayitYonetim.aspx");
                }
                else
                {
                    String mesaj;
                    mesaj = "Şifre yanlış !";

                    ClientScript.RegisterStartupScript(this.GetType(), "myalert", "alert('" + mesaj + "');", true);

                    txtYSifre.Text = "";
                    txtYSifre.Focus();
                }
            }
        }

        protected void LinkButton1_Click(object sender, EventArgs e)
        {
            Response.Redirect("SifremiUnuttumAkademisyen.aspx");
        }

        protected void LinkButton2_Click(object sender, EventArgs e)
        {
            Response.Redirect("SifremiUnuttum.aspx");
        }

        protected void LinkButton3_Click(object sender, EventArgs e)
        {
            Response.Redirect("YeniKayitOgrenci.aspx");
        }


    
        }
    }
