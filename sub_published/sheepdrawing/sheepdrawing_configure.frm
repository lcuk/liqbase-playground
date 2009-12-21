VERSION 5.00
Begin VB.Form sheepdrawing_configure 
   BackColor       =   &H00000000&
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Base Form"
   ClientHeight    =   7200
   ClientLeft      =   45
   ClientTop       =   360
   ClientWidth     =   12015
   BeginProperty Font 
      Name            =   "Trebuchet MS"
      Size            =   9.75
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   LinkTopic       =   "frmBase800x480"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   7200
   ScaleWidth      =   12015
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox txtthread 
      BackColor       =   &H00400000&
      BeginProperty Font 
         Name            =   "Trebuchet MS"
         Size            =   24
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   795
      Left            =   4620
      TabIndex        =   8
      Text            =   "threadid"
      Top             =   5190
      Width           =   7005
   End
   Begin VB.TextBox txtpassword 
      BackColor       =   &H00400000&
      BeginProperty Font 
         Name            =   "Trebuchet MS"
         Size            =   24
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   795
      IMEMode         =   3  'DISABLE
      Left            =   4620
      PasswordChar    =   "*"
      TabIndex        =   7
      Text            =   "password"
      Top             =   3810
      Width           =   7005
   End
   Begin VB.TextBox txtusername 
      BackColor       =   &H00400000&
      BeginProperty Font 
         Name            =   "Trebuchet MS"
         Size            =   24
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   795
      Left            =   4620
      TabIndex        =   6
      Text            =   "username"
      Top             =   2400
      Width           =   7005
   End
   Begin VB.Label slidetext1 
      BackColor       =   &H00000000&
      Caption         =   "talk.maemo.org username"
      BeginProperty Font 
         Name            =   "Trebuchet MS"
         Size            =   15.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   465
      Left            =   360
      TabIndex        =   5
      Top             =   2610
      Width           =   3885
   End
   Begin VB.Label slidetext2 
      BackColor       =   &H00000000&
      Caption         =   "talk.maemo.org password"
      BeginProperty Font 
         Name            =   "Trebuchet MS"
         Size            =   15.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   465
      Left            =   390
      TabIndex        =   4
      Top             =   3990
      Width           =   3855
   End
   Begin VB.Label slidetext3 
      BackColor       =   &H00000000&
      Caption         =   "thread id"
      BeginProperty Font 
         Name            =   "Trebuchet MS"
         Size            =   15.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   465
      Left            =   480
      TabIndex        =   3
      Top             =   5280
      Width           =   3765
   End
   Begin VB.Label author 
      BackColor       =   &H00000000&
      Caption         =   "configure your sheep!"
      BeginProperty Font 
         Name            =   "Trebuchet MS"
         Size            =   27.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   735
      Left            =   360
      TabIndex        =   2
      Top             =   1260
      Width           =   10455
   End
   Begin VB.Label head 
      BackColor       =   &H00000000&
      Caption         =   "sheepdrawing configure"
      BeginProperty Font 
         Name            =   "Trebuchet MS"
         Size            =   48
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H0000FFFF&
      Height          =   1215
      Left            =   270
      TabIndex        =   1
      Top             =   0
      Width           =   11700
   End
   Begin VB.Label Label3 
      Alignment       =   2  'Center
      BackColor       =   &H00000000&
      Caption         =   "open source comes from the heart.  please donate to all projects."
      BeginProperty Font 
         Name            =   "Trebuchet MS"
         Size            =   15.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   465
      Left            =   210
      TabIndex        =   0
      Top             =   6690
      Width           =   11475
   End
End
Attribute VB_Name = "sheepdrawing_configure"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub cmdall_Click()

End Sub

Private Sub cmdinvert_Click()

End Sub
