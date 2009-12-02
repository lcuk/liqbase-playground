VERSION 5.00
Begin VB.UserControl liqmap_selectitem 
   BackColor       =   &H00000000&
   ClientHeight    =   795
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
   ScaleHeight     =   795
   ScaleWidth      =   12015
   Begin VB.Label lblcountry 
      BackColor       =   &H00000000&
      Caption         =   "United Kingdom"
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
      Left            =   6750
      TabIndex        =   3
      Top             =   150
      Width           =   2565
   End
   Begin VB.Label lblheight 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00000000&
      Caption         =   "960"
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
      Left            =   10680
      TabIndex        =   2
      Top             =   150
      Width           =   1155
   End
   Begin VB.Label lblwidth 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00000000&
      Caption         =   "1600"
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
      Left            =   9420
      TabIndex        =   1
      Top             =   150
      Width           =   1125
   End
   Begin VB.Label lblname 
      BackColor       =   &H00000000&
      Caption         =   "London Underground"
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
      Left            =   90
      TabIndex        =   0
      Top             =   90
      Width           =   6615
   End
End
Attribute VB_Name = "liqmap_selectitem"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

