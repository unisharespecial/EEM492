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
    public partial class WebForm4 : System.Web.UI.Page
    {
        SqlConnection con = new SqlConnection("Server=.\\SQLEXPRESS;Database=BITIRME_PROJE;Trusted_Connection=yes");  
        protected void Page_Load(object sender, EventArgs e)
        {

        }

    }
}