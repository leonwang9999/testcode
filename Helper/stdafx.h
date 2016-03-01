 /*---------------------------------------------------------------------------
|                                  DCUtility                                  |
|--------------------------------------+--------------------------------------|
|    SolutionName : ScreenSnaperGadget                                        |
|    ProjectName  : Helper                                                    |
|    FileName     : stdafx.h                                                  |
|    CreationDate : 2007-03-07                                                |
|    Author       : Dany Cantin                                               |
|    Comments     : dcutility@hotmail.com                                     |
|--------------------------------------+--------------------------------------|
|                             Screen Capture Tool                             |
|                         Windows Vista SideBar Gadget                        |
|--------------------------------------+--------------------------------------|
|                          Copyright © 2007 DCUtility                         |
|                              All rights reserved.                           |
 ---------------------------------------------------------------------------*/
#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN
#endif

#ifndef WINVER
#define WINVER 0x0501
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif                        

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS

#include <afxwin.h>
#include <afxext.h>

#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>
#endif


#ifdef __cplusplus
extern "C" {
#endif

    typedef void (WINAPI* pPrintScreenDelegate)(int nMode);
    BOOL WINAPI SetPrintScreen(pPrintScreenDelegate pDelegate, int nMode);

    enum eSnapType { CT_DESKTOP, CT_WINDOW, CT_REGION };
    HBITMAP WINAPI GetSnapType(eSnapType SnapType);

    BOOL WINAPI RegisterListener(BOOL bRegister);
    BOOL WINAPI ShowSettings();

#ifdef __cplusplus
}
#endif