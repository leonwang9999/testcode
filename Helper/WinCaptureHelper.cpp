 /*---------------------------------------------------------------------------
|                                  DCUtility                                  |
|--------------------------------------+--------------------------------------|
|    SolutionName : ScreenSnaperGadget                                        |
|    ProjectName  : Helper                                                    |
|    FileName     : WinCaptureHelper.cpp                                      |
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
#include "WinCaptureHelper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CCtrColor::CCtrColor()
{
    m_BackColor = RGB(0, 255, 0);    
}

BEGIN_MESSAGE_MAP(CCtrColor, CStatic)
    //{{AFX_MSG_MAP(CCtrColor)
    ON_WM_PAINT()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CCtrColor::OnPaint() 
{
    CPaintDC dc(this);
    CRect rect;
    GetClientRect(rect);
    dc.FillSolidRect(rect, m_BackColor);
}

CCtrZoom::CCtrZoom()
{
    m_nZoomFactorIndex = AfxGetApp()->GetProfileInt((LPCTSTR)"WinCapture",
                                                    (LPCTSTR)"ZoomFactor",
                                                    ZOOM_FACTOR_DEFAULT);
    
    int nTemp[] = {2, 3, 4, 5, 6, 7, 8, 10, 12, 14};
    for (int i = ZOOM_FACTOR_MIN; i < ZOOM_FACTOR_MAX; i++)
        m_nZoomFactorTable[i] = nTemp[i];

    m_bDesktopPos = FALSE;
};

CCtrZoom::~CCtrZoom()
{
    AfxGetApp()->WriteProfileInt((LPCTSTR)"WinCapture",
                                 (LPCTSTR)"ZoomFactor",
                                 m_nZoomFactorIndex);
};

BEGIN_MESSAGE_MAP(CCtrZoom, CStatic)
    //{{AFX_MSG_MAP(CCtrZoom)
    ON_WM_PAINT()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CCtrZoom::OnPaint() 
{
    CPaintDC dc(this);

    m_DrawUtil.DoTheZoom(&dc, m_Size, m_pMemDC, m_DesktopSize, m_CurrentPoint,
                         m_nZoomFactorTable[m_nZoomFactorIndex], TRUE, 1, m_bDesktopPos);
}

void CCtrZoom::SetZoomFactor(BOOL bStepIt)
{
    BOOL bErase = FALSE;

    if (bStepIt) {
        if (m_nZoomFactorIndex < ZOOM_FACTOR_MAX-1) {
            m_nZoomFactorIndex++;
            bErase = TRUE;
        }
    }
    else {
        if (m_nZoomFactorIndex > ZOOM_FACTOR_MIN) {
            m_nZoomFactorIndex--;
            bErase = TRUE;
        }
    }
    
    if (bErase)
        DoTheZoomIn(m_CurrentPoint, m_bDesktopPos);
}

CWinCaptureHelper::CWinCaptureHelper(CWnd* pParent /*=NULL*/)
    : CDialog(CWinCaptureHelper::IDD, pParent)
{
    //{{AFX_DATA_INIT(CWinCaptureHelper)
    //}}AFX_DATA_INIT
}

void CWinCaptureHelper::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CWinCaptureHelper)
    DDX_Control(pDX, IDC_ZOOM_TEXT, m_ctrZoomText);
    DDX_Control(pDX, IDC_ZOOM_DRAW, m_ctrZoomDraw);
    DDX_Control(pDX, IDC_COLOR_TEXT, m_ctrColorText);
    DDX_Control(pDX, IDC_COLOR_DRAW, m_ctrColorDraw);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWinCaptureHelper, CDialog)
    //{{AFX_MSG_MAP(CWinCaptureHelper)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CWinCaptureHelper::OnInitDialog() 
{
    CDialog::OnInitDialog();

    UpdateZoomFactor(m_ctrZoomDraw.GetZoomFactor());

    return TRUE;
}

BOOL CWinCaptureHelper::TrackPos(CDC* pDC, CPoint pt, BOOL bDesktopPos)
{
    BOOL bTraked = TRUE;

    CRect rc;
    GetWindowRect(rc);
    CSize Tolerance(10, -(rc.Height() / 2));

    if (rc.left == 0 && rc.top == 0) {
        
        if (pt.x < rc.right+Tolerance.cx)
            SetWindowPos(NULL, m_DesktopSize.cx-rc.Width(), rc.top, 0, 0, SWP_NOSIZE);
        else if (pt.y < rc.bottom+Tolerance.cy)
            SetWindowPos(NULL, rc.left, m_DesktopSize.cy-rc.Height(), 0, 0, SWP_NOSIZE);
        else
            bTraked = FALSE;
    }
    else if (rc.left == 0 && rc.top != 0) {
        
        if (pt.x < rc.right+Tolerance.cx)
            SetWindowPos(NULL, m_DesktopSize.cx-rc.Width(), rc.top, 0, 0, SWP_NOSIZE);
        else if (pt.y > rc.top-Tolerance.cy)
            SetWindowPos(NULL, rc.left, 0, 0, 0, SWP_NOSIZE);
        else
            bTraked = FALSE;
    }
    else if (rc.left != 0 && rc.top == 0) {
        
        if (pt.x > rc.left-Tolerance.cx)
            SetWindowPos(NULL, 0, rc.top, 0, 0, SWP_NOSIZE);
        else if (pt.y < rc.bottom+Tolerance.cy)
            SetWindowPos(NULL, rc.left, m_DesktopSize.cy-rc.Height(), 0, 0, SWP_NOSIZE);
        else
            bTraked = FALSE;
    }
    else if (rc.left != 0 && rc.top != 0) {
        
        if (pt.x > rc.left-Tolerance.cx)
            SetWindowPos(NULL, 0, rc.top, 0, 0, SWP_NOSIZE);
        else if (pt.y > rc.top-Tolerance.cy)
            SetWindowPos(NULL, rc.left, 0, 0, 0, SWP_NOSIZE);
        else
            bTraked = FALSE;
    }
    else
        bTraked = FALSE;

    m_ctrZoomDraw.DoTheZoomIn(pt, bDesktopPos);

    if (pDC)
        UpdateColorInfo(pDC, pt); 
    
    return bTraked;
}

void CWinCaptureHelper::DoZoomFactor(BOOL bStepIt)
{
    m_ctrZoomDraw.SetZoomFactor(bStepIt);
    UpdateZoomFactor(m_ctrZoomDraw.GetZoomFactor());
}

void CWinCaptureHelper::UpdateZoomFactor(int nZoomFactor)
{
    CString sz;
    CRect   rc;
    sz.Format("1:%d", nZoomFactor);
    m_ctrZoomText.SetWindowText(sz);
    m_ctrZoomText.GetWindowRect(rc);
    ScreenToClient(rc);
    InvalidateRect(rc);

}

void CWinCaptureHelper::UpdateColorInfo(CDC* pDC, CPoint pt)
{
    COLORREF  col = pDC->GetPixel(pt);
    CString   sz;
    CRect     rc;

    sz.Format("RGB: %d-%d-%d", GetRValue(col), GetGValue(col), GetBValue(col));
    m_ctrColorText.SetWindowText(sz);
    m_ctrColorText.GetWindowRect(rc);
    ScreenToClient(rc);
    InvalidateRect(rc);

    m_ctrColorDraw.SetColor(col);
    m_ctrColorDraw.GetWindowRect(rc);
    ScreenToClient(rc);
    InvalidateRect(rc);
}
