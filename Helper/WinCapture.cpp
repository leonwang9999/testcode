 /*---------------------------------------------------------------------------
|                                  DCUtility                                  |
|--------------------------------------+--------------------------------------|
|    SolutionName : ScreenSnaperGadget                                        |
|    ProjectName  : Helper                                                    |
|    FileName     : WinCapture.cpp                                            |
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
#include "OptionsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define SLEEP_TRACKED_INTERVAL  30
#define ID_TIMER_FRAME_RECT     2
#define TIMER_FRAME_RECT_ELAPSE 350
#define VK_PLUS                 187
#define VK_MINUS                189
#define PIXEL_INCREMENTAL_MOVE  10

#define SetRegInt AfxGetApp()->WriteProfileInt
#define GetRegInt AfxGetApp()->GetProfileInt

CWinCapture::CWinCapture(CWnd* pParent /*=NULL*/)
    : CDialog(CWinCapture::IDD, pParent)
{
    //{{AFX_DATA_INIT(CWinCapture)
    //}}AFX_DATA_INIT

    m_CaptureType           = CT_DESKTOP;
    
    m_CMWDrawMode           = (CDrawUtil::eDrawMode)GetRegInt("WinCapture",
                                                              "CMWDrawMode",
                                                              CDrawUtil::DM_RECTANGLE);
    m_bCMWShowPos           = GetRegInt("WinCapture", "bCMWShowPos", TRUE);
    m_nCMWPenWidth          = GetRegInt("WinCapture", "nCMWPenWidth", 3);
    m_nCMWRectRoundWidth    = GetRegInt("WinCapture", "nCMWRectRoundWidth", 25);
    m_CMRDrawMode           = (CDrawUtil::eDrawMode)GetRegInt("WinCapture",
                                                              "CMRDrawMode",
                                                              CDrawUtil::DM_RECTANGLE);
    m_bCMRShowPos           = GetRegInt("WinCapture", "bCMRShowPos", TRUE);
    m_nCMRPenWidth          = GetRegInt("WinCapture", "nCMRPenWidth", 1);
    m_nCMRRectRoundWidth    = GetRegInt("WinCapture", "nCMRRectRoundWidth", 25);
    m_Backcolor             = GetRegInt("WinCapture", "Backcolor", RGB(255, 0, 255));
    m_bPlaySound            = GetRegInt("WinCapture", "bPlaySound", TRUE);
    m_bShowHelp             = GetRegInt("WinCapture", "ShowHelper", TRUE);
        
    m_pOldMemBitmap         = NULL;
    m_FirstDownClick        = FALSE;
    m_bEndSelection         = FALSE;
    m_ShiftKeyPressed       = FALSE;
    m_bRestoreCursorArrow   = FALSE;
    m_bShowCursor           = TRUE;
}

BOOL CWinCapture::DestroyWindow() 
{
    SuspendTimer();
    
    if (m_pOldMemBitmap)
        m_MemDC.SelectObject(m_pOldMemBitmap);

    m_pWinCaptureHelper.DestroyWindow();

    SetRegInt("WinCapture", "CMWDrawMode", m_CMWDrawMode);
    SetRegInt("WinCapture", "bCMWShowPos", m_bCMWShowPos);
    SetRegInt("WinCapture", "nCMWPenWidth", m_nCMWPenWidth);
    SetRegInt("WinCapture", "nCMWRectRoundWidth", m_nCMWRectRoundWidth);
    SetRegInt("WinCapture", "CMRDrawMode", m_CMRDrawMode);
    SetRegInt("WinCapture", "bCMRShowPos", m_bCMRShowPos);
    SetRegInt("WinCapture", "nCMRPenWidth", m_nCMRPenWidth);
    SetRegInt("WinCapture", "nCMRRectRoundWidth", m_nCMRRectRoundWidth);
    SetRegInt("WinCapture", "Backcolor", m_Backcolor);
    SetRegInt("WinCapture", "bPlaySound", m_bPlaySound);

    return CDialog::DestroyWindow();
}

