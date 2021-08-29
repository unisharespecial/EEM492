<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="OgrenciProjeArama.aspx.cs" Inherits="ProjeSistemi.WebForm6" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
    <style type="text/css">
        .auto-style1
        {
            width: 902px;
        }
        .auto-style3
        {
            width: 6px;
        }
        .auto-style4
        {
            width: 6px;
            height: 23px;
        }
        .auto-style7
        {
            width: 120px;
        }
        .auto-style9
        {
            width: 11px;
            height: 23px;
        }
        .auto-style10
        {
            width: 11px;
        }
        .auto-style11
        {
            width: 1px;
        }
        .auto-style12
        {
            width: 1px;
            height: 23px;
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
                <td class="auto-style7">
                    <asp:Label ID="lblProjeYıl" runat="server" Font-Bold="True" ForeColor="Red" 
                        Text="Proje Yılı"></asp:Label>
                </td>
                <td class="auto-style3">&nbsp;</td>
                <td class="auto-style10">&nbsp;</td>
                <td class="auto-style11">&nbsp;</td>
            </tr>
            <tr>
                <td rowspan="4">
                    <asp:ListBox ID="lbProjeAdi" runat="server" Width="81px"></asp:ListBox>
                </td>
                <td rowspan="4">
                    <asp:ListBox ID="lbProjeSorumlusu" runat="server"></asp:ListBox>
                </td>
                <td rowspan="4" class="auto-style7">
                    <asp:ListBox ID="lbProjeYili" runat="server"></asp:ListBox>
                </td>
                <td class="auto-style3">&nbsp;</td>
                <td class="auto-style10">&nbsp;</td>
                <td class="auto-style11">&nbsp;</td>
            </tr>
            <tr>
                <td class="auto-style4"></td>
                <td class="auto-style9"></td>
                <td class="auto-style12"></td>
            </tr>
            <tr>
                <td class="auto-style3">&nbsp;</td>
                <td class="auto-style10">&nbsp;</td>
                <td class="auto-style11">&nbsp;</td>
            </tr>
            <tr>
                <td class="auto-style3">&nbsp;</td>
                <td class="auto-style10">&nbsp;</td>
                <td class="auto-style11">&nbsp;</td>
            </tr>
            <tr>
                <td>
                    <asp:Label ID="lblProjeDonem" runat="server" Font-Bold="True" ForeColor="Red" 
                        Text="Proje Dönemi :"></asp:Label>
                    <asp:DropDownList ID="ddlProjeDonemi" runat="server">
                        <asp:ListItem>Bahar</asp:ListItem>
                        <asp:ListItem>Güz</asp:ListItem>
                    </asp:DropDownList>
                </td>
                <td>
                    <asp:Button ID="btnAra" runat="server" Text="Ara" OnClick="btnAra_Click" />
                </td>
                <td class="auto-style7">&nbsp;</td>
                <td class="auto-style3">&nbsp;</td>
                <td class="auto-style10">&nbsp;</td>
                <td class="auto-style11">&nbsp;</td>
            </tr>
            <tr>
                <td>
                    <asp:ListBox ID="lbAramaSonucu" runat="server"></asp:ListBox>
                </td>
                <td>

        <asp:Image ID="imgAfis" runat="server" Width="243px" />

                </td>
                <td class="auto-style7">&nbsp;</td>
                <td class="auto-style3">&nbsp;</td>
                <td class="auto-style10">&nbsp;</td>
                <td class="auto-style11">&nbsp;</td>
            </tr>
        </table>
    </div>

    <div>

    </div>
    </form>
</body>
</html>
