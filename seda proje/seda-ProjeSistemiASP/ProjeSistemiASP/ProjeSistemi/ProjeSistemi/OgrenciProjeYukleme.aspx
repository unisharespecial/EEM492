<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="OgrenciProjeYukleme.aspx.cs" Inherits="ProjeSistemi.WebForm9" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
    <style type="text/css">
        .auto-style1
        {
            width: 100%;
        }
        </style>
</head>
<body>
    <form id="form1" runat="server">
        <table class="auto-style1">
            <tr>
                <td>
                    <asp:Label ID="lblProjeBilgisi" runat="server" 
                        Text="Proje Bilgilerini Giriniz:" Font-Bold="True" ForeColor="Red"></asp:Label>
                </td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
            </tr>
            <tr>
                <td>
                    <asp:Label ID="lblProjeAd" runat="server" Text="Proje Adı:"></asp:Label>
                </td>
                <td>
                    <asp:TextBox ID="tbProjeAdı" runat="server"></asp:TextBox>
                </td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
            </tr>
            <tr>
                <td style="margin-left: 40px">
                    <asp:Label ID="lblProjeSorumlu" runat="server" Text="Proje Sorumlusu:"></asp:Label>
                </td>
                <td>
                    <asp:TextBox ID="tbProjeSorumlu" runat="server"></asp:TextBox>
                </td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
            </tr>
            <tr>
                <td>
                    <asp:Label ID="lblProjePoster" runat="server" Text="Proje Posteri URL:"></asp:Label>
                </td>
                <td>
                    <asp:TextBox ID="tbAfisURL" runat="server"></asp:TextBox>
                </td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
            </tr>
            <tr>
                <td>
                    <asp:Label ID="lblProjeURL" runat="server" Text="Proje URL:"></asp:Label>
                </td>
                <td>
                    <asp:TextBox ID="tbURL" runat="server"></asp:TextBox>
                </td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
            </tr>
            <tr>
                <td>
                    <asp:Label ID="lblProjeYıl" runat="server" Text="Proje Yılı:"></asp:Label>
                </td>
                <td>
                    <asp:TextBox ID="tbProjeYıl" runat="server"></asp:TextBox>
                </td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
            </tr>
            <tr>
                <td>
                    <asp:Label ID="lblProjeDonem" runat="server" Text="Proje Dönemi:"></asp:Label>
                </td>
                <td>
                    <asp:DropDownList ID="ddDonem" runat="server">
                        <asp:ListItem>Seçiniz...</asp:ListItem>
                        <asp:ListItem Enabled="False" Selected="True">Güz</asp:ListItem>
                        <asp:ListItem>Bahar</asp:ListItem>
                    </asp:DropDownList>
                </td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
            </tr>
            <tr>
                <td>
                    <asp:Button ID="btnProjeEkle" runat="server" Text="Proje Ekle" />
                </td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
            </tr>
            </table>
    <div>
    
    </div>
    </form>
</body>
</html>
