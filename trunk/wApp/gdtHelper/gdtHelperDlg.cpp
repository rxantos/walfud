
// gdtHelperDlg.cpp : implementation file
//

#include "stdafx.h"
#include "gdtHelper.h"
#include "gdtHelperDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static const unsigned sc_bitG = 55,
					  sc_bitDB = 54,
					  sc_bitL = 53,
					  sc_bitAVL = 52,

					  sc_bitP = 47,
					  sc_bitS = 44;

// CgdtHelperDlg dialog

CgdtHelperDlg::CgdtHelperDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CgdtHelperDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CgdtHelperDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT_SEGMENT_BASE, m_editSegmentBase);
	DDX_Control(pDX, IDC_EDIT_SEGMENT_BOUND, m_editSegmentBound);
	DDX_Control(pDX, IDC_CHECK_DB, m_checkDB);
	DDX_Control(pDX, IDC_CHECK_G, m_checkG);
	DDX_Control(pDX, IDC_CHECK_L, m_checkL);
	DDX_Control(pDX, IDC_CHECK_AVL, m_checkAVL);
	DDX_Control(pDX, IDC_CHECK_P, m_checkP);
	DDX_Control(pDX, IDC_CHECK_S, m_checkS);

	DDX_Control(pDX, IDC_RADIO_DPL_00, m_radioDPL_00);
	DDX_Control(pDX, IDC_RADIO_DPL_01, m_radioDPL_01);
	DDX_Control(pDX, IDC_RADIO_DPL_10, m_radioDPL_10);
	DDX_Control(pDX, IDC_RADIO_DPL_11, m_radioDPL_11);

	DDX_Control(pDX, IDC_RADIO_TYPE_0000, m_radioType_0000);
	DDX_Control(pDX, IDC_RADIO_TYPE_0010, m_radioType_0010);
	DDX_Control(pDX, IDC_RADIO_TYPE_0100, m_radioType_0100);
	DDX_Control(pDX, IDC_RADIO_TYPE_0110, m_radioType_0110);
	DDX_Control(pDX, IDC_RADIO_TYPE_1000, m_radioType_1000);
	DDX_Control(pDX, IDC_RADIO_TYPE_1010, m_radioType_1010);
	DDX_Control(pDX, IDC_RADIO_TYPE_1100, m_radioType_1100);
	DDX_Control(pDX, IDC_RADIO_TYPE_1110, m_radioType_1110);

	{
		unsigned i = 0;
		DDX_Control(pDX, IDC_EDIT_0, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_1, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_2, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_3, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_4, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_5, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_6, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_7, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_8, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_9, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_10, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_11, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_12, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_13, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_14, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_15, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_16, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_17, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_18, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_19, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_20, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_21, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_22, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_23, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_24, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_25, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_26, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_27, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_28, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_29, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_30, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_31, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_32, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_33, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_34, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_35, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_36, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_37, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_38, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_39, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_40, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_41, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_42, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_43, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_44, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_45, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_46, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_47, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_48, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_49, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_50, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_51, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_52, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_53, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_54, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_55, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_56, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_57, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_58, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_59, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_60, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_61, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_62, m_editBits[i++]);
		DDX_Control(pDX, IDC_EDIT_63, m_editBits[i++]);
	}
}

BEGIN_MESSAGE_MAP(CgdtHelperDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT_SEGMENT_BASE, &CgdtHelperDlg::OnEnChangeEditSegmentBase)
	ON_EN_CHANGE(IDC_EDIT_SEGMENT_BOUND, &CgdtHelperDlg::OnEnChangeEditSegmentBound)
	ON_BN_CLICKED(IDC_CHECK_G, &CgdtHelperDlg::OnBnClickedCheckG)
	ON_BN_CLICKED(IDC_CHECK_DB, &CgdtHelperDlg::OnBnClickedCheckDb)
	ON_BN_CLICKED(IDC_CHECK_L, &CgdtHelperDlg::OnBnClickedCheckL)
	ON_BN_CLICKED(IDC_CHECK_AVL, &CgdtHelperDlg::OnBnClickedCheckAvl)
	ON_BN_CLICKED(IDC_CHECK_P, &CgdtHelperDlg::OnBnClickedCheckP)
	ON_BN_CLICKED(IDC_CHECK_S, &CgdtHelperDlg::OnBnClickedCheckS)
END_MESSAGE_MAP()


// CgdtHelperDlg message handlers

BOOL CgdtHelperDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_checkG.SetCheck(0);
	m_checkDB.SetCheck(1);
	m_checkL.SetCheck(0);
	m_checkAVL.SetCheck(0);
	m_checkP.SetCheck(1);
	m_checkS.SetCheck(1);

	m_radioDPL_00.SetCheck(1);
	m_radioType_0000.SetCheck(1);

	for (unsigned i = 0; i < msc_bitCnt; ++i)
	{
		m_editBits[i].SetWindowText("0");
	}
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CgdtHelperDlg::OnPaint()
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
HCURSOR CgdtHelperDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CgdtHelperDlg::OnEnChangeEditSegmentBase()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

}


void CgdtHelperDlg::OnEnChangeEditSegmentBound()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

/*
 *
 *		This macro used to shorten the same line in 'void CgdtHelperDlg::OnBnClickedCheckXXX()'.
 *
 */
#define Foo(bitName) m_editBits[sc_bit##bitName].SetWindowText(m_check##bitName.GetCheck() == 0 ? "0" : "1")

void CgdtHelperDlg::OnBnClickedCheckG()
{ Foo(G); }
void CgdtHelperDlg::OnBnClickedCheckDb()
{ Foo(DB); }
void CgdtHelperDlg::OnBnClickedCheckL()
{ Foo(L); }
void CgdtHelperDlg::OnBnClickedCheckAvl()
{ Foo(AVL); }
void CgdtHelperDlg::OnBnClickedCheckP()
{ Foo(P); }
void CgdtHelperDlg::OnBnClickedCheckS()
{ Foo(S); }