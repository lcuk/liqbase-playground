VERSION 5.00
Object = "{A964BDA3-3E93-11CF-9A0F-9E6261DACD1C}#3.0#0"; "Resize32.ocx"
Begin VB.UserControl timelinerow 
   BackColor       =   &H00000000&
   ClientHeight    =   870
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   11760
   BeginProperty Font 
      Name            =   "Trebuchet MS"
      Size            =   9.75
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   ForeColor       =   &H00808080&
   ScaleHeight     =   870
   ScaleWidth      =   11760
   Begin ResizeLibCtl.ReSize ReSize1 
      Left            =   6810
      Top             =   240
      _Version        =   196608
      _ExtentX        =   741
      _ExtentY        =   741
      _StockProps     =   64
      Enabled         =   -1  'True
      Enabled         =   -1  'True
      FormMinWidth    =   0
      FormMinHeight   =   0
      FormDesignHeight=   870
      FormDesignWidth =   11760
   End
   Begin VB.Label cmdnext 
      Alignment       =   2  'Center
      BackColor       =   &H00404000&
      BorderStyle     =   1  'Fixed Single
      Caption         =   ">"
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
      Left            =   10050
      TabIndex        =   4
      Top             =   60
      Width           =   795
   End
   Begin VB.Label cmdframecount 
      Alignment       =   2  'Center
      BackColor       =   &H00004000&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "|...|...|...|...|...|...|...|...|...|...|...|..."
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
      Left            =   3180
      TabIndex        =   3
      Top             =   60
      Width           =   6825
   End
   Begin VB.Label cmdprev 
      Alignment       =   2  'Center
      BackColor       =   &H00404000&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "<"
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
      Left            =   2370
      TabIndex        =   2
      Top             =   60
      Width           =   765
   End
   Begin VB.Label cmdconfig 
      Alignment       =   2  'Center
      BackColor       =   &H00400000&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "%"
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
      Left            =   10890
      TabIndex        =   1
      Top             =   60
      Width           =   795
   End
   Begin VB.Label title 
      BackColor       =   &H00000000&
      Caption         =   "timeline"
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
      Left            =   60
      TabIndex        =   0
      Top             =   120
      Width           =   2205
   End
End
Attribute VB_Name = "timelinerow"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

