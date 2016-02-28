# Microsoft Developer Studio Project File - Name="Sqlitecpp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Sqlitecpp - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Sqlitecpp.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Sqlitecpp.mak" CFG="Sqlitecpp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Sqlitecpp - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Sqlitecpp - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Sqlitecpp - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "SQLITE_ENABLE_COLUMN_METADATA" /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Release\SqlitecppR.lib"

!ELSEIF  "$(CFG)" == "Sqlitecpp - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /w /W0 /Gm /GX /ZI /Od /D "_DEBUG" /D "SQLITE_ENABLE_COLUMN_METADATA" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Debug\SqlitecppD.lib"

!ENDIF 

# Begin Target

# Name "Sqlitecpp - Win32 Release"
# Name "Sqlitecpp - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "src"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\Backup.cpp
# End Source File
# Begin Source File

SOURCE=.\src\Column.cpp
# End Source File
# Begin Source File

SOURCE=.\src\Database.cpp
# End Source File
# Begin Source File

SOURCE=.\src\Statement.cpp
# End Source File
# Begin Source File

SOURCE=.\src\Transaction.cpp
# End Source File
# End Group
# Begin Group "include"

# PROP Default_Filter ""
# Begin Group "SQLiteCpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\include\SQLiteCpp\Assertion.h
# End Source File
# Begin Source File

SOURCE=.\include\SQLiteCpp\Backup.h
# End Source File
# Begin Source File

SOURCE=.\include\SQLiteCpp\Column.h
# End Source File
# Begin Source File

SOURCE=.\include\SQLiteCpp\Database.h
# End Source File
# Begin Source File

SOURCE=.\include\SQLiteCpp\Exception.h
# End Source File
# Begin Source File

SOURCE=.\include\SQLiteCpp\SQLiteCpp.h
# End Source File
# Begin Source File

SOURCE=.\include\SQLiteCpp\Statement.h
# End Source File
# Begin Source File

SOURCE=.\include\SQLiteCpp\Transaction.h
# End Source File
# End Group
# End Group
# Begin Group "sqlite3"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sqlite3\sqlite3.c
# End Source File
# Begin Source File

SOURCE=.\sqlite3\sqlite3.h
# End Source File
# Begin Source File

SOURCE=.\sqlite3\sqlite3ext.h
# End Source File
# End Group
# End Target
# End Project
