
// DropToListTemplateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DropToListTemplate.h"
#include "DropToListTemplateDlg.h"
#include "afxdialogex.h"
#include "wCppExt.h"
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Status.
map<Status::ErrId, string> Status::ms_idStr;

Status::Status() : m_id(ErrId::success) { init(); }
Status &Status::operator=(const Status &other)
{
	if (this != &other)
	{
		m_id = other.m_id;
	}

	return *this;
}
Status::Status(ErrId errId) : m_id(errId) { init(); }

// Interface.
Status::ErrId Status::toId() const
{ return m_id; }
string Status::toStr() const
{ return ms_idStr.find(m_id) != ms_idStr.end() ? ms_idStr[m_id] : ms_idStr[ErrId::unknownFail]; }

// logic.
void Status::init()
{
	static bool once = true;
	if (once)
	{
		ms_idStr[ErrId::success] = "success";
		ms_idStr[ErrId::fileNotFound] = "file not found";
		ms_idStr[ErrId::unknownFail] = "unknown fail";
		once = false;
	}
}

// Res.
Res::Res() : /*m_size(0),*/ m_status(Status::ErrId::unknownFail) {}	// TODO: 
Res &Res::operator=(const Res &other)
{
	if (this != &other)
	{
		//m_size = other.m_size;	// TODO: 
		m_status = other.m_status;
	}

	return *this;
}
//Res::Res(int size, Status status) : m_size(size), m_status(status) {}	// TODO: 


// Interface.
string Res::toStr() const
{ return m_status.toId() == Status::ErrId::success ? ""/*to_string(m_size)*/ : m_status.toStr(); }	// TODO: 

// CDropToListTemplateDlg dialog
const int CDropToListTemplateDlg::sc_colIndex_targetFullpath = 0;
		  //CDropToListTemplateDlg::sc_colIndex_targetSize = 1;	// TODO: 
const char *CDropToListTemplateDlg::sc_colTitle_targetFullpath = "file fullpath";
		   //*CDropToListTemplateDlg::sc_colTitle_targetSize = "size in byte";	// TODO: 
const int CDropToListTemplateDlg::sc_colWidth_targetFullpath = 350;
		  //CDropToListTemplateDlg::sc_colWidth_targetSize = 80;	// TODO: 


CDropToListTemplateDlg::CDropToListTemplateDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDropToListTemplateDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDropToListTemplateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_list);
}

BEGIN_MESSAGE_MAP(CDropToListTemplateDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON_HANDLE, &CDropToListTemplateDlg::OnBnClickedButtonHandle)
END_MESSAGE_MAP()


// CDropToListTemplateDlg message handlers

BOOL CDropToListTemplateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// Initialize widget.
	m_list.InsertColumn(sc_colIndex_targetFullpath, sc_colTitle_targetFullpath, LVCFMT_LEFT, sc_colWidth_targetFullpath);
	//m_list.InsertColumn(sc_colIndex_targetSize, sc_colTitle_targetSize, LVCFMT_LEFT, sc_colWidth_targetSize);	// TODO: 
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDropToListTemplateDlg::OnPaint()
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
HCURSOR CDropToListTemplateDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDropToListTemplateDlg::OnDropFiles(HDROP hDropInfo)
{
	// Get files.
	vector<string> targets;
	for (UINT i = 0; i < DragQueryFile(hDropInfo, 0xffffffff, nullptr, 0); ++i)
	{
		char targetFullpath[MAX_PATH] = {};
		DragQueryFile(hDropInfo, i, targetFullpath, arrCnt(targetFullpath));

		m_res[targetFullpath];
	}

	// .
	OnBnClickedButtonHandle();
}

// Interface.
void CDropToListTemplateDlg::OnBnClickedButtonHandle()
{
	handleAll();

	//
	updateList();
}

// logic.
void CDropToListTemplateDlg::handleAll()
{
	for (auto &i : m_res)
	{
		i.second = handleOne(i.first);
	}
}

Res CDropToListTemplateDlg::handleOne(const string &target)
{
	// Get file size.
	Res r;

	// TODO: 
	//ifstream inFile(target.c_str(), ios_base::in | ios_base::binary);
	//if (inFile.is_open())
	//{	
	//	inFile.seekg(0, ios_base::end);
	//	r = Res(static_cast<int>(inFile.tellg()), Status::ErrId::success);

	//	inFile.close();
	//}
	//else
	//{
	//	r = Res(0, Status::ErrId::unknownFail);
	//}

	return r;
}

void CDropToListTemplateDlg::updateList()
{
	m_list.DeleteAllItems();
	for (auto const &i : m_res)
	{
		int index = m_list.InsertItem(m_list.GetItemCount(), i.first.c_str());
		//m_list.SetItemText(index, sc_colIndex_targetSize, i.second.toStr().c_str());	// TODO: 
	}
}