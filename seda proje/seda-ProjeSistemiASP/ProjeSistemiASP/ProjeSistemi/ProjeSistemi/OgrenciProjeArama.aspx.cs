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
    public partial class WebForm6 : System.Web.UI.Page
    {
        SqlConnection con = new SqlConnection("Server=.\\SQLEXPRESS;Database=BITIRME_PROJE;Trusted_Connection=yes");
        protected void Page_Load(object sender, EventArgs e)
        {
            SqlDataAdapter ProjeAd = new SqlDataAdapter("SELECT DISTINCT Yılı FROM Proje", con);
            SqlDataAdapter ProjeSorumlu = new SqlDataAdapter("SELECT DISTINCT Sorumlu FROM Proje", con);
            SqlDataAdapter ProjeYil = new SqlDataAdapter("SELECT DISTINCT Yılı FROM Proje", con);

            DataSet dsAd = new DataSet();
            ProjeAd.Fill(dsAd, "Peroje Adı");
            lbProjeAdi.DataSource = dsAd.Tables[0];
            lbProjeAdi.DataTextField = dsAd.Tables[0].Columns[0].ToString();
            lbProjeAdi.DataValueField = dsAd.Tables[0].Columns[0].ToString();
            DataBind();
            
            DataSet dsSorumlu = new DataSet();
            ProjeAd.Fill(dsSorumlu, "Peroje Sorumlusu");
            lbProjeSorumlusu.DataSource = dsSorumlu.Tables[0];
            lbProjeSorumlusu.DataTextField = dsSorumlu.Tables[0].Columns[0].ToString();
            lbProjeSorumlusu.DataValueField = dsSorumlu.Tables[0].Columns[0].ToString();
            DataBind();
            
            DataSet dsYil = new DataSet();
            ProjeAd.Fill(dsYil, "Peroje Yılı");
            lbProjeYili.DataSource = dsYil.Tables[0];
            lbProjeYili.DataTextField = dsYil.Tables[0].Columns[0].ToString();
            lbProjeYili.DataValueField = dsYil.Tables[0].Columns[0].ToString();
            DataBind();

        }

        protected void btnAra_Click(object sender, EventArgs e)
        {
            if (lbProjeAdi.SelectedIndex != 0)
            {
                if (lbProjeSorumlusu.SelectedIndex != 0)
                {
                    if (lbProjeYili.SelectedIndex != 0)
                    {

                        SqlDataAdapter ProjeGetir1 = new SqlDataAdapter("SELECT * FROM Proje WHERE ProjeAdı='" + lbProjeAdi.SelectedItem + "' AND Sorumlu='" + lbProjeSorumlusu.SelectedItem + "' AND Yılı=" + lbProjeYili.SelectedItem + " AND Donem='" + ddlProjeDonemi.SelectedItem + "'", con);
                        DataTable dt = new DataTable();
                        con.Open();
                        ProjeGetir1.Fill(dt);
                        con.Close();
                        lbAramaSonucu.DataSource = dt;
                        lbAramaSonucu.DataBind();

                    }
                    else
                    {
                        SqlDataAdapter ProjeGetir2 = new SqlDataAdapter("SELECT * FROM Proje WHERE ProjeAdı='" + lbProjeAdi.SelectedItem + "' AND Sorumlu='" + lbProjeSorumlusu.SelectedItem + "' AND Donem='" + ddlProjeDonemi.SelectedItem + "'", con);
                        DataTable dt = new DataTable();
                        con.Open();
                        ProjeGetir2.Fill(dt);
                        con.Close();
                        lbAramaSonucu.DataSource = dt;
                        lbAramaSonucu.DataBind();
                    }
                }
                else
                {
                    SqlDataAdapter ProjeGetir3 = new SqlDataAdapter("SELECT * FROM Proje WHERE ProjeAdı='" + lbProjeAdi.SelectedItem + "' AND Donem='" + ddlProjeDonemi.SelectedItem + "'", con);
                    DataTable dt = new DataTable();
                    con.Open();
                    ProjeGetir3.Fill(dt);
                    con.Close();
                    lbAramaSonucu.DataSource = dt;
                    lbAramaSonucu.DataBind();
                }
            }
            else if (lbProjeSorumlusu.SelectedIndex != 0)
            {
                if (lbProjeYili.SelectedIndex != 0)
                {

                    SqlDataAdapter ProjeGetir4 = new SqlDataAdapter("SELECT * FROM Proje WHERE Sorumlu='" + lbProjeSorumlusu.SelectedItem + "' AND Yılı=" + lbProjeYili.SelectedItem + " AND Donem='" + ddlProjeDonemi.SelectedItem + "'", con);
                    DataTable dt = new DataTable();
                    con.Open();
                    ProjeGetir4.Fill(dt);
                    con.Close();
                    lbAramaSonucu.DataSource = dt;
                    lbAramaSonucu.DataBind();
                }
                else
                {
                    SqlDataAdapter ProjeGetir5 = new SqlDataAdapter("SELECT * FROM Proje WHERE Sorumlu='" + lbProjeSorumlusu.SelectedItem + "' AND Donem='" + ddlProjeDonemi.SelectedItem + "'", con);
                    DataTable dt = new DataTable();
                    con.Open();
                    ProjeGetir5.Fill(dt);
                    con.Close();
                    lbAramaSonucu.DataSource = dt;
                    lbAramaSonucu.DataBind();
                }
            }
            else if (lbProjeYili.SelectedIndex != 0)
            {
                SqlDataAdapter ProjeGetir6 = new SqlDataAdapter("SELECT * FROM Proje WHERE Yılı=" + lbProjeYili.SelectedItem + " AND Donem='" + ddlProjeDonemi.SelectedItem + "'", con);
                DataTable dt = new DataTable();
                con.Open();
                ProjeGetir6.Fill(dt);
                con.Close();
                lbAramaSonucu.DataSource = dt;
                lbAramaSonucu.DataBind();
            }
            else
            {
                String mesaj;
                mesaj = "En az bir seçim yapınız!";

                ClientScript.RegisterStartupScript(this.GetType(), "myalert", "alert('" + mesaj + "');", true);

            }
        }
     
        }

        

        
    }
}