 /*---------------------------------------------------------------------------
|                                  DCUtility                                  |
|--------------------------------------+--------------------------------------|
|    SolutionName : ScreenSnaperGadget                                        |
|    ProjectName  : Helper                                                    |
|    FileName     : SortableObList.cpp                                        |
|    CreationDate : 1999-03-02                                                |
|    Author       : Douglas Peterson                                          |
|    Comments     : http://www.codeguru.com/                                  |
|--------------------------------------+--------------------------------------|
|                             Screen Capture Tool                             |
|                         Windows Vista SideBar Gadget                        |
|--------------------------------------+--------------------------------------|
|                          Copyright © 2007 DCUtility                         |
|                              All rights reserved.                           |
 ---------------------------------------------------------------------------*/

#include "stdafx.h"
#include "SortableObList.h"

void CSortableObList::Sort(int (*CompareFunc)(CObject* pFirstObj,
                           CObject* pSecondObj))
{
    ASSERT_VALID(this);

    if (m_pNodeHead == NULL)
        return;

    CObject *pOtemp;
    CObList::CNode *pNi,*pNj;

    for (pNi = m_pNodeHead->pNext; pNi != NULL; pNi = pNi->pNext) {
        pOtemp = pNi->data;

        for (pNj = pNi;
            pNj->pPrev != NULL && CompareFunc(pNj->pPrev->data,pOtemp) > 0;
            pNj = pNj->pPrev)
            pNj->data = pNj->pPrev->data;

        pNj->data = pOtemp;
    }
}

void CSortableObList::Sort(POSITION posStart, int iElements,
                           int (*CompareFunc)(CObject* pFirstObj,
                           CObject* pSecondObj))
{
    ASSERT_VALID(this);
    ASSERT( AfxIsValidAddress((CObList::CNode*)posStart, sizeof(CObList::CNode)));

    if (m_pNodeHead == NULL)
        return;

    CObject *pOtemp;
    CObList::CNode *pNi,*pNj;

    for (pNi = (CObList::CNode*)posStart;
        pNi != NULL && iElements != 0;
        pNi = pNi->pNext, iElements--) {
        pOtemp = pNi->data;

        for (pNj = pNi;
            pNj->pPrev != NULL && pNj->pPrev != ((CObList::CNode*)posStart)->pPrev && CompareFunc(pNj->pPrev->data,pOtemp) > 0;
            pNj = pNj->pPrev)
            pNj->data = pNj->pPrev->data;

        pNj->data = pOtemp;
    }
}
