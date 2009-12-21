VERSION 5.00
Begin VB.Form sheepdog_leveldesign 
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
   Begin VB.TextBox txttitle 
      BackColor       =   &H00400000&
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
      Height          =   735
      Left            =   1770
      TabIndex        =   6
      Text            =   "Text1"
      Top             =   930
      Width           =   9975
   End
   Begin VB.Label Label1 
      BackColor       =   &H00000000&
      Caption         =   "title"
      BeginProperty Font 
         Name            =   "Trebuchet MS"
         Size            =   20.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   660
      Left            =   420
      TabIndex        =   8
      Top             =   960
      Width           =   5790
   End
   Begin VB.Label cmdaddholes 
      Alignment       =   2  'Center
      BackColor       =   &H00404000&
      Caption         =   "add pens"
      BeginProperty Font 
         Name            =   "Trebuchet MS"
         Size            =   18
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   795
      Left            =   540
      TabIndex        =   7
      Top             =   4620
      Width           =   4965
   End
   Begin VB.Label Label3 
      BackColor       =   &H00000000&
      Caption         =   "preview"
      BeginProperty Font 
         Name            =   "Trebuchet MS"
         Size            =   20.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   660
      Left            =   6570
      TabIndex        =   5
      Top             =   2250
      Width           =   4620
   End
   Begin VB.Label cmdaddstickers 
      Alignment       =   2  'Center
      BackColor       =   &H00404000&
      Caption         =   "add stickers"
      BeginProperty Font 
         Name            =   "Trebuchet MS"
         Size            =   18
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   795
      Left            =   540
      TabIndex        =   4
      Top             =   3690
      Width           =   4965
   End
   Begin VB.Label cmdsetbackground 
      Alignment       =   2  'Center
      BackColor       =   &H00404000&
      Caption         =   "select background"
      BeginProperty Font 
         Name            =   "Trebuchet MS"
         Size            =   18
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   735
      Left            =   540
      TabIndex        =   3
      Top             =   2850
      Width           =   4965
   End
   Begin VB.Label cmdaccept 
      Alignment       =   2  'Center
      BackColor       =   &H00004000&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "save"
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
      Left            =   8910
      TabIndex        =   1
      Top             =   6480
      Width           =   3105
   End
   Begin VB.Label title 
      BackColor       =   &H00808080&
      Caption         =   "Level designer"
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
      Width           =   5955
   End
   Begin VB.Label preview 
      Alignment       =   2  'Center
      BackColor       =   &H00404040&
      Caption         =   "preview goes here, click to test"
      ForeColor       =   &H000000FF&
      Height          =   2925
      Left            =   6600
      TabIndex        =   2
      Top             =   3090
      Width           =   4635
   End
End
Attribute VB_Name = "sheepdog_leveldesign"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub cmdall_Click()

End Sub
