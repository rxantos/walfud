// dllmain.cpp : Implementation of DllMain.

#include "stdafx.h"
#include "resource.h"
#include "DropOnTarget_i.h"
#include "dllmain.h"

CDropOnTargetModule _AtlModule;

class CDropOnTargetApp : public CWinApp
{
public:

// Overrides
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CDropOnTargetApp, CWinApp)
END_MESSAGE_MAP()

CDropOnTargetApp theApp;

BOOL CDropOnTargetApp::InitInstance()
{
	return CWinApp::InitInstance();
}

int CDropOnTargetApp::ExitInstance()
{
	return CWinApp::ExitInstance();
}