void CWinCapture::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CWinCapture)
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWinCapture, CDialog)
    //{{AFX_MSG_MAP(CWinCapture)
    ON_WM_ERASEBKGND()
    ON_WM_MOUSEMOVE()
    ON_WM_TIMER()
    ON_WM_SETCURSOR()
    ON_WM_LBUTTONDOWN()
    ON_WM_RBUTTONDOWN()
    ON_COMMAND(ID_POP_DISMISS, OnPopDismiss)
    ON_COMMAND(ID_POP_ACCEPT, OnPopAccept)
    ON_COMMAND(ID_POP_ABORT, OnPopAbort)
    ON_COMMAND(ID_POP_SWITCH_DESKTOP, OnPopSwitchDesktop)
    ON_COMMAND(ID_POP_SWITCH_WINDOW, OnPopSwitchWindow)
    ON_COMMAND(ID_POP_SWITCH_REGION, OnPopSwitchRegion)
    ON_COMMAND(ID_POP_OPTIONS, OnPopOptions)
    ON_COMMAND(ID_POP_TOGGLE_HELP, OnPopToggleHelp)
    ON_COMMAND(ID_POP_RESET_REGION, OnPopResetRegion)
    ON_COMMAND(ID_POP_TOGGLE_CURSOR, OnPopToggleCursor)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CWinCapture::OnInitDialog() 
{
    CDialog::OnInitDialog();
    
    m_WindowHelper.GetAllVisibleWindows();

    m_DesktopSize = CSize(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
    
    CWindowDC dc(NULL);
    m_MemBitmap.CreateCompatibleBitmap(&dc, m_DesktopSize.cx, m_DesktopSize.cy);
    m_MemDC.CreateCompatibleDC(&dc);
    m_pOldMemBitmap = m_MemDC.SelectObject(&m_MemBitmap);
    m_MemDC.BitBlt(0, 0, m_DesktopSize.cx, m_DesktopSize.cy, &dc, 0, 0, SRCCOPY);

    if (m_CaptureType == CT_DESKTOP) {
        m_rcSnap.SetRect(0, 0, m_DesktopSize.cx, m_DesktopSize.cy);
        OnOK();
    }
    else {
        SetCursorPos(m_DesktopSize.cx / 2, m_DesktopSize.cy / 2);

        SetWindowPos(&wndTopMost, 0,0, m_DesktopSize.cx, m_DesktopSize.cy, SWP_SHOWWINDOW);    
    
        m_pWinCaptureHelper.Create(IDD_DIALOG_SNAP_HELPER, this);
        m_pWinCaptureHelper.SetDesktopInfo(&m_MemDC, m_DesktopSize);
    
        if (m_CaptureType == CT_WINDOW)
            SetTimer(ID_TIMER_FRAME_RECT, TIMER_FRAME_RECT_ELAPSE, NULL);

        if (m_bShowHelp)
            m_pWinCaptureHelper.ShowWindow(SW_SHOW);
    }

    return TRUE;
}

BOOL CWinCapture::OnEraseBkgnd(CDC* pDC) 
{
    SetWindowPos(&wndTopMost, 0,0, m_DesktopSize.cx, m_DesktopSize.cy, SWP_SHOWWINDOW);    

    if (m_bEndSelection || m_CaptureType == CT_DESKTOP) {
        pDC->BitBlt(0, 0, m_DesktopSize.cx, m_DesktopSize.cy, &m_MemDC, 0, 0, SRCCOPY);    
        OnOK();
    }

    if (m_CaptureType == CT_WINDOW) {
        CMemDCEx MemDC(pDC);
        MemDC.BitBlt(0, 0, m_DesktopSize.cx, m_DesktopSize.cy, &m_MemDC, 0, 0, SRCCOPY);    
        m_DrawUtil.DrawFrame(&MemDC, m_rcSnap, m_bCMWShowPos, m_CMWDrawMode, m_nCMWPenWidth,
                             CPoint(m_nCMWRectRoundWidth, m_nCMWRectRoundWidth));
    }
    else if (m_CaptureType == CT_REGION) {
        
        if (!m_FirstDownClick) {
            pDC->BitBlt(0, 0, m_DesktopSize.cx, m_DesktopSize.cy, &m_MemDC, 0, 0, SRCCOPY);    
            m_DrawUtil.DrawSreenCross(pDC, m_CurrentPoint, m_DesktopSize);
        }
        else {
            CMemDCEx MemDC(pDC);
            MemDC.BitBlt(0, 0, m_DesktopSize.cx, m_DesktopSize.cy, &m_MemDC, 0, 0, SRCCOPY);    
            m_DrawUtil.DrawFrame(&MemDC, m_rcSnap, m_bCMRShowPos, m_CMRDrawMode, m_nCMRPenWidth,
                                 CPoint(m_nCMRRectRoundWidth, m_nCMRRectRoundWidth));
        }    
    }

    return TRUE;
}

BOOL CWinCapture::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
    UNREFERENCED_PARAMETER(pWnd);
    UNREFERENCED_PARAMETER(nHitTest);
    UNREFERENCED_PARAMETER(message);
    
    if (m_bShowCursor || m_bRestoreCursorArrow) {

        if (m_bRestoreCursorArrow) {
            SetCursor(LoadCursor(NULL, IDC_ARROW));
        }
        else if (m_CaptureType == CT_WINDOW) {
            SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR_WINDOW));
        }
        else if (m_CaptureType == CT_REGION) {

            if (!m_FirstDownClick)
                SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR_CROSS));
            else
                SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR_TRACKER));
        }
    }
    else
        SetCursor(NULL);

    return TRUE;
}

