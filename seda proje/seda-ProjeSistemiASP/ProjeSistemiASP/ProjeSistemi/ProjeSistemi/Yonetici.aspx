<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Yonetici.aspx.cs" Inherits="ProjeSistemi.WebForm4" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
    <style type="text/css">
        .auto-style1 {
            width: 100%;
            height: 420px;
        }
        .auto-style2 {
            width: 136px;
        }
        .auto-style5 {
            width: 136px;
            height: 6px;
        }
        .auto-style6 {
            height: 6px;
        }
        .auto-style7 {
            width: 136px;
            height: 27px;
        }
        .auto-style8 {
            height: 27px;
        }
    </style>
</head>
<body>
    <form id="form1" runat="server">
    <div>
    
        <table class="auto-style1">
            <tr>
                <td class="auto-style7"></td>
                <td class="auto-style8"></td>
                <td class="auto-style8"></td>
                <td class="auto-style8"></td>
                <td class="auto-style8">
                    <asp:LinkButton ID="lnklblCikis" runat="server">Çıkış</asp:LinkButton>
                </td>
            </tr>
            <tr>
                <td class="auto-style5"></td>
                <td class="auto-style6"></td>
                <td class="auto-style6"></td>
                <td class="auto-style6"></td>
                <td class="auto-style6"></td>
            </tr>
            <tr>
                <td class="auto-style2">
                    <asp:LinkButton ID="lbYeniEkleCikart" runat="server">Yeni Kişi Ekle/Çıkar</asp:LinkButton>
                </td>
                <td>&nbsp;</td>
                <td colspan="3">
                    <asp:Label ID="lblMerhaba" runat="server" Text="Merhaba"></asp:Label>
                </td>
            </tr>
            <tr>
                <td class="auto-style2">
                    <asp:Label ID="lblKişiler" runat="server" Text="Kişiler"></asp:Label>
                </td>
                <td>&nbsp;</td>
                <td colspan="3" rowspan="2">&nbsp;</td>
            </tr>
            <tr>
                <td class="auto-style2">&nbsp;</td>
                <td>&nbsp;</td>
            </tr>
        </table>
    
    </div>
    </form>
</body>
</html>
