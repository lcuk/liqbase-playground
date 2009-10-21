VERSION 5.00
Begin VB.Form liqmap_main 
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
   Begin liqmap.liqmapzoom liqmapzoom1 
      Height          =   6615
      Left            =   0
      TabIndex        =   3
      Top             =   570
      Width           =   12015
      _ExtentX        =   21193
      _ExtentY        =   11668
   End
   Begin VB.Label cmdreset 
      Alignment       =   2  'Center
      BackColor       =   &H00404000&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "reset"
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
      Height          =   585
      Left            =   6510
      TabIndex        =   2
      Top             =   0
      Width           =   2205
   End
   Begin VB.Label cmdchange 
      Alignment       =   2  'Center
      BackColor       =   &H00004000&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "change"
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
      Height          =   585
      Left            =   8730
      TabIndex        =   1
      Top             =   0
      Width           =   2235
   End
   Begin VB.Label title 
      BackColor       =   &H00808080&
      Caption         =   "liqmap viewer"
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
      Width           =   12015
   End
End
Attribute VB_Name = "liqmap_main"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub cmdall_Click()

End Sub
