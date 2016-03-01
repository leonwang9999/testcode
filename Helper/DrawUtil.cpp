 /*---------------------------------------------------------------------------
|                                  DCUtility                                  |
|--------------------------------------+--------------------------------------|
|    SolutionName : ScreenSnaperGadget                                        |
|    ProjectName  : Helper                                                    |
|    FileName     : DrawUtil.cpp                                              |
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
#include "DrawUtil.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define BOUND(x,min,max) ((x) < (min) ? (min) : ((x) > (max) ? (max) : (x)))

CDrawUtil::CDrawUtil()
{
}

CDrawUtil::~CDrawUtil()
{
}

BOOL CDrawUtil::DoTheZoom(CDC* pDCDest, CSize SizeDest, CDC* pDCSrc,
                          CSize SizeSrc, CPoint point, int nZoomFactor,
                          BOOL bDrawCross, int nCrossWidth, BOOL bDesktopPos)
{
    CSize       Zoomed;
    CBitmap     Bitmap;
    CPoint      pt;

    Zoomed.cx = ((SizeDest.cx / nZoomFactor) / 2) + 1;
    Zoomed.cy = ((SizeDest.cy / nZoomFactor) / 2) + 1;

    Bitmap.CreateCompatibleBitmap(pDCSrc, SizeDest.cx, SizeDest.cy);
    CBitmap* pOldBitmap = pDCDest->SelectObject(&Bitmap);

    pt.x = BOUND(point.x, Zoomed.cx, SizeSrc.cx - Zoomed.cx);
    pt.y = BOUND(point.y, Zoomed.cy, SizeSrc.cy - Zoomed.cy);

    pDCDest->SetStretchBltMode(COLORONCOLOR);
    pDCDest->StretchBlt(0, 0, SizeDest.cx, SizeDest.cy,
                  pDCSrc, 
                  pt.x - Zoomed.cx, pt.y - Zoomed.cy,
                  Zoomed.cx*2, Zoomed.cy*2,
                  SRCCOPY);

    if (bDrawCross) {
        pt = CPoint(SizeDest.cx/2, SizeDest.cy/2);
        DrawSreenCross(pDCDest, pt, CSize(SizeDest.cx, SizeDest.cy),
                       nCrossWidth, (bDesktopPos)?TRUE:FALSE);
        pDCDest->SetROP2(R2_NOT);
        pDCDest->Rectangle(pt.x, pt.y, pt.x+nZoomFactor-1, pt.y+nZoomFactor-1);
    }

    pDCDest->SelectObject(pOldBitmap);
    Bitmap.DeleteObject();
    
    return TRUE;
}

BOOL CDrawUtil::DrawSreenCross(CDC* pDC, CPoint pt, CSize Size,
                               int nPenWidth, BOOL bDesktopPos)
{
    UNREFERENCED_PARAMETER(nPenWidth);

    BOOL bRet;

    bRet  = pDC->PatBlt(0, pt.y, Size.cx, 1, DSTINVERT);
    bRet |= pDC->PatBlt(pt.x, 0, 1, Size.cy, DSTINVERT);

    if (bDesktopPos) {
        CRect  rc(0, 0, pt.x, pt.y);
        bRet |= DrawPosition(pDC, rc, bDesktopPos);
    }

    return bRet;
}

BOOL CDrawUtil::DrawFrame(CDC* pDC, CRect rc, BOOL bShowPos, eDrawMode DrawMode,
                          int nPenWidth, CPoint pt)
{
    CPen Pen;
    if (!Pen.CreatePen(PS_INSIDEFRAME,
                       nPenWidth * GetSystemMetrics(SM_CXBORDER), RGB(0,0,0)))
        return FALSE;
    
    CBrush* pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
    if (!pBrush)
        return FALSE;
    
    CPen* pOldPen = pDC->SelectObject(&Pen);
    CBrush* pOldBrush = pDC->SelectObject(pBrush);
    
    pDC->SetROP2(R2_NOT);
    
    if (DrawMode == DM_ELLIPSE)
        pDC->Ellipse(rc);
    else if (DrawMode == DM_RECTANGLE)
        pDC->Rectangle(rc);
    else if (DrawMode == DM_RECTANGLE_ROUND)
        pDC->RoundRect(rc, pt);    

    pDC->SelectObject(pOldBrush);
    pDC->SelectObject(pOldPen);
    
    Pen.DeleteObject();
    pBrush->DeleteObject();

    if (bShowPos)
        return DrawPosition(pDC, rc);

    return TRUE;
}

BOOL CDrawUtil::DrawPosition(CDC* pDC, CRect rc, BOOL bDesktopPos)
{
    CString sz;
    CPoint  pt;
    CSize   Size;

    if (bDesktopPos) {
        GetCursorPos(&pt);
        sz.Format("%dx%d", pt.x+1, pt.y+1);
    }
    else
        sz.Format("%dx%d", rc.right-rc.left+1, rc.bottom-rc.top+1);

    Size = pDC->GetTextExtent(sz);
    
    pt.x  =  (rc.Width() < Size.cx*3)&&(rc.Height() < Size.cy*3)?
             abs(rc.left-Size.cx):abs(rc.right+rc.left - Size.cx) / 2;
    
    pt.y  =  ((rc.Height() < Size.cy*3)&&(rc.Width() < Size.cx*3))?
             abs(rc.top-Size.cy):abs(rc.bottom+rc.top - Size.cy) / 2;
    
    pDC->SetTextColor(RGB(255, 255, 255));
    pDC->SetBkColor(RGB(0, 0, 0));

    return pDC->ExtTextOut(pt.x, pt.y, 0, NULL, sz, NULL);
}

CBitmap* CDrawUtil::CopyBitmap(CBitmap* poSourceBmp)
{
    if (!poSourceBmp)
        return NULL;

    BITMAP bmp;
    poSourceBmp->GetBitmap(&bmp);

    CBitmap* poCloneBmp = new CBitmap();
    if (!poCloneBmp->CreateBitmapIndirect(&bmp))
    {
        delete poCloneBmp;
        return NULL;
    }

    CDC oSourceDC, oDestDC;
    if (!oSourceDC.CreateCompatibleDC(NULL) ||
        !oDestDC.CreateCompatibleDC(NULL))
    {
        delete poCloneBmp;
        return NULL;
    }

    CBitmap* poPrevSrcBmp = oSourceDC.SelectObject(poSourceBmp);
    CBitmap* poPrevDestBmp = oDestDC.SelectObject(poCloneBmp);

    oDestDC.BitBlt(0, 0, bmp.bmWidth, bmp.bmHeight, &oSourceDC, 0, 0, SRCCOPY);

    oDestDC.SelectObject(poPrevDestBmp);
    oSourceDC.SelectObject(poPrevSrcBmp);

    return poCloneBmp;
}
