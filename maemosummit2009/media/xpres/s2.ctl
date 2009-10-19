VERSION 5.00
Begin VB.UserControl s2 
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
      TabIndex        =   4
      Top             =   5340
      Width           =   12015
   End
   Begin VB.Label Label5 
      BackColor       =   &H00000000&
      Caption         =   "A different approach"
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
      Left            =   2550
      TabIndex        =   3
      Top             =   4080
      Width           =   6975
   End
   Begin VB.Label Label4 
      BackColor       =   &H00000000&
      Caption         =   "Simple API, limited to the essentials"
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
      Left            =   2550
      TabIndex        =   2
      Top             =   3180
      Width           =   6975
   End
   Begin VB.Label Label2 
      BackColor       =   &H00000000&
      Caption         =   "Scalable rendering engine, no wasted cycles"
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
      Left            =   2520
      TabIndex        =   1
      Top             =   2280
      Width           =   6975
   End
   Begin VB.Label Label3 
      BackColor       =   &H00000000&
      Caption         =   "Design goals"
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
      Left            =   270
      TabIndex        =   0
      Top             =   630
      Width           =   11445
   End
End
Attribute VB_Name = "s2"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

