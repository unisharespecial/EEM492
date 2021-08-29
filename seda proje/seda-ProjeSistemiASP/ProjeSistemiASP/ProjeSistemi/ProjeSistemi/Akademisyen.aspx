<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Akademisyen.aspx.cs" Inherits="ProjeSistemi.WebForm3" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
    <style type="text/css">
        .auto-style1 {
            width: 100%;
            height: 333px;
        }
        #form1 {
            height: 339px;
        }
        .auto-style2
        {
            width: 353px;
        }
        .auto-style3
        {
            width: 144px;
        }
        .auto-style5
        {}
        .auto-style8
        {
            width: 15px;
        }
    </style>
</head>
<body>
    <form id="form1" runat="server">
    <div style="height: 60px">
    
        <table class="auto-style1">
            <tr>
                <td class="auto-style3">&nbsp;</td>
                <td class="auto-style8">&nbsp;</td>
                <td>&nbsp;</td>
                <td class="auto-style2">&nbsp;</td>
                <td>
                    <asp:LinkButton ID="lnklblCikis" runat="server" OnClick="lnklblCikis_Click">Çıkış</asp:LinkButton>
                </td>
            </tr>
            <tr>
                <td class="auto-style3">
                    <asp:LinkButton ID="lbProjeAra" runat="server" OnClick="lbProjeAra_Click">Proje Arama</asp:LinkButton>
                </td>
                <td colspan="3">
                    <asp:Label ID="lblMerhaba" runat="server" Text="Merhaba"></asp:Label>
                    ,&nbsp;&nbsp;&nbsp;&nbsp;
                    </td>
                <td>&nbsp;</td>
            </tr>
            <tr>
                <td class="auto-style3"></td>
                <td colspan="3">
                    <asp:Label ID="lblHerYil" runat="server" Text="Bu Yıl Yapılan Çalışmalar:"></asp:Label>
                </td>
                <td class="auto-style5">
                    &nbsp;</td>
            </tr>
            <tr>
                <td class="auto-style3">&nbsp;</td>
                <td class="auto-style8">
                    <asp:ListBox ID="lbHerYil" runat="server" Width="327px"></asp:ListBox>
                </td>
                <td>&nbsp;</td>
                <td class="auto-style2">&nbsp;</td>
                <td>&nbsp;</td>
            </tr>
        </table>
    
    </div>
    </form>
</body>
</html>
