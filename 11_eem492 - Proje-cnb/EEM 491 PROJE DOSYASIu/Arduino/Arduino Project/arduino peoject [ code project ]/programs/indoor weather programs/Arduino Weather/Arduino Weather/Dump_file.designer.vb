<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Dump_files
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
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(Dump_files))
        Me.Label1 = New System.Windows.Forms.Label
        Me.Button1 = New System.Windows.Forms.Button
        Me.Label2 = New System.Windows.Forms.Label
        Me.Button2 = New System.Windows.Forms.Button
        Me.TextBox1 = New System.Windows.Forms.TextBox
        Me.Label3 = New System.Windows.Forms.Label
        Me.Button3 = New System.Windows.Forms.Button
        Me.Button4 = New System.Windows.Forms.Button
        Me.archivecontrol = New System.Windows.Forms.GroupBox
        Me.archived = New System.Windows.Forms.TextBox
        Me.clear = New System.Windows.Forms.Button
        Me.Label4 = New System.Windows.Forms.Label
        Me.Button5 = New System.Windows.Forms.Button
        Me.TextBox2 = New System.Windows.Forms.TextBox
        Me.archivecontrol.SuspendLayout()
        Me.SuspendLayout()
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Location = New System.Drawing.Point(62, 9)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(39, 13)
        Me.Label1.TabIndex = 0
        Me.Label1.Text = "Label1"
        '
        'Button1
        '
        Me.Button1.Location = New System.Drawing.Point(216, 4)
        Me.Button1.Name = "Button1"
        Me.Button1.Size = New System.Drawing.Size(92, 23)
        Me.Button1.TabIndex = 1
        Me.Button1.Text = "dump ram file"
        Me.Button1.UseVisualStyleBackColor = True
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.Location = New System.Drawing.Point(62, 48)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(72, 13)
        Me.Label2.TabIndex = 2
        Me.Label2.Text = "no files stored"
        '
        'Button2
        '
        Me.Button2.Location = New System.Drawing.Point(216, 37)
        Me.Button2.Name = "Button2"
        Me.Button2.Size = New System.Drawing.Size(92, 23)
        Me.Button2.TabIndex = 3
        Me.Button2.Text = "dump this sector"
        Me.Button2.UseVisualStyleBackColor = True
        '
        'TextBox1
        '
        Me.TextBox1.Location = New System.Drawing.Point(334, 39)
        Me.TextBox1.Name = "TextBox1"
        Me.TextBox1.Size = New System.Drawing.Size(100, 20)
        Me.TextBox1.TabIndex = 4
        Me.TextBox1.Text = "0"
        '
        'Label3
        '
        Me.Label3.AutoSize = True
        Me.Label3.BackColor = System.Drawing.SystemColors.ActiveCaptionText
        Me.Label3.Location = New System.Drawing.Point(16, 100)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(0, 13)
        Me.Label3.TabIndex = 5
        '
        'Button3
        '
        Me.Button3.Location = New System.Drawing.Point(454, 30)
        Me.Button3.Name = "Button3"
        Me.Button3.Size = New System.Drawing.Size(28, 18)
        Me.Button3.TabIndex = 6
        Me.Button3.Text = "+1"
        Me.Button3.UseVisualStyleBackColor = True
        '
        'Button4
        '
        Me.Button4.Location = New System.Drawing.Point(454, 54)
        Me.Button4.Name = "Button4"
        Me.Button4.Size = New System.Drawing.Size(28, 18)
        Me.Button4.TabIndex = 7
        Me.Button4.Text = "-1"
        Me.Button4.UseVisualStyleBackColor = True
        '
        'archivecontrol
        '
        Me.archivecontrol.Controls.Add(Me.archived)
        Me.archivecontrol.Controls.Add(Me.clear)
        Me.archivecontrol.Controls.Add(Me.Label4)
        Me.archivecontrol.Controls.Add(Me.Button5)
        Me.archivecontrol.Controls.Add(Me.TextBox2)
        Me.archivecontrol.Location = New System.Drawing.Point(551, 9)
        Me.archivecontrol.Name = "archivecontrol"
        Me.archivecontrol.Size = New System.Drawing.Size(164, 358)
        Me.archivecontrol.TabIndex = 8
        Me.archivecontrol.TabStop = False
        Me.archivecontrol.Text = "Archive controls"
        '
        'archived
        '
        Me.archived.BackColor = System.Drawing.SystemColors.ActiveCaptionText
        Me.archived.Location = New System.Drawing.Point(20, 115)
        Me.archived.Multiline = True
        Me.archived.Name = "archived"
        Me.archived.ReadOnly = True
        Me.archived.ScrollBars = System.Windows.Forms.ScrollBars.Vertical
        Me.archived.Size = New System.Drawing.Size(124, 224)
        Me.archived.TabIndex = 5
        '
        'clear
        '
        Me.clear.Location = New System.Drawing.Point(104, 86)
        Me.clear.Name = "clear"
        Me.clear.Size = New System.Drawing.Size(40, 23)
        Me.clear.TabIndex = 4
        Me.clear.Text = "clear"
        Me.clear.UseVisualStyleBackColor = True
        '
        'Label4
        '
        Me.Label4.AutoSize = True
        Me.Label4.Location = New System.Drawing.Point(17, 91)
        Me.Label4.Name = "Label4"
        Me.Label4.Size = New System.Drawing.Size(70, 13)
        Me.Label4.TabIndex = 2
        Me.Label4.Text = "Archived files"
        '
        'Button5
        '
        Me.Button5.Location = New System.Drawing.Point(28, 48)
        Me.Button5.Name = "Button5"
        Me.Button5.Size = New System.Drawing.Size(100, 23)
        Me.Button5.TabIndex = 1
        Me.Button5.Text = "archive this file"
        Me.Button5.UseVisualStyleBackColor = True
        '
        'TextBox2
        '
        Me.TextBox2.Location = New System.Drawing.Point(28, 21)
        Me.TextBox2.Name = "TextBox2"
        Me.TextBox2.Size = New System.Drawing.Size(100, 20)
        Me.TextBox2.TabIndex = 0
        Me.TextBox2.Text = "0"
        '
        'Dump_files
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(727, 379)
        Me.Controls.Add(Me.archivecontrol)
        Me.Controls.Add(Me.Button4)
        Me.Controls.Add(Me.Button3)
        Me.Controls.Add(Me.Label3)
        Me.Controls.Add(Me.TextBox1)
        Me.Controls.Add(Me.Button2)
        Me.Controls.Add(Me.Label2)
        Me.Controls.Add(Me.Button1)
        Me.Controls.Add(Me.Label1)
        Me.Icon = CType(resources.GetObject("$this.Icon"), System.Drawing.Icon)
        Me.Name = "Dump_files"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen
        Me.Text = "File management"
        Me.TopMost = True
        Me.archivecontrol.ResumeLayout(False)
        Me.archivecontrol.PerformLayout()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents Button1 As System.Windows.Forms.Button
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents Button2 As System.Windows.Forms.Button
    Friend WithEvents TextBox1 As System.Windows.Forms.TextBox
    Friend WithEvents Label3 As System.Windows.Forms.Label
    Friend WithEvents Button3 As System.Windows.Forms.Button
    Friend WithEvents Button4 As System.Windows.Forms.Button
    Friend WithEvents archivecontrol As System.Windows.Forms.GroupBox
    Friend WithEvents Label4 As System.Windows.Forms.Label
    Friend WithEvents Button5 As System.Windows.Forms.Button
    Friend WithEvents TextBox2 As System.Windows.Forms.TextBox
    Friend WithEvents clear As System.Windows.Forms.Button
    Friend WithEvents archived As System.Windows.Forms.TextBox

End Class
