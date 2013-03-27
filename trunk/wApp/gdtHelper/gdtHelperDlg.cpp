
// gdtHelperDlg.cpp : implementation file
//

#include "stdafx.h"
#include "gdtHelper.h"
#include "gdtHelperDlg.h"
#include "afxdialogex.h"
#include "wCppExt.h"
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static const unsigned sc_bitG = 55,
					  sc_bitDB = 54,
					  sc_bitL = 53,
					  sc_bitAVL = 52,
					  sc_bitP = 47,
					  sc_bitS = 44,

					  sc_bitDPL_1 = 46,
					  sc_bitDPL_0 = 45,

					  sc_bitType_3 = 43,
					  sc_bitType_2 = 42,
					  sc_bitType_1 = 41,
					  sc_bitType_0 = 40;

// CgdtHelperDlg dialog

CgdtHelperDlg::CgdtHelperDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CgdtHelperDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CgdtHelperDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CHECK_DB, m_checkDB);
	DDX_Control(pDX, IDC_CHECK_G, m_checkG);
	DDX_Control(pDX, IDC_CHECK_L, m_checkL);
	DDX_Control(pDX, IDC_CHECK_AVL, m_checkAVL);
	DDX_Control(pDX, IDC_CHECK_P, m_checkP);
	DDX_Control(pDX, IDC_CHECK_S, m_checkS);

	DDX_Control(pDX, IDC_EDIT_SEGMENT_BASE, m_editSegmentBase);
	DDX_Control(pDX, IDC_EDIT_SEGMENT_BOUND, m_editSegmentBound);

	DDX_Control(pDX, IDC_STATIC_BASEWRONG, m_staticBaseWrong);
	DDX_Control(pDX, IDC_STATIC_BOUNDWRONG, m_staticBoundWrong);

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

	DDX_Control(pDX, IDC_EDIT_RES_63_32, m_editResHigh);
	DDX_Control(pDX, IDC_EDIT_RES_31_0, m_editResLow);

	DDX_Control(pDX, IDC_STATIC_RES_HIGHPART_WRONG, m_staticResHighPartWrong);
	DDX_Control(pDX, IDC_STATIC_RES_LOWPART_WRONG, m_staticResLowPartWrong);
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

	ON_BN_CLICKED(IDC_RADIO_DPL_00, &CgdtHelperDlg::OnBnClickedRadioDpl00)
	ON_BN_CLICKED(IDC_RADIO_DPL_01, &CgdtHelperDlg::OnBnClickedRadioDpl01)
	ON_BN_CLICKED(IDC_RADIO_DPL_10, &CgdtHelperDlg::OnBnClickedRadioDpl10)
	ON_BN_CLICKED(IDC_RADIO_DPL_11, &CgdtHelperDlg::OnBnClickedRadioDpl11)

	ON_BN_CLICKED(IDC_RADIO_TYPE_0000, &CgdtHelperDlg::OnBnClickedRadioType0000)
	ON_BN_CLICKED(IDC_RADIO_TYPE_0010, &CgdtHelperDlg::OnBnClickedRadioType0010)
	ON_BN_CLICKED(IDC_RADIO_TYPE_0100, &CgdtHelperDlg::OnBnClickedRadioType0100)
	ON_BN_CLICKED(IDC_RADIO_TYPE_0110, &CgdtHelperDlg::OnBnClickedRadioType0110)
	ON_BN_CLICKED(IDC_RADIO_TYPE_1000, &CgdtHelperDlg::OnBnClickedRadioType1000)
	ON_BN_CLICKED(IDC_RADIO_TYPE_1010, &CgdtHelperDlg::OnBnClickedRadioType1010)
	ON_BN_CLICKED(IDC_RADIO_TYPE_1100, &CgdtHelperDlg::OnBnClickedRadioType1100)
	ON_BN_CLICKED(IDC_RADIO_TYPE_1110, &CgdtHelperDlg::OnBnClickedRadioType1110)

	ON_EN_CHANGE(IDC_EDIT_0, &CgdtHelperDlg::OnEnChangeEdit0)
	ON_EN_CHANGE(IDC_EDIT_1, &CgdtHelperDlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT_2, &CgdtHelperDlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT_3, &CgdtHelperDlg::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT_4, &CgdtHelperDlg::OnEnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT_5, &CgdtHelperDlg::OnEnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT_6, &CgdtHelperDlg::OnEnChangeEdit6)
	ON_EN_CHANGE(IDC_EDIT_7, &CgdtHelperDlg::OnEnChangeEdit7)
	ON_EN_CHANGE(IDC_EDIT_8, &CgdtHelperDlg::OnEnChangeEdit8)
	ON_EN_CHANGE(IDC_EDIT_9, &CgdtHelperDlg::OnEnChangeEdit9)
	ON_EN_CHANGE(IDC_EDIT_10, &CgdtHelperDlg::OnEnChangeEdit10)
	ON_EN_CHANGE(IDC_EDIT_11, &CgdtHelperDlg::OnEnChangeEdit11)
	ON_EN_CHANGE(IDC_EDIT_12, &CgdtHelperDlg::OnEnChangeEdit12)
	ON_EN_CHANGE(IDC_EDIT_13, &CgdtHelperDlg::OnEnChangeEdit13)
	ON_EN_CHANGE(IDC_EDIT_14, &CgdtHelperDlg::OnEnChangeEdit14)
	ON_EN_CHANGE(IDC_EDIT_15, &CgdtHelperDlg::OnEnChangeEdit15)
	ON_EN_CHANGE(IDC_EDIT_16, &CgdtHelperDlg::OnEnChangeEdit16)
	ON_EN_CHANGE(IDC_EDIT_17, &CgdtHelperDlg::OnEnChangeEdit17)
	ON_EN_CHANGE(IDC_EDIT_18, &CgdtHelperDlg::OnEnChangeEdit18)
	ON_EN_CHANGE(IDC_EDIT_19, &CgdtHelperDlg::OnEnChangeEdit19)
	ON_EN_CHANGE(IDC_EDIT_20, &CgdtHelperDlg::OnEnChangeEdit20)
	ON_EN_CHANGE(IDC_EDIT_21, &CgdtHelperDlg::OnEnChangeEdit21)
	ON_EN_CHANGE(IDC_EDIT_22, &CgdtHelperDlg::OnEnChangeEdit22)
	ON_EN_CHANGE(IDC_EDIT_23, &CgdtHelperDlg::OnEnChangeEdit23)
	ON_EN_CHANGE(IDC_EDIT_24, &CgdtHelperDlg::OnEnChangeEdit24)
	ON_EN_CHANGE(IDC_EDIT_25, &CgdtHelperDlg::OnEnChangeEdit25)
	ON_EN_CHANGE(IDC_EDIT_26, &CgdtHelperDlg::OnEnChangeEdit26)
	ON_EN_CHANGE(IDC_EDIT_27, &CgdtHelperDlg::OnEnChangeEdit27)
	ON_EN_CHANGE(IDC_EDIT_28, &CgdtHelperDlg::OnEnChangeEdit28)
	ON_EN_CHANGE(IDC_EDIT_29, &CgdtHelperDlg::OnEnChangeEdit29)
	ON_EN_CHANGE(IDC_EDIT_30, &CgdtHelperDlg::OnEnChangeEdit30)
	ON_EN_CHANGE(IDC_EDIT_31, &CgdtHelperDlg::OnEnChangeEdit31)
	ON_EN_CHANGE(IDC_EDIT_32, &CgdtHelperDlg::OnEnChangeEdit32)
	ON_EN_CHANGE(IDC_EDIT_33, &CgdtHelperDlg::OnEnChangeEdit33)
	ON_EN_CHANGE(IDC_EDIT_34, &CgdtHelperDlg::OnEnChangeEdit34)
	ON_EN_CHANGE(IDC_EDIT_35, &CgdtHelperDlg::OnEnChangeEdit35)
	ON_EN_CHANGE(IDC_EDIT_36, &CgdtHelperDlg::OnEnChangeEdit36)
	ON_EN_CHANGE(IDC_EDIT_37, &CgdtHelperDlg::OnEnChangeEdit37)
	ON_EN_CHANGE(IDC_EDIT_38, &CgdtHelperDlg::OnEnChangeEdit38)
	ON_EN_CHANGE(IDC_EDIT_39, &CgdtHelperDlg::OnEnChangeEdit39)
	ON_EN_CHANGE(IDC_EDIT_40, &CgdtHelperDlg::OnEnChangeEdit40)
	ON_EN_CHANGE(IDC_EDIT_41, &CgdtHelperDlg::OnEnChangeEdit41)
	ON_EN_CHANGE(IDC_EDIT_42, &CgdtHelperDlg::OnEnChangeEdit42)
	ON_EN_CHANGE(IDC_EDIT_43, &CgdtHelperDlg::OnEnChangeEdit43)
	ON_EN_CHANGE(IDC_EDIT_44, &CgdtHelperDlg::OnEnChangeEdit44)
	ON_EN_CHANGE(IDC_EDIT_45, &CgdtHelperDlg::OnEnChangeEdit45)
	ON_EN_CHANGE(IDC_EDIT_46, &CgdtHelperDlg::OnEnChangeEdit46)
	ON_EN_CHANGE(IDC_EDIT_47, &CgdtHelperDlg::OnEnChangeEdit47)
	ON_EN_CHANGE(IDC_EDIT_48, &CgdtHelperDlg::OnEnChangeEdit48)
	ON_EN_CHANGE(IDC_EDIT_49, &CgdtHelperDlg::OnEnChangeEdit49)
	ON_EN_CHANGE(IDC_EDIT_50, &CgdtHelperDlg::OnEnChangeEdit50)
	ON_EN_CHANGE(IDC_EDIT_51, &CgdtHelperDlg::OnEnChangeEdit51)
	ON_EN_CHANGE(IDC_EDIT_52, &CgdtHelperDlg::OnEnChangeEdit52)
	ON_EN_CHANGE(IDC_EDIT_53, &CgdtHelperDlg::OnEnChangeEdit53)
	ON_EN_CHANGE(IDC_EDIT_54, &CgdtHelperDlg::OnEnChangeEdit54)
	ON_EN_CHANGE(IDC_EDIT_55, &CgdtHelperDlg::OnEnChangeEdit55)
	ON_EN_CHANGE(IDC_EDIT_56, &CgdtHelperDlg::OnEnChangeEdit56)
	ON_EN_CHANGE(IDC_EDIT_57, &CgdtHelperDlg::OnEnChangeEdit57)
	ON_EN_CHANGE(IDC_EDIT_58, &CgdtHelperDlg::OnEnChangeEdit58)
	ON_EN_CHANGE(IDC_EDIT_59, &CgdtHelperDlg::OnEnChangeEdit59)	
	ON_EN_CHANGE(IDC_EDIT_60, &CgdtHelperDlg::OnEnChangeEdit60)
	ON_EN_CHANGE(IDC_EDIT_61, &CgdtHelperDlg::OnEnChangeEdit61)
	ON_EN_CHANGE(IDC_EDIT_62, &CgdtHelperDlg::OnEnChangeEdit62)
	ON_EN_CHANGE(IDC_EDIT_63, &CgdtHelperDlg::OnEnChangeEdit63)
