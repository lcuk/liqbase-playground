VERSION 5.00
Begin VB.Form liqpostcard_intro 
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
   Begin VB.TextBox recipient 
      BeginProperty Font 
         Name            =   "Trebuchet MS"
         Size            =   26.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   765
      Left            =   840
      TabIndex        =   8
      Text            =   "liquid@gmail.com"
      Top             =   6360
      Width           =   7545
   End
   Begin VB.PictureBox picfront 
      BackColor       =   &H00000040&
      Height          =   2805
      Left            =   300
      ScaleHeight     =   2745
      ScaleWidth      =   5475
      TabIndex        =   1
      Top             =   1680
      Width           =   5535
   End
   Begin VB.PictureBox massageback 
      BackColor       =   &H00000040&
      Height          =   2805
      Left            =   6270
      ScaleHeight     =   2745
      ScaleWidth      =   5475
      TabIndex        =   0
      Top             =   1680
      Width           =   5535
   End
   Begin VB.Label cmdmessagewrite 
      Alignment       =   2  'Center
      BackColor       =   &H00400000&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "Write"
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
      Left            =   6270
      TabIndex        =   10
      Top             =   4500
      Width           =   2655
   End
   Begin VB.Label Label5 
      BackColor       =   &H00404000&
      Caption         =   "Recipient"
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
      Height          =   495
      Left            =   840
      TabIndex        =   9
      Top             =   5850
      Width           =   5535
   End
   Begin VB.Label cmdmessagedraw 
      Alignment       =   2  'Center
      BackColor       =   &H00400000&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "Draw"
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
      Left            =   9150
      TabIndex        =   7
      Top             =   4500
      Width           =   2655
   End
   Begin VB.Label cmdpicchoose 
      Alignment       =   2  'Center
      BackColor       =   &H00400000&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "Choose"
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
      Left            =   1680
      TabIndex        =   6
      Top             =   4500
      Width           =   2655
   End
   Begin VB.Label cmdsend 
      Alignment       =   2  'Center
      BackColor       =   &H00004000&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "Send"
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
      Height          =   945
      Left            =   8610
      TabIndex        =   5
      Top             =   6270
      Width           =   3405
   End
   Begin VB.Label pichead 
      BackColor       =   &H00404000&
      Caption         =   "Picture"
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
      Height          =   555
      Left            =   300
      TabIndex        =   4
      Top             =   1110
      Width           =   5535
   End
   Begin VB.Label messagehead 
      BackColor       =   &H00404000&
      Caption         =   "Message"
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
      Height          =   555
      Left            =   6270
      TabIndex        =   3
      Top             =   1110
      Width           =   5535
   End
   Begin VB.Label title 
      BackColor       =   &H00004040&
      Caption         =   "postcard :: send to a loved one"
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
      Height          =   855
      Left            =   0
      TabIndex        =   2
      Top             =   0
      Width           =   12015
   End
End
Attribute VB_Name = "liqpostcard_intro"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub cmdall_Click()

End Sub
