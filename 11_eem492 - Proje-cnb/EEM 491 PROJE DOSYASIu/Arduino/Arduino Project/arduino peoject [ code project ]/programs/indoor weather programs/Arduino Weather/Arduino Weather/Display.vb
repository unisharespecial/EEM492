
Public Class Display
#Region "system variables"
    Public temperature(1439) As Int32  'only 0 to 1023 possible
    Public humidity(1439) As Int32 'only 0 to 1023 possible
    Public airpressure(1439) As Int32  'only 0 to 1023 possible
    Public rainfall(1439) As Int32 'only 0 to 1023 possible
    Public cursorTH As Integer = 375  'pass the cursor from mouse e.X
    Public cursorAR As Integer = 375  'pass the cursor from mouse e.X
    Public display_start_time As DateTime  'pass the right hand side time
    Public display_span_time As TimeSpan  'pass  the time span of display
    Private full_image As New Bitmap(1570, 1075, Drawing.Imaging.PixelFormat.Format24bppRgb)
    Private ARfull_image As New Bitmap(1570, 1075, Drawing.Imaging.PixelFormat.Format24bppRgb)
    Private g As Graphics = Graphics.FromImage(full_image)
    Private ARg As Graphics = Graphics.FromImage(ARfull_image)
    Private scale_image As New Bitmap(1570, 430, Drawing.Imaging.PixelFormat.Format24bppRgb)
    Private gs As Graphics = Graphics.FromImage(scale_image)
    Private ARscale_image As New Bitmap(1570, 430, Drawing.Imaging.PixelFormat.Format24bppRgb)
    Private ARgs As Graphics = Graphics.FromImage(ARscale_image)
    Private stemperature(1439) As Int32  'only 0 to 1023 possible
    Private shumidity(1439) As Int32  'only 0 to 1023 possible
    Private sairpressure(1439) As Int32  'only 0 to 1023 possible
    Private srainfall(1439) As Int32 'only 0 to 1023 possible
