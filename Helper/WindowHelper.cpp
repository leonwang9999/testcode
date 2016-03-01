 /*---------------------------------------------------------------------------
|                                  DCUtility                                  |
|--------------------------------------+--------------------------------------|
|    SolutionName : ScreenSnaperGadget                                        |
|    ProjectName  : Helper                                                    |
|    FileName     : WindowHelper.cpp                                          |
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
#include "WindowHelper.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define MAX_BUFFER 255

CWindowHelper::CWindowHelper()
{
}

CWindowHelper::~CWindowHelper()
{
    DeleteAndRemoveAll(&m_ListWindow);
}

void CWindowHelper::DeleteAndRemoveAll(CTypedSortableObList<stWINDOW_INFO*>* pListWindow)
{
    int nCount = (int)pListWindow->GetCount();
    for (int i = 0; i < nCount; i++) {

        stWINDOW_INFO* stWH = (stWINDOW_INFO*)pListWindow->GetAt(pListWindow->FindIndex(i));

        DeleteAndRemoveAll(&stWH->m_ListChild);

        delete stWH;
        stWH = NULL;
    }

    pListWindow->RemoveAll();
}

void CWindowHelper::GetAllVisibleWindows()
{
    EnumWindows(EnumWindowsProc, (LPARAM)&m_ListWindow);
}

BOOL CALLBACK CWindowHelper::EnumWindowsProc(HWND hwnd, LPARAM lParam) 
{ 
    CTypedSortableObList<stWINDOW_INFO*>* pListWindow = (CTypedSortableObList<stWINDOW_INFO*>*)lParam;
    
    if (::IsWindowVisible(hwnd)) {

        stWINDOW_INFO* stWH = new stWINDOW_INFO;
        stWH->m_hWnd = hwnd;
        GetWindowRect(stWH->m_hWnd, stWH->m_Rect);

        EnumChildWindows(stWH->m_hWnd, EnumChildProc, (LPARAM)stWH);
        stWH->m_ListChild.Sort(CWindowHelper::CompBackward);

        if(pListWindow->IsEmpty())
            pListWindow->AddHead(stWH);
        else
            pListWindow->AddTail(stWH);
    }

    return TRUE; 
}

BOOL CALLBACK CWindowHelper::EnumChildProc(HWND hwnd, LPARAM lParam)
{
    stWINDOW_INFO* stWHParent = (stWINDOW_INFO*)lParam;
    
    if (::IsWindowVisible(hwnd) && ::GetParent(hwnd) == stWHParent->m_hWnd) {

        stWINDOW_INFO* stWH = new stWINDOW_INFO;
        stWH->m_hWnd = hwnd;
        GetWindowRect(stWH->m_hWnd, stWH->m_Rect);

        EnumChildWindows(stWH->m_hWnd, EnumChildProc, (LPARAM)stWH);
        stWH->m_ListChild.Sort(CWindowHelper::CompBackward);

         if(stWHParent->m_ListChild.IsEmpty())
            stWHParent->m_ListChild.AddHead(stWH);
        else
            stWHParent->m_ListChild.AddTail(stWH);
    }

    return TRUE;
}

CRect CWindowHelper::GetWindowRectFromPoint(CPoint pt)
{
    return GetWindowRectFromPoint(&m_ListWindow, pt);
}

CRect CWindowHelper::GetWindowRectFromPoint(CTypedSortableObList<stWINDOW_INFO*>* pListWindow, CPoint& pt)
{
    int nCount = (int)pListWindow->GetCount();
    for (int i = 0; i < nCount; i++) {

        stWINDOW_INFO* stWH = (stWINDOW_INFO*)pListWindow->GetAt(pListWindow->FindIndex(i));
        
        if (stWH->m_Rect.PtInRect(pt)) {

            CRect rc = GetWindowRectFromPoint(&stWH->m_ListChild, pt);
            if (!rc.IsRectEmpty()) {
                return rc;
            }
            else {
                return stWH->m_Rect;
            }
        }
    }

    return CRect(0, 0, 0, 0);
}

int CWindowHelper::CompBackward(stWINDOW_INFO* pFirstObj, stWINDOW_INFO* pSecondObj)
{
    if (pFirstObj->m_Rect == pSecondObj->m_Rect)
        return 0;
    
    if ((pFirstObj->m_Rect.left > pSecondObj->m_Rect.left) &&
        (pFirstObj->m_Rect.top > pSecondObj->m_Rect.top) &&
        (pFirstObj->m_Rect.right < pSecondObj->m_Rect.right) &&
        (pFirstObj->m_Rect.bottom < pSecondObj->m_Rect.bottom)) {
        return -1;
    }

    return 1;
}
