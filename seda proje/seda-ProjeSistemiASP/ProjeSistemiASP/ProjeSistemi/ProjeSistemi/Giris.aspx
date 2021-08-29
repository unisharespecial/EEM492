<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Giris.aspx.cs" Inherits="ProjeSistemi.WebForm1" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
    <style type="text/css">
        .auto-style1 {
            width: 108%;
            height: 223px;
        }
        .auto-style2 {
            width: 143px;
        }
        .auto-style3 {
            width: 138px;
        }
        .auto-style5 {
            width: 132px;
        }
        .auto-style6 {
            width: 148px;
        }
        .auto-style7 {
            width: 143px;
            height: 27px;
        }
        .auto-style8 {
            width: 138px;
            height: 27px;
        }
        .auto-style9 {
            width: 148px;
            height: 27px;
        }
        .auto-style10 {
            width: 132px;
            height: 27px;
        }
        .auto-style11 {
            height: 27px;
        }
        .auto-style12 {
            width: 360px;
        }
        .auto-style13 {
            height: 27px;
            width: 360px;
        }
        .auto-style14
        {
            width: 143px;
            height: 23px;
        }
        .auto-style15
        {
            width: 138px;
            height: 23px;
        }
        .auto-style16
        {
            width: 148px;
            height: 23px;
        }
        .auto-style17
        {
            width: 132px;
            height: 23px;
        }
        .auto-style18
        {
            width: 360px;
            height: 23px;
        }
        .auto-style19
        {
            height: 23px;
        }
        .auto-style20
        {
            width: 143px;
            height: 36px;
        }
        .auto-style21
        {
            width: 138px;
            height: 36px;
        }
        .auto-style22
        {
            width: 148px;
            height: 36px;
        }
        .auto-style23
        {
            width: 132px;
            height: 36px;
        }
        .auto-style24
        {
            width: 360px;
            height: 36px;
        }
        .auto-style25
        {
            height: 36px;
        }
    </style>
</head>
<body>
    <form id="form1" runat="server">
    <div style="height: 308px">
    
        <table class="auto-style1">
            <tr>
                <td class="auto-style14">
                    <asp:Label ID="lblAPersonel" runat="server" Font-Bold="True" ForeColor="Red" Text="Akademik Personel :"></asp:Label>
                </td>
                <td class="auto-style15"></td>
                <td class="auto-style16"></td>
                <td class="auto-style17">
                    <asp:Label ID="lblOgrenci" runat="server" Font-Bold="True" ForeColor="Red" Text="Öğrenci :"></asp:Label>
                </td>
                <td class="auto-style18"></td>
                <td class="auto-style19">
                    <asp:Label ID="Label4" runat="server" Font-Bold="True" ForeColor="Red" Text="Yönetici"></asp:Label>
                </td>
                <td class="auto-style19"></td>
            </tr>
            <tr>
                <td class="auto-style2">&nbsp;</td>
                <td class="auto-style3">&nbsp;</td>
                <td class="auto-style6">&nbsp;</td>
                <td class="auto-style5">&nbsp;</td>
                <td class="auto-style12">&nbsp;</td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
            </tr>
            <tr>
                <td class="auto-style2">E-mail : </td>
                <td class="auto-style3">
                    <asp:TextBox ID="txtAEmail" runat="server"></asp:TextBox>
                </td>
                <td class="auto-style6">
                    <asp:Label ID="lblAEmail" runat="server" Text="@baskent.edu.tr"></asp:Label>
                </td>
                <td class="auto-style5">
                    <asp:Label ID="Label1" runat="server" Text="E-mail:"></asp:Label>
                </td>
                <td class="auto-style12">
                    <asp:TextBox ID="txtOEmail" runat="server"></asp:TextBox>
                    <asp:Label ID="Label3" runat="server" Text="@mail.baskent.edu.tr"></asp:Label>
                </td>
                <td>
                    <asp:Label ID="Label5" runat="server" Text="Şifre :"></asp:Label>
                </td>
                <td>
                    <asp:TextBox ID="txtYSifre" runat="server"></asp:TextBox>
                </td>
            </tr>
            <tr>
                <td class="auto-style7">Şifre :</td>
                <td class="auto-style8">
                    <asp:TextBox ID="txtASifre" runat="server"></asp:TextBox>
                </td>
                <td class="auto-style9"></td>
                <td class="auto-style10">
                    <asp:Label ID="Label2" runat="server" Text="Şifre:"></asp:Label>
                </td>
                <td class="auto-style13">
                    <asp:TextBox ID="txtOSifre" runat="server"></asp:TextBox>
                </td>
                <td class="auto-style11">&nbsp;</td>
                <td class="auto-style11">&nbsp;</td>
            </tr>
            <tr>
                <td class="auto-style2">
                    <asp:Button ID="btnAGiris" runat="server" Text="Giriş" 
                        OnClick="btnAGiris_Click" />
                </td>
                <td class="auto-style3">&nbsp;</td>
                <td class="auto-style6">&nbsp;</td>
                <td class="auto-style5">
                    <asp:Button ID="btnOGiris" runat="server" Text="Giriş" 
                        OnClick="btnOGiris_Click" />
                </td>
                <td class="auto-style12">&nbsp;</td>
                <td>
                    <asp:Button ID="btnYGiris" runat="server" Height="27px" Text="Giriş" 
                        OnClick="btnYGiris_Click" />
                </td>
                <td>&nbsp;</td>
            </tr>
            <tr>
                <td class="auto-style20">
                    <asp:LinkButton ID="LinkButton1" runat="server" OnClick="LinkButton1_Click">Şifremi Unuttum</asp:LinkButton>
                </td>
                <td class="auto-style21"></td>
                <td class="auto-style22"></td>
                <td class="auto-style23">
                    <asp:LinkButton ID="LinkButton2" runat="server" OnClick="LinkButton2_Click">Şifremi Unuttum</asp:LinkButton>
                </td>
                <td class="auto-style24">
                    <asp:LinkButton ID="LinkButton3" runat="server" OnClick="LinkButton3_Click">Yeni Kayıt</asp:LinkButton>
                </td>
                <td class="auto-style25"></td>
                <td class="auto-style25"></td>
            </tr>
            </table>
    
    </div>
    
    </form>
</body>
</html>
