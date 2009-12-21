VERSION 5.00
Begin VB.Form sheepdog_levelplay 
   BackColor       =   &H00000000&
   BorderStyle     =   1  'Fixed Single
   Caption         =   "OWNCODE"
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
   Begin VB.Label score 
      BackColor       =   &H00000000&
      Caption         =   "80 points"
      ForeColor       =   &H0000FFFF&
      Height          =   525
      Left            =   9330
      TabIndex        =   3
      Top             =   30
      Width           =   2655
   End
   Begin VB.Label gameover 
      Alignment       =   2  'Center
      BackColor       =   &H00000000&
      Caption         =   "Game Over"
      BeginProperty Font 
         Name            =   "Trebuchet MS"
         Size            =   27.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H000000FF&
      Height          =   705
      Left            =   2670
      TabIndex        =   2
      Top             =   3570
      Visible         =   0   'False
      Width           =   6375
   End
   Begin VB.Label countdown 
      BackColor       =   &H00000000&
      Caption         =   "30 seconds left"
      ForeColor       =   &H0000FFFF&
      Height          =   525
      Left            =   4170
      TabIndex        =   1
      Top             =   30
      Width           =   2655
   End
   Begin VB.Label backplane 
      Alignment       =   2  'Center
      BackColor       =   &H00404040&
      Caption         =   "backplane"
      ForeColor       =   &H000000FF&
      Height          =   7200
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   12015
   End
End
Attribute VB_Name = "sheepdog_levelplay"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub cmdall_Click()

End Sub
