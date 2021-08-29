<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="OgrenciEkran.aspx.cs" Inherits="ProjeSistemi.WebForm2" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
    <style type="text/css">
        .auto-style5 {
            width: 100%;
            height: 406px;
        }
        .auto-style6 {
            height: 56px;
            margin-left: 40px;
        }
        .auto-style9 {
            height: 23px;
        }
        .auto-style10 {
            width: 335px;
            height: 60px;
        }
        .auto-style11 {
            height: 23px;
            width: 335px;
        }
        .auto-style16
        {
            height: 56px;
            width: 124px;
        }
        .auto-style19
        {
            height: 60px;
        }
        .auto-style20
        {
            height: 60px;
            }
        .auto-style21
        {
            height: 23px;
            width: 397px;
        }
        .auto-style27
        {
            width: 124px;
            height: 60px;
        }
        .auto-style28
        {
            width: 124px;
        }
        .auto-style29
        {
            height: 23px;
            width: 124px;
        }
        .auto-style30
        {}
    </style>
</head>
<body>
    <form id="form1" runat="server">
    <div>
    
       
    
        <table class="auto-style5">
            <tr>
                <td class="auto-style27"></td>
                <td class="auto-style10"></td>
                <td class="auto-style20" colspan="2">
                    <asp:LinkButton ID="LinkButton1" runat="server" OnClick="LinkButton1_Click">Çıkış</asp:LinkButton>
                </td>
            </tr>
            <tr>
                <td class="auto-style16">
                    <asp:LinkButton ID="lbProjeAra" runat="server" OnClick="lbProjeAra_Click">Proje Ara</asp:LinkButton>
                </td>
                <td class="auto-style6" colspan="3">
                    <asp:Label ID="lblMerhaba" runat="server" Text="Merhaba"></asp:Label>
                    ,&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                    </td>
            </tr>
            <tr>
                <td class="auto-style28">
                    &nbsp;</td>
                <td colspan="3" rowspan="2">
                    <asp:Label ID="lblHerYil" runat="server" Text="Bu Yıl Yapılan Çalışmalar:"></asp:Label>
                </td>
            </tr>
            <tr>
                <td class="auto-style28" rowspan="2">
                </td>
            </tr>
            <tr>
                <td colspan="3" class="auto-style30">
                    <asp:ListBox ID="lbHerYil" runat="server" Height="109px" Width="587px"></asp:ListBox>
                </td>
            </tr>
            <tr>
                <td class="auto-style29"></td>
                <td class="auto-style11"></td>
                <td class="auto-style21">
                    <asp:Button ID="btnProjeEkle" runat="server" Text="Proje Ekle" />
                </td>
                <td class="auto-style9">&nbsp;</td>
            </tr>
        </table>
    
       
    
    </div>
    </form>
</body>
</html>
