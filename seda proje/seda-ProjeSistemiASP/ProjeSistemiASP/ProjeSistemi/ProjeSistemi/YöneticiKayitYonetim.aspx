<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="YöneticiKayitYonetim.aspx.cs" Inherits="ProjeSistemi.WebForm8" %>

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
            width: 133px;
        }
        .auto-style3
        {
            width: 184px;
        }
    </style>
</head>
<body>
    <form id="form1" runat="server">
    <div>
    
        <table class="auto-style1">
            <tr>
                <td class="auto-style2">
                    <asp:Label ID="Label1" runat="server" Font-Bold="True" ForeColor="Red" 
                        Text="Öğrenci Yönetim"></asp:Label>
                </td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
                <td>
                    <asp:Label ID="Label2" runat="server" Font-Bold="True" ForeColor="Red" 
                        Text="Akademisyen Yönetim"></asp:Label>
                </td>
                <td class="auto-style3">&nbsp;</td>
                <td>&nbsp;</td>
            </tr>
            <tr>
                <td class="auto-style2">
                    <asp:Label ID="lblAd" runat="server" Text="Ad:"></asp:Label>
                </td>
                <td>
                    <asp:TextBox ID="txtOAd" runat="server"></asp:TextBox>
                </td>
                <td>&nbsp;</td>
                <td>
                    <asp:Label ID="lblAAd" runat="server" Text="Ad:"></asp:Label>
                </td>
                <td class="auto-style3">
                    <asp:TextBox ID="txtAAd" runat="server"></asp:TextBox>
                </td>
                <td>&nbsp;</td>
            </tr>
            <tr>
                <td class="auto-style2">
                    <asp:Label ID="lblSoyad" runat="server" Text="Soyad :"></asp:Label>
                </td>
                <td>
                    <asp:TextBox ID="txtOSoyad" runat="server"></asp:TextBox>
                </td>
                <td>&nbsp;</td>
                <td>
                    <asp:Label ID="lblASoyad" runat="server" Text="Soyad :"></asp:Label>
                </td>
                <td class="auto-style3">
                    <asp:TextBox ID="txtASoyad" runat="server"></asp:TextBox>
                </td>
                <td>&nbsp;</td>
            </tr>
            <tr>
                <td class="auto-style2">
                    <asp:Label ID="lblOgrenciNo" runat="server" Text="Öğrenci No:"></asp:Label>
                </td>
                <td>
                    <asp:TextBox ID="txtOOgrenciNo" runat="server"></asp:TextBox>
                </td>
                <td>
                    <asp:Label ID="lblEmailText" runat="server" Text="@mail.baskent.edu.tr"></asp:Label>
                </td>
                <td>
                    <asp:Label ID="lblAEmail" runat="server" Text="E-mail :"></asp:Label>
                </td>
                <td class="auto-style3">
                    <asp:TextBox ID="txtAEmail" runat="server"></asp:TextBox>
                </td>
                <td>
                    <asp:Label ID="lblAEmailText" runat="server" Text="@baskent.edu.tr"></asp:Label>
                </td>
            </tr>
            <tr>
                <td class="auto-style2">
                    <asp:Label ID="lblBolum" runat="server" Text="Bölüm:"></asp:Label>
                </td>
                <td>
                    <asp:TextBox ID="txtOBolum" runat="server"></asp:TextBox>
                </td>
                <td>&nbsp;</td>
                <td>
                    <asp:Label ID="lblAUnvan" runat="server" Text="Ünvan :"></asp:Label>
                </td>
                <td class="auto-style3">
                    <asp:TextBox ID="txtAUnvan" runat="server"></asp:TextBox>
                </td>
                <td>&nbsp;</td>
            </tr>
            <tr>
                <td class="auto-style2">
                    <asp:Button ID="btnOEkle" runat="server" OnClick="btnOEkle_Click" Text="Ekle" />
                </td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
                <td>
                    <asp:Button ID="btnAEkle" runat="server" OnClick="btnAEkle_Click" Text="Ekle" />
                    <asp:Button ID="btnAPasif" runat="server" OnClick="btnAPasif_Click" 
                        Text="Pasif" />
                </td>
                <td class="auto-style3">&nbsp;</td>
                <td>&nbsp;</td>
            </tr>
        </table>
    
    </div>
    </form>
</body>
</html>
