<%@ Page Language="VB" AutoEventWireup="false" CodeFile="listele.aspx.vb" Inherits="listele" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>Untitled Page</title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
    
        <asp:GridView ID="GridView1" runat="server" BackColor="White" 
            BorderColor="#E7E7FF" BorderStyle="None" BorderWidth="1px" CellPadding="3" 
            GridLines="Horizontal" AllowPaging="True" AllowSorting="True" 
            AutoGenerateColumns="False" DataKeyNames="id" DataSourceID="AccessDataSource1">
            <RowStyle BackColor="#E7E7FF" ForeColor="#4A3C8C" />
            <Columns>
                <asp:BoundField DataField="id" HeaderText="ID" InsertVisible="False" 
                    ReadOnly="True" SortExpression="id" />
                <asp:BoundField DataField="lokasyonid" HeaderText="Yer Kodu" 
                    SortExpression="lokasyonid" />
                <asp:BoundField DataField="problem" HeaderText="Arıza" 
                    SortExpression="problem" />
                <asp:BoundField DataField="ip" HeaderText="Ip" SortExpression="ip" />
                <asp:BoundField DataField="kayitzamani" HeaderText="Kayıt Zamanı" 
                    SortExpression="kayitzamani" />
            </Columns>
            <FooterStyle BackColor="#B5C7DE" ForeColor="#4A3C8C" />
            <PagerStyle BackColor="#E7E7FF" ForeColor="#4A3C8C" HorizontalAlign="Right" />
            <SelectedRowStyle BackColor="#738A9C" Font-Bold="True" ForeColor="#F7F7F7" />
            <HeaderStyle BackColor="#4A3C8C" Font-Bold="True" ForeColor="#F7F7F7" />
            <AlternatingRowStyle BackColor="#F7F7F7" />
        </asp:GridView>
        <asp:AccessDataSource ID="AccessDataSource1" runat="server" 
            DataFile="~/App_Data/veriler.mdb" 
            SelectCommand="SELECT * FROM [detaylar] ORDER BY [id] DESC">
        </asp:AccessDataSource>
    
        <asp:Button ID="Button1" runat="server" Text="DB Temizle" Visible="False" />
    
    </div>
    </form>
</body>
</html>