END_MESSAGE_MAP()


// CgdtHelperDlg message handlers

BOOL CgdtHelperDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// Initialize widget.
	m_editSegmentBase.SetLimitText(8);
	m_editSegmentBound.SetLimitText(6);
	for (unsigned i = 0; i < arrCnt(m_editBits); ++i)
	{
		m_editBits[i].SetLimitText(1);
	}

	// Initialize data.
	m_editSegmentBase.SetWindowText("00000000");
	m_editSegmentBound.SetWindowText("000000");

	m_radioDPL_00.SetCheck(1);
	m_radioType_0000.SetCheck(1); 

	for (unsigned i = 0; i < arrCnt(m_editBits); ++i)
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
	char num[1024] = {};
	m_editSegmentBase.GetWindowText(num, arrCnt(num));

	// Check input valid.
	if (regex_match(num, regex("(0[xX])?[0-9a-fA-F]+")))
	{
		m_staticBaseWrong.ShowWindow(SW_HIDE);

		unsigned val = static_cast<unsigned>(stoul(num, nullptr, 16));
		// SegmentBase[15-0] => GlobalDescriptor[31-16].
		for (unsigned i = 0; i < 16; ++i)
		{
			m_editBits[16 + i].SetWindowText((val & 1<<i) == 0 ? "0" : "1");
		}
		// SegmentBase[23-16] => GlobalDescriptor[39-32].
		for (unsigned i = 16; i < 24; ++i)
		{
			m_editBits[16 + i].SetWindowText((val & 1<<i) == 0 ? "0" : "1");
		}
		// SegmentBase[31-24] => GlobalDescriptor[63-56].
		for (unsigned i = 24; i < 32; ++i)
		{
			m_editBits[32 + i].SetWindowText((val & 1<<i) == 0 ? "0" : "1");
		}
	}
	else
	{
		m_staticBaseWrong.ShowWindow(SW_SHOW);
	}
}

void CgdtHelperDlg::OnEnChangeEditSegmentBound()
{
	char num[1024] = {};
	m_editSegmentBound.GetWindowText(num, arrCnt(num));

	// Check input valid.
	if (regex_match(num, regex("(0[xX])?[0-9a-fA-F]+")))
	{
		m_staticBoundWrong.ShowWindow(SW_HIDE);

		unsigned val = static_cast<unsigned>(stoul(num, nullptr, 16));
		// SegmentBound[15-0] => GlobalDescriptor[15-0].
		for (unsigned i = 0; i < 16; ++i)
		{
			m_editBits[i].SetWindowText((val & 1<<i) == 0 ? "0" : "1");
		}
		// SegmentBound[19-16] => GlobalDescriptor[51-48].
		for (unsigned i = 16; i < 24; ++i)
		{
			m_editBits[32 + i].SetWindowText((val & 1<<i) == 0 ? "0" : "1");
		}
	}
	else
	{
		m_staticBoundWrong.ShowWindow(SW_SHOW);
	}
}

void CgdtHelperDlg::OnBnClickedCheckG() { m_editBits[sc_bitG].SetWindowText(m_checkG.GetCheck() == 0 ? "0" : "1"); }
void CgdtHelperDlg::OnBnClickedCheckDb() { m_editBits[sc_bitDB].SetWindowText(m_checkDB.GetCheck() == 0 ? "0" : "1"); }
void CgdtHelperDlg::OnBnClickedCheckL() { m_editBits[sc_bitL].SetWindowText(m_checkL.GetCheck() == 0 ? "0" : "1"); }
void CgdtHelperDlg::OnBnClickedCheckAvl() { m_editBits[sc_bitAVL].SetWindowText(m_checkAVL.GetCheck() == 0 ? "0" : "1"); }
void CgdtHelperDlg::OnBnClickedCheckP() { m_editBits[sc_bitP].SetWindowText(m_checkP.GetCheck() == 0 ? "0" : "1"); }
void CgdtHelperDlg::OnBnClickedCheckS() { m_editBits[sc_bitS].SetWindowText(m_checkS.GetCheck() == 0 ? "0" : "1"); }

