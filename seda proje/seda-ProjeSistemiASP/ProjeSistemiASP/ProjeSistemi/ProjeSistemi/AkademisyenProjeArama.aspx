<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="AkademisyenProjeArama.aspx.cs" Inherits="ProjeSistemi.WebForm7" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
    <style type="text/css">
        .auto-style1
        {
            width: 100%;
        }
        .auto-style2
        {
            width: 164px;
        }
    </style>
</head>
<body>
    <form id="form1" runat="server">
    <div>
    
        <table class="auto-style1">
            <tr>
                <td>
                    <asp:Label ID="lblProjeAdi" runat="server" Font-Bold="True" ForeColor="Red" 
                        Text="Proje Adı"></asp:Label>
                </td>
                <td>
                    <asp:Label ID="lblProjeSorumlu" runat="server" Font-Bold="True" ForeColor="Red" 
                        Text="Proje Sorumlusu"></asp:Label>
                </td>
                <td>
                    <asp:Label ID="lblProjeYil" runat="server" Font-Bold="True" ForeColor="Red" 
                        Text="Proje Yılı"></asp:Label>
                </td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
            </tr>
            <tr>
                <td rowspan="4">
                    <asp:ListBox ID="lbProjeAd" runat="server">
                        <asp:ListItem>Seçiniz..</asp:ListItem>
                    </asp:ListBox>
                </td>
                <td rowspan="4">
                    <asp:ListBox ID="lbProjeSorumlu" runat="server">
                        <asp:ListItem>Seçiniz..</asp:ListItem>
                    </asp:ListBox>
                </td>
                <td rowspan="4">
                    <asp:ListBox ID="lbProjeYil" runat="server">
                        <asp:ListItem>Seçiniz..</asp:ListItem>
                    </asp:ListBox>
                </td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
            </tr>
            <tr>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
            </tr>
            <tr>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
            </tr>
            <tr>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
            </tr>
            <tr>
                <td>
                    <asp:Label ID="lblProjeDonem" runat="server" Font-Bold="True" ForeColor="Red" 
                        Text="Proje Dönemi :"></asp:Label>
                    <asp:DropDownList ID="ddlProjeDonem" runat="server">
                        <asp:ListItem>Bahar</asp:ListItem>
                        <asp:ListItem>Güz</asp:ListItem>
                    </asp:DropDownList>
                </td>
                <td>
                    <asp:Button ID="btnAra" runat="server" Text="Ara" OnClick="btnAra_Click" />
                </td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
            </tr>
        </table>
    
    </div>

    <div>


        <asp:ListBox ID="lbAramaSonucu" runat="server" Enabled="False" Width="892px">
        </asp:ListBox>


    </div>

    <div style="height: 200px">

        <table class="auto-style1">
            <tr>
                <td class="auto-style2">
                    <asp:Label ID="lbpa" runat="server" Text="Proje Adı :"></asp:Label>
                </td>
                <td>
                    <asp:Label ID="Label8" runat="server" Text="Label"></asp:Label>
                </td>
                <td>&nbsp;</td>
            </tr>
            <tr>
                <td class="auto-style2">
                    <asp:Label ID="lbps" runat="server" Text="Proje Sorumlusu:"></asp:Label>
                </td>
                <td>
                    <asp:Label ID="Label9" runat="server" Text="Label"></asp:Label>
                </td>
                <td>&nbsp;</td>
            </tr>
            <tr>
                <td class="auto-style2">
                    <asp:Label ID="lbpp" runat="server" Text="Proje Posteri :"></asp:Label>
                </td>
                <td>
                    <asp:Label ID="Label10" runat="server" Text="Label"></asp:Label>
                </td>
                <td>&nbsp;</td>
            </tr>
            <tr>
                <td class="auto-style2">
                    <asp:Label ID="lblurl" runat="server" Text="URL :"></asp:Label>
                </td>
                <td>
                    <asp:Label ID="Label11" runat="server" Text="Label"></asp:Label>
                </td>
                <td>&nbsp;</td>
            </tr>
            <tr>
                <td class="auto-style2">
                    <asp:Label ID="lbpy" runat="server" Text="Proje Yılı :"></asp:Label>
                </td>
                <td>
                    <asp:Label ID="Label12" runat="server" Text="Label"></asp:Label>
                </td>
                <td>&nbsp;</td>
            </tr>
            <tr>
                <td class="auto-style2">
                    <asp:Label ID="lbpd" runat="server" Text="Proje Dönemi :"></asp:Label>
                </td>
                <td>
                    <asp:Label ID="Label13" runat="server" Text="Label"></asp:Label>
                </td>
                <td>&nbsp;</td>
            </tr>
            <tr>
                <td class="auto-style2">
                    <asp:Label ID="lbOgrenci" runat="server" Text="Öğrenci :"></asp:Label>
                </td>
                <td>
                    <asp:Label ID="Label14" runat="server" Text="Label"></asp:Label>
                </td>
                <td>&nbsp;</td>
            </tr>
        </table>

    </div>
    </form>
</body>
</html>
