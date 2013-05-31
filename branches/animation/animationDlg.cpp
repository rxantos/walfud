
// animationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "animation.h"
#include "animationDlg.h"
#include "afxdialogex.h"
#include "animation/graph.h"
#include "animation/track.h"
#include "animation/speed.h"
#include <thread>
#include <chrono>
#include <future>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CanimationDlg dialog

void Animation(MyGraph &mg, MyTrack &mt, Speed &s)
{
	while (true)
	{
		Coordinate_2D pos = mt.next();
		mg.setCoordinate(pos);

		mg.draw();

		this_thread::sleep_for(chrono::milliseconds(s.next()));
	}
}



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
	HDC dc = ::GetDC(m_hWnd);

	MyGraph mg(dc, RGB(123, 62, 200));
	MyTrack mt;
	MySpeed s;

	async(Animation, mg, mt, s);
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

