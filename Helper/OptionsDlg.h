 /*---------------------------------------------------------------------------
|                                  DCUtility                                  |
|--------------------------------------+--------------------------------------|
|    SolutionName : ScreenSnaperGadget                                        |
|    ProjectName  : Helper                                                    |
|    FileName     : OptionsDlg.h                                              |
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

#include "WinCaptureHelper.h"

class CWinCapture;
class CWinCaptureHelper;

class COptionsDlg : public CDialog
{
public:
    COptionsDlg(CWnd* pParent = NULL);

    //{{AFX_DATA(COptionsDlg)
    enum { IDD = IDD_DIALOG_OPTIONS };
    CCtrColor       m_ctrColor;
    CSpinButtonCtrl m_ctrSpinRectangleRoundWidth;
    CSpinButtonCtrl m_ctrSpinBorderWidth;
    BOOL            m_bPlaySound;
    BOOL            m_bShowToolTip;
    int             m_nShape;
    BOOL            m_bShowHelp;
    //}}AFX_DATA

private:
    CWinCapture* m_pParent;
    int          m_nRectangleRoundWidth;
    int          m_nBorderWidth;
    COLORREF     m_Backcolor;

public:
    void SetParams(CWinCapture* pParent,
                   CDrawUtil::eDrawMode DrawMode,
                   int  nRectangleRoundWidth,
                   int  nBorderWidth,
                   COLORREF Backcolor,
                   BOOL bShowToolTip,
                   BOOL bPlaySound,
                   BOOL bShowHelp);
    
    void GetParams(CDrawUtil::eDrawMode& DrawMode,
                   int&  nRectangleRoundWidth,
                   int&  nBorderWidth,
                   COLORREF& Backcolor,
                   BOOL& bShowToolTip,
                   BOOL& bPlaySound,
                   BOOL& bShowHelp);

    //{{AFX_VIRTUAL(COptionsDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(COptionsDlg)
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    afx_msg void OnDeltaposSpinBorderWidth(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnDeltaposSpinRectangleRoundWidth(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnCheckHelp();
    afx_msg void OnButtonColor();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
