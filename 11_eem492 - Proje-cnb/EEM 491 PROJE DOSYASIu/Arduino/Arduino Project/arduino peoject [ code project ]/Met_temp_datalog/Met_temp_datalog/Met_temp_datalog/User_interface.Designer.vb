<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class User_interface
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
        Me.Timer1 = New System.Windows.Forms.Timer(Me.components)
        Me.Previous = New System.Windows.Forms.Button
        Me.Current = New System.Windows.Forms.Button
        Me.Dispnext = New System.Windows.Forms.Button
        Me.Label2 = New System.Windows.Forms.Label
        Me.PictureBox1 = New System.Windows.Forms.PictureBox
        CType(Me.PictureBox1, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'Timer1
        '
        Me.Timer1.Interval = 50000
        '
        'Previous
        '
        Me.Previous.Location = New System.Drawing.Point(22, 667)
        Me.Previous.Name = "Previous"
        Me.Previous.Size = New System.Drawing.Size(107, 23)
        Me.Previous.TabIndex = 16
        Me.Previous.Text = "display previous"
        Me.Previous.UseVisualStyleBackColor = True
        '
        'Current
        '
        Me.Current.Location = New System.Drawing.Point(264, 667)
        Me.Current.Name = "Current"
        Me.Current.Size = New System.Drawing.Size(83, 23)
        Me.Current.TabIndex = 15
        Me.Current.Text = "show current"
        Me.Current.UseVisualStyleBackColor = True
        '
        'Dispnext
        '
        Me.Dispnext.Location = New System.Drawing.Point(160, 667)
        Me.Dispnext.Name = "Dispnext"
        Me.Dispnext.Size = New System.Drawing.Size(75, 23)
        Me.Dispnext.TabIndex = 14
        Me.Dispnext.Text = "display next"
        Me.Dispnext.UseVisualStyleBackColor = True
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label2.Location = New System.Drawing.Point(449, 667)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(104, 20)
        Me.Label2.TabIndex = 13
        Me.Label2.Text = "air pressure"
        '
        'PictureBox1
        '
        Me.PictureBox1.Location = New System.Drawing.Point(0, 2)
        Me.PictureBox1.Name = "PictureBox1"
        Me.PictureBox1.Size = New System.Drawing.Size(1015, 650)
        Me.PictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage
        Me.PictureBox1.TabIndex = 17
        Me.PictureBox1.TabStop = False
        '
        'User_interface
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(1016, 741)
        Me.Controls.Add(Me.PictureBox1)
        Me.Controls.Add(Me.Previous)
        Me.Controls.Add(Me.Current)
        Me.Controls.Add(Me.Dispnext)
        Me.Controls.Add(Me.Label2)
        Me.Name = "User_interface"
        Me.Text = "Met_temp_datalog"
        CType(Me.PictureBox1, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents Timer1 As System.Windows.Forms.Timer
    Friend WithEvents Previous As System.Windows.Forms.Button
    Friend WithEvents Current As System.Windows.Forms.Button
    Friend WithEvents Dispnext As System.Windows.Forms.Button
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents PictureBox1 As System.Windows.Forms.PictureBox

End Class
