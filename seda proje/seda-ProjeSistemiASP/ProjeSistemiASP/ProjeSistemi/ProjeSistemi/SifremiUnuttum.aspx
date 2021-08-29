<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="SifremiUnuttum.aspx.cs" Inherits="ProjeSistemi.WebForm10" %>

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
            width: 127px;
        }
        .auto-style3
        {
            width: 443px;
        }
    </style>
</head>
<body>
    <form id="form1" runat="server">
    <div>
    
        <table class="auto-style1">
            <tr>
                <td class="auto-style2">
                    <asp:Label ID="lblSifremiUnuttum" runat="server" Font-Bold="True" 
                        ForeColor="Red" Text="Şifremi Unuttum"></asp:Label>
                </td>
                <td class="auto-style3">&nbsp;</td>
                <td>&nbsp;</td>
            </tr>
            <tr>
                <td class="auto-style2">
                    <asp:Label ID="lblEmail" runat="server" Text="E-mail :"></asp:Label>
                </td>
                <td class="auto-style3">
                    <asp:TextBox ID="txtEmail" runat="server"></asp:TextBox>
&nbsp;
                    <asp:Label ID="lblEmailText" runat="server" Text="@mail.baskent.edu.tr"></asp:Label>
                </td>
                <td>
                    <asp:Button ID="btnGonder" runat="server" Text="Gönder" 
                        OnClick="btnGonder_Click" />
                </td>
            </tr>
        </table>
    
    </div>
    </form>
</body>
</html>
