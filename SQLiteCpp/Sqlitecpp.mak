# Microsoft Developer Studio Generated NMAKE File, Based on Sqlitecpp.dsp
!IF "$(CFG)" == ""
CFG=Sqlitecpp - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Sqlitecpp - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Sqlitecpp - Win32 Release" && "$(CFG)" != "Sqlitecpp - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
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
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Sqlitecpp - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\Sqlitecpp.lib"


CLEAN :
	-@erase "$(INTDIR)\Backup.obj"
	-@erase "$(INTDIR)\Column.obj"
	-@erase "$(INTDIR)\Database.obj"
	-@erase "$(INTDIR)\sqlite3.obj"
	-@erase "$(INTDIR)\Statement.obj"
	-@erase "$(INTDIR)\Transaction.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\Sqlitecpp.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "SQLITE_ENABLE_COLUMN_METADATA" /Fp"$(INTDIR)\Sqlitecpp.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Sqlitecpp.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\Sqlitecpp.lib" 
LIB32_OBJS= \
	"$(INTDIR)\Backup.obj" \
	"$(INTDIR)\Column.obj" \
	"$(INTDIR)\Database.obj" \
	"$(INTDIR)\Statement.obj" \
	"$(INTDIR)\Transaction.obj" \
	"$(INTDIR)\sqlite3.obj"

"$(OUTDIR)\Sqlitecpp.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Sqlitecpp - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\Sqlitecpp.lib" "$(OUTDIR)\Sqlitecpp.bsc"


CLEAN :
	-@erase "$(INTDIR)\Backup.obj"
	-@erase "$(INTDIR)\Backup.sbr"
	-@erase "$(INTDIR)\Column.obj"
	-@erase "$(INTDIR)\Column.sbr"
	-@erase "$(INTDIR)\Database.obj"
	-@erase "$(INTDIR)\Database.sbr"
	-@erase "$(INTDIR)\sqlite3.obj"
	-@erase "$(INTDIR)\sqlite3.sbr"
	-@erase "$(INTDIR)\Statement.obj"
	-@erase "$(INTDIR)\Statement.sbr"
	-@erase "$(INTDIR)\Transaction.obj"
	-@erase "$(INTDIR)\Transaction.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Sqlitecpp.bsc"
	-@erase "$(OUTDIR)\Sqlitecpp.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /w /W0 /Gm /GX /ZI /Od /D "_DEBUG" /D "SQLITE_ENABLE_COLUMN_METADATA" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Sqlitecpp.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Sqlitecpp.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Backup.sbr" \
	"$(INTDIR)\Column.sbr" \
	"$(INTDIR)\Database.sbr" \
	"$(INTDIR)\Statement.sbr" \
	"$(INTDIR)\Transaction.sbr" \
	"$(INTDIR)\sqlite3.sbr"

"$(OUTDIR)\Sqlitecpp.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\Sqlitecpp.lib" 
LIB32_OBJS= \
	"$(INTDIR)\Backup.obj" \
	"$(INTDIR)\Column.obj" \
	"$(INTDIR)\Database.obj" \
	"$(INTDIR)\Statement.obj" \
	"$(INTDIR)\Transaction.obj" \
	"$(INTDIR)\sqlite3.obj"

"$(OUTDIR)\Sqlitecpp.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("Sqlitecpp.dep")
!INCLUDE "Sqlitecpp.dep"
!ELSE 
!MESSAGE Warning: cannot find "Sqlitecpp.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Sqlitecpp - Win32 Release" || "$(CFG)" == "Sqlitecpp - Win32 Debug"
SOURCE=.\src\Backup.cpp

!IF  "$(CFG)" == "Sqlitecpp - Win32 Release"


"$(INTDIR)\Backup.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Sqlitecpp - Win32 Debug"


"$(INTDIR)\Backup.obj"	"$(INTDIR)\Backup.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\Column.cpp

!IF  "$(CFG)" == "Sqlitecpp - Win32 Release"


"$(INTDIR)\Column.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Sqlitecpp - Win32 Debug"


"$(INTDIR)\Column.obj"	"$(INTDIR)\Column.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\Database.cpp

!IF  "$(CFG)" == "Sqlitecpp - Win32 Release"


"$(INTDIR)\Database.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Sqlitecpp - Win32 Debug"


"$(INTDIR)\Database.obj"	"$(INTDIR)\Database.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\Statement.cpp

!IF  "$(CFG)" == "Sqlitecpp - Win32 Release"


"$(INTDIR)\Statement.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Sqlitecpp - Win32 Debug"


"$(INTDIR)\Statement.obj"	"$(INTDIR)\Statement.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\Transaction.cpp

!IF  "$(CFG)" == "Sqlitecpp - Win32 Release"


"$(INTDIR)\Transaction.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Sqlitecpp - Win32 Debug"


"$(INTDIR)\Transaction.obj"	"$(INTDIR)\Transaction.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\sqlite3\sqlite3.c

!IF  "$(CFG)" == "Sqlitecpp - Win32 Release"


"$(INTDIR)\sqlite3.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Sqlitecpp - Win32 Debug"


"$(INTDIR)\sqlite3.obj"	"$(INTDIR)\sqlite3.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 


!ENDIF 

