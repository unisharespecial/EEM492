<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="YeniKayitOgrenci.aspx.cs" Inherits="ProjeSistemi.WebForm5" %>

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
            width: 112px;
        }
        .auto-style3
        {
            width: 112px;
            height: 30px;
        }
        .auto-style4
        {
            height: 30px;
        }
    </style>
</head>
<body>
    <form id="form1" runat="server">
    <div>
    
        <table class="auto-style1">
            <tr>
                <td class="auto-style2">
                    <asp:Label ID="lblYenikayit" runat="server" Font-Bold="True" ForeColor="Red" 
                        Text="Yeni Kayit"></asp:Label>
                </td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
            </tr>
            <tr>
                <td class="auto-style2">
                    <asp:Label ID="lblAd" runat="server" Text="Ad :"></asp:Label>
                </td>
                <td>
                    <asp:TextBox ID="txtAd" runat="server"></asp:TextBox>
                </td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
            </tr>
            <tr>
                <td class="auto-style2">
                    <asp:Label ID="lblSoyad" runat="server" Text="Soyadı :"></asp:Label>
                </td>
                <td>
                    <asp:TextBox ID="txtSoyad" runat="server"></asp:TextBox>
                </td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
            </tr>
            <tr>
                <td class="auto-style2">
                    <asp:Label ID="Label4" runat="server" Text="Öğrenci No :"></asp:Label>
                </td>
                <td>
                    <asp:TextBox ID="txtNo" runat="server"></asp:TextBox>
                </td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
            </tr>
            <tr>
                <td class="auto-style2">
                    <asp:Label ID="lblBolum" runat="server" Text="Bölüm :"></asp:Label>
                </td>
                <td>
                    <asp:TextBox ID="txtBolum" runat="server"></asp:TextBox>
                </td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
            </tr>
            <tr>
                <td class="auto-style3">
                    <asp:Button ID="btnEkle" runat="server" OnClick="btnEkle_Click" 
                        Text="Kayıt ol" />
                </td>
                <td class="auto-style4"></td>
                <td class="auto-style4"></td>
                <td class="auto-style4"></td>
            </tr>
        </table>
    
    </div>
    </form>
</body>
</html>