void CWinCapture::OnTimer(UINT_PTR nIDEvent) 
{
    if (m_CaptureType != CT_WINDOW)
        SuspendTimer();
    else if (nIDEvent == ID_TIMER_FRAME_RECT)
        FlashFrameRect();
    else 
        CDialog::OnTimer(nIDEvent);
}

void CWinCapture::FlashFrameRect()
{
    CClientDC dc(this);
    m_DrawUtil.DrawFrame(&dc, m_rcSnap, m_bCMWShowPos, m_CMWDrawMode, m_nCMWPenWidth,
                         CPoint(m_nCMWRectRoundWidth, m_nCMWRectRoundWidth));
}

void CWinCapture::OnLButtonDown(UINT nFlags, CPoint point) 
{
    if (m_CaptureType == CT_WINDOW) {

        SuspendTimer();
        m_bEndSelection = TRUE;
        Invalidate();
        UpdateHelperState(FALSE, FALSE);
    }
    else if (m_CaptureType == CT_REGION) {
    
        m_FirstDownClick = !m_FirstDownClick;

        if (!m_FirstDownClick) {

            m_bEndSelection = TRUE;
            Invalidate();
            UpdateHelperState(FALSE, FALSE); 
        }
        else {
            m_LastPoint = point;
        }
    }

    CDialog::OnLButtonDown(nFlags, point);
}

void CWinCapture::OnMouseMove(UINT nFlags, CPoint point) 
{ 
    SetWindowPos(&wndTopMost, 0,0, m_DesktopSize.cx, m_DesktopSize.cy, SWP_SHOWWINDOW);    
    
    BOOL bTraked = m_pWinCaptureHelper.TrackPos(
                       &m_MemDC,
                       point,
                       (m_CaptureType == CT_REGION && !m_FirstDownClick)?TRUE:FALSE
                   );
    
    if (m_CaptureType == CT_WINDOW) {

        CRect rc = m_WindowHelper.GetWindowRectFromPoint(point);
    
        if (m_rcSnap != rc || bTraked) {

            m_rcSnap = rc;
            if (bTraked)
                Sleep(SLEEP_TRACKED_INTERVAL);

            Invalidate();
        }
    }
    else if (m_CaptureType == CT_REGION) {

        if (m_FirstDownClick) {
            m_rcSnap.SetRect(m_LastPoint.x, m_LastPoint.y,
                             point.x, point.y);
            m_rcSnap.NormalizeRect();
        }

        Invalidate();
    }
    
    m_CurrentPoint = point;

    CDialog::OnMouseMove(nFlags, point);
}

CBitmap* CWinCapture::GetSnapBitmap(BOOL& bPlaySound)
{
    bPlaySound = m_bPlaySound;

    if (m_rcSnap.IsRectEmpty())
        return NULL;

    if (m_CaptureType == CT_DESKTOP) {
        return m_DrawUtil.CopyBitmap(&m_MemBitmap);
    }

    CWindowDC dc(NULL);
    m_MemDC.DeleteDC();
    m_MemBitmap.DeleteObject();

    if (!m_MemDC.CreateCompatibleDC(&dc))
        return NULL;
    
    if (!m_MemBitmap.CreateCompatibleBitmap(&dc, m_rcSnap.Width(), m_rcSnap.Height()))
        return NULL;

    m_pOldMemBitmap = m_MemDC.SelectObject(&m_MemBitmap);
    
    CDrawUtil::eDrawMode DrawMode = CDrawUtil::DM_RECTANGLE;
    int       nRectRoundWidth      = 0;
    int       nPenWidth;

    if (m_CaptureType == CT_WINDOW) {
        DrawMode        = m_CMWDrawMode;
        nPenWidth       = m_nCMWPenWidth;
        nRectRoundWidth = m_nCMWRectRoundWidth;
    }
    else if (m_CaptureType == CT_REGION) {
        DrawMode        = m_CMRDrawMode;
        nPenWidth       = m_nCMRPenWidth;
        nRectRoundWidth = m_nCMRRectRoundWidth;
    }

    if (DrawMode != CDrawUtil::DM_RECTANGLE && m_CaptureType != CT_DESKTOP) {
        
        CRect rcSnap = CRect(0, 0, m_rcSnap.Width(), m_rcSnap.Height());
        CRgn  rgn;

        if (DrawMode == CDrawUtil::DM_ELLIPSE)
            rgn.CreateEllipticRgnIndirect(rcSnap);
        else
            rgn.CreateRoundRectRgn(0, 0, rcSnap.Width(), rcSnap.Height(),
                                   nRectRoundWidth, nRectRoundWidth);

        m_MemDC.FillSolidRect(rcSnap, m_Backcolor);
        m_MemDC.SelectClipRgn(&rgn);
        m_MemDC.BitBlt(0, 0, m_rcSnap.Width(), m_rcSnap.Height(), &dc,
                       m_rcSnap.left, m_rcSnap.top, SRCCOPY);
        rgn.DeleteObject();
    }
    else
        m_MemDC.BitBlt(0, 0, m_rcSnap.Width(), m_rcSnap.Height(), &dc,
                       m_rcSnap.left, m_rcSnap.top, SRCCOPY);

    m_MemDC.SelectObject(&m_pOldMemBitmap);
    m_MemDC.DeleteDC();

    return m_DrawUtil.CopyBitmap(&m_MemBitmap);
}

