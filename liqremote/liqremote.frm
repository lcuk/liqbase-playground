VERSION 5.00
Begin VB.Form liqremote 
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
   Begin VB.Label title 
      BackColor       =   &H00000000&
      Caption         =   "liqremote"
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
      Height          =   615
      Left            =   630
      TabIndex        =   0
      Top             =   120
      Width           =   2805
   End
   Begin VB.Label cmdFastforward 
      Alignment       =   2  'Center
      BackColor       =   &H00004000&
      Caption         =   ">> Advance 5 Sec"
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
      Height          =   2025
      Left            =   8310
      TabIndex        =   7
      Top             =   3810
      Width           =   3555
   End
   Begin VB.Label cmdRewind 
      Alignment       =   2  'Center
      BackColor       =   &H00004000&
      Caption         =   "<< Rewind 5 Sec"
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
      Height          =   2025
      Left            =   4185
      TabIndex        =   6
      Top             =   3810
      Width           =   3555
   End
   Begin VB.Label cmdPlay 
      Alignment       =   2  'Center
      BackColor       =   &H00404000&
      Caption         =   "Play/Pause"
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
      Height          =   2025
      Left            =   60
      TabIndex        =   5
      Top             =   3810
      Width           =   3555
   End
   Begin VB.Label cmdVolumeMute 
      Alignment       =   2  'Center
      BackColor       =   &H00004000&
      Caption         =   "Volume Mute"
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
      Height          =   2025
      Left            =   8310
      TabIndex        =   4
      Top             =   1230
      Width           =   3555
   End
   Begin VB.Label cmdVolumeUp 
      Alignment       =   2  'Center
      BackColor       =   &H00004000&
      Caption         =   "Volume Up"
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
      Height          =   2025
      Left            =   4185
      TabIndex        =   3
      Top             =   1230
      Width           =   3555
   End
   Begin VB.Label cmdVolumeDown 
      Alignment       =   2  'Center
      BackColor       =   &H00004000&
      Caption         =   "Volume Down"
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
      Height          =   2025
      Left            =   60
      TabIndex        =   2
      Top             =   1230
      Width           =   3555
   End
   Begin VB.Label Label5 
      Alignment       =   2  'Center
      BackColor       =   &H00800000&
      Caption         =   "server status"
      BeginProperty Font 
         Name            =   "Trebuchet MS"
         Size            =   20.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00C0FFFF&
      Height          =   615
      Left            =   990
      TabIndex        =   1
      Top             =   6390
      Width           =   10845
   End
End
Attribute VB_Name = "liqremote"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Form_Load()

End Sub
