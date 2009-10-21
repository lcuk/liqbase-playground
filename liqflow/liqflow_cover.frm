VERSION 5.00
Begin VB.Form liqflow_cover 
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
   Begin VB.Label slidepreview 
      BackColor       =   &H00404040&
      Height          =   3075
      Left            =   7380
      TabIndex        =   5
      Tag             =   "liqflow_run"
      Top             =   3060
      Width           =   3615
   End
   Begin VB.Label slidetext1 
      BackColor       =   &H00000000&
      Caption         =   "fluid dynamics at your fingertips"
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
      Left            =   630
      TabIndex        =   4
      Top             =   3510
      Width           =   6645
   End
   Begin VB.Label slidetext2 
      BackColor       =   &H00000000&
      Caption         =   "natural flowing patterns"
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
      Left            =   660
      TabIndex        =   3
      Top             =   4410
      Width           =   6645
   End
   Begin VB.Label slidetext3 
      BackColor       =   &H00000000&
      Caption         =   "Accelerometer controllable"
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
      Left            =   660
      TabIndex        =   2
      Top             =   5310
      Width           =   6645
   End
   Begin VB.Label Label2 
      BackColor       =   &H00000000&
      Caption         =   "written by Gary Birkett."
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
      Left            =   630
      TabIndex        =   1
      Top             =   1350
      Width           =   10455
   End
   Begin VB.Label Label1 
      BackColor       =   &H00000000&
      Caption         =   "liqflow"
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
      Left            =   540
      TabIndex        =   0
      Top             =   90
      Width           =   9660
   End
End
Attribute VB_Name = "liqflow_cover"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub cmdall_Click()

End Sub

Private Sub cmdinvert_Click()
End Sub
