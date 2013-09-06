
// animationBase.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CanimationApp:
// See animationBase.cpp for the implementation of this class
//

class CanimationApp : public CWinApp
{
public:
	CanimationApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CanimationApp theApp;