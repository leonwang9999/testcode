 /*---------------------------------------------------------------------------
|                                  DCUtility                                  |
|--------------------------------------+--------------------------------------|
|    SolutionName : ScreenSnaperGadget                                        |
|    ProjectName  : Helper                                                    |
|    FileName     : WindowHelper.h                                            |
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

#include "SortableObList.h"

class CWindowHelper  
{
public:
    CWindowHelper();
    virtual ~CWindowHelper();

    void    GetAllVisibleWindows();
    CRect   GetWindowRectFromPoint(CPoint pt);

private:
    class stWINDOW_INFO : public CObject {
    public:
        HWND     m_hWnd;
        CRect    m_Rect;
        CTypedSortableObList<stWINDOW_INFO*> m_ListChild;
    };
    
    CTypedSortableObList<stWINDOW_INFO*> m_ListWindow;

    static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);
    static BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam);
    static int  CompBackward(stWINDOW_INFO* pFirstObj,
                             stWINDOW_INFO* pSecondObj);
    void  DeleteAndRemoveAll(CTypedSortableObList<stWINDOW_INFO*>* pListWindow);
    CRect GetWindowRectFromPoint(CTypedSortableObList<stWINDOW_INFO*>* pListWindow,
                                 CPoint& pt);
};
