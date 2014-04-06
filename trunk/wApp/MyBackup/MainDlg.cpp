

// MainDlg.cpp
//

#include "stdafx.h"
#include "MainDlg.h"
#include "MyBackup.h"
using namespace std;
using namespace w;

LRESULT CMainDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	//Copy(string("c:\\1\\"), string("e:\\2\\"));
//	foo("E:\\walfud\\trunk\\wApp\\MyBackup\\test.xml");


	auto projs = traverseNextLevel("E:\\walfud\\trunk\\wApp\\MyBackup\\TestProjs\\");
	for (auto const &i : projs)
	{
		MyBackup mb;
		mb.Load(i);
		mb.Backup();
	}

	// center the dialog on the screen
	CenterWindow();

	// set icons
	HICON hIcon = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON));
	SetIcon(hIcon, TRUE);
	HICON hIconSmall = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON));
	SetIcon(hIconSmall, FALSE);

	// register object for message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);
	pLoop->AddIdleHandler(this);

	UIAddChildWindowContainer(m_hWnd);

	return TRUE;
}