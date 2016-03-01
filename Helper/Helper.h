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
    BOOL    SetPrintScreen(pPrintScreenDelegate pDelegate, int nMode);
    BOOL    ShowSettings();
    HBITMAP GetImage(eSnapType SnapType);
    void    SetCaptureInProgress(BOOL bCaptureInProgress);

public:
    virtual BOOL InitInstance();
    DECLARE_MESSAGE_MAP()
};
