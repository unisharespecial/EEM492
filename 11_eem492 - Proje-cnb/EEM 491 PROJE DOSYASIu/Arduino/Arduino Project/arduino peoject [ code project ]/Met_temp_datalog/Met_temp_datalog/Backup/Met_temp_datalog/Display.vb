
Public Class Display   
    Private part As New Bitmap(1570, 1070, Drawing.Imaging.PixelFormat.Format24bppRgb)
    Public display_now(1439) As Int16  'only 0 to 1023 possible
    Public dt As String = ""  'the time used on the current display
    Public Sub show_now()
        Dim aorp As String = dt.Substring(dt.Length - 2, 2)  'am or pm
        Dim tn = dt.Substring(0, dt.Length - 3) 'time without am or pm
        Dim g As Graphics = Graphics.FromImage(part)
        g.FillRectangle(Brushes.Black, 0, 0, 1570, 1070)
        Dim Bpen As New System.Drawing.Pen(Color.Cyan, 3)
        Dim Rpen As New System.Drawing.Pen(Color.Crimson, 3)
        g.DrawLine(Bpen, 62, 22, 62, 1040)
        g.DrawLine(Bpen, 1508, 22, 1508, 1040)
        g.DrawLine(Bpen, 785, 22, 785, 1040)
        g.DrawLine(Bpen, 62, 22, 1508, 22)
        g.DrawLine(Bpen, 62, 1040, 1508, 1040)
        Dim nfont As New System.Drawing.Font("arial", 16, FontStyle.Regular)
        g.DrawString(tn, nfont, Brushes.Cyan, 58, 1041)
        g.DrawString(tn, nfont, Brushes.Cyan, 1464, 1041)
        g.DrawString(tn, nfont, Brushes.Cyan, 765, 1041)
        g.DrawString(tn, nfont, Brushes.Cyan, 58, 0)
        g.DrawString(tn, nfont, Brushes.Cyan, 1464, 0)
        g.DrawString(tn, nfont, Brushes.Cyan, 765, 0)
        If aorp = "AM" Then
            g.DrawString("AM", nfont, Brushes.Cyan, 390, 0)
            g.DrawString("AM", nfont, Brushes.Cyan, 390, 1041)
            g.DrawString("PM", nfont, Brushes.Cyan, 1076, 0)
            g.DrawString("PM", nfont, Brushes.Cyan, 1076, 1041)
        Else
            g.DrawString("PM", nfont, Brushes.Cyan, 390, 0)
            g.DrawString("PM", nfont, Brushes.Cyan, 390, 1041)
            g.DrawString("AM", nfont, Brushes.Cyan, 1076, 0)
            g.DrawString("AM", nfont, Brushes.Cyan, 1076, 1041)
        End If
        For i = 1 To 23
            g.DrawLine(Pens.Cyan, 62 + 60 * i, 22, 62 + 60 * i, 1040)
        Next
        For i = 0 To 1438
            If display_now(i + 1) = 0 Then Exit For 'only display the real samples
            g.DrawLine(Rpen, 62 + i, 1040 - display_now(i), 63 + i, 1040 - display_now(i + 1))
        Next
        g.DrawString("40", nfont, Brushes.Crimson, 30, 15)
        g.DrawString("20", nfont, Brushes.Crimson, 30, 520)
        g.DrawString("0", nfont, Brushes.Crimson, 40, 1020)
        g.DrawString("40", nfont, Brushes.Crimson, 1508, 15)
        g.DrawString("20", nfont, Brushes.Crimson, 1508, 520)
        g.DrawString("0", nfont, Brushes.Crimson, 1508, 1020)
        g.DrawLine(Bpen, 62, 531, 1508, 531)  'middle y line
        For i = 1 To 40  'y lines
            g.DrawLine(Pens.Cyan, 62, CInt(22 + 25.4 * i), 1508, CInt(22 + 25.4 * i))
        Next
        g.Dispose()
        User_interface.PictureBox1.Image = part
    End Sub
End Class
