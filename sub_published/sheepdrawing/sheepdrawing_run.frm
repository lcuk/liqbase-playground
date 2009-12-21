VERSION 5.00
Begin VB.Form sheepdrawing_run 
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
   Begin VB.Label Label1 
      Alignment       =   2  'Center
      BackColor       =   &H00004040&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "color"
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
      Height          =   1875
      Left            =   10920
      TabIndex        =   6
      Top             =   3270
      Width           =   1095
   End
   Begin VB.Label cmdselect 
      Alignment       =   2  'Center
      BackColor       =   &H00400000&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "select"
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
      Height          =   1365
      Left            =   10920
      TabIndex        =   5
      Top             =   5160
      Width           =   1095
   End
   Begin VB.Label cmdclear 
      Alignment       =   2  'Center
      BackColor       =   &H00000040&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "clear"
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
      Height          =   1305
      Left            =   10920
      TabIndex        =   4
      Top             =   1980
      Width           =   1095
   End
   Begin VB.Label cmdundo 
      Alignment       =   2  'Center
      BackColor       =   &H00400040&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "undo"
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
      Height          =   1095
      Left            =   10920
      TabIndex        =   3
      Top             =   900
      Width           =   1095
   End
   Begin VB.Label cmdaccept 
      Alignment       =   2  'Center
      BackColor       =   &H00004000&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "Upload"
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
      Top             =   6510
      Width           =   3105
   End
   Begin VB.Label title 
      BackColor       =   &H00808080&
      Caption         =   "Draw your sheep"
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
      Height          =   885
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   12015
   End
   Begin VB.Label backplane 
      Alignment       =   2  'Center
      BackColor       =   &H00404000&
      Caption         =   "backplane"
      ForeColor       =   &H000000FF&
      Height          =   6330
      Left            =   0
      TabIndex        =   2
      Top             =   870
      Width           =   12015
   End
End
Attribute VB_Name = "sheepdrawing_run"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub cmdall_Click()

End Sub

Private Sub cmdinvert_Click()
End Sub
