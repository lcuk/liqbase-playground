VERSION 5.00
Begin VB.Form liqmap_select 
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
   Begin VB.CommandButton Command2 
      BackColor       =   &H00004000&
      Caption         =   "Select"
      BeginProperty Font 
         Name            =   "Trebuchet MS"
         Size            =   24
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Left            =   8910
      Style           =   1  'Graphical
      TabIndex        =   4
      Top             =   6480
      Width           =   3105
   End
   Begin VB.CommandButton cmdrefresh 
      BackColor       =   &H00404000&
      Caption         =   "Refresh"
      BeginProperty Font 
         Name            =   "Trebuchet MS"
         Size            =   18
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Left            =   6000
      Style           =   1  'Graphical
      TabIndex        =   3
      Top             =   6480
      Width           =   2865
   End
   Begin VB.PictureBox Picture1 
      BackColor       =   &H00404080&
      BorderStyle     =   0  'None
      Height          =   6495
      Left            =   0
      ScaleHeight     =   6495
      ScaleWidth      =   12015
      TabIndex        =   1
      Top             =   720
      Width           =   12015
      Begin liqmap.liqmap_selectitem itemx 
         Height          =   795
         Left            =   0
         TabIndex        =   2
         Top             =   0
         Width           =   12045
         _ExtentX        =   21246
         _ExtentY        =   1402
      End
   End
   Begin VB.Label title 
      BackColor       =   &H00808080&
      Caption         =   "liqmap map select"
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
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   12015
   End
End
Attribute VB_Name = "liqmap_select"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub cmdall_Click()

End Sub
