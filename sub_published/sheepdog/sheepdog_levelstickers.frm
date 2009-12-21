VERSION 5.00
Begin VB.Form sheepdog_levelstickers 
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
   Begin VB.Label cmdnone 
      Alignment       =   2  'Center
      BackColor       =   &H00404000&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "del"
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
      Height          =   1755
      Left            =   10710
      TabIndex        =   4
      Top             =   2850
      Width           =   1305
   End
   Begin VB.Label cmdall 
      Alignment       =   2  'Center
      BackColor       =   &H00404000&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "add"
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
      Height          =   1455
      Left            =   10710
      TabIndex        =   3
      Top             =   1320
      Width           =   1305
   End
   Begin VB.Label cmdaccept 
      Alignment       =   2  'Center
      BackColor       =   &H00004000&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "Save"
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
      Caption         =   "add level details"
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
      Height          =   585
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   5955
   End
   Begin VB.Label backplane 
      Alignment       =   2  'Center
      BackColor       =   &H00404040&
      Caption         =   "backplane"
      ForeColor       =   &H000000FF&
      Height          =   5835
      Left            =   60
      TabIndex        =   2
      Top             =   600
      Width           =   10545
   End
End
Attribute VB_Name = "sheepdog_levelstickers"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub cmdall_Click()

End Sub