void CgdtHelperDlg::OnBnClickedRadioDpl00() { m_editBits[sc_bitDPL_1].SetWindowText("0"), m_editBits[sc_bitDPL_0].SetWindowText("0"); }
void CgdtHelperDlg::OnBnClickedRadioDpl01() { m_editBits[sc_bitDPL_1].SetWindowText("0"), m_editBits[sc_bitDPL_0].SetWindowText("1"); }
void CgdtHelperDlg::OnBnClickedRadioDpl10() { m_editBits[sc_bitDPL_1].SetWindowText("1"), m_editBits[sc_bitDPL_0].SetWindowText("0"); }
void CgdtHelperDlg::OnBnClickedRadioDpl11() { m_editBits[sc_bitDPL_1].SetWindowText("1"), m_editBits[sc_bitDPL_0].SetWindowText("1"); }

#define Bar(d, c, b, a) do \
{\
	m_editBits[sc_bitType_3].SetWindowText(#d), \
	m_editBits[sc_bitType_2].SetWindowText(#c), \
	m_editBits[sc_bitType_1].SetWindowText(#b), \
	m_editBits[sc_bitType_0].SetWindowText(#a); \
} while (0)

void CgdtHelperDlg::OnBnClickedRadioType0000() { Bar(0, 0, 0, 0); }
void CgdtHelperDlg::OnBnClickedRadioType0010() { Bar(0, 0, 1, 0); }
void CgdtHelperDlg::OnBnClickedRadioType0100() { Bar(0, 1, 0, 0); }
void CgdtHelperDlg::OnBnClickedRadioType0110() { Bar(0, 1, 1, 0); }
void CgdtHelperDlg::OnBnClickedRadioType1000() { Bar(1, 0, 0, 0); }
void CgdtHelperDlg::OnBnClickedRadioType1010() { Bar(1, 0, 1, 0); }
void CgdtHelperDlg::OnBnClickedRadioType1100() { Bar(1, 1, 0, 0); }
void CgdtHelperDlg::OnBnClickedRadioType1110() { Bar(1, 1, 1, 0); }

void CgdtHelperDlg::OnEnChangeEdit0 () { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit1 () { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit2 () { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit3 () { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit4 () { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit5 () { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit6 () { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit7 () { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit8 () { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit9 () { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit10() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit11() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit12() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit13() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit14() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit15() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit16() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit17() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit18() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit19() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit20() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit21() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit22() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit23() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit24() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit25() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit26() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit27() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit28() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit29() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit30() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit31() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit32() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit33() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit34() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit35() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit36() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit37() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit38() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit39() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit40() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit41() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit42() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit43() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit44() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit45() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit46() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit47() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit48() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit49() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit50() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit51() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit52() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit53() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit54() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit55() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit56() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit57() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit58() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit59() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit60() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit61() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit62() { getRes(); }
void CgdtHelperDlg::OnEnChangeEdit63() { getRes(); }

// logic.
void CgdtHelperDlg::getRes()
{
	string res;
	for (unsigned i = 0; i < arrCnt(m_editBits); ++i)
	{
		char txt[2] = {};
		m_editBits[arrCnt(m_editBits)-1 - i].GetWindowText(txt, arrCnt(txt));
		txt[1] = '\0';

		res.push_back(txt[0]);
	}

	// High part.
	string strHighPart = res.substr(0, 32);
	if (regex_match(strHighPart, regex("^[01]{32}$")))
	{
		// Binary string to hexdecimal string.
		unsigned uHighPart = static_cast<unsigned>(stoul(strHighPart, nullptr, 2));
		ostringstream ossHigh;
		ossHigh <<hex <<setfill('0') <<setw(8) <<uHighPart;
		m_editResHigh.SetWindowText(ossHigh.str().c_str());
		m_staticResHighPartWrong.ShowWindow(SW_HIDE);
	}
	else
	{
		m_staticResHighPartWrong.ShowWindow(SW_SHOW);
	}
	// Low part.
	string strLowPart = res.substr(32, 32);
	if (regex_match(strLowPart, regex("^[01]{32}$")))
	{
		// Binary string to hexdecimal string.
		unsigned uLowPart = static_cast<unsigned>(stoul(strLowPart, nullptr, 2));
		ostringstream ossLow;
		ossLow <<hex <<setfill('0') <<setw(8) <<uLowPart;
		m_editResLow.SetWindowText(ossLow.str().c_str());
		m_staticResLowPartWrong.ShowWindow(SW_HIDE);
	}
	else
	{
		m_staticResLowPartWrong.ShowWindow(SW_SHOW);
	}
}