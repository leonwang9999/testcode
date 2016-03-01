 /*---------------------------------------------------------------------------
|                                  DCUtility                                  |
|--------------------------------------+--------------------------------------|
|    SolutionName : ScreenSnaperGadget                                        |
|    ProjectName  : Helper                                                    |
|    FileName     : OptionsDlg.cpp                                            |
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
#include "OptionsDlg.h"
#include "WinCapture.h"
#include "WinCaptureHelper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

COptionsDlg::COptionsDlg(CWnd* pParent /*=NULL*/)
    : CDialog(COptionsDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(COptionsDlg)
    m_bPlaySound    = TRUE;
    m_bShowToolTip  = TRUE;
    m_nShape        = 0;
    m_bShowHelp     = FALSE;
    //}}AFX_DATA_INIT

    m_pParent              = NULL;
    m_nRectangleRoundWidth = 50;
    m_nBorderWidth         = 1;
}

void COptionsDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(COptionsDlg)
    DDX_Control(pDX, IDC_COLOR, m_ctrColor);
    DDX_Control(pDX, IDC_SPIN_RECTANGLE_ROUND_WIDTH, m_ctrSpinRectangleRoundWidth);
    DDX_Control(pDX, IDC_SPIN_BORDER_WIDTH, m_ctrSpinBorderWidth);
    DDX_Check(pDX, IDC_CHECK_PLAY_SOUND, m_bPlaySound);
    DDX_Check(pDX, IDC_CHECK_SHOW_TOOLTIP, m_bShowToolTip);
    DDX_Radio(pDX, IDC_RADIO_SHAPE, m_nShape);
    DDX_Check(pDX, IDC_CHECK_HELP, m_bShowHelp);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(COptionsDlg, CDialog)
    //{{AFX_MSG_MAP(COptionsDlg)
    ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_BORDER_WIDTH, OnDeltaposSpinBorderWidth)
    ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_RECTANGLE_ROUND_WIDTH, OnDeltaposSpinRectangleRoundWidth)
    ON_BN_CLICKED(IDC_CHECK_HELP, OnCheckHelp)
    ON_BN_CLICKED(IDC_BUTTON_COLOR, OnButtonColor)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL COptionsDlg::OnInitDialog() 
{
    CDialog::OnInitDialog();
    
    m_ctrSpinRectangleRoundWidth.SetRange(5, 250); 
    m_ctrSpinRectangleRoundWidth.SetPos(m_nRectangleRoundWidth);
    
    m_ctrSpinBorderWidth.SetRange(1, 15); 
    m_ctrSpinBorderWidth.SetPos(m_nBorderWidth);

    m_ctrColor.SetColor(m_Backcolor);
    
    UpdateData(0);
      
    SetWindowPos(&wndTopMost, 0,0, 0, 0, SWP_NOSIZE|SWP_NOMOVE|SWP_SHOWWINDOW);    

    CRect rc;
    GetWindowRect(rc);
    SetCursorPos(rc.right-rc.left/2, rc.bottom-rc.top/2);

    return TRUE;
}

void COptionsDlg::SetParams(CWinCapture* pParent,
                            CDrawUtil::eDrawMode DrawMode,
                            int  nRectangleRoundWidth,
                            int  nBorderWidth,
                            COLORREF Backcolor,
                            BOOL bShowToolTip,
                            BOOL bPlaySound,
                            BOOL bShowHelp)
{
    m_pParent               = pParent;
    m_nShape                = (int)DrawMode;
    m_nRectangleRoundWidth  = nRectangleRoundWidth;
    m_nBorderWidth          = nBorderWidth;
    m_Backcolor             = Backcolor;
    m_bShowToolTip          = bShowToolTip;
    m_bPlaySound            = bPlaySound;
    m_bShowHelp             = bShowHelp;
}

void COptionsDlg::GetParams(CDrawUtil::eDrawMode& DrawMode,
                            int&  nRectangleRoundWidth,
                            int&  nBorderWidth,
                            COLORREF& Backcolor,
                            BOOL& bShowToolTip,
                            BOOL& bPlaySound,
                            BOOL& bShowHelp)
{
    DrawMode              = (CDrawUtil::eDrawMode)m_nShape;
    nRectangleRoundWidth  = m_nRectangleRoundWidth;
    nBorderWidth          = m_nBorderWidth;
    Backcolor             = m_Backcolor;
    bShowToolTip          = m_bShowToolTip;
    bPlaySound            = m_bPlaySound;
    bShowHelp             = m_bShowHelp;
}

void COptionsDlg::OnOK() 
{
    UpdateData();
    
    m_nRectangleRoundWidth = m_ctrSpinRectangleRoundWidth.GetPos();
    m_nBorderWidth = m_ctrSpinBorderWidth.GetPos();
    m_Backcolor    = m_ctrColor.GetColor();

    UpdateData(0);
    
    CDialog::OnOK();
}

void COptionsDlg::OnDeltaposSpinBorderWidth(NMHDR* pNMHDR, LRESULT* pResult) 
{
    UNREFERENCED_PARAMETER(pNMHDR);
    
    CRect rc;
    GetDlgItem(IDC_STATIC_BORDER_WIDTH)->GetWindowRect(rc);
    ScreenToClient(rc);
    InvalidateRect(rc);
    *pResult = 0;
}

void COptionsDlg::OnDeltaposSpinRectangleRoundWidth(NMHDR* pNMHDR, LRESULT* pResult) 
{
    UNREFERENCED_PARAMETER(pNMHDR);

    CRect rc;
    GetDlgItem(IDC_STATIC_CORNER_WIDTH)->GetWindowRect(rc);
    ScreenToClient(rc);
    InvalidateRect(rc);
    *pResult = 0;
}

void COptionsDlg::OnCheckHelp() 
{
    m_pParent->UpdateHelperState();
}

void COptionsDlg::OnButtonColor() 
{
    CColorDialog Dlg;
    
    if (Dlg.DoModal() == IDOK) {
        m_ctrColor.SetColor(Dlg.GetColor()); 
    }
}
