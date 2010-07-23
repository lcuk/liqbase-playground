VERSION 5.00
Begin VB.Form invar_calibrate 
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
   Begin VB.Label lblbackground 
      Caption         =   "Label4"
      Height          =   4095
      Left            =   1470
      TabIndex        =   9
      Top             =   1950
      Width           =   8805
   End
   Begin VB.Label Label2 
      Alignment       =   2  'Center
      BackColor       =   &H00004000&
      Caption         =   "Calibration tool for Inverted AR positioning system"
      BeginProperty Font 
         Name            =   "Trebuchet MS"
         Size            =   15.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   465
      Left            =   0
      TabIndex        =   8
      Top             =   840
      Width           =   12015
   End
   Begin VB.Label cmdtopright 
      Alignment       =   2  'Center
      BackColor       =   &H00000040&
      Caption         =   "top right"
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
      Height          =   975
      Left            =   8040
      TabIndex        =   7
      Top             =   2010
      Width           =   2175
   End
   Begin VB.Label cmdtopleft 
      Alignment       =   2  'Center
      BackColor       =   &H00000040&
      Caption         =   "top left"
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
      Height          =   975
      Left            =   1530
      TabIndex        =   6
      Top             =   2010
      Width           =   2175
   End
   Begin VB.Label cmdbottomright 
      Alignment       =   2  'Center
      BackColor       =   &H00000040&
      Caption         =   "bottom right"
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
      Height          =   975
      Left            =   8040
      TabIndex        =   5
      Top             =   5010
      Width           =   2175
   End
   Begin VB.Label title 
      BackColor       =   &H00004040&
      Caption         =   "invar :: calibration utility"
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
      Height          =   840
      Left            =   0
      TabIndex        =   4
      Top             =   0
      Width           =   12015
   End
   Begin VB.Label cmdsave 
      Alignment       =   2  'Center
      BackColor       =   &H00004000&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "Save"
      Enabled         =   0   'False
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
      Height          =   945
      Left            =   8610
      TabIndex        =   3
      Top             =   6270
      Width           =   3405
   End
   Begin VB.Label cmdbottomleft 
      Alignment       =   2  'Center
      BackColor       =   &H00000040&
      Caption         =   "bottom left"
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
      Height          =   975
      Left            =   1530
      TabIndex        =   2
      Top             =   5010
      Width           =   2175
   End
   Begin VB.Label Label3 
      Alignment       =   2  'Center
      BackColor       =   &H00004000&
      Caption         =   "Place device in each corner of the detection range and click corrposponding button"
      BeginProperty Font 
         Name            =   "Trebuchet MS"
         Size            =   15.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   465
      Left            =   0
      TabIndex        =   1
      Top             =   1290
      Width           =   12015
   End
   Begin VB.Label Label1 
      Alignment       =   2  'Center
      BackColor       =   &H000000FF&
      Caption         =   "Calibration incomplete"
      BeginProperty Font 
         Name            =   "Trebuchet MS"
         Size            =   18
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H0000FFFF&
      Height          =   555
      Left            =   2130
      TabIndex        =   0
      Top             =   6450
      Width           =   6345
   End
End
Attribute VB_Name = "invar_calibrate"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

