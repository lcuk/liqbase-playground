VERSION 5.00
Begin VB.Form liqpostcard_template 
   BackColor       =   &H00FFFFFF&
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
   Begin VB.Label notice 
      Alignment       =   1  'Right Justify
      Caption         =   "postcard created within liqbase on maemo"
      Height          =   315
      Left            =   6300
      TabIndex        =   6
      Top             =   6840
      Width           =   5655
   End
   Begin VB.Label line4 
      BackColor       =   &H00000000&
      Height          =   45
      Left            =   5760
      TabIndex        =   5
      Top             =   5220
      Width           =   4875
   End
   Begin VB.Label line3 
      BackColor       =   &H00000000&
      Height          =   45
      Left            =   5760
      TabIndex        =   4
      Top             =   4380
      Width           =   4875
   End
   Begin VB.Label line2 
      BackColor       =   &H00000000&
      Height          =   45
      Left            =   5760
      TabIndex        =   3
      Top             =   3600
      Width           =   4875
   End
   Begin VB.Label line1 
      BackColor       =   &H00000000&
      Height          =   45
      Left            =   5760
      TabIndex        =   2
      Top             =   2850
      Width           =   4875
   End
   Begin VB.Label modbar 
      BackColor       =   &H00000000&
      Height          =   5655
      Left            =   5280
      TabIndex        =   1
      Top             =   540
      Width           =   45
   End
   Begin VB.Label stamp 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H00E0E0E0&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "stamp"
      BeginProperty Font 
         Name            =   "Trebuchet MS"
         Size            =   18
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   1875
      Left            =   10470
      TabIndex        =   0
      Top             =   210
      Width           =   1425
   End
End
Attribute VB_Name = "liqpostcard_template"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub cmdall_Click()

End Sub
