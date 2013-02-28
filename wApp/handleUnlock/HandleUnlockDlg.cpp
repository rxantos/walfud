
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
}

BEGIN_MESSAGE_MAP(CHandleUnlockDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DROPFILES()
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
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
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
		m_filesFullpath.push_back(fileFullpath);
	}

	// Query handle information from all processes.
	auto idHandle_all = w::getIdHandleMap();
	auto idValName = w::getIdHandlevalueHandlename(idHandle_all);
	for (auto const &i : m_filesFullpath)
	{
		for (auto const &j : idValName)
		{
			int processId = get<0>(j);
			HANDLE val = get<1>(j);
			string name = get<2>(j);
			if (w::dosNameToNtName(i) == name)
			{
				//cout <<processId <<" : " <<name <<endl;
				int index = m_list.InsertItem((numeric_limits<int>::max)(), name.c_str(), -1);
				m_list.SetItemText(index, 1, to_string(processId).c_str());
			}
		}//for j
	}//for i

	//// Close the handle from specified process..
	//if (HANDLE processHandle = OpenProcess(PROCESS_DUP_HANDLE, FALSE, processId))
	//{
	//	if (DuplicateHandle(processHandle, val, GetCurrentProcess(), nullptr, 0, false, DUPLICATE_CLOSE_SOURCE))
	//	{
	//		cout <<"ok.";
	//	}
	//	else
	//	{
	//		cout <<"fail.";
	//	}

	//	CloseHandle(processHandle);
	//}
}