BOOL CWinCapture::PreTranslateMessage(MSG* pMsg) 
{
    if(pMsg->message == WM_KEYDOWN) {

        CPoint pt = m_CurrentPoint;

        switch (pMsg->wParam) {
        case VK_RETURN:
            return TRUE;
            break;
        case VK_ADD:
        case VK_PLUS:
            m_pWinCaptureHelper.DoZoomFactor(TRUE);
            break;
        case VK_SUBTRACT:
        case VK_MINUS:
            m_pWinCaptureHelper.DoZoomFactor(FALSE);
            break;
        case VK_F1:
            UpdateHelperState();
            break;
         case VK_SPACE:
            OnLButtonDown(MK_LBUTTON, m_CurrentPoint);
            break;
        case VK_UP:
            pt.y -= (m_ShiftKeyPressed)?PIXEL_INCREMENTAL_MOVE:1;
            SetCursorPos(pt.x, pt.y);
            OnMouseMove(0, pt);
            break;
        case VK_DOWN:
            pt.y += (m_ShiftKeyPressed)?PIXEL_INCREMENTAL_MOVE:1;
            SetCursorPos(pt.x, pt.y);
            OnMouseMove(0, pt);
            break;
        case VK_LEFT:
            pt.x -= (m_ShiftKeyPressed)?PIXEL_INCREMENTAL_MOVE:1;
            SetCursorPos(pt.x, pt.y);
            OnMouseMove(0, pt);
            break;
        case VK_RIGHT:
            pt.x += (m_ShiftKeyPressed)?PIXEL_INCREMENTAL_MOVE:1;
            SetCursorPos(pt.x, pt.y);
            OnMouseMove(0, pt);
            break;
        case VK_SHIFT:
            m_ShiftKeyPressed = TRUE;
            break;
        }
    }
    else if(pMsg->message == WM_KEYUP) {

        switch (pMsg->wParam) {
        case VK_SHIFT:
            m_ShiftKeyPressed = FALSE;
            break;
        }        
    }

    return CDialog::PreTranslateMessage(pMsg);
}


void CWinCapture::OnRButtonDown(UINT nFlags, CPoint point) 
{
    CMenu Menu;

    if (m_CaptureType == CT_WINDOW) {
        Menu.LoadMenu(IDR_MENU_WINDOW_MODE);
    }
    else if (m_CaptureType == CT_REGION) {
        Menu.LoadMenu(IDR_MENU_REGION_MODE);

        if (!m_FirstDownClick) {
            Menu.EnableMenuItem(ID_POP_RESET_REGION, MF_BYCOMMAND|MF_GRAYED);
        }
    }
    else
        return;

    CMenu* pMenu = Menu.GetSubMenu(0);
    pMenu->SetDefaultItem(ID_POP_ACCEPT);
    pMenu->CheckMenuItem(ID_POP_TOGGLE_CURSOR,
                         MF_BYCOMMAND|(m_bShowCursor)?MF_CHECKED:MF_UNCHECKED);
    pMenu->CheckMenuItem(ID_POP_TOGGLE_HELP,
                         MF_BYCOMMAND|(m_pWinCaptureHelper.IsWindowVisible())?MF_CHECKED:MF_UNCHECKED);
    
    if (m_CaptureType == CT_REGION && !m_FirstDownClick)
        pMenu->EnableMenuItem(ID_POP_RESET_REGION, MF_BYCOMMAND|MF_GRAYED);
    
    ShowArrowCursor(TRUE, CPoint(10, 10));
    SuspendTimer();
    pMenu->TrackPopupMenu(TPM_RIGHTBUTTON, point.x+1, point.y+1, this, NULL);
    ShowArrowCursor(FALSE);
    SuspendTimer(FALSE);

    CDialog::OnRButtonDown(nFlags, point);
}

