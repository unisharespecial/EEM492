<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="SifremiUnuttumAkademisyen.aspx.cs" Inherits="ProjeSistemi.WebForm11" %>

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
    <div>
    
        <table class="auto-style1">
            <tr>
                <td>
                    <asp:Label ID="Label1" runat="server" Font-Bold="True" ForeColor="Red" 
                        Text="Şifremi Unuttum"></asp:Label>
                </td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
            </tr>
            <tr>
                <td>
                    <asp:Label ID="lblEmail" runat="server" Text="E-mail :"></asp:Label>
                </td>
                <td>
                    <asp:TextBox ID="txtEmail" runat="server"></asp:TextBox>
&nbsp;
                    <asp:Label ID="lblmailtext" runat="server" Text="@baskent.edu.tr"></asp:Label>
                </td>
                <td>
                    <asp:Button ID="btnGonder" runat="server" Font-Bold="False" Text="Gönder" 
                        OnClick="btnGonder_Click" />
                </td>
            </tr>
        </table>
    
    </div>
    </form>
</body>
</html>
