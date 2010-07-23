VERSION 5.00
Begin VB.Form liqbase_about 
   BackColor       =   &H00000000&
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Base Form"
   ClientHeight    =   12015
   ClientLeft      =   45
   ClientTop       =   360
   ClientWidth     =   7200
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
   ScaleHeight     =   12015
   ScaleWidth      =   7200
   StartUpPosition =   3  'Windows Default
   Begin VB.Label Label8 
      BackColor       =   &H00000000&
      BeginProperty Font 
         Name            =   "Trebuchet MS"
         Size            =   14.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   435
      Left            =   270
      TabIndex        =   8
      Top             =   7770
      Width           =   6705
   End
   Begin VB.Label Label7 
      BackColor       =   &H00000000&
      Caption         =   "http://collabora.co.uk"
      BeginProperty Font 
         Name            =   "Trebuchet MS"
         Size            =   14.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   375
      Left            =   360
      TabIndex        =   7
      Top             =   8490
      Width           =   5835
   End
   Begin VB.Label Label5 
      BackColor       =   &H00000000&
      ForeColor       =   &H00FFFFFF&
      Height          =   375
      Left            =   330
      TabIndex        =   6
      Top             =   6720
      Width           =   6075
   End
   Begin VB.Image appicon 
      Appearance      =   0  'Flat
      Height          =   2415
      Left            =   210
      Picture         =   "liqbase_about.frx":0000
      Stretch         =   -1  'True
      Top             =   930
      Width           =   2550
   End
   Begin VB.Label Label3 
      BackColor       =   &H00000000&
      Caption         =   "http://liqbase.net"
      BeginProperty Font 
         Name            =   "Trebuchet MS"
         Size            =   14.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   375
      Left            =   360
      TabIndex        =   5
      Top             =   5880
      Width           =   5835
   End
   Begin VB.Label Label2 
      BackColor       =   &H00000000&
      Caption         =   "Like what you see?  Donate to the developers, everything is open source."
      ForeColor       =   &H00C0FFC0&
      Height          =   345
      Left            =   210
      TabIndex        =   4
      Top             =   11550
      Width           =   6885
   End
   Begin VB.Label Label6 
      BackColor       =   &H00000000&
      Caption         =   "faster than paper"
      BeginProperty Font 
         Name            =   "Trebuchet MS"
         Size            =   21.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   615
      Left            =   2880
      TabIndex        =   3
      Top             =   2160
      Width           =   3735
   End
   Begin VB.Image avatar 
      Height          =   1395
      Left            =   270
      Picture         =   "liqbase_about.frx":7E932
      Stretch         =   -1  'True
      Top             =   3630
      Width           =   1125
   End
   Begin VB.Label title 
      BackColor       =   &H00004000&
      Caption         =   "liqbase about"
      BeginProperty Font 
         Name            =   "Trebuchet MS"
         Size            =   26.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   840
      Left            =   0
      TabIndex        =   2
      Top             =   0
      Width           =   7215
   End
   Begin VB.Label Label4 
      BackColor       =   &H00000000&
      Caption         =   "liqbase"
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
      Height          =   825
      Left            =   2850
      TabIndex        =   1
      Top             =   1350
      Width           =   3285
   End
   Begin VB.Label Label1 
      BackColor       =   &H00000000&
      Caption         =   "Created by Gary Birkett (liquid@gmail.com)"
      BeginProperty Font 
         Name            =   "Trebuchet MS"
         Size            =   14.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   405
      Left            =   330
      TabIndex        =   0
      Top             =   5370
      Width           =   6435
   End
End
Attribute VB_Name = "liqbase_about"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

