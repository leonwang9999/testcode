 /*---------------------------------------------------------------------------
|                                  DCUtility                                  |
|--------------------------------------+--------------------------------------|
|    SolutionName : ScreenSnaperGadget                                        |
|    ProjectName  : Helper                                                    |
|    FileName     : SortableObList.h                                          |
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
#pragma once

#include <Afxcoll.h>
#include <Afxtempl.h>

class CSortableObList : public CObList
{
public:
    CSortableObList(int nBlockSize = 10) : CObList(nBlockSize) { }

    void Sort(int(*CompareFunc)(CObject* pFirstObj, CObject*pSecondObj));
    void Sort(POSITION posStart, int iElements,
              int (*CompareFunc)(CObject* pFirstObj, CObject* pSecondObj));
};

template< class TYPE >
class CTypedSortableObList : public CSortableObList
{
public:
    CTypedSortableObList(int nBlockSize = 10) : CSortableObList(nBlockSize) { }

    TYPE& GetHead()
        { return (TYPE&)CSortableObList::GetHead(); }
    TYPE GetHead() const
        { return (TYPE)CSortableObList::GetHead(); }
    TYPE& GetTail()
        { return (TYPE&)CSortableObList::GetTail(); }
    TYPE GetTail() const
        { return (TYPE)CSortableObList::GetTail(); }

    TYPE RemoveHead()
        { return (TYPE)CSortableObList::RemoveHead(); }
    TYPE RemoveTail()
        { return (TYPE)CSortableObList::RemoveTail(); }

    POSITION AddHead(TYPE newElement)
        { return CSortableObList::AddHead(newElement); }
    POSITION AddTail(TYPE newElement)
        { return CSortableObList::AddTail(newElement); }

    void AddHead(CTypedSortableObList< TYPE >* pNewList)
        { CSortableObList::AddHead(pNewList); }
    void AddTail(CTypedSortableObList< TYPE >* pNewList)
        { CSortableObList::AddTail(pNewList); }

    TYPE& GetNext(POSITION& rPosition)
        { return (TYPE&)CSortableObList::GetNext(rPosition); }
    TYPE GetNext(POSITION& rPosition) const
        { return (TYPE)CSortableObList::GetNext(rPosition); }
    TYPE& GetPrev(POSITION& rPosition)
        { return (TYPE&)CSortableObList::GetPrev(rPosition); }
    TYPE GetPrev(POSITION& rPosition) const
        { return (TYPE)CSortableObList::GetPrev(rPosition); }

    TYPE& GetAt(POSITION position)
        { return (TYPE&)CSortableObList::GetAt(position); }
    TYPE GetAt(POSITION position) const
        { return (TYPE)CSortableObList::GetAt(position); }
    void SetAt(POSITION pos, TYPE newElement)
        { CSortableObList::SetAt(pos, newElement); }

    void Sort( int(*CompareFunc)(TYPE pFirstObj, TYPE pSecondObj) )
        { CSortableObList::Sort((int(*)(CObject*,CObject*))CompareFunc); }
    void Sort( POSITION posStart, int iElements,
               int(*CompareFunc)(TYPE pFirstObj, TYPE pSecondObj) )
        { CSortableObList::Sort(posStart, iElements,
                                (int(*)(CObject*,CObject*))CompareFunc); }
};
