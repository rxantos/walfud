
// animationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "main.h"
#include "animationDlg.h"
#include "afxdialogex.h"
#include <chrono>
using namespace std;
using namespace this_thread;
using namespace chrono;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CanimationDlg dialog

CanimationDlg::CanimationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CanimationDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CanimationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CanimationDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, &CanimationDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, &CanimationDlg::OnBnClickedButtonPause)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CanimationDlg::OnBnClickedButtonStop)
END_MESSAGE_MAP()


// CanimationDlg message handlers

BOOL CanimationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	{
		m_maH.setBoard(m_hWnd);
		m_maH.setGraph(MyGraph2(RGB(123, 62, 200)));
		m_maH.setTrack(MyTrack2());
		m_maH.setSpeed(MySpeed2());
		m_maH.setDoneCallback([&](void *param)
		{
			auto pMa = reinterpret_cast<MyAnimation2 *>(param);
			pMa->stop(false);
		}, &m_maH);
	}
	{
		m_maT.setBoard(m_hWnd);
		m_maT.setGraph(MyGraph(RGB(240, 240, 240)));
		m_maT.setTrack(MyTrack2());
		m_maT.setSpeed(MySpeed2());
		m_maT.setDoneCallback([&](void *param)
		{
			auto pMa = reinterpret_cast<MyAnimation2 *>(param);
			pMa->stop(false);
		}, &m_maT);
	}
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CanimationDlg::OnPaint()
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
HCURSOR CanimationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CanimationDlg::OnBnClickedButtonStart()
{
	m_maH.start();
	if (!(m_maH.getStatus() == MyAnimation2::Status::Running && m_maT.getStatus() == MyAnimation2::Status::Running
		  || m_maH.getStatus() == MyAnimation2::Status::Paused && m_maT.getStatus() == MyAnimation2::Status::Paused))
	{
		sleep_for(milliseconds(777));
	}
	m_maT.start();
}


void CanimationDlg::OnBnClickedButtonPause()
{
	m_maH.pause();
	m_maT.pause();
}


void CanimationDlg::OnBnClickedButtonStop()
{
	m_maH.stop();
	m_maT.stop();
}
