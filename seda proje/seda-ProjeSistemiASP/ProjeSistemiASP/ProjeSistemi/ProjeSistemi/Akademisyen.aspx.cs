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
    public partial class WebForm3 : System.Web.UI.Page
    {
        SqlConnection con = new SqlConnection("Server=.\\SQLEXPRESS;Database=BITIRME_PROJE;Trusted_Connection=yes");  
        protected void Page_Load(object sender, EventArgs e)
        {
            int yıl = DateTime.Now.Year;
            /*SqlCommand DonemProjeleri = new SqlCommand("[YilaGoreProje]", con);
            DonemProjeleri.Parameters.AddWithValue("@Year", yıl);
            con.Open();
            DonemProjeleri.ExecuteNonQuery();
            con.Close();
            DataSet ds = new DataSet();
            DonemProjeleri.Fill(ds, "Peroje Yılı");
            ListBox1.DataSource = ds.Tables[0];
            ListBox1.DataTextField = ds.Tables[0].Columns[0].ToString();
            ListBox1.DataValueField = ds.Tables[0].Columns[0].ToString();
            DataBind();
            */
            SqlDataAdapter DonemProjeleri = new SqlDataAdapter("SELECT ProjeAdı FROM Proje WHERE Yılı="+yıl, con);
            DataTable dt = new DataTable();
            con.Open();
            DonemProjeleri.Fill(dt);
            con.Close();
            lbHerYil.DataSource = dt;
            lbHerYil.DataBind();

        }

        protected void lbProjeAra_Click(object sender, EventArgs e)
        {
            Response.Redirect("AkademisyenProjeArama.aspx");
        }

        protected void lnklblCikis_Click(object sender, EventArgs e)
        {
            Response.Redirect("Giris.aspx");
        }


    }
}