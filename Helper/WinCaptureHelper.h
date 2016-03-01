 /*---------------------------------------------------------------------------
|                                  DCUtility                                  |
|--------------------------------------+--------------------------------------|
|    SolutionName : ScreenSnaperGadget                                        |
|    ProjectName  : Helper                                                    |
|    FileName     : WinCaptureHelper.h                                        |
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

#define ZOOM_FACTOR_MIN     0
#define ZOOM_FACTOR_MAX     10
#define ZOOM_FACTOR_DEFAULT 0

class CCtrColor : public CStatic
{
public:
    CCtrColor();
    virtual ~CCtrColor() {};
    void SetColor(COLORREF col) {
        m_BackColor = col;
        Invalidate();
    }
    COLORREF GetColor() {
        return m_BackColor;
    }
    
private:
    COLORREF m_BackColor;

    //{{AFX_VIRTUAL(CCtrColor)
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CCtrColor)
    afx_msg void OnPaint();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


class CCtrZoom : public CStatic
{
public:
    CCtrZoom();
    virtual ~CCtrZoom();
    void  DoTheZoomIn(CPoint pt, BOOL bDesktopPos = FALSE) {
        m_CurrentPoint = pt;
        m_bDesktopPos = bDesktopPos;
        Invalidate();
    }
    void  SetDesktopInfo(CDC* pDC, CSize DesktopSize) {
        m_pMemDC      = pDC;
        m_DesktopSize = DesktopSize;
        CRect rc;
        GetWindowRect(rc);
        rc.DeflateRect(2, 2);
        m_Size = CSize(rc.Width(), rc.Height());
    }
    int  GetZoomFactor() { return m_nZoomFactorTable[m_nZoomFactorIndex]; }
    void SetZoomFactor(BOOL bStepIt);

private:
    CDrawUtil m_DrawUtil;
    int       m_nZoomFactorTable[ZOOM_FACTOR_MAX];
    int       m_nZoomFactorIndex;
    CSize     m_DesktopSize; 
    CPoint    m_CurrentPoint;
    CSize     m_Size;
    CDC*      m_pMemDC;
    BOOL      m_bDesktopPos;

    //{{AFX_VIRTUAL(CCtrZoom)
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CCtrZoom)
    afx_msg void OnPaint();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


class CWinCaptureHelper : public CDialog
{
public:
    CWinCaptureHelper(CWnd* pParent = NULL);

    //{{AFX_DATA(CWinCaptureHelper)
    enum { IDD = IDD_DIALOG_SNAP_HELPER };
    CStatic     m_ctrZoomText;
    CCtrZoom    m_ctrZoomDraw;
    CStatic     m_ctrColorText;
    CCtrColor   m_ctrColorDraw;
    //}}AFX_DATA

private:
    CSize m_DesktopSize; 

public:
    BOOL  TrackPos(CDC* pDC, CPoint pt, BOOL bDesktopPos = FALSE);
    void  DoZoomFactor(BOOL bStepIt);
    void  SetDesktopInfo(CDC* pDC, CSize DesktopSize) {
        m_DesktopSize = DesktopSize;
        m_ctrZoomDraw.SetDesktopInfo(pDC, DesktopSize);
    }

private:
    void  UpdateColorInfo(CDC* pDC, CPoint pt);
    void  UpdateZoomFactor(int nZoomFactor);

    //{{AFX_VIRTUAL(CWinCaptureHelper)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    //}}AFX_VIRTUAL

// Implementation
protected:
    //{{AFX_MSG(CWinCaptureHelper)
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
