
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
		m_maLH.setBoard(m_hWnd);
		m_maLH.setGraph(MyGraph2(RGB(123, 62, 200)));
		m_maLH.setTrack(MyTrack3());
		m_maLH.setSpeed(MySpeed2());
		m_maLH.setDoneCallback([](void *param)
		{
			auto p = reinterpret_cast<CanimationDlg *>(param);
			p->m_maLH.stop(false);
		}, this);
	}
	{
		m_maLT.setBoard(m_hWnd);
		m_maLT.setGraph(MyGraph(RGB(240, 240, 240)));
		m_maLT.setTrack(MyTrack3());
		m_maLT.setSpeed(MySpeed2());
		m_maLT.setDoneCallback([](void *param)
		{
			auto p = reinterpret_cast<CanimationDlg *>(param);

			p->GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
			p->GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(FALSE);
			p->GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);

			p->m_maLT.stop(false);
			p->m_maRH.start();
			sleep_for(milliseconds(777));
			p->m_maRT.start();

			p->GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
			p->GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(TRUE);
			p->GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
		}, this);
	}
	{
		m_maRH.setBoard(m_hWnd);
		m_maRH.setGraph(MyGraph(RGB(123, 62, 200)));
		m_maRH.setTrack(MyTrack2());
		m_maRH.setSpeed(MySpeed2());
		m_maRH.setDoneCallback([](void *param)
		{
			auto p = reinterpret_cast<CanimationDlg *>(param);
			p->m_maRH.stop(false);
		}, this);
	}
	{
		m_maRT.setBoard(m_hWnd);
		m_maRT.setGraph(MyGraph(RGB(240, 240, 240)));
		m_maRT.setTrack(MyTrack2());
		m_maRT.setSpeed(MySpeed2());
		m_maRT.setDoneCallback([](void *param)
		{
			auto p = reinterpret_cast<CanimationDlg *>(param);

			p->GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
			p->GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(FALSE);
			p->GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);

			p->m_maRT.stop(false);
			p->m_maLH.start();
			sleep_for(milliseconds(777));
			p->m_maLT.start();

			p->GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
			p->GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(TRUE);
			p->GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
		}, this);
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
	if (m_maLH.getStatus() == MyAnimation2::Status::Stopped
		&& m_maLT.getStatus() == MyAnimation2::Status::Stopped
		&& m_maRH.getStatus() == MyAnimation2::Status::Stopped
		&& m_maRT.getStatus() == MyAnimation2::Status::Stopped)
	{
		// All stopped.
		GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);

		m_maLH.start();
		sleep_for(milliseconds(777));
		m_maLT.start();

		GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
	}
	else if (m_maLH.getStatus() == MyAnimation2::Status::Paused
			 && m_maLT.getStatus() == MyAnimation2::Status::Paused)
	{
		// Left paused.
		m_maLH.start();
		m_maLT.start();
	}
	else if (m_maRH.getStatus() == MyAnimation2::Status::Paused
			 && m_maRT.getStatus() == MyAnimation2::Status::Paused)
	{
		// Right paused.
		m_maRH.start();
		m_maRT.start();
	}
	else
	{
		// 
		if (m_maLH.getStatus() == MyAnimation2::Status::Stopped
			&& (m_maLT.getStatus() == MyAnimation2::Status::Running || m_maLT.getStatus() == MyAnimation2::Status::Paused))
		{
			// Left stopping.
			m_maLT.start();
		}
		else if (m_maRH.getStatus() == MyAnimation2::Status::Stopped
				 && (m_maRT.getStatus() == MyAnimation2::Status::Running || m_maRT.getStatus() == MyAnimation2::Status::Paused))
		{
			// Right stopping.
			m_maRT.start();
		}
		else
		{}
	}
}


void CanimationDlg::OnBnClickedButtonPause()
{
	m_maLH.pause();
	m_maLT.pause();
	m_maRH.pause();
	m_maRT.pause();
}


void CanimationDlg::OnBnClickedButtonStop()
{
	m_maLH.stop(false);
	m_maLT.stop(false);
	m_maRH.stop(false);
	m_maRT.stop(false);
}
