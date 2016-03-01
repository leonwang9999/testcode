 /*---------------------------------------------------------------------------
|                                  DCUtility                                  |
|--------------------------------------+--------------------------------------|
|    SolutionName : ScreenSnaperGadget                                        |
|    ProjectName  : Helper                                                    |
|    FileName     : Helper.cpp                                                |
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

#include "stdafx.h"
#include "Helper.h"
#include "WinCapture.h"
#include "DrawUtil.h"

#pragma comment( lib, "winmm.lib" )
#include <mmsystem.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CHelperApp theApp;

BEGIN_MESSAGE_MAP(CHelperApp, CWinApp)
END_MESSAGE_MAP()

CHelperApp::CHelperApp()
{
}

BOOL CHelperApp::InitInstance()
{
    SetRegistryKey("DCUtility");

    CWinApp::InitInstance();

    return TRUE;
}

BOOL CHelperApp::SetPrintScreen(pPrintScreenDelegate pDelegate, int nMode)
{
    return m_SystemHelper.SetPrintScreen(pDelegate, nMode);
}

void CHelperApp::SetCaptureInProgress(BOOL bCaptureInProgress)
{
    m_SystemHelper.SetCaptureInProgress(bCaptureInProgress);
}

BOOL CHelperApp::RegisterListener(BOOL bRegister)
{
    return m_SystemHelper.RegisterListener(bRegister);
}

BOOL CHelperApp::ShowSettings()
{
    return m_SystemHelper.ShowSettings();
}

HBITMAP CHelperApp::GetImage(eSnapType SnapType)
{
    if (SnapType == CT_DESKTOP || SnapType == CT_WINDOW || SnapType == CT_REGION) {

        CWinCapture Dlg;
        Dlg.SetCaptureMode(SnapType);
        
        if (Dlg.DoModal() != IDCANCEL) {

            BOOL        bPlaySound;
            CBitmap*    pBitmap = Dlg.GetSnapBitmap(bPlaySound);
            if (!pBitmap)
                return NULL;

            HBITMAP  hBitmap = (HBITMAP)pBitmap->Detach();
            delete   pBitmap;

            if (bPlaySound)
                PlaySound(MAKEINTRESOURCE(IDR_SNAP),
                          AfxGetInstanceHandle(),
                          SND_RESOURCE|SND_ASYNC);    

            return hBitmap;
        }
    }

    return NULL;
}

extern "C" HBITMAP WINAPI GetSnapType(eSnapType SnapType)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    
    theApp.SetCaptureInProgress(TRUE);
    HBITMAP hBitmap = theApp.GetImage(SnapType);
    theApp.SetCaptureInProgress(FALSE);

    return hBitmap;
}

extern "C" BOOL WINAPI SetPrintScreen(pPrintScreenDelegate pDelegate, int nMode)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    return theApp.SetPrintScreen(pDelegate, nMode);
}

extern "C" BOOL WINAPI RegisterListener(BOOL bRegister)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    return theApp.RegisterListener(bRegister);    
}

extern "C" BOOL WINAPI ShowSettings()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    return theApp.ShowSettings();    
}
