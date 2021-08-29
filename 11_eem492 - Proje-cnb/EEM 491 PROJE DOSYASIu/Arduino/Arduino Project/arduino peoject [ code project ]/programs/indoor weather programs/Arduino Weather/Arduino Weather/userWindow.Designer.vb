<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class ArduinoWeather
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(ArduinoWeather))
        Me.comdisplay = New System.Windows.Forms.TextBox
        Me.GroupBox1 = New System.Windows.Forms.GroupBox
        Me.RadioButton9 = New System.Windows.Forms.RadioButton
        Me.RadioButton8 = New System.Windows.Forms.RadioButton
        Me.RadioButton7 = New System.Windows.Forms.RadioButton
        Me.RadioButton6 = New System.Windows.Forms.RadioButton
        Me.RadioButton5 = New System.Windows.Forms.RadioButton
        Me.RadioButton4 = New System.Windows.Forms.RadioButton
        Me.RadioButton3 = New System.Windows.Forms.RadioButton
        Me.RadioButton2 = New System.Windows.Forms.RadioButton
        Me.RadioButton1 = New System.Windows.Forms.RadioButton
        Me.temphumid = New System.Windows.Forms.PictureBox
        Me.zoomTH = New System.Windows.Forms.Button
        Me.clickoffset = New System.Windows.Forms.Label
        Me.airrain = New System.Windows.Forms.PictureBox
        Me.display_noconnect = New System.Windows.Forms.Timer(Me.components)
        Me.zoomAR = New System.Windows.Forms.Button
        Me.overflow = New System.Windows.Forms.Label
        Me.displayarchive = New System.Windows.Forms.Button
        Me.archivedisplay = New System.Windows.Forms.ComboBox
        Me.hasbeenoffset = New System.Windows.Forms.Label
        Me.MenuStrip1 = New System.Windows.Forms.MenuStrip
        Me.HelpToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem
        Me.HelpToolStripMenuItem1 = New System.Windows.Forms.ToolStripMenuItem
        Me.GroupBox1.SuspendLayout()
        CType(Me.temphumid, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.airrain, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.MenuStrip1.SuspendLayout()
        Me.SuspendLayout()
        '
        'comdisplay
        '
        Me.comdisplay.BackColor = System.Drawing.SystemColors.ActiveCaptionText
        Me.comdisplay.Location = New System.Drawing.Point(1, 35)
        Me.comdisplay.Multiline = True
        Me.comdisplay.Name = "comdisplay"
        Me.comdisplay.ReadOnly = True
        Me.comdisplay.Size = New System.Drawing.Size(102, 89)
        Me.comdisplay.TabIndex = 3
        '
        'GroupBox1
        '
        Me.GroupBox1.Controls.Add(Me.RadioButton9)
        Me.GroupBox1.Controls.Add(Me.RadioButton8)
        Me.GroupBox1.Controls.Add(Me.RadioButton7)
        Me.GroupBox1.Controls.Add(Me.RadioButton6)
        Me.GroupBox1.Controls.Add(Me.RadioButton5)
        Me.GroupBox1.Controls.Add(Me.RadioButton4)
        Me.GroupBox1.Controls.Add(Me.RadioButton3)
        Me.GroupBox1.Controls.Add(Me.RadioButton2)
        Me.GroupBox1.Controls.Add(Me.RadioButton1)
        Me.GroupBox1.Location = New System.Drawing.Point(1, 175)
        Me.GroupBox1.Name = "GroupBox1"
        Me.GroupBox1.Size = New System.Drawing.Size(102, 231)
        Me.GroupBox1.TabIndex = 7
        Me.GroupBox1.TabStop = False
        Me.GroupBox1.Text = "display span"
        '
        'RadioButton9
        '
        Me.RadioButton9.AutoSize = True
        Me.RadioButton9.Location = New System.Drawing.Point(11, 203)
        Me.RadioButton9.Name = "RadioButton9"
        Me.RadioButton9.Size = New System.Drawing.Size(57, 17)
        Me.RadioButton9.TabIndex = 10
        Me.RadioButton9.TabStop = True
        Me.RadioButton9.Text = "4week"
        Me.RadioButton9.UseVisualStyleBackColor = True
        '
        'RadioButton8
        '
        Me.RadioButton8.AutoSize = True
        Me.RadioButton8.Location = New System.Drawing.Point(11, 180)
        Me.RadioButton8.Name = "RadioButton8"
        Me.RadioButton8.Size = New System.Drawing.Size(60, 17)
        Me.RadioButton8.TabIndex = 9
        Me.RadioButton8.TabStop = True
        Me.RadioButton8.Text = "2 week"
        Me.RadioButton8.UseVisualStyleBackColor = True
        '
        'RadioButton7
        '
        Me.RadioButton7.AutoSize = True
        Me.RadioButton7.Location = New System.Drawing.Point(12, 157)
        Me.RadioButton7.Name = "RadioButton7"
        Me.RadioButton7.Size = New System.Drawing.Size(51, 17)
        Me.RadioButton7.TabIndex = 8
        Me.RadioButton7.TabStop = True
        Me.RadioButton7.Text = "7 day"
        Me.RadioButton7.UseVisualStyleBackColor = True
        '
        'RadioButton6
        '
        Me.RadioButton6.AutoSize = True
        Me.RadioButton6.Location = New System.Drawing.Point(12, 134)
        Me.RadioButton6.Name = "RadioButton6"
        Me.RadioButton6.Size = New System.Drawing.Size(51, 17)
        Me.RadioButton6.TabIndex = 7
        Me.RadioButton6.Text = "4 day"
        Me.RadioButton6.UseVisualStyleBackColor = True
        '
        'RadioButton5
        '
        Me.RadioButton5.AutoSize = True
        Me.RadioButton5.Location = New System.Drawing.Point(12, 111)
        Me.RadioButton5.Name = "RadioButton5"
        Me.RadioButton5.Size = New System.Drawing.Size(51, 17)
        Me.RadioButton5.TabIndex = 6
        Me.RadioButton5.TabStop = True
        Me.RadioButton5.Text = "2 day"
        Me.RadioButton5.UseVisualStyleBackColor = True
        '
        'RadioButton4
        '
        Me.RadioButton4.AutoSize = True
        Me.RadioButton4.Location = New System.Drawing.Point(11, 88)
        Me.RadioButton4.Name = "RadioButton4"
        Me.RadioButton4.Size = New System.Drawing.Size(61, 17)
        Me.RadioButton4.TabIndex = 5
        Me.RadioButton4.TabStop = True
        Me.RadioButton4.Text = "24 hour"
        Me.RadioButton4.UseVisualStyleBackColor = True
        '
        'RadioButton3
        '
        Me.RadioButton3.AutoSize = True
        Me.RadioButton3.Location = New System.Drawing.Point(11, 65)
        Me.RadioButton3.Name = "RadioButton3"
        Me.RadioButton3.Size = New System.Drawing.Size(61, 17)
        Me.RadioButton3.TabIndex = 4
        Me.RadioButton3.TabStop = True
        Me.RadioButton3.Text = "12 hour"
        Me.RadioButton3.UseVisualStyleBackColor = True
        '
        'RadioButton2
        '
        Me.RadioButton2.AutoSize = True
        Me.RadioButton2.Location = New System.Drawing.Point(11, 42)
        Me.RadioButton2.Name = "RadioButton2"
        Me.RadioButton2.Size = New System.Drawing.Size(55, 17)
        Me.RadioButton2.TabIndex = 3
        Me.RadioButton2.TabStop = True
        Me.RadioButton2.Text = "8 hour"
        Me.RadioButton2.UseVisualStyleBackColor = True
        '
        'RadioButton1
        '
        Me.RadioButton1.AutoSize = True
        Me.RadioButton1.Checked = True
        Me.RadioButton1.Location = New System.Drawing.Point(12, 19)
        Me.RadioButton1.Name = "RadioButton1"
        Me.RadioButton1.Size = New System.Drawing.Size(55, 17)
        Me.RadioButton1.TabIndex = 2
        Me.RadioButton1.TabStop = True
        Me.RadioButton1.Text = "4 hour"
        Me.RadioButton1.UseVisualStyleBackColor = True
        '
        'temphumid
        '
        Me.temphumid.Cursor = System.Windows.Forms.Cursors.SizeNS
        Me.temphumid.Location = New System.Drawing.Point(119, 6)
        Me.temphumid.Name = "temphumid"
        Me.temphumid.Size = New System.Drawing.Size(885, 232)
        Me.temphumid.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage
        Me.temphumid.TabIndex = 8
        Me.temphumid.TabStop = False
        '
        'zoomTH
        '
        Me.zoomTH.Location = New System.Drawing.Point(1, 421)
        Me.zoomTH.Name = "zoomTH"
        Me.zoomTH.Size = New System.Drawing.Size(102, 34)
        Me.zoomTH.TabIndex = 9
        Me.zoomTH.Text = "expand " & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10) & "temp-humid"
        Me.zoomTH.UseVisualStyleBackColor = True
        '
        'clickoffset
        '
        Me.clickoffset.AutoSize = True
        Me.clickoffset.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.clickoffset.Location = New System.Drawing.Point(479, 241)
        Me.clickoffset.Name = "clickoffset"
        Me.clickoffset.Size = New System.Drawing.Size(107, 15)
        Me.clickoffset.TabIndex = 10
        Me.clickoffset.Text = "click to offset display"
        '
        'airrain
        '
        Me.airrain.Cursor = System.Windows.Forms.Cursors.SizeNS
        Me.airrain.Location = New System.Drawing.Point(119, 259)
        Me.airrain.Name = "airrain"
        Me.airrain.Size = New System.Drawing.Size(885, 232)
        Me.airrain.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage
        Me.airrain.TabIndex = 11
        Me.airrain.TabStop = False
        '
        'display_noconnect
        '
        Me.display_noconnect.Interval = 10000
        '
        'zoomAR
        '
        Me.zoomAR.Location = New System.Drawing.Point(1, 470)
        Me.zoomAR.Name = "zoomAR"
        Me.zoomAR.Size = New System.Drawing.Size(102, 34)
        Me.zoomAR.TabIndex = 12
        Me.zoomAR.Text = "expand" & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10) & "air_rain"
        Me.zoomAR.UseVisualStyleBackColor = True
        '
        'overflow
        '
        Me.overflow.AutoSize = True
        Me.overflow.Font = New System.Drawing.Font("Microsoft Sans Serif", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.overflow.ForeColor = System.Drawing.Color.Red
        Me.overflow.Location = New System.Drawing.Point(-2, 517)
        Me.overflow.Name = "overflow"
        Me.overflow.Size = New System.Drawing.Size(0, 13)
        Me.overflow.TabIndex = 13
        '
        'displayarchive
        '
        Me.displayarchive.Font = New System.Drawing.Font("Microsoft Sans Serif", 8.25!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.displayarchive.ForeColor = System.Drawing.SystemColors.ControlText
        Me.displayarchive.Location = New System.Drawing.Point(1, 546)
        Me.displayarchive.Name = "displayarchive"
        Me.displayarchive.Size = New System.Drawing.Size(102, 34)
        Me.displayarchive.TabIndex = 14
        Me.displayarchive.Text = "display" & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10) & "archived file"
        Me.displayarchive.UseVisualStyleBackColor = True
        '
        'archivedisplay
        '
        Me.archivedisplay.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.archivedisplay.Font = New System.Drawing.Font("Microsoft Sans Serif", 8.25!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.archivedisplay.FormattingEnabled = True
        Me.archivedisplay.Location = New System.Drawing.Point(1, 596)
        Me.archivedisplay.Name = "archivedisplay"
        Me.archivedisplay.Size = New System.Drawing.Size(102, 21)
        Me.archivedisplay.TabIndex = 15
        '
        'hasbeenoffset
        '
        Me.hasbeenoffset.AutoSize = True
        Me.hasbeenoffset.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.hasbeenoffset.ForeColor = System.Drawing.Color.Red
        Me.hasbeenoffset.Location = New System.Drawing.Point(705, 240)
        Me.hasbeenoffset.Name = "hasbeenoffset"
        Me.hasbeenoffset.Size = New System.Drawing.Size(85, 15)
        Me.hasbeenoffset.TabIndex = 16
        Me.hasbeenoffset.Text = "display offset to "
        '
        'MenuStrip1
        '
        Me.MenuStrip1.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.HelpToolStripMenuItem, Me.HelpToolStripMenuItem1})
        Me.MenuStrip1.Location = New System.Drawing.Point(0, 0)
        Me.MenuStrip1.Name = "MenuStrip1"
        Me.MenuStrip1.Size = New System.Drawing.Size(1016, 24)
        Me.MenuStrip1.TabIndex = 17
        Me.MenuStrip1.Text = "MenuStrip1"
        '
        'HelpToolStripMenuItem
        '
        Me.HelpToolStripMenuItem.Name = "HelpToolStripMenuItem"
        Me.HelpToolStripMenuItem.Size = New System.Drawing.Size(40, 20)
        Me.HelpToolStripMenuItem.Text = "Files"
        '
        'HelpToolStripMenuItem1
        '
        Me.HelpToolStripMenuItem1.Name = "HelpToolStripMenuItem1"
        Me.HelpToolStripMenuItem1.Size = New System.Drawing.Size(39, 20)
        Me.HelpToolStripMenuItem1.Text = "help"
        '
        'ArduinoWeather
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(1016, 708)
        Me.Controls.Add(Me.hasbeenoffset)
        Me.Controls.Add(Me.archivedisplay)
        Me.Controls.Add(Me.displayarchive)
        Me.Controls.Add(Me.overflow)
        Me.Controls.Add(Me.zoomAR)
        Me.Controls.Add(Me.airrain)
        Me.Controls.Add(Me.clickoffset)
        Me.Controls.Add(Me.zoomTH)
        Me.Controls.Add(Me.temphumid)
        Me.Controls.Add(Me.GroupBox1)
        Me.Controls.Add(Me.comdisplay)
        Me.Controls.Add(Me.MenuStrip1)
        Me.Icon = CType(resources.GetObject("$this.Icon"), System.Drawing.Icon)
        Me.MainMenuStrip = Me.MenuStrip1
        Me.Name = "ArduinoWeather"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.Manual
        Me.Text = "Arduino Weather"
        Me.GroupBox1.ResumeLayout(False)
        Me.GroupBox1.PerformLayout()
        CType(Me.temphumid, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.airrain, System.ComponentModel.ISupportInitialize).EndInit()
        Me.MenuStrip1.ResumeLayout(False)
        Me.MenuStrip1.PerformLayout()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents comdisplay As System.Windows.Forms.TextBox
    Friend WithEvents GroupBox1 As System.Windows.Forms.GroupBox
    Friend WithEvents RadioButton9 As System.Windows.Forms.RadioButton
    Friend WithEvents RadioButton8 As System.Windows.Forms.RadioButton
    Friend WithEvents RadioButton7 As System.Windows.Forms.RadioButton
    Friend WithEvents RadioButton6 As System.Windows.Forms.RadioButton
    Friend WithEvents RadioButton5 As System.Windows.Forms.RadioButton
    Friend WithEvents RadioButton4 As System.Windows.Forms.RadioButton
    Friend WithEvents RadioButton3 As System.Windows.Forms.RadioButton
    Friend WithEvents RadioButton2 As System.Windows.Forms.RadioButton
    Friend WithEvents RadioButton1 As System.Windows.Forms.RadioButton
    Friend WithEvents temphumid As System.Windows.Forms.PictureBox
    Friend WithEvents zoomTH As System.Windows.Forms.Button
    Friend WithEvents clickoffset As System.Windows.Forms.Label
    Friend WithEvents airrain As System.Windows.Forms.PictureBox
    Friend WithEvents display_noconnect As System.Windows.Forms.Timer
    Friend WithEvents zoomAR As System.Windows.Forms.Button
    Friend WithEvents overflow As System.Windows.Forms.Label
    Friend WithEvents displayarchive As System.Windows.Forms.Button
    Friend WithEvents archivedisplay As System.Windows.Forms.ComboBox
    Friend WithEvents hasbeenoffset As System.Windows.Forms.Label
    Friend WithEvents MenuStrip1 As System.Windows.Forms.MenuStrip
    Friend WithEvents HelpToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents HelpToolStripMenuItem1 As System.Windows.Forms.ToolStripMenuItem

End Class
