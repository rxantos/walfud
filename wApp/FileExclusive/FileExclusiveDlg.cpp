
// FileExclusiveDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FileExclusive.h"
#include "FileExclusiveDlg.h"
#include "afxdialogex.h"
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFileExclusiveDlg dialog

static const int sc_colFullpath = 0, sc_colStatus = 1;
static const wchar_t *sc_statusLocked = L"locked",
					 *sc_statusUnlocked = L"unlocked";

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
	m_listFile.InsertColumn(sc_colFullpath, L"file fullpath", LVCFMT_CENTER, 300);
	m_listFile.InsertColumn(sc_colStatus, L"status", LVCFMT_CENTER, 50);

	// Get file target from command line.
	GetArgsFromCmdLine();
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
		wchar_t filename[MAX_PATH] = {};
		DragQueryFile(hDropInfo, i, filename, sizeof(filename)/sizeof(filename[0]));

		exclusiveFile(filename);
	}

	return;
}


void CFileExclusiveDlg::GetArgsFromCmdLine()
{
	int argc = 0;
	wchar_t **argv = CommandLineToArgvW(GetCommandLineW(), &argc);

	for (int i = 1; i < argc; ++i)
	{
		exclusiveFile(argv[i]);
	}

	LocalFree(argv);
	argv = NULL;
}

// logic.
void CFileExclusiveDlg::exclusiveFile(const wstring &fullpath)
{
	if (m_filenameHandle.find(fullpath) == m_filenameHandle.end())
	{
		// Exclusive a file.
		HANDLE h = CreateFile(fullpath.c_str(), GENERIC_ALL, 0, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
		if (h == INVALID_HANDLE_VALUE)
		{
			wstring info = wstring(L"Can NOT lock file: ") + L"'" + fullpath + L"'.";
			OutputDebugString(info.c_str());
		}
		else
		{
			m_filenameHandle[fullpath] = h;

			// Insert to list.
			int index = m_listFile.InsertItem(m_listFile.GetItemCount(), fullpath.c_str());
			m_listFile.SetItemText(index, sc_colStatus, sc_statusLocked);

			wstring info = wstring(L"Lock file: ") + L"'" + fullpath + L"'.";
			OutputDebugString(info.c_str());
		}
	}
	else
	{
		wstring info = wstring(L"File: ") + L"'" + fullpath + L"' has locked before. Do NOTHING.";
		OutputDebugString(info.c_str());
	}
}