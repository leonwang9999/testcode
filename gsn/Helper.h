 /*---------------------------------------------------------------------------
|                                  DCUtility                                  |
|--------------------------------------+--------------------------------------|
|    SolutionName : ScreenSnaperGadget                                        |
|    ProjectName  : Helper                                                    |
|    FileName     : Helper.h                                                  |
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

#ifndef __AFXWIN_H__
    #error "include 'stdafx.h' before this file for PCH"
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

#include "resource.h"
#include "SystemHelper.h"



class CHelperApp : public CWinApp
{
public:
    CHelperApp();

private:
    CSystemHelper m_SystemHelper;

public:
    BOOL    RegisterListener(BOOL bRegister);
	//typedef void (WINAPI* pPrintScreenDelegate)(int nMode);
    BOOL    SetPrintScreen(pPrintScreenDelegate pDelegate, int nMode);
    BOOL    ShowSettings();
	//enum eSnapType { CT_DESKTOP, CT_WINDOW, CT_REGION };
    HBITMAP GetImage(eSnapType SnapType);
    void    SetCaptureInProgress(BOOL bCaptureInProgress);

public:
    virtual BOOL InitInstance();
    DECLARE_MESSAGE_MAP()
};
