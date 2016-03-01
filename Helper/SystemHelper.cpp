/*---------------------------------------------------------------------------
|                                  DCUtility                                  |
|--------------------------------------+--------------------------------------|
|    SolutionName : ScreenSnaperGadget                                        |
|    ProjectName  : Helper                                                    |
|    FileName     : SystemHelper.cpp                                          |
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
#include "SystemHelper.h"

#pragma comment( lib, "winmm.lib" )
#include <mmsystem.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#pragma data_seg(".SYSHELP")
pPrintScreenDelegate g_PrintScreenDelegate = NULL;
int                  g_nMode               = 0;
HWND                 g_hWndDialog          = NULL;
HHOOK                g_hKeyboardHook       = NULL;
BOOL                 g_bCaptureInProgress  = FALSE;
#pragma data_seg()
#pragma comment(linker, "/section:.SYSHELP,rws")

#define UWM_PRINTSCREEN   WM_APP+2
#define UWM_END_DIALOG    WM_APP+3
#define UWM_SHOW_SETTINGS WM_APP+4

DWORD WINAPI ThreadDialog(LPVOID lpParameter);
BOOL CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

CSystemHelper::CSystemHelper()
{
}

CSystemHelper::~CSystemHelper()
{
}

BOOL CSystemHelper::RegisterListener(BOOL bRegister) {

    if (bRegister) {
    
        if (!g_hWndDialog)
            return CreateThread(NULL, 0, ThreadDialog, NULL, 0, NULL) != NULL ? TRUE : FALSE;
        else
            return TRUE;
    }
    else {
    
        if (g_hWndDialog) {

            g_hWndDialog = NULL;
            return (BOOL)PostMessage(g_hWndDialog, UWM_END_DIALOG, 0, 0);
        }
        else
            return FALSE;
    }

    return FALSE;
}

BOOL CSystemHelper::SetPrintScreen(pPrintScreenDelegate pDelegate, int nMode)
{
	if (pDelegate) {

		if (!LoadHook())
			return FALSE;

        g_PrintScreenDelegate = pDelegate;
        g_nMode               = nMode;

		return TRUE;	
	}

    return UnloadHook();
}

void CSystemHelper::SetCaptureInProgress(BOOL bCaptureInProgress)
{
    g_bCaptureInProgress = bCaptureInProgress;
}

BOOL CSystemHelper::LoadHook()
{
    if (UnloadHook()) {

        g_hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD, KeyboardProc, AfxGetInstanceHandle(), 0);
        if (g_hKeyboardHook)
            return TRUE;
    }

    return FALSE;
}

BOOL CSystemHelper::UnloadHook()
{
    if (!g_hKeyboardHook)
        return TRUE;

    BOOL bUnhooked = UnhookWindowsHookEx(g_hKeyboardHook);
    if (bUnhooked) {

        g_hKeyboardHook       = NULL;
        g_PrintScreenDelegate = NULL;
    }

    return bUnhooked;
}

BOOL CSystemHelper::ShowSettings()
{
    if (g_hWndDialog)
        return (BOOL)PostMessage(g_hWndDialog, UWM_SHOW_SETTINGS, 0, 0);

    return FALSE;
}

LRESULT CALLBACK CSystemHelper::KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode >= 0) {

        if (nCode == HC_ACTION) {

            if (wParam == VK_SNAPSHOT) {

                if (!g_bCaptureInProgress && g_hWndDialog)
                    PostMessage(g_hWndDialog, UWM_PRINTSCREEN, 0, 0);

                return 1;
            }
	    }
    }

    return CallNextHookEx(g_hKeyboardHook, nCode, wParam, lParam);
}

DWORD WINAPI ThreadDialog(LPVOID lpParameter)
{
   return (DWORD)DialogBoxParam(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDD_DIALOG_PRINTSCREEN), NULL, (DLGPROC)DialogProc, (LPARAM)lpParameter);
}

BOOL CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(wParam);

    switch (uMsg) {

        case WM_WINDOWPOSCHANGING: {
            ((WINDOWPOS*)lParam)->flags &= ~SWP_SHOWWINDOW;
            break;
        }
        case WM_INITDIALOG: {
            g_hWndDialog = hwndDlg;
            break;
        }
        case UWM_SHOW_SETTINGS: {
            CWnd*  pWnd = CWnd::FromHandle(FindWindow("BasicWindow", "Screen Snaper"));
            CRect  rc;
            CPoint pt;

            pWnd->GetWindowRect(rc);
            GetCursorPos(&pt);
            SetCursorPos(rc.right-8, rc.top+28);
            mouse_event(MOUSEEVENTF_LEFTDOWN|MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);       
            SetCursorPos(pt.x, pt.y);
            break;
        }
        case UWM_PRINTSCREEN: {

            if (g_PrintScreenDelegate) {

                SetWindowPos(g_hWndDialog, HWND_TOPMOST, 0, 0, 10, 10, SWP_HIDEWINDOW);

                if (AfxGetApp()->GetProfileInt("WinCapture", "bPlaySound", TRUE))
                    PlaySound(MAKEINTRESOURCE(IDR_SNAP), AfxGetInstanceHandle(), SND_RESOURCE|SND_ASYNC);    

                mouse_event(MOUSEEVENTF_LEFTDOWN|MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);       
                
                (*(g_PrintScreenDelegate))(g_nMode);
            }
            break;
        }
        case UWM_END_DIALOG: {
            EndDialog(hwndDlg, NULL);
            break;
        }
    }

    return FALSE;
}