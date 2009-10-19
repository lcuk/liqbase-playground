VERSION 5.00
Begin VB.UserControl s3a_hardware 
   BackColor       =   &H00000000&
   ClientHeight    =   5760
   ClientLeft      =   0
   ClientTop       =   0
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
   ForeColor       =   &H00808080&
   ScaleHeight     =   5760
   ScaleWidth      =   12015
   Begin VB.Label Label4 
      Alignment       =   2  'Center
      BackColor       =   &H00000000&
      Caption         =   "Actively seeking sponsorship.  Please discuss after this presentation"
      BeginProperty Font 
         Name            =   "Trebuchet MS"
         Size            =   15.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H000000FF&
      Height          =   435
      Left            =   0
      TabIndex        =   8
      Top             =   5340
      Width           =   12015
   End
   Begin VB.Label Label3 
      BackColor       =   &H00000000&
      Caption         =   "PowerVR GL ES Graphics"
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
      Left            =   510
      TabIndex        =   7
      Top             =   4590
      Width           =   6975
   End
   Begin VB.Label Label2 
      BackColor       =   &H00000000&
      Caption         =   "GPS, Accelerometer, BT, IR"
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
      Left            =   510
      TabIndex        =   6
      Top             =   4050
      Width           =   6975
   End
   Begin VB.Label Label1 
      BackColor       =   &H00000000&
      Caption         =   "Hardware keyboard"
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
      Left            =   510
      TabIndex        =   5
      Top             =   3510
      Width           =   6975
   End
   Begin VB.Label slidepreview 
      BackColor       =   &H00000000&
      Height          =   3075
      Left            =   7890
      TabIndex        =   4
      Tag             =   "http://static.arstechnica.com/assets/2009/08/nokia_n900_640_ars-thumb-640xauto-8044.jpg"
      Top             =   1920
      Width           =   3615
   End
   Begin VB.Label slidetext3 
      BackColor       =   &H00000000&
      Caption         =   "5MP Camera"
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
      Left            =   510
      TabIndex        =   3
      Top             =   2970
      Width           =   6975
   End
   Begin VB.Label slidetext2 
      BackColor       =   &H00000000&
      Caption         =   "3g modem and phone"
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
      Left            =   510
      TabIndex        =   2
      Top             =   2430
      Width           =   6975
   End
   Begin VB.Label slidetext1 
      BackColor       =   &H00000000&
      Caption         =   "600mhz Arm Processor"
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
      Left            =   510
      TabIndex        =   1
      Top             =   1890
      Width           =   6975
   End
   Begin VB.Label slidetitle 
      BackColor       =   &H00000000&
      Caption         =   "N900 Hardware"
      BeginProperty Font 
         Name            =   "Trebuchet MS"
         Size            =   24
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H0000FFFF&
      Height          =   615
      Left            =   240
      TabIndex        =   0
      Top             =   630
      Width           =   11445
   End
End
Attribute VB_Name = "s3a_hardware"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

