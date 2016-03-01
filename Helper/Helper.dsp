# Microsoft Developer Studio Project File - Name="Helper" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Helper - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Helper.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Helper.mak" CFG="Helper - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Helper - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Helper - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Helper - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_WINDOWS" /D "_DEBUG" /D "_USRDLL" /D "_MBCS" /Fp"$(IntDir)\Helper.pch" /YX /GZ /c
# ADD CPP /nologo /MTd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_WINDOWS" /D "_DEBUG" /D "_USRDLL" /D "_MBCS" /Fp"$(IntDir)\Helper.pch" /YX /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
# ADD BASE RSC /l 0x40c /i "$(IntDir)" /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /pdb:" Helper.pdb" /debug /machine:IX86 /out:"$Release\Helper.dll" /pdbtype:sept
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /pdb:" Helper.pdb" /debug /machine:IX86 /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Helper - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W4 /GX /Zi /O1 /D "WIN32" /D "_WINDOWS" /D "NDEBUG" /D "_USRDLL" /D "_MBCS" /Fp"$(IntDir)\Helper.pch" /YX /c
# ADD CPP /nologo /MT /W4 /GX /Zi /O1 /D "WIN32" /D "_WINDOWS" /D "NDEBUG" /D "_USRDLL" /D "_MBCS" /Fp"$(IntDir)\Helper.pch" /YX /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
# ADD BASE RSC /l 0x40c /i "$(IntDir)" /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /pdb:"Helper.pdb" /debug /machine:IX86 /pdbtype:sept /opt:ref /opt:icf
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /pdb:"Helper.pdb" /debug /machine:IX86 /pdbtype:sept /opt:ref /opt:icf
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "Helper - Win32 Debug"
# Name "Helper - Win32 Release"
# Begin Group "Fichiers sources"

# PROP Default_Filter "cpp;c;cc;cxx;def;odl;idl;hpj;bat;asm;asmx"
# Begin Source File

SOURCE=.\DrawUtil.cpp
DEP_CPP_DRAWU=\
	".\DrawUtil.h"\
	".\Helper.h"\
	".\MemDCEx.h"\
	".\stdafx.h"\
	".\SystemHelper.h"\
	
# End Source File
# Begin Source File

SOURCE=.\Helper.cpp
DEP_CPP_HELPE=\
	".\DrawUtil.h"\
	".\Helper.h"\
	".\MemDCEx.h"\
	".\SortableObList.h"\
	".\stdafx.h"\
	".\SystemHelper.h"\
	".\WinCapture.h"\
	".\WinCaptureHelper.h"\
	".\WindowHelper.h"\
	
# End Source File
# Begin Source File

SOURCE=.\Helper.def
# End Source File
# Begin Source File

SOURCE=.\OptionsDlg.cpp
DEP_CPP_OPTIO=\
	".\DrawUtil.h"\
	".\Helper.h"\
	".\MemDCEx.h"\
	".\OptionsDlg.h"\
	".\SortableObList.h"\
	".\stdafx.h"\
	".\SystemHelper.h"\
	".\WinCapture.h"\
	".\WinCaptureHelper.h"\
	".\WindowHelper.h"\
	
# End Source File
# Begin Source File

SOURCE=.\SortableObList.cpp
DEP_CPP_SORTA=\
	".\SortableObList.h"\
	".\stdafx.h"\
	
# End Source File
# Begin Source File

SOURCE=.\stdafx.cpp
DEP_CPP_STDAF=\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "Helper - Win32 Debug"

# ADD CPP /nologo /GX /Yc"stdafx.h" /GZ

!ELSEIF  "$(CFG)" == "Helper - Win32 Release"

# ADD CPP /nologo /GX /Yc"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SystemHelper.cpp
DEP_CPP_SYSTE=\
	".\Helper.h"\
	".\stdafx.h"\
	".\SystemHelper.h"\
	
# End Source File
# Begin Source File

SOURCE=.\WinCapture.cpp
DEP_CPP_WINCA=\
	".\DrawUtil.h"\
	".\Helper.h"\
	".\MemDCEx.h"\
	".\OptionsDlg.h"\
	".\SortableObList.h"\
	".\stdafx.h"\
	".\SystemHelper.h"\
	".\WinCapture.h"\
	".\WinCaptureHelper.h"\
	".\WindowHelper.h"\
	
# End Source File
# Begin Source File

SOURCE=.\WinCaptureHelper.cpp
DEP_CPP_WINCAP=\
	".\DrawUtil.h"\
	".\Helper.h"\
	".\MemDCEx.h"\
	".\stdafx.h"\
	".\SystemHelper.h"\
	".\WinCaptureHelper.h"\
	
# End Source File
# Begin Source File

SOURCE=.\WindowHelper.cpp
DEP_CPP_WINDO=\
	".\SortableObList.h"\
	".\stdafx.h"\
	".\WindowHelper.h"\
	
# End Source File
# End Group
# Begin Group "Fichiers d'en-t¨ºt"

# PROP Default_Filter "h;hpp;hxx;hm;inl;inc;xsd"
# Begin Source File

SOURCE=.\DrawUtil.h
# End Source File
# Begin Source File

SOURCE=.\Helper.h
# End Source File
# Begin Source File

SOURCE=.\MemDC.h
# End Source File
# Begin Source File

SOURCE=.\OptionsDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SortableObList.h
# End Source File
# Begin Source File

SOURCE=.\stdafx.h
# End Source File
# Begin Source File

SOURCE=.\SystemHelper.h
# End Source File
# Begin Source File

SOURCE=.\WinCapture.h
# End Source File
# Begin Source File

SOURCE=.\WinCaptureHelper.h
# End Source File
# Begin Source File

SOURCE=.\WindowHelper.h
# End Source File
# End Group
# Begin Group "Fichiers de ressources"

# PROP Default_Filter "rc;ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe;resx;tiff;tif;png;wav"
# Begin Source File

SOURCE=.\res\Helper.ico
# End Source File
# Begin Source File

SOURCE=.\Helper.rc
# End Source File
# Begin Source File

SOURCE=.\res\RegionMode1.cur
# End Source File
# Begin Source File

SOURCE=.\res\RegionMode2.cur
# End Source File
# Begin Source File

SOURCE=.\res\Snap.wav
# End Source File
# Begin Source File

SOURCE=.\res\WindowMode.cur
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\Helper.manifest
# End Source File
# End Target
# End Project
