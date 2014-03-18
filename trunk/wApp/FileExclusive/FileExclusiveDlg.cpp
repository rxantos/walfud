
// FileExclusiveDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FileExclusive.h"
#include "FileExclusiveDlg.h"
#include "afxdialogex.h"
#include "wStrUtil.h"
#include <limits>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifndef	WM_COPYGLOBALDATA
#define WM_COPYGLOBALDATA 0x0049
#endif

#define ERROR_UNKNOWN (numeric_limits<unsigned>::max())

string lastErrToStr(unsigned lastErr)
{
	static bool once = false;
	static map<unsigned, string> s_idDescription;
	if (!once)
	{
		s_idDescription[ERROR_SUCCESS] = "locked";
		s_idDescription[ERROR_FILE_NOT_FOUND] = "file not found";
		s_idDescription[ERROR_ACCESS_DENIED] = "access denied";
		s_idDescription[ERROR_SHARING_VIOLATION] = "sharing violation";
		s_idDescription[ERROR_UNKNOWN] = "unknown fail";

		once = true;
	}

	return s_idDescription.find(lastErr) != s_idDescription.end() ? 
			s_idDescription[lastErr] : s_idDescription[ERROR_UNKNOWN];
}

// CFileExclusiveDlg dialog

static const int sc_colFullpath = 0, sc_colStatus = 1;
static const int sc_colFullpathWidth = 300, sc_colStatusWidth = 100;

CFileExclusiveDlg::CFileExclusiveDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFileExclusiveDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFileExclusiveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_FILE, m_listFile);
}

BEGIN_MESSAGE_MAP(CFileExclusiveDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DROPFILES()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, &CFileExclusiveDlg::OnBnClickedButtonRefresh)
END_MESSAGE_MAP()


// CFileExclusiveDlg message handlers

BOOL CFileExclusiveDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// Initialize controls.
	m_listFile.InsertColumn(sc_colFullpath, "file fullpath", LVCFMT_CENTER, sc_colFullpathWidth);
	m_listFile.InsertColumn(sc_colStatus, "status", LVCFMT_CENTER, sc_colStatusWidth);

	// Get file target from command line.
	getArgsFromCmdLine();

	// Allow message for lower privilege.
	using T_ChangeWindowMessageFilter = BOOL (WINAPI *)(_In_  UINT message, _In_  DWORD dwFlag);
	if (auto pfnChangeWindowMessageFilter = (T_ChangeWindowMessageFilter)GetProcAddress(GetModuleHandle("User32.dll"), "ChangeWindowMessageFilter"))
	{
		pfnChangeWindowMessageFilter(WM_DROPFILES, MSGFLT_ADD);
		pfnChangeWindowMessageFilter(WM_COPYGLOBALDATA, MSGFLT_ADD);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFileExclusiveDlg::OnPaint()
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
HCURSOR CFileExclusiveDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CFileExclusiveDlg::OnDropFiles(HDROP hDropInfo)
{
	UINT cnt = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);	
	for(UINT i = 0; i < cnt; ++i)
	{
		// Get filename.
		char filename[MAX_PATH] = {};
		DragQueryFile(hDropInfo, i, filename, sizeof(filename)/sizeof(filename[0]));

		exclusiveFile(filename);
	}

	return;
}

void CFileExclusiveDlg::OnTimer(UINT_PTR nIDEvent)
{}

// Interface.
void CFileExclusiveDlg::getArgsFromCmdLine()
{
	int argc = 0;
	wchar_t **argv = CommandLineToArgvW(GetCommandLineW(), &argc);

	for (int i = 1; i < argc; ++i)
	{
		exclusiveFile(w::wStrToStr(argv[i]));
	}

	LocalFree(argv);
	argv = NULL;
}

// logic.
void CFileExclusiveDlg::exclusiveFile(const string &fullpath)
{
	int index = 0;
	auto toLock = m_targetsInfo.find(fullpath);
	if (m_targetsInfo.find(fullpath) == m_targetsInfo.end())
	{
		// New item.
		m_targetsInfo[fullpath] = INVALID_HANDLE_VALUE;
		index = m_listFile.InsertItem(m_listFile.GetItemCount(), fullpath.c_str());
	}
	else
	{
		// Existing.
		index = distance(m_targetsInfo.begin(), toLock);
		CloseHandle(toLock->second);
		m_targetsInfo[fullpath] = INVALID_HANDLE_VALUE;
	}
	
	// Try to lock file.
	m_targetsInfo[fullpath] = reinterpret_cast<void *>(CreateFile(fullpath.c_str(), GENERIC_ALL, 0, NULL, 
													   OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL));
	unsigned lastErr = static_cast<unsigned>(GetLastError());
	m_listFile.SetItemText(index, sc_colStatus, lastErrToStr(lastErr).c_str());
}

void CFileExclusiveDlg::OnBnClickedButtonRefresh()
{
	vector<string> filenames;
	transform(m_targetsInfo.begin(), m_targetsInfo.end(), back_inserter(filenames), [](const pair<string, void *> &p) { return p.first; });

	for (auto i : filenames)
	{
		exclusiveFile(i);
	}
}