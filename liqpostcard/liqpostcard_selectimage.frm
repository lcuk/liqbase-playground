VERSION 5.00
Begin VB.Form liqpostcard_selectimage 
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
   Begin VB.CommandButton cmdSelect 
      BackColor       =   &H00004000&
      Caption         =   "Select"
      BeginProperty Font 
         Name            =   "Trebuchet MS"
         Size            =   20.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   915
      Left            =   8700
      Style           =   1  'Graphical
      TabIndex        =   2
      Top             =   6300
      Width           =   3315
   End
   Begin liqpostcard.liqrecentphotos liqrecentphotos1 
      Height          =   6315
      Left            =   0
      TabIndex        =   1
      Top             =   870
      Width           =   12015
      _ExtentX        =   21193
      _ExtentY        =   11139
   End
   Begin VB.Label title 
      BackColor       =   &H00004040&
      Caption         =   "postcard :: select image to include"
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
      TabIndex        =   0
      Top             =   0
      Width           =   12015
   End
End
Attribute VB_Name = "liqpostcard_selectimage"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub cmdall_Click()

End Sub
