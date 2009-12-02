VERSION 5.00
Begin VB.UserControl liqmapzoom 
   BackColor       =   &H00004000&
   ClientHeight    =   7200
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   12000
   ScaleHeight     =   7200
   ScaleWidth      =   12000
   Begin VB.PictureBox zoom 
      BackColor       =   &H00808000&
      BorderStyle     =   0  'None
      Height          =   6765
      Left            =   0
      ScaleHeight     =   6765
      ScaleWidth      =   555
      TabIndex        =   1
      Top             =   0
      Width           =   555
      Begin VB.PictureBox knob 
         BackColor       =   &H0000FF00&
         BorderStyle     =   0  'None
         Height          =   495
         Left            =   0
         ScaleHeight     =   495
         ScaleWidth      =   555
         TabIndex        =   2
         Top             =   0
         Width           =   555
      End
   End
   Begin VB.PictureBox backplane 
      BackColor       =   &H00400000&
      BorderStyle     =   0  'None
      Height          =   7185
      Left            =   0
      ScaleHeight     =   7185
      ScaleWidth      =   11985
      TabIndex        =   0
      Top             =   0
      Width           =   11985
   End
End
Attribute VB_Name = "liqmapzoom"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

