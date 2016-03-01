 /*---------------------------------------------------------------------------
|                                  DCUtility                                  |
|--------------------------------------+--------------------------------------|
|    SolutionName : ScreenSnaperGadget                                        |
|    ProjectName  : Helper                                                    |
|    FileName     : DrawUtil.h                                                |
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

#include "MemDCEx.h"

class CDrawUtil  
{
public:
    CDrawUtil();
    virtual ~CDrawUtil();

    enum eDrawMode { DM_NONE = -1, DM_ELLIPSE, DM_RECTANGLE, DM_RECTANGLE_ROUND, };

    BOOL     DrawSreenCross(CDC* pDC,
                            CPoint pt,
                            CSize Size,
                            int nPenWidth = 1,
                            BOOL bDesktopPos = FALSE);

    BOOL     DrawFrame(CDC* pDC,
                       CRect rc,
                       BOOL bShowPos = TRUE,
                       eDrawMode DrawMode = DM_RECTANGLE,
                       int nPenWidth = 1,
                       CPoint pt = CPoint(0,0));

    BOOL     DrawPosition(CDC* pDC,
                          CRect rc,
                          BOOL bDesktopPos = FALSE);

    BOOL     DoTheZoom(CDC* pDCDest,
                       CSize SizeDest,
                       CDC* pDCSrc,
                       CSize SizeSrc,
                       CPoint point,
                       int nZoomFactor,
                       BOOL bDrawCross = TRUE,
                       int nCrossWidth = 1,
                       BOOL bDesktopPos = FALSE);

    CBitmap* CopyBitmap(CBitmap* poSourceBmp);
};
