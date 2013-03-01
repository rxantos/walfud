
// FileExclusiveDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FileExclusive.h"
#include "FileExclusiveDlg.h"
#include "afxdialogex.h"
#include "wStrUtil.h"
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
bool operator==(const TargetInfo &a, const TargetInfo &b) { return w::strICmp(a.filename, b.filename); }

// Status.
map<Status::Key, string> Status::ms_idDescription;

Status::Status() : m_curStatusKey(Key::UNKNOWN)
{ init(); }
Status::Status(unsigned id) : m_curStatusKey(static_cast<Status::Key>(id))
{ init(); }
Status &Status::operator==(unsigned id)
{
	m_curStatusKey = ms_idDescription.find(static_cast<Status::Key>(id)) == ms_idDescription.end() ? Key::UNKNOWN : static_cast<Status::Key>(id);
	return *this;
}
Status::Status(Status::Key key) : m_curStatusKey(key)
{ init(); }
Status &Status::operator==(Status::Key key)
{
	m_curStatusKey = key;
	return *this;
}

// Interface.
string Status::toString() const
{ return ms_idDescription[m_curStatusKey]; }

// private.
void Status::init()
{
	static bool once = false;
	if (!once)
	{
		ms_idDescription[Key::SUCCESS] = "locked";
		ms_idDescription[Key::FILE_NOT_FOUND] = "file not found";
		ms_idDescription[Key::ACCESS_DENIED] = "access denied";
		ms_idDescription[Key::SHARING_VIOLATION] = "sharing violation";
		ms_idDescription[Key::UNKNOWN] = "unknown fail";

		once = true;
	}
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
	auto toLock = find(m_targetsInfo.begin(), m_targetsInfo.end(), TargetInfo(fullpath));
	if (toLock == m_targetsInfo.end())
	{
		m_targetsInfo.push_back(TargetInfo(fullpath, INVALID_HANDLE_VALUE));
		index = m_listFile.InsertItem(m_listFile.GetItemCount(), fullpath.c_str());
	}
	else
	{
		index = distance(m_targetsInfo.begin(), toLock);
	}
	
	// Update status.
	Status s = tryExclusive(index);
	m_listFile.SetItemText(index, sc_colStatus, s.toString().c_str());
}
void CFileExclusiveDlg::freeFile(const string &fullpath)
{
	auto toFree = find(m_targetsInfo.begin(), m_targetsInfo.end(), TargetInfo(fullpath));
	if (toFree != m_targetsInfo.end())
	{
		CloseHandle(toFree->handle);
		
		// Remove from list.
		int pos = distance(m_targetsInfo.begin(), toFree);
		m_listFile.DeleteItem(pos);
		// Remove from container.
		m_targetsInfo.erase(toFree);
	}
}

void CFileExclusiveDlg::OnBnClickedButtonRefresh()
{
	vector<string> filenames;
	transform(m_targetsInfo.begin(), m_targetsInfo.end(), back_inserter(filenames), [](const TargetInfo &ti) { return ti.filename; });

	for (auto i : filenames)
	{
		exclusiveFile(i);
	}
}

Status CFileExclusiveDlg::tryExclusive(unsigned index)
{
	Status res;

	CloseHandle(m_targetsInfo[index].handle);
	m_targetsInfo[index].handle = CreateFile(m_targetsInfo[index].filename.c_str(), GENERIC_ALL, 0, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
	res = GetLastError();

	return res;
}