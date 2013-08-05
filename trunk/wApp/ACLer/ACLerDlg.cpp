
// ACLerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ACLer.h"
#include "ACLerDlg.h"
#include "afxdialogex.h"
#include "wCppExt.h"
#include <Aclapi.h>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CDropToListTemplateDlg dialog
const int CDropToListTemplateDlg::sc_colIndex_targetFullpath = 0,
		  CDropToListTemplateDlg::sc_colIndex_permission = 1;
const char *CDropToListTemplateDlg::sc_colTitle_targetFullpath = "file fullpath",
		   *CDropToListTemplateDlg::sc_colTitle_permission = "permission";
const int CDropToListTemplateDlg::sc_colWidth_targetFullpath = 350,
		  CDropToListTemplateDlg::sc_colWidth_permission = 80;


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
	ON_BN_CLICKED(IDC_BUTTON_GRANT, &CDropToListTemplateDlg::OnBnClickedButtonGrant)
	ON_BN_CLICKED(IDC_BUTTON_STRIP, &CDropToListTemplateDlg::OnBnClickedButtonStrip)
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
	m_list.InsertColumn(sc_colIndex_permission, sc_colTitle_permission, LVCFMT_LEFT, sc_colWidth_permission);

	// Target fullpath through command line.
	vector<string> argv = w::getArgv();
	if (argv.size() >= 3)
	{
		int rtn = 0;

		argv[0];			// Exec fullpath.
		argv[1];			// `grant/strip`.
		argv[2];			// Targets fullpath...
		for (size_t i = 2; i < argv.size(); ++i)
		{
			m_res[argv[i]] = Res::UNKNOWN;
		}

		// Handle automatically.
		if (argv[1] == "grant")
		{
			grantAll();
		}
		else if (argv[1] == "strip")
		{
			stripAll();
		}
		else
		{
			rtn = -1;
			cerr <<"unknown op. `" <<argv[1] <<"`." <<endl;
		}

		exit(rtn);
	}

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

		m_res[targetFullpath] = Res::UNKNOWN;
	}

	updateList();
}

// logic.
void CDropToListTemplateDlg::grantAll()
{
	for (auto &i : m_res)
	{
		i.second = handleOne(i.first, true);
	}
}
void CDropToListTemplateDlg::stripAll()
{
	for (auto &i : m_res)
	{
		i.second = handleOne(i.first, false);
	}
}

CDropToListTemplateDlg::Res CDropToListTemplateDlg::handleOne(const string &target, bool grant)
{
	// Get file size.
	Res res = Res::UNKNOWN;

	// Open file.
	HANDLE file = CreateFile(target.c_str(),
							 READ_CONTROL | WRITE_DAC,
							 0,
							 nullptr,
							 OPEN_EXISTING,
							 0,	
							 nullptr);
	if (file != INVALID_HANDLE_VALUE)
	{
		// Get old acl.
		PSECURITY_DESCRIPTOR pSd = nullptr;
		PACL pNewDacl = nullptr;

		// Construct new acl.
		EXPLICIT_ACCESS ea = {};
		ea.grfAccessMode = SET_ACCESS;
		ea.grfAccessPermissions = grant ? GENERIC_ALL : READ_CONTROL | WRITE_DAC | SYNCHRONIZE;
		ea.grfInheritance = NO_INHERITANCE;
		ea.Trustee.TrusteeForm = TRUSTEE_IS_NAME;
		ea.Trustee.TrusteeType = TRUSTEE_IS_USER;
		ea.Trustee.ptstrName = "everyone";
		if (SetEntriesInAcl(1, &ea, nullptr, &pNewDacl) == ERROR_SUCCESS)
		{
			// Bind new acl to target.
			if (SetSecurityInfo(file,					// Erase old DACL.
							    SE_FILE_OBJECT, 
								DACL_SECURITY_INFORMATION, 
								nullptr, nullptr, 
								nullptr, nullptr) == ERROR_SUCCESS
				&& SetSecurityInfo(file,				// Set new and the only ACE.
								   SE_FILE_OBJECT, 
								   DACL_SECURITY_INFORMATION, 
								   nullptr, nullptr, 
								   pNewDacl, nullptr) == ERROR_SUCCESS)
			{
				res = grant ? Res::GRANT : Res::STRIP;
			}

			LocalFree(pNewDacl);
		}
	
		LocalFree(pSd);
		CloseHandle(file);
	}

	return res;
}

void CDropToListTemplateDlg::updateList()
{
	m_list.DeleteAllItems();
	for (auto const &i : m_res)
	{
		int index = m_list.InsertItem(m_list.GetItemCount(), i.first.c_str());

		string res;
		switch (i.second)
		{
		case Res::UNKNOWN:
			res = "fail";
			break;
		case Res::GRANT:
			res = "grant";
			break;
		case Res::STRIP:
			res = "strip";
			break;
		default:
			break;
		}
		m_list.SetItemText(index, sc_colIndex_permission, res.c_str());
	}
}

void CDropToListTemplateDlg::OnBnClickedButtonGrant()
{
	grantAll();

	//
	updateList();
}
void CDropToListTemplateDlg::OnBnClickedButtonStrip()
{
	stripAll();

	//
	updateList();
}
