VERSION 5.00
Begin VB.UserControl t3_fish 
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
   Begin VB.Label Label3 
      BackColor       =   &H00000000&
      Caption         =   "User and Developer ready"
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
      Top             =   1950
      Width           =   6975
   End
   Begin VB.Label Label1 
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
      TabIndex        =   6
      Top             =   5340
      Width           =   12015
   End
   Begin VB.Label Label2 
      BackColor       =   &H00000000&
      Caption         =   "Bindings for qt/py/etc"
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
      Top             =   4530
      Width           =   6975
   End
   Begin VB.Label slidepreview 
      BackColor       =   &H00000000&
      Height          =   3075
      Left            =   7890
      TabIndex        =   4
      Tag             =   "*"
      Top             =   1920
      Width           =   3615
   End
   Begin VB.Label slidetext3 
      BackColor       =   &H00000000&
      Caption         =   "The Orchestra - collective data sharing"
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
      Top             =   3870
      Width           =   6975
   End
   Begin VB.Label slidetext2 
      BackColor       =   &H00000000&
      Caption         =   "dynamic HWR,OCR,Barcode meta extraction"
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
      Top             =   3210
      Width           =   6975
   End
   Begin VB.Label slidetext1 
      BackColor       =   &H00000000&
      Caption         =   "collaborative presentations"
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
      Top             =   2550
      Width           =   6975
   End
   Begin VB.Label slidetitle 
      BackColor       =   &H00000000&
      Caption         =   "The Future..."
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
Attribute VB_Name = "t3_fish"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Private Sub Label1_Click()

End Sub
