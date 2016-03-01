 /*---------------------------------------------------------------------------
|                                  DCUtility                                  |
|--------------------------------------+--------------------------------------|
|    SolutionName : ScreenSnaperGadget                                        |
|    ProjectName  : Helper                                                    |
|    FileName     : WinCapture.h                                              |
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

#include "DrawUtil.h"
#include "WindowHelper.h"
#include "WinCaptureHelper.h"
#include "Helper.h"

class COptionsDlg;

class CWinCapture : public CDialog
{
public:
    CWinCapture(CWnd* pParent = NULL);

    //{{AFX_DATA(CWinCapture)
    enum { IDD = IDD_DIALOG_SNAP };
    //}}AFX_DATA

public:
    BOOL                 m_bPlaySound;

private:
    CDrawUtil            m_DrawUtil;
    CWinCaptureHelper    m_pWinCaptureHelper;
    eSnapType            m_CaptureType;
    CDrawUtil::eDrawMode m_CMWDrawMode;
    BOOL                 m_bCMWShowPos;
    int                  m_nCMWPenWidth;
    int                  m_nCMWRectRoundWidth;
    CDrawUtil::eDrawMode m_CMRDrawMode;
    BOOL                 m_bCMRShowPos;
    int                  m_nCMRPenWidth;
    int                  m_nCMRRectRoundWidth;
    COLORREF             m_Backcolor;
    BOOL                 m_bShowHelp;
    CSize                m_DesktopSize;
    CDC                  m_MemDC;
    CBitmap              m_MemBitmap;
    CBitmap*             m_pOldMemBitmap;
    CRect                m_rcSnap;
    CPoint               m_LastPoint;
    CPoint               m_CurrentPoint;
    CWindowHelper        m_WindowHelper;
    BOOL                 m_FirstDownClick;
    BOOL                 m_bEndSelection;
    BOOL                 m_ShiftKeyPressed;
    BOOL                 m_bRestoreCursorArrow;
    BOOL                 m_bShowCursor;

public:
    void     SetCaptureMode(eSnapType CaptureType) { m_CaptureType = CaptureType; }
    CBitmap* GetSnapBitmap(BOOL& bPlaySound);
    void     UpdateHelperState(BOOL bShow = TRUE, BOOL bSave = TRUE);

private:
    void     FlashFrameRect();
    void     SuspendTimer(BOOL bSuspend = TRUE);
    void     ShowArrowCursor(BOOL bShowArrow, CPoint pt = CPoint(0, 0));

    //{{AFX_VIRTUAL(CWinCapture)
    public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    virtual BOOL DestroyWindow();
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CWinCapture)
    virtual BOOL OnInitDialog();
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnPopDismiss();
    afx_msg void OnPopAccept();
    afx_msg void OnPopAbort();
    afx_msg void OnPopSwitchDesktop();
    afx_msg void OnPopSwitchWindow();
    afx_msg void OnPopSwitchRegion();
    afx_msg void OnPopOptions();
    afx_msg void OnPopToggleHelp();
    afx_msg void OnPopResetRegion();
    afx_msg void OnPopToggleCursor();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