void CWinCapture::OnPopDismiss() {}

void CWinCapture::OnPopAccept() 
{
    OnLButtonDown(MK_LBUTTON, m_CurrentPoint);
}

void CWinCapture::OnPopAbort() 
{
    OnCancel();    
}

void CWinCapture::OnPopSwitchDesktop() 
{
    SuspendTimer();
    m_CaptureType = CT_DESKTOP;
    m_rcSnap.SetRect(0, 0, m_DesktopSize.cx, m_DesktopSize.cy);
    UpdateHelperState(FALSE, FALSE);
}

void CWinCapture::OnPopSwitchWindow() 
{
    m_CaptureType = CT_WINDOW;
    Invalidate();
    SuspendTimer(FALSE);
}

void CWinCapture::OnPopSwitchRegion() 
{
    OnPopResetRegion();
}

void CWinCapture::OnPopResetRegion() 
{
    SuspendTimer();
    m_FirstDownClick = FALSE;
    m_CaptureType    = CT_REGION;
}

void CWinCapture::OnPopToggleCursor() 
{
    m_bShowCursor = !m_bShowCursor;    
}

void CWinCapture::OnPopOptions() 
{
    COptionsDlg Dlg;
    
    if (m_CaptureType == CT_WINDOW) {

        Dlg.SetParams(this,
                      m_CMWDrawMode,
                      m_nCMWRectRoundWidth,
                      m_nCMWPenWidth,
                      m_Backcolor,
                      m_bCMWShowPos,
                      m_bPlaySound,
                      m_bShowHelp);
    }
    else if (m_CaptureType == CT_REGION) {

        Dlg.SetParams(this,
                      m_CMRDrawMode,
                      m_nCMRRectRoundWidth,
                      m_nCMRPenWidth,
                      m_Backcolor,
                      m_bCMRShowPos,
                      m_bPlaySound,
                      m_bShowHelp);
    }

    ShowArrowCursor(TRUE, CPoint(-1, -1));
    SuspendTimer();
    
    if (Dlg.DoModal() == IDOK) {

        if (m_CaptureType == CT_WINDOW) {

            Dlg.GetParams(m_CMWDrawMode,
                          m_nCMWRectRoundWidth,
                          m_nCMWPenWidth,
                          m_Backcolor,
                          m_bCMWShowPos,
                          m_bPlaySound,
                          m_bShowHelp);
        }
        else if (m_CaptureType == CT_REGION) {

            Dlg.GetParams(m_CMRDrawMode,
                          m_nCMRRectRoundWidth,
                          m_nCMRPenWidth,
                          m_Backcolor,
                          m_bCMRShowPos,
                          m_bPlaySound,
                          m_bShowHelp);
        }
    }

    ShowArrowCursor(FALSE);
    SuspendTimer(FALSE);
}

void CWinCapture::OnPopToggleHelp() 
{
    UpdateHelperState();
}


void CWinCapture::ShowArrowCursor(BOOL bShowArrow, CPoint pt)
{
    m_bRestoreCursorArrow = bShowArrow;

    if (pt != CPoint(-1, -1)) {
        SetCursorPos(m_CurrentPoint.x+pt.x , m_CurrentPoint.y+pt.y);
    }
}

void CWinCapture::SuspendTimer(BOOL bSuspend)
{
    if (m_CaptureType == CT_WINDOW) {
        if (bSuspend) {
            KillTimer(ID_TIMER_FRAME_RECT);
        }
        else {
            SetTimer(ID_TIMER_FRAME_RECT, TIMER_FRAME_RECT_ELAPSE, NULL);
        }
    }
}

void CWinCapture::UpdateHelperState(BOOL bShow, BOOL bSave)
{
    BOOL bVisible = m_pWinCaptureHelper.IsWindowVisible();

    if (bShow)
        m_pWinCaptureHelper.ShowWindow((!bVisible)?SW_SHOW:SW_HIDE);
    else
        m_pWinCaptureHelper.ShowWindow(SW_HIDE);

    if (bVisible || !bShow) {
        Sleep(SLEEP_TRACKED_INTERVAL);
        Invalidate();
    }

    if (bSave) {
        m_bShowHelp = m_pWinCaptureHelper.IsWindowVisible();
        SetRegInt("WinCapture", "ShowHelper", m_bShowHelp);
    }
}
