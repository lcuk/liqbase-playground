VERSION 5.00
Begin VB.Form liqpostcard_ready 
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
   Begin VB.PictureBox picback 
      Height          =   3615
      Left            =   6090
      ScaleHeight     =   3555
      ScaleWidth      =   5475
      TabIndex        =   5
      Top             =   1680
      Width           =   5535
   End
   Begin VB.PictureBox picfront 
      Height          =   3615
      Left            =   300
      ScaleHeight     =   3555
      ScaleWidth      =   5475
      TabIndex        =   4
      Top             =   1680
      Width           =   5535
   End
   Begin VB.Label Label3 
      BackColor       =   &H00004040&
      Caption         =   "postcard :: Ready to send"
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
      TabIndex        =   6
      Top             =   0
      Width           =   12015
   End
   Begin VB.Label Label2 
      BackColor       =   &H00404000&
      Caption         =   "Back"
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
      Left            =   6090
      TabIndex        =   3
      Top             =   1110
      Width           =   5505
   End
   Begin VB.Label Label1 
      BackColor       =   &H00404000&
      Caption         =   "Front"
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
      TabIndex        =   2
      Top             =   1110
      Width           =   5535
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
      Height          =   1215
      Left            =   8370
      TabIndex        =   1
      Top             =   5700
      Width           =   3405
   End
   Begin VB.Label cmddiscard 
      Alignment       =   2  'Center
      BackColor       =   &H00000040&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "Discard"
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
      Height          =   1215
      Left            =   5130
      TabIndex        =   0
      Top             =   5700
      Width           =   3195
   End
End
Attribute VB_Name = "liqpostcard_ready"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub cmdall_Click()

End Sub