#End Region
    Public Sub full_temp_hum()
        Dim tn = display_start_time 'righthand side current time
        Dim tnll = tn.Subtract(display_span_time)  'graph left side time
        g.FillRectangle(Brushes.Black, 0, 0, 1570, 1070)
        Dim Bpen As New System.Drawing.Pen(Color.Cyan, 3)
        Dim Rpen As New System.Drawing.Pen(Color.Crimson, 3)
        Dim Gpen As New System.Drawing.Pen(Color.Lime, 3)
        g.DrawLine(Bpen, 62, 22, 62, 1045)  'left
        g.DrawLine(Bpen, 1508, 22, 1508, 1045)  'right
        g.DrawLine(Bpen, 62, 22, 1508, 22)   'top
        g.DrawLine(Bpen, 62, 278, 1508, 278)
        g.DrawLine(Bpen, 62, 534, 1508, 534)  'middle
        g.DrawLine(Bpen, 62, 790, 1508, 790)
        g.DrawLine(Bpen, 62, 1045, 1508, 1045)  'bottom
        Dim nfont As New System.Drawing.Font("arial", 16, FontStyle.Regular)
        g.DrawString(tnll.ToString("h:mm tt..d MMM yy"), nfont, Brushes.Cyan, 58, 1046)
        g.DrawString(tn.ToString("h:mm tt..d MMM yy"), nfont, Brushes.Cyan, 1310, 1046)
        g.DrawString(tnll.ToString("h:mm tt..d MMM yy"), nfont, Brushes.Cyan, 58, 0)
        g.DrawString(tn.ToString("h:mm tt..d MMM yy"), nfont, Brushes.Cyan, 1310, 0)
        For i = 1439 To 1 Step -1
            If (temperature(i - 1) > 1023 Or temperature(i) > 1023) Then
            Else
                g.DrawLine(Rpen, 63 + i, 1045 - temperature(i - 1), 64 + i, 1045 - temperature(i))
            End If
            If (humidity(i - 1) > 1023 Or humidity(i) > 1023) Then
            Else
                g.DrawLine(Gpen, 63 + i, 1045 - humidity(i - 1), 64 + i, 1045 - humidity(i))
            End If
        Next
        g.DrawString("40", nfont, Brushes.Crimson, 30, 10)
        g.DrawString("30", nfont, Brushes.Crimson, 30, 260)
        g.DrawString("20", nfont, Brushes.Crimson, 30, 520)
        g.DrawString("10", nfont, Brushes.Crimson, 30, 778)
        g.DrawString("0", nfont, Brushes.Crimson, 40, 1020)  'all the left
        g.DrawString("40", nfont, Brushes.Crimson, 1508, 10)
        g.DrawString("30", nfont, Brushes.Crimson, 1508, 260)
        g.DrawString("20", nfont, Brushes.Crimson, 1508, 520)
        g.DrawString("10", nfont, Brushes.Crimson, 1508, 778)
        g.DrawString("0", nfont, Brushes.Crimson, 1508, 1020)  'all the right
        g.DrawString("100", nfont, Brushes.Lime, 20, 30)
        g.DrawString("75", nfont, Brushes.Lime, 30, 280)
        g.DrawString("50", nfont, Brushes.Lime, 30, 540)
        g.DrawString("25", nfont, Brushes.Lime, 30, 798)
        g.DrawString("0", nfont, Brushes.Lime, 40, 1040)  'all the left
        g.DrawString("100", nfont, Brushes.Lime, 1508, 30)
        g.DrawString("75", nfont, Brushes.Lime, 1508, 280)
        g.DrawString("50", nfont, Brushes.Lime, 1508, 540)
        g.DrawString("25", nfont, Brushes.Lime, 1508, 798)
        g.DrawString("0", nfont, Brushes.Lime, 1508, 1040)  'all the right
        cursorTH = (cursorTH / ArduinoWeather.temphumid.Width) * 1570
        If cursorTH < 65 Then cursorTH = 65 'cant go further left
        If cursorTH > 1503 Then cursorTH = 1503 'cant go further right
        g.DrawLine(Pens.White, cursorTH, 22, cursorTH, 1045)
        Dim dtemp = (temperature(cursorTH - 65) / 25.6).ToString("f1")
        Dim dhumid = (humidity(cursorTH - 65) / 10.23).ToString("f1")
        If dhumid > 101 Then dhumid = 0 'for blank case
        If dtemp > 41 Then dtemp = 0
        g.DrawString(("humidity = " & dhumid & "%"), nfont, Brushes.Lime, 358, 0)
        g.DrawString(("humidity = " & dhumid & "%"), nfont, Brushes.Lime, 358, 1046)
        g.DrawString(("temperature = " & dtemp & "C"), nfont, Brushes.Crimson, 1000, 0)
        g.DrawString(("temperature = " & dtemp & "C"), nfont, Brushes.Crimson, 1000, 1046)
        Dim curtime = TimeSpan.FromMinutes(display_span_time.TotalMinutes - (display_span_time.TotalMinutes * (cursorTH - 65) / 1438))
        Dim tnl = tn.Subtract(curtime)  'graph mid time at cursor
        g.DrawString(tnl.ToString("h:mm tt..d MMM yy"), nfont, Brushes.Cyan, 650, 0)  'top
        g.DrawString(tnl.ToString("h:mm tt..d MMM yy"), nfont, Brushes.Cyan, 650, 1046)  'bottom
        ArduinoWeather.temphumid.Image = full_image
    End Sub
    Public Sub scale_temp_hum()
        Try
            For i = 0 To 1439
                stemperature(i) = temperature(i) / 2.7
                shumidity(i) = humidity(i) / 2.7  'scale down the display
            Next
            Dim tn = display_start_time 'righthand side current time
            Dim tnll = tn.Subtract(display_span_time)  'graph left side time
            gs.FillRectangle(Brushes.Black, 0, 0, 1570, 1070)
            Dim Bpen As New System.Drawing.Pen(Color.Cyan, 3)
            Dim Rpen As New System.Drawing.Pen(Color.Crimson, 3)
            Dim Gpen As New System.Drawing.Pen(Color.Lime, 3)
            gs.DrawLine(Bpen, 62, 22, 62, 400)  'left
            gs.DrawLine(Bpen, 1508, 22, 1508, 400)  'right
            gs.DrawLine(Bpen, 62, 22, 1508, 22)   'top
            gs.DrawLine(Bpen, 62, 116, 1508, 116)
            gs.DrawLine(Bpen, 62, 211, 1508, 211)  'middle
            gs.DrawLine(Bpen, 62, 306, 1508, 306)
            gs.DrawLine(Bpen, 62, 400, 1508, 400)  'bottom
            Dim nfont As New System.Drawing.Font("arial", 16, FontStyle.Regular)
            gs.DrawString(tnll.ToString("h:mm tt..d MMM yy"), nfont, Brushes.Cyan, 58, 401)
            gs.DrawString(tn.ToString("h:mm tt..d MMM yy"), nfont, Brushes.Cyan, 1310, 401)
            gs.DrawString(tnll.ToString("h:mm tt..d MMM yy"), nfont, Brushes.Cyan, 58, 0)
            gs.DrawString(tn.ToString("h:mm tt..d MMM yy"), nfont, Brushes.Cyan, 1310, 0)
            For i = 1439 To 1 Step -1
                If (stemperature(i - 1) > 1023 Or stemperature(i) > 1023) Then
                Else
                    gs.DrawLine(Rpen, 63 + i, 400 - stemperature(i - 1), 64 + i, 400 - stemperature(i))
                End If
                If (shumidity(i - 1) > 1023 Or shumidity(i) > 1023) Then
                Else
                    gs.DrawLine(Gpen, 63 + i, 400 - shumidity(i - 1), 64 + i, 400 - shumidity(i))
                End If
            Next
            gs.DrawString("40", nfont, Brushes.Crimson, 30, 10)
            gs.DrawString("30", nfont, Brushes.Crimson, 30, 96)
            gs.DrawString("20", nfont, Brushes.Crimson, 30, 190)
            gs.DrawString("10", nfont, Brushes.Crimson, 30, 286)
            gs.DrawString("0", nfont, Brushes.Crimson, 40, 380)  'all the left
            gs.DrawString("40", nfont, Brushes.Crimson, 1508, 10)
            gs.DrawString("30", nfont, Brushes.Crimson, 1508, 96)
            gs.DrawString("20", nfont, Brushes.Crimson, 1508, 190)
            gs.DrawString("10", nfont, Brushes.Crimson, 1508, 286)
            gs.DrawString("0", nfont, Brushes.Crimson, 1508, 380)  'all the right
            gs.DrawString("100", nfont, Brushes.Lime, 20, 30)
            gs.DrawString("75", nfont, Brushes.Lime, 30, 116)
            gs.DrawString("50", nfont, Brushes.Lime, 30, 210)
            gs.DrawString("25", nfont, Brushes.Lime, 30, 306)
            gs.DrawString("0", nfont, Brushes.Lime, 40, 400)  'all the left
            gs.DrawString("100", nfont, Brushes.Lime, 1508, 30)
            gs.DrawString("75", nfont, Brushes.Lime, 1508, 116)
            gs.DrawString("50", nfont, Brushes.Lime, 1508, 210)
            gs.DrawString("25", nfont, Brushes.Lime, 1508, 306)
            gs.DrawString("0", nfont, Brushes.Lime, 1508, 400)  'all the right
            Dim Tcurser As Integer = (cursorTH / ArduinoWeather.temphumid.Width) * 1570
            If Tcurser < 65 Then Tcurser = 65 'cant go further left
            If Tcurser > 1503 Then Tcurser = 1503 'cant go further right
            gs.DrawLine(Pens.White, Tcurser, 22, Tcurser, 400)
            Dim dtemp = (temperature(Tcurser - 65) / 25.6).ToString("f1")
            If dtemp > 41 Then dtemp = 0
            Dim dhumid = (humidity(Tcurser - 65) / 10.23).ToString("f1")
            If dhumid > 101 Then dhumid = 0 'for blank case
            gs.DrawString(("humidity = " & dhumid & "%"), nfont, Brushes.Lime, 358, 0)
            gs.DrawString(("humidity = " & dhumid & "%"), nfont, Brushes.Lime, 358, 401)
            gs.DrawString(("temperature = " & dtemp & "C"), nfont, Brushes.Crimson, 1000, 0)
            gs.DrawString(("temperature = " & dtemp & "C"), nfont, Brushes.Crimson, 1000, 401)
            Dim curtime = TimeSpan.FromMinutes(display_span_time.TotalMinutes - (display_span_time.TotalMinutes * (Tcurser - 65) / 1438))
            Dim tnl = tn.Subtract(curtime)  'graph mid time at cursor
            gs.DrawString(tnl.ToString("h:mm tt..d MMM yy"), nfont, Brushes.Cyan, 650, 0)  'top
            gs.DrawString(tnl.ToString("h:mm tt..d MMM yy"), nfont, Brushes.Cyan, 650, 401)  'bottom
            ArduinoWeather.temphumid.Image = scale_image
        Catch ex As Exception
        End Try
    End Sub
    Public Sub full_air_rain()
        Dim tn = display_start_time 'righthand side current time
        Dim tnll = tn.Subtract(display_span_time)  'graph left side time
        ARg.FillRectangle(Brushes.Black, 0, 0, 1570, 1070)
        Dim Bpen As New System.Drawing.Pen(Color.Cyan, 3)
        Dim Rpen As New System.Drawing.Pen(Color.Crimson, 3)
        Dim Gpen As New System.Drawing.Pen(Color.Lime, 3)
        ARg.DrawLine(Bpen, 62, 22, 62, 1045)  'left
        ARg.DrawLine(Bpen, 1508, 22, 1508, 1045)  'right
        ARg.DrawLine(Bpen, 62, 22, 1508, 22)   'top
        ARg.DrawLine(Bpen, 62, 278, 1508, 278)
        ARg.DrawLine(Bpen, 62, 534, 1508, 534)  'middle
        ARg.DrawLine(Bpen, 62, 790, 1508, 790)
        ARg.DrawLine(Bpen, 62, 1045, 1508, 1045)  'bottom
        Dim nfont As New System.Drawing.Font("arial", 16, FontStyle.Regular)
        ARg.DrawString(tnll.ToString("h:mm tt..d MMM yy"), nfont, Brushes.Cyan, 58, 1046)
        ARg.DrawString(tn.ToString("h:mm tt..d MMM yy"), nfont, Brushes.Cyan, 1310, 1046)
        ARg.DrawString(tnll.ToString("h:mm tt..d MMM yy"), nfont, Brushes.Cyan, 58, 0)
        ARg.DrawString(tn.ToString("h:mm tt..d MMM yy"), nfont, Brushes.Cyan, 1310, 0)
        For i = 1439 To 1 Step -1
            If (airpressure(i - 1) > 1023 Or airpressure(i) > 1023) Then
            Else
                ARg.DrawLine(Rpen, 63 + i, 1045 - airpressure(i - 1), 64 + i, 1045 - airpressure(i))
            End If
            If (rainfall(i - 1) > 1023 Or rainfall(i) > 1023) Then
            Else
                ARg.DrawLine(Gpen, 63 + i, 1045 - rainfall(i - 1), 64 + i, 1045 - rainfall(i))
            End If
        Next
        ARg.DrawString("1070", nfont, Brushes.Crimson, 8, 10)
        ARg.DrawString("1040", nfont, Brushes.Crimson, 8, 260)
        ARg.DrawString("1010", nfont, Brushes.Crimson, 8, 520)
        ARg.DrawString("980", nfont, Brushes.Crimson, 20, 778)
        ARg.DrawString("950", nfont, Brushes.Crimson, 20, 1020)  'all the left
        ARg.DrawString("1070", nfont, Brushes.Crimson, 1508, 10)
        ARg.DrawString("1040", nfont, Brushes.Crimson, 1508, 260)
        ARg.DrawString("1010", nfont, Brushes.Crimson, 1508, 520)
        ARg.DrawString("980", nfont, Brushes.Crimson, 1508, 778)
        ARg.DrawString("950", nfont, Brushes.Crimson, 1508, 1020)  'all the right
        'ARg.DrawString("100", nfont, Brushes.Lime, 20, 30)
        ' ARg.DrawString("75", nfont, Brushes.Lime, 30, 280)
        'ARg.DrawString("50", nfont, Brushes.Lime, 30, 540)
        'ARg.DrawString("25", nfont, Brushes.Lime, 30, 798)
        'ARg.DrawString("0", nfont, Brushes.Lime, 40, 1040)  'all the left
        'ARg.DrawString("100", nfont, Brushes.Lime, 1508, 30)
        'ARg.DrawString("75", nfont, Brushes.Lime, 1508, 280)
        'ARg.DrawString("50", nfont, Brushes.Lime, 1508, 540)
        'ARg.DrawString("25", nfont, Brushes.Lime, 1508, 798)
        'ARg.DrawString("0", nfont, Brushes.Lime, 1508, 1040)  'all the right
        Dim Tcurser As Integer = (cursorAR / ArduinoWeather.airrain.Width) * 1570
        If Tcurser < 65 Then Tcurser = 65 'cant go further left
        If Tcurser > 1503 Then Tcurser = 1503 'cant go further right
        ARg.DrawLine(Pens.White, Tcurser, 22, Tcurser, 1045)
        Dim dtemp = (950 + (airpressure(Tcurser - 65) * 0.117)).ToString("f0")
        'Dim dhumid = (humidity(Tcurser - 65) / 10.23).ToString("f1")
        'If dhumid > 101 Then dhumid = 0 'for blank case
        If dtemp > 1051 Then dtemp = 0
        'ARg.DrawString(("rainfall = " & dhumid & "mm"), nfont, Brushes.Lime, 358, 0)
        'ARg.DrawString(("rainfall = " & dhumid & "mm"), nfont, Brushes.Lime, 358, 1046)
        ARg.DrawString(("air pressure = " & dtemp & "mb"), nfont, Brushes.Crimson, 1000, 0)
        ARg.DrawString(("air pressure = " & dtemp & "mb"), nfont, Brushes.Crimson, 1000, 1046)
        Dim curtime = TimeSpan.FromMinutes(display_span_time.TotalMinutes - (display_span_time.TotalMinutes * (cursorTH - 65) / 1438))
        Dim tnl = tn.Subtract(curtime)  'graph mid time at cursor
        ARg.DrawString(tnl.ToString("h:mm tt..d MMM yy"), nfont, Brushes.Cyan, 650, 0)  'top
        ARg.DrawString(tnl.ToString("h:mm tt..d MMM yy"), nfont, Brushes.Cyan, 650, 1046)  'bottom
        ArduinoWeather.airrain.Image = ARfull_image
    End Sub
    Public Sub scale_air_rain()
        Try
            For i = 0 To 1439
                sairpressure(i) = airpressure(i) / 2.7
                srainfall(i) = rainfall(i) / 2.7  'scale down the display
            Next
            Dim tn = display_start_time 'righthand side current time
            Dim tnll = tn.Subtract(display_span_time)  'graph left side time
            ARgs.FillRectangle(Brushes.Black, 0, 0, 1570, 1070)
            Dim Bpen As New System.Drawing.Pen(Color.Cyan, 3)
            Dim Rpen As New System.Drawing.Pen(Color.Crimson, 3)
            Dim Gpen As New System.Drawing.Pen(Color.Lime, 3)
            ARgs.DrawLine(Bpen, 62, 22, 62, 400)  'left
            ARgs.DrawLine(Bpen, 1508, 22, 1508, 400)  'right
            ARgs.DrawLine(Bpen, 62, 22, 1508, 22)   'top
            ARgs.DrawLine(Bpen, 62, 116, 1508, 116)
            ARgs.DrawLine(Bpen, 62, 211, 1508, 211)  'middle
            ARgs.DrawLine(Bpen, 62, 306, 1508, 306)
            ARgs.DrawLine(Bpen, 62, 400, 1508, 400)  'bottom
            Dim nfont As New System.Drawing.Font("arial", 16, FontStyle.Regular)
            ARgs.DrawString(tnll.ToString("h:mm tt..d MMM yy"), nfont, Brushes.Cyan, 58, 401)
            ARgs.DrawString(tn.ToString("h:mm tt..d MMM yy"), nfont, Brushes.Cyan, 1310, 401)
            ARgs.DrawString(tnll.ToString("h:mm tt..d MMM yy"), nfont, Brushes.Cyan, 58, 0)
            ARgs.DrawString(tn.ToString("h:mm tt..d MMM yy"), nfont, Brushes.Cyan, 1310, 0)
            For i = 1439 To 1 Step -1
                If (sairpressure(i - 1) > 1023 Or sairpressure(i) > 1023) Then
                Else
                    ARgs.DrawLine(Rpen, 63 + i, 400 - sairpressure(i - 1), 64 + i, 400 - sairpressure(i))
                End If
                If (srainfall(i - 1) > 1023 Or srainfall(i) > 1023) Then
                Else
                    ARgs.DrawLine(Gpen, 63 + i, 400 - srainfall(i - 1), 64 + i, 400 - srainfall(i))
                End If
            Next
            ARgs.DrawString("1070", nfont, Brushes.Crimson, 8, 10)
            ARgs.DrawString("1040", nfont, Brushes.Crimson, 8, 96)
            ARgs.DrawString("1010", nfont, Brushes.Crimson, 8, 190)
            ARgs.DrawString("980", nfont, Brushes.Crimson, 20, 286)
            ARgs.DrawString("950", nfont, Brushes.Crimson, 20, 380)  'all the left
            ARgs.DrawString("1070", nfont, Brushes.Crimson, 1508, 10)
            ARgs.DrawString("1040", nfont, Brushes.Crimson, 1508, 96)
            ARgs.DrawString("1010", nfont, Brushes.Crimson, 1508, 190)
            ARgs.DrawString("980", nfont, Brushes.Crimson, 1508, 286)
            ARgs.DrawString("950", nfont, Brushes.Crimson, 1508, 380)  'all the right
            'ARgs.DrawString("100", nfont, Brushes.Lime, 20, 30)
            'ARgs.DrawString("75", nfont, Brushes.Lime, 30, 116)
            'ARgs.DrawString("50", nfont, Brushes.Lime, 30, 210)
            'ARgs.DrawString("25", nfont, Brushes.Lime, 30, 306)
            'ARgs.DrawString("0", nfont, Brushes.Lime, 40, 400)  'all the left
            'ARgs.DrawString("100", nfont, Brushes.Lime, 1508, 30)
            'ARgs.DrawString("75", nfont, Brushes.Lime, 1508, 116)
            'Rgs.DrawString("50", nfont, Brushes.Lime, 1508, 210)
            'ARgs.DrawString("25", nfont, Brushes.Lime, 1508, 306)
            'ARgs.DrawString("0", nfont, Brushes.Lime, 1508, 400)  'all the right
            Dim Tcurser As Integer = (cursorAR / ArduinoWeather.airrain.Width) * 1570
            If Tcurser < 65 Then Tcurser = 65 'cant go further left
            If Tcurser > 1503 Then Tcurser = 1503 'cant go further right
            ARgs.DrawLine(Pens.White, Tcurser, 22, Tcurser, 400)
            Dim dtemp = (950 + (airpressure(Tcurser - 65) * 0.117)).ToString("f0")
            'Dim dhumid = (rainfall(Tcurser - 65) / 10.23).ToString("f1")
            'If dhumid > 101 Then dhumid = 0 'for blank case
            If dtemp > 1051 Then dtemp = 0
            'ARgs.DrawString(("rainfall = " & dhumid & "mm"), nfont, Brushes.Lime, 358, 0)
            'ARgs.DrawString(("rainfall = " & dhumid & "mm"), nfont, Brushes.Lime, 358, 401)
            ARgs.DrawString(("air pressure = " & dtemp & "mb"), nfont, Brushes.Crimson, 1000, 0)
            ARgs.DrawString(("air pressure = " & dtemp & "mb"), nfont, Brushes.Crimson, 1000, 401)
            Dim curtime = TimeSpan.FromMinutes(display_span_time.TotalMinutes - (display_span_time.TotalMinutes * (Tcurser - 65) / 1438))
            Dim tnl = tn.Subtract(curtime)  'graph mid time at cursor
            ARgs.DrawString(tnl.ToString("h:mm tt..d MMM yy"), nfont, Brushes.Cyan, 650, 0)  'top
            ARgs.DrawString(tnl.ToString("h:mm tt..d MMM yy"), nfont, Brushes.Cyan, 650, 401)  'bottom
            ArduinoWeather.airrain.Image = ARscale_image
        Catch ex As Exception
        End Try
    End Sub
End Class
