/*---------------------------------------------------------------------------
|                                  DCUtility                                  |
|--------------------------------------+--------------------------------------|
|    SolutionName : ScreenSnaperGadget                                        |
|    ProjectName  : Helper                                                    |
|    FileName     : SystemHelper.h                                            |
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

class CSystemHelper  
{
public:
	CSystemHelper();
	virtual ~CSystemHelper();

public:
    BOOL RegisterListener(BOOL bRegister);
    BOOL SetPrintScreen(pPrintScreenDelegate pDelegate, int nMode);
    void SetCaptureInProgress(BOOL bCaptureInProgress);
    BOOL ShowSettings();
    
private:
    BOOL LoadHook();
    BOOL UnloadHook();
    static LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
};
