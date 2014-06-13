#include "StdAfx.h"
#include "Resource.h"
#include "MainDlg.h"
#include <atlctrls.h>
using namespace std;
using namespace w;

bool ProcNameAsc(const ProcessInfo &a, const ProcessInfo &b) { return a.name < b.name; }
bool ProcNameDesc(const ProcessInfo &a, const ProcessInfo &b) { return a.name > b.name; }
bool PidAsc(const ProcessInfo &a, const ProcessInfo &b) { return a.id < b.id; }
bool PidDesc(const ProcessInfo &a, const ProcessInfo &b) { return a.id > b.id; }

LRESULT CMainDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// center the dialog on the screen
	CenterWindow();

	// set icons
	HICON hIcon = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
		IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
	SetIcon(hIcon, TRUE);
	HICON hIconSmall = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
		IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
	SetIcon(hIconSmall, FALSE);

	// Initialize list control 'IDC_LIST_PROC'.
	auto p = static_cast<CListViewCtrl &>(GetDlgItem(IDC_LIST_PROC));
	p.InsertColumn(0, "proc name", LVCFMT_LEFT, 300);
	p.InsertColumn(1, "pid", LVCFMT_LEFT, 200);

	m_sort = Sort::ProcName_Asc;

	auto checkRefresh = static_cast<CButton &>(GetDlgItem(IDC_CHECK_REFRESH_BEFORE_CRASH_IT));
	checkRefresh.SetCheck(TRUE);

	// 
	GetDlgItem(IDC_EDIT_SVN).SetWindowText("http://walfud.googlecode.com/svn/trunk/wApp/WeAreOne");
	GetDlgItem(IDC_EDIT_NEWEST_BINARY).SetWindowText("http://walfud.googlecode.com/svn/trunk/wApp/bin/WeAreOne");

	// 
	GetDlgItem(IDC_EDIT_INJECTEE_FILENAME).SetWindowText("crashee.dll");
	GetDlgItem(IDC_EDIT_INJECTEE_FILENAME64).SetWindowText("crashee64.dll");

	return TRUE;
}
LRESULT CMainDlg::OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// Get proc info from system.
	auto mProcInfo = getProcessesInfo();

	// `map` => `vector`.
	m_procInfo.clear();
	vector<ProcessInfo> vProcInfo;
	transform(mProcInfo.begin(), mProcInfo.end(), back_inserter(m_procInfo), [](const pair<int, ProcessInfo> &m) -> ProcessInfo { return m.second; });

	// Draw.
	drawWithSort();

	return 0;
}
LRESULT CMainDlg::OnKeyDown(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// If focus is on edit ctrl, we crash the specified program.
	auto vKey = static_cast<DWORD>(wParam);
	switch (vKey)
	{
	case VK_RETURN:
		{
			// Refresh if needed.
			auto checkRefresh = static_cast<CButton &>(GetDlgItem(IDC_CHECK_REFRESH_BEFORE_CRASH_IT));
			if (checkRefresh.GetCheck())
			{
				SendMessage(WM_LBUTTONDOWN, 0, 0);
			}

			// Kill by ??.
			auto focus = GetFocus();
			if (focus == GetDlgItem(IDC_EDIT_TARGET_PROCNAME).m_hWnd)
			{
				crashByProcname();
			}
			else if (focus == GetDlgItem(IDC_EDIT_TARGET_PID).m_hWnd)
			{
				crashByPid();
			}
		}
		break;

	default:
		break;
	}

	return 0;
}
LRESULT CMainDlg::OnProcListHeadClick(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/)
{
	auto pNMListView = (NM_LISTVIEW *)pNMHDR;
	switch (pNMListView->iSubItem)
	{
	case 0:
		// Sort by proc name.
		switch (m_sort)
		{
		case Sort::ProcName_Asc:
			m_sort = Sort::ProcName_Desc;
			break;

		case Sort::ProcName_Desc:
			m_sort = Sort::ProcName_Asc;
			break;

		default:
			m_sort = Sort::ProcName_Asc;
			break;
		}
		break;

	case 1:
		// Sort by pid.
		switch (m_sort)
		{
		case Sort::Pid_Asc:
			m_sort = Sort::Pid_Desc;
			break;

		case Sort::Pid_Desc:
			m_sort = Sort::Pid_Asc; 
			break;

		default:
			m_sort = Sort::Pid_Asc;
			break;
		}
		break;

	default:
		m_sort = Sort::ProcName_Asc;
		break;
	}

	drawWithSort();
	return 0;
}
LRESULT CMainDlg::OnProcListItemClick(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/)
{
	auto p = (LPNMLISTVIEW)pNMHDR;
	crashIt(p->iItem);

	//// 
	//this_thread::sleep_for(chrono::seconds(1));

	//// Is that proc crashed?
	//auto hProc = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, m_procInfo[p->iItem].id);
	//if (hProc == nullptr)
	//{
	//	// If proc crashed, remove from list.
	//	auto list = static_cast<CListViewCtrl &>(GetDlgItem(IDC_LIST_PROC));
	//	list.DeleteItem(p->iItem);
	//	auto it = m_procInfo.begin();
	//	advance(it, p->iItem);
	//	m_procInfo.erase(it);
	//}
	//else
	//{
	//	CloseHandle(hProc);
	//}

	return 0;
}
LRESULT CMainDlg::OnBnClickedCopySvn(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CString strSvn;
	GetDlgItem(IDC_EDIT_SVN).GetWindowText(strSvn);
	copyStringToClipboard(strSvn.GetString());

	return 0;
}
LRESULT CMainDlg::OnBnClickedOpenNewestBinary(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CString newBinUrl;
	GetDlgItem(IDC_EDIT_NEWEST_BINARY).GetWindowText(newBinUrl);
	ShellExecute(nullptr, "open", newBinUrl, nullptr, nullptr, SW_SHOW);

	return 0;
}

