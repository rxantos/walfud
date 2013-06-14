
// screenBrightnessDlg.cpp : implementation file
//

#include "stdafx.h"
#include "screenBrightness.h"
#include "screenBrightnessDlg.h"
#include "afxdialogex.h"
#include <string>
#include <HighLevelMonitorConfigurationAPI.h>
#include <thread>
#include <chrono>
#include <future>
#include "Brightness.h"
using namespace std;

#pragma comment(lib, "Dxva2.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CscreenBrightnessDlg dialog

static HANDLE getScreenHandle(HWND hWnd)
{
	HANDLE res = nullptr;

	HMONITOR hMonitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONULL);

	DWORD monitorCnt = 0;
	if (GetNumberOfPhysicalMonitorsFromHMONITOR(hMonitor, &monitorCnt))
	{
		PHYSICAL_MONITOR *buf = new PHYSICAL_MONITOR[monitorCnt];
		fill(reinterpret_cast<char *>(buf), reinterpret_cast<char *>(buf) + sizeof(PHYSICAL_MONITOR)*monitorCnt, '\0');
		if (GetPhysicalMonitorsFromHMONITOR(hMonitor, monitorCnt, buf))
		{
			//for (DWORD i = 0; i < monitorCnt; ++i)
			//{
			//	buf[i].hPhysicalMonitor;
			//}
			res = buf[0].hPhysicalMonitor;
		}

		delete []buf;
		buf = nullptr;
	}

	return res;
}

static void Worker(HWND hWnd)
{
	MyBrightness bv;
	while (true)
	{
		// 
		//HANDLE h = getScreenHandle(hWnd);
		//SetMonitorBrightness(h, bv.getVal());

		bv.getVal();

		this_thread::sleep_for(chrono::seconds(1));
	}
}



CscreenBrightnessDlg::CscreenBrightnessDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CscreenBrightnessDlg::IDD, pParent),
	  m_originalBrightness(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CscreenBrightnessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, m_slider_bright);
}

BEGIN_MESSAGE_MAP(CscreenBrightnessDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_NOTIFY(TRBN_THUMBPOSCHANGING, IDC_SLIDER_BRIGHT, &CscreenBrightnessDlg::OnTRBNThumbPosChangingSliderBright)
ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CscreenBrightnessDlg message handlers

BOOL CscreenBrightnessDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	// Store current brightness.
	HANDLE h = getScreenHandle(m_hWnd);
	DWORD minBrightness = 0, curBrightness = 0, maxBrightness = 0;
	GetMonitorBrightness(h, &minBrightness, &curBrightness, &maxBrightness);
	m_originalBrightness = curBrightness;

	// Sliderbar.
	m_slider_bright.SetRange(0, 100);
	m_slider_bright.SetPos(m_originalBrightness);

	// Auto.
	async(Worker, m_hWnd);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CscreenBrightnessDlg::OnPaint()
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
HCURSOR CscreenBrightnessDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CscreenBrightnessDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	int curPos = m_slider_bright.GetPos();
	
	HANDLE h = getScreenHandle(m_hWnd);
	SetMonitorBrightness(h, curPos);

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
