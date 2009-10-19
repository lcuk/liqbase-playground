VERSION 5.00
Begin VB.Form liqslidehost 
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
   Begin VB.PictureBox backplane 
      BackColor       =   &H00404040&
      BorderStyle     =   0  'None
      Height          =   5775
      Left            =   0
      ScaleHeight     =   5775
      ScaleWidth      =   12015
      TabIndex        =   3
      Top             =   690
      Width           =   12015
      Begin VB.PictureBox allslides 
         BackColor       =   &H00400000&
         BorderStyle     =   0  'None
         Height          =   5775
         Left            =   0
         ScaleHeight     =   5775
         ScaleWidth      =   12015
         TabIndex        =   6
         Top             =   0
         Width           =   12015
      End
   End
   Begin VB.Label timer 
      Alignment       =   2  'Center
      Caption         =   "00:00"
      Height          =   285
      Left            =   9090
      TabIndex        =   5
      Top             =   180
      Width           =   1725
   End
   Begin VB.Label Label2 
      Alignment       =   2  'Center
      BackColor       =   &H00004040&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "<"
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
      Height          =   735
      Left            =   8490
      TabIndex        =   4
      Top             =   6480
      Width           =   1455
   End
   Begin VB.Label cmdaccept 
      Alignment       =   2  'Center
      BackColor       =   &H00004000&
      BorderStyle     =   1  'Fixed Single
      Caption         =   ">"
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
      Height          =   735
      Left            =   9960
      TabIndex        =   2
      Top             =   6480
      Width           =   2055
   End
   Begin VB.Label Label1 
      BackColor       =   &H00000000&
      Caption         =   "liqbase by Gary Birkett :: liquid@gmail.com"
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
      Left            =   1320
      TabIndex        =   1
      Top             =   6660
      Width           =   6975
   End
   Begin VB.Label title 
      BackColor       =   &H00808080&
      Caption         =   "maemo & liqbase"
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
      Height          =   705
      Left            =   0
      TabIndex        =   0
      Top             =   0
      UseMnemonic     =   0   'False
      Width           =   12015
   End
End
Attribute VB_Name = "liqslidehost"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub cmdall_Click()

End Sub

Private Sub cmdinvert_Click()

End Sub