// logic.
void CMainDlg::drawWithSort()
{
	// Sort.
	function<bool (const ProcessInfo &, const ProcessInfo &)> funcLess;
	switch (m_sort)
	{
	case Sort::ProcName_Asc:
		// Proc name ascending order.
		funcLess = ProcNameAsc;
		break;
	case Sort::ProcName_Desc:
		// Proc name descending order.
		funcLess = ProcNameDesc;
		break;

	case Sort::Pid_Asc:
		// Pid ascending order.
		funcLess = PidAsc;
		break;
	case Sort::Pid_Desc:
		// Pid descending order.
		funcLess = PidDesc;
		break;

	case Sort::Default:
	default:
		funcLess = ProcNameAsc;
		break;
	}
	sort(m_procInfo.begin(), m_procInfo.end(), funcLess);

	// Draw.
	drawProcList();
}
void CMainDlg::drawProcList()
{
	auto list = static_cast<CListViewCtrl &>(GetDlgItem(IDC_LIST_PROC));
	list.DeleteAllItems();
	for (auto const &i : m_procInfo)
	{
		auto index = list.AddItem(numeric_limits<int>::max(), 0, i.name.c_str());
		list.AddItem(index, 1, intToStr(i.id).c_str());
	}
}

void CMainDlg::crashIt(int index)
{
	auto pid = m_procInfo[index].id;

	char modulePath[MAX_PATH] = {};
	GetModuleFileName(nullptr, modulePath, _countof(modulePath));
	PathRemoveFileSpec(modulePath);

	CString crasheeFilename, crasheeFilename64;
	GetDlgItem(IDC_EDIT_INJECTEE_FILENAME).GetWindowText(crasheeFilename);
	GetDlgItem(IDC_EDIT_INJECTEE_FILENAME64).GetWindowText(crasheeFilename64);

	char injectorFullpath[MAX_PATH] = {}, injector64Fullpath[MAX_PATH] = {};
	PathCombine(injectorFullpath, modulePath, "Injector.exe");
	PathCombine(injector64Fullpath, modulePath, "Injector64.exe");
	runAndWait(injectorFullpath, "-pid:" + intToStr(pid) + " " + crasheeFilename.GetString(), 0, false);
	if (isOs64())
	{
		runAndWait(injector64Fullpath, "-pid:" + intToStr(pid) + " " + crasheeFilename64.GetString(), 0, false);
	}
}

BOOL CMainDlg::PreTranslateMessage(MSG* pMsg)
{
	BOOL bHandled = FALSE;
	if (pMsg->message == WM_KEYDOWN)
	{
		OnKeyDown(WM_KEYDOWN, pMsg->wParam, pMsg->lParam, bHandled);
	}

	return CWindow::IsDialogMessage(pMsg);
}

void CMainDlg::crashByProcname()
{
	auto &edit = static_cast<CEdit>(GetDlgItem(IDC_EDIT_TARGET_PROCNAME));
	CString name;
	edit.GetWindowText(name);
	for (int i = 0; i < static_cast<int>(m_procInfo.size()); ++i)
	{
		if (name.CompareNoCase(m_procInfo[i].name.c_str()) == 0)
		{
			crashIt(i);
		}
	}
}
void CMainDlg::crashByPid()
{
	auto &edit = static_cast<CEdit>(GetDlgItem(IDC_EDIT_TARGET_PID));
	CString pid;
	edit.GetWindowText(pid);
	for (int i = 0; i < static_cast<int>(m_procInfo.size()); ++i)
	{
		if (m_procInfo[i].id == strToInt(pid.GetString()))
		{
			crashIt(i);
		}
	}
}