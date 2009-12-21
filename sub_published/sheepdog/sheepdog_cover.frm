VERSION 5.00
Begin VB.Form sheepdog_cover 
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
   Begin VB.Label cmdoptions 
      Alignment       =   2  'Center
      BackColor       =   &H00404000&
      Caption         =   "Options"
      BeginProperty Font 
         Name            =   "Trebuchet MS"
         Size            =   36
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   945
      Left            =   1470
      TabIndex        =   7
      Top             =   5550
      Width           =   3705
   End
   Begin VB.Label cmdplay 
      Alignment       =   2  'Center
      BackColor       =   &H00004000&
      Caption         =   "Play"
      BeginProperty Font 
         Name            =   "Trebuchet MS"
         Size            =   36
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   945
      Left            =   6630
      TabIndex        =   6
      Top             =   5550
      Width           =   3705
   End
   Begin VB.Image preview 
      BorderStyle     =   1  'Fixed Single
      Height          =   2775
      Left            =   6240
      Stretch         =   -1  'True
      Top             =   2490
      Width           =   4425
   End
   Begin VB.Label slidetext1 
      BackColor       =   &H00000000&
      Caption         =   "simple accelerometer base game"
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
      TabIndex        =   5
      Top             =   3390
      Width           =   6645
   End
   Begin VB.Label slidetext2 
      BackColor       =   &H00000000&
      Caption         =   "get all the sheep into the pen"
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
      Width           =   6645
   End
   Begin VB.Label slidetext3 
      BackColor       =   &H00000000&
      Caption         =   "up against the clock"
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
      TabIndex        =   3
      Top             =   4620
      Width           =   6645
   End
   Begin VB.Label author 
      BackColor       =   &H00000000&
      Caption         =   "by Gary Birkett and Kathy Smith"
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
      Width           =   11475
   End
   Begin VB.Label appname 
      BackColor       =   &H00000000&
      Caption         =   "sheepdog"
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
      Width           =   9660
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
Attribute VB_Name = "sheepdog_cover"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub cmdall_Click()

End Sub

Private Sub cmdinvert_Click()

End Sub

