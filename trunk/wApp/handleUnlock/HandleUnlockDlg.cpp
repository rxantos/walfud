
// HandleUnlockDlg.cpp : implementation file
//

#include "stdafx.h"
#include "handleUnlock.h"
#include "HandleUnlockDlg.h"
#include "afxdialogex.h"
#include "wCppExt.h"
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHandleUnlockDlg dialog



CHandleUnlockDlg::CHandleUnlockDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHandleUnlockDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHandleUnlockDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_list);
	DDX_Control(pDX, IDC_CHECK_REFRESH_PER_QUERY, m_checkRefreshPerQuery);
}

BEGIN_MESSAGE_MAP(CHandleUnlockDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_HANDLE, &CHandleUnlockDlg::OnBnClickedButtonCloseHandle)
	ON_BN_CLICKED(IDC_BUTTON_QUERY, &CHandleUnlockDlg::OnBnClickedButtonQuery)
END_MESSAGE_MAP()


// CHandleUnlockDlg message handlers

BOOL CHandleUnlockDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_list.InsertColumn(0, "file fullpath", LVCFMT_LEFT, 300);
	m_list.InsertColumn(1, "pid", LVCFMT_LEFT, 50);
	m_checkRefreshPerQuery.SetCheck(TRUE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to updateList the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CHandleUnlockDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CHandleUnlockDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CHandleUnlockDlg::OnDropFiles(HDROP hDropInfo)
{
	// Get files.
	for (UINT i = 0; i < DragQueryFile(hDropInfo, 0xffffffff, nullptr, 0); ++i)
	{
		char fileFullpath[MAX_PATH] = {};
		DragQueryFile(hDropInfo, i, fileFullpath, arrCnt(fileFullpath));

		m_handleRefInfo.insert(make_pair(fileFullpath, HandleRefInfo()));
	}

	OnBnClickedButtonQuery();
}

void CHandleUnlockDlg::query()
{
	// Get handles name.
	set<string> handlesName;
	transform(m_handleRefInfo.begin(), m_handleRefInfo.end(), inserter(handlesName, handlesName.begin()), 
			  [&handlesName](const pair<string, HandleRefInfo> &p) -> string { return p.first; });

	// Query from all processes.
	m_handleRefInfo.clear();
	for (auto &i : handlesName)
	{
		string ntName = w::dosNameToNtName(i);
		for (size_t j = 0; j < m_handleState.size(); ++j)
		{
			int processId = get<0>(m_handleState[j]);
			HANDLE val = get<1>(m_handleState[j]);
			string name = get<2>(m_handleState[j]);
			if (name.find(ntName) == 0)
			{
				m_handleRefInfo.insert(make_pair(w::ntNameToDosName(name), HandleRefInfo(processId, val)));
			}
		}
	}//for i
}

void CHandleUnlockDlg::OnBnClickedButtonCloseHandle()
{
	// Close the handle from specified process.
	for (auto &i : m_handleRefInfo)
	{
		if (HANDLE processHandle = OpenProcess(PROCESS_DUP_HANDLE, FALSE, i.second.processId))
		{
			HANDLE duplicatedHandle;
			if (DuplicateHandle(processHandle, i.second.val, GetCurrentProcess(), &duplicatedHandle, 0, false, DUPLICATE_CLOSE_SOURCE))
			{
				CloseHandle(duplicatedHandle);

				i.second.processId = HandleRefInfo::sc_invalidId;
				i.second.val = INVALID_HANDLE_VALUE;
			}

			CloseHandle(processHandle);
		}
	}

	// Update result.
	updateList();
}

// logic.
void CHandleUnlockDlg::updateList()
{
	m_list.DeleteAllItems();
	for (auto const &i : m_handleRefInfo)
	{
		int index = m_list.InsertItem((numeric_limits<int>::max)(), i.first.c_str(), -1);
		string processId = i.second.processId == HandleRefInfo::sc_invalidId ? "-" : to_string(i.second.processId);
		m_list.SetItemText(index, 1, processId.c_str());
	}
}

void CHandleUnlockDlg::OnBnClickedButtonQuery()
{
	if (m_checkRefreshPerQuery.GetCheck())
	{
		if (m_checkRefreshPerQuery.GetCheck())
		{
			auto idHandle_all = w::getIdHandleMap();
			m_handleState = w::getIdHandlevalueHandlename(idHandle_all);
		}
	}

	query();

	// Update result.
	updateList();
}
