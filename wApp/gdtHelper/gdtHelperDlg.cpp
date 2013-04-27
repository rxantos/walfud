
// gdtHelperDlg.cpp : implementation file
//

#include "stdafx.h"
#include "main.h"
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

	{
		unsigned i = 0;
		DDX_Control(pDX, IDC_RADIO_DPL_00, m_radioDPL[i++]);
		DDX_Control(pDX, IDC_RADIO_DPL_01, m_radioDPL[i++]);
		DDX_Control(pDX, IDC_RADIO_DPL_10, m_radioDPL[i++]);
		DDX_Control(pDX, IDC_RADIO_DPL_11, m_radioDPL[i++]);
	}

	{
		unsigned i = 0;
		DDX_Control(pDX, IDC_RADIO_TYPE_0000, m_radioType[i++]);
		DDX_Control(pDX, IDC_RADIO_TYPE_0001, m_radioType[i++]);
		DDX_Control(pDX, IDC_RADIO_TYPE_0010, m_radioType[i++]);
		DDX_Control(pDX, IDC_RADIO_TYPE_0011, m_radioType[i++]);
		DDX_Control(pDX, IDC_RADIO_TYPE_0100, m_radioType[i++]);
		DDX_Control(pDX, IDC_RADIO_TYPE_0101, m_radioType[i++]);
		DDX_Control(pDX, IDC_RADIO_TYPE_0110, m_radioType[i++]);
		DDX_Control(pDX, IDC_RADIO_TYPE_0111, m_radioType[i++]);
		DDX_Control(pDX, IDC_RADIO_TYPE_1000, m_radioType[i++]);
		DDX_Control(pDX, IDC_RADIO_TYPE_1001, m_radioType[i++]);
		DDX_Control(pDX, IDC_RADIO_TYPE_1010, m_radioType[i++]);
		DDX_Control(pDX, IDC_RADIO_TYPE_1011, m_radioType[i++]);
		DDX_Control(pDX, IDC_RADIO_TYPE_1100, m_radioType[i++]);
		DDX_Control(pDX, IDC_RADIO_TYPE_1101, m_radioType[i++]);
		DDX_Control(pDX, IDC_RADIO_TYPE_1110, m_radioType[i++]);
		DDX_Control(pDX, IDC_RADIO_TYPE_1111, m_radioType[i++]);
	}

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

	DDX_Control(pDX, IDC_EDIT_RES_32_64, m_editResHigh);
	DDX_Control(pDX, IDC_EDIT_RES_0_32, m_editResLow);

	DDX_Control(pDX, IDC_STATIC_RES_HIGHPART_WRONG, m_staticResHighPartWrong);
	DDX_Control(pDX, IDC_STATIC_RES_LOWPART_WRONG, m_staticResLowPartWrong);
	DDX_Control(pDX, IDC_STATIC_TYPE, m_staticTypeDesc);
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
	ON_BN_CLICKED(IDC_RADIO_TYPE_0001, &CgdtHelperDlg::OnBnClickedRadioType0001)
	ON_BN_CLICKED(IDC_RADIO_TYPE_0010, &CgdtHelperDlg::OnBnClickedRadioType0010)
	ON_BN_CLICKED(IDC_RADIO_TYPE_0011, &CgdtHelperDlg::OnBnClickedRadioType0011)
	ON_BN_CLICKED(IDC_RADIO_TYPE_0100, &CgdtHelperDlg::OnBnClickedRadioType0100)
	ON_BN_CLICKED(IDC_RADIO_TYPE_0101, &CgdtHelperDlg::OnBnClickedRadioType0101)
	ON_BN_CLICKED(IDC_RADIO_TYPE_0110, &CgdtHelperDlg::OnBnClickedRadioType0110)
	ON_BN_CLICKED(IDC_RADIO_TYPE_0111, &CgdtHelperDlg::OnBnClickedRadioType0111)
	ON_BN_CLICKED(IDC_RADIO_TYPE_1000, &CgdtHelperDlg::OnBnClickedRadioType1000)
	ON_BN_CLICKED(IDC_RADIO_TYPE_1001, &CgdtHelperDlg::OnBnClickedRadioType1001)
	ON_BN_CLICKED(IDC_RADIO_TYPE_1010, &CgdtHelperDlg::OnBnClickedRadioType1010)
	ON_BN_CLICKED(IDC_RADIO_TYPE_1011, &CgdtHelperDlg::OnBnClickedRadioType1011)
	ON_BN_CLICKED(IDC_RADIO_TYPE_1100, &CgdtHelperDlg::OnBnClickedRadioType1100)
	ON_BN_CLICKED(IDC_RADIO_TYPE_1101, &CgdtHelperDlg::OnBnClickedRadioType1101)
	ON_BN_CLICKED(IDC_RADIO_TYPE_1110, &CgdtHelperDlg::OnBnClickedRadioType1110)
	ON_BN_CLICKED(IDC_RADIO_TYPE_1111, &CgdtHelperDlg::OnBnClickedRadioType1111)

	//ON_EN_CHANGE(IDC_EDIT_0, &CgdtHelperDlg::OnEnChangeEdit0)
	//ON_EN_CHANGE(IDC_EDIT_1, &CgdtHelperDlg::OnEnChangeEdit1)
	//ON_EN_CHANGE(IDC_EDIT_2, &CgdtHelperDlg::OnEnChangeEdit2)
	//ON_EN_CHANGE(IDC_EDIT_3, &CgdtHelperDlg::OnEnChangeEdit3)
	//ON_EN_CHANGE(IDC_EDIT_4, &CgdtHelperDlg::OnEnChangeEdit4)
	//ON_EN_CHANGE(IDC_EDIT_5, &CgdtHelperDlg::OnEnChangeEdit5)
	//ON_EN_CHANGE(IDC_EDIT_6, &CgdtHelperDlg::OnEnChangeEdit6)
	//ON_EN_CHANGE(IDC_EDIT_7, &CgdtHelperDlg::OnEnChangeEdit7)
	//ON_EN_CHANGE(IDC_EDIT_8, &CgdtHelperDlg::OnEnChangeEdit8)
	//ON_EN_CHANGE(IDC_EDIT_9, &CgdtHelperDlg::OnEnChangeEdit9)
	//ON_EN_CHANGE(IDC_EDIT_10, &CgdtHelperDlg::OnEnChangeEdit10)
	//ON_EN_CHANGE(IDC_EDIT_11, &CgdtHelperDlg::OnEnChangeEdit11)
	//ON_EN_CHANGE(IDC_EDIT_12, &CgdtHelperDlg::OnEnChangeEdit12)
	//ON_EN_CHANGE(IDC_EDIT_13, &CgdtHelperDlg::OnEnChangeEdit13)
	//ON_EN_CHANGE(IDC_EDIT_14, &CgdtHelperDlg::OnEnChangeEdit14)
	//ON_EN_CHANGE(IDC_EDIT_15, &CgdtHelperDlg::OnEnChangeEdit15)
	//ON_EN_CHANGE(IDC_EDIT_16, &CgdtHelperDlg::OnEnChangeEdit16)
	//ON_EN_CHANGE(IDC_EDIT_17, &CgdtHelperDlg::OnEnChangeEdit17)
	//ON_EN_CHANGE(IDC_EDIT_18, &CgdtHelperDlg::OnEnChangeEdit18)
	//ON_EN_CHANGE(IDC_EDIT_19, &CgdtHelperDlg::OnEnChangeEdit19)
	//ON_EN_CHANGE(IDC_EDIT_20, &CgdtHelperDlg::OnEnChangeEdit20)
	//ON_EN_CHANGE(IDC_EDIT_21, &CgdtHelperDlg::OnEnChangeEdit21)
	//ON_EN_CHANGE(IDC_EDIT_22, &CgdtHelperDlg::OnEnChangeEdit22)
	//ON_EN_CHANGE(IDC_EDIT_23, &CgdtHelperDlg::OnEnChangeEdit23)
	//ON_EN_CHANGE(IDC_EDIT_24, &CgdtHelperDlg::OnEnChangeEdit24)
	//ON_EN_CHANGE(IDC_EDIT_25, &CgdtHelperDlg::OnEnChangeEdit25)
	//ON_EN_CHANGE(IDC_EDIT_26, &CgdtHelperDlg::OnEnChangeEdit26)
	//ON_EN_CHANGE(IDC_EDIT_27, &CgdtHelperDlg::OnEnChangeEdit27)
	//ON_EN_CHANGE(IDC_EDIT_28, &CgdtHelperDlg::OnEnChangeEdit28)
	//ON_EN_CHANGE(IDC_EDIT_29, &CgdtHelperDlg::OnEnChangeEdit29)
	//ON_EN_CHANGE(IDC_EDIT_30, &CgdtHelperDlg::OnEnChangeEdit30)
	//ON_EN_CHANGE(IDC_EDIT_31, &CgdtHelperDlg::OnEnChangeEdit31)
	//ON_EN_CHANGE(IDC_EDIT_32, &CgdtHelperDlg::OnEnChangeEdit32)
	//ON_EN_CHANGE(IDC_EDIT_33, &CgdtHelperDlg::OnEnChangeEdit33)
	//ON_EN_CHANGE(IDC_EDIT_34, &CgdtHelperDlg::OnEnChangeEdit34)
	//ON_EN_CHANGE(IDC_EDIT_35, &CgdtHelperDlg::OnEnChangeEdit35)
	//ON_EN_CHANGE(IDC_EDIT_36, &CgdtHelperDlg::OnEnChangeEdit36)
	//ON_EN_CHANGE(IDC_EDIT_37, &CgdtHelperDlg::OnEnChangeEdit37)
	//ON_EN_CHANGE(IDC_EDIT_38, &CgdtHelperDlg::OnEnChangeEdit38)
	//ON_EN_CHANGE(IDC_EDIT_39, &CgdtHelperDlg::OnEnChangeEdit39)
	//ON_EN_CHANGE(IDC_EDIT_40, &CgdtHelperDlg::OnEnChangeEdit40)
	//ON_EN_CHANGE(IDC_EDIT_41, &CgdtHelperDlg::OnEnChangeEdit41)
	//ON_EN_CHANGE(IDC_EDIT_42, &CgdtHelperDlg::OnEnChangeEdit42)
	//ON_EN_CHANGE(IDC_EDIT_43, &CgdtHelperDlg::OnEnChangeEdit43)
	//ON_EN_CHANGE(IDC_EDIT_44, &CgdtHelperDlg::OnEnChangeEdit44)
	//ON_EN_CHANGE(IDC_EDIT_45, &CgdtHelperDlg::OnEnChangeEdit45)
	//ON_EN_CHANGE(IDC_EDIT_46, &CgdtHelperDlg::OnEnChangeEdit46)
	//ON_EN_CHANGE(IDC_EDIT_47, &CgdtHelperDlg::OnEnChangeEdit47)
	//ON_EN_CHANGE(IDC_EDIT_48, &CgdtHelperDlg::OnEnChangeEdit48)
	//ON_EN_CHANGE(IDC_EDIT_49, &CgdtHelperDlg::OnEnChangeEdit49)
	//ON_EN_CHANGE(IDC_EDIT_50, &CgdtHelperDlg::OnEnChangeEdit50)
	//ON_EN_CHANGE(IDC_EDIT_51, &CgdtHelperDlg::OnEnChangeEdit51)
	//ON_EN_CHANGE(IDC_EDIT_52, &CgdtHelperDlg::OnEnChangeEdit52)
	//ON_EN_CHANGE(IDC_EDIT_53, &CgdtHelperDlg::OnEnChangeEdit53)
	//ON_EN_CHANGE(IDC_EDIT_54, &CgdtHelperDlg::OnEnChangeEdit54)
	//ON_EN_CHANGE(IDC_EDIT_55, &CgdtHelperDlg::OnEnChangeEdit55)
	//ON_EN_CHANGE(IDC_EDIT_56, &CgdtHelperDlg::OnEnChangeEdit56)
	//ON_EN_CHANGE(IDC_EDIT_57, &CgdtHelperDlg::OnEnChangeEdit57)
	//ON_EN_CHANGE(IDC_EDIT_58, &CgdtHelperDlg::OnEnChangeEdit58)
	//ON_EN_CHANGE(IDC_EDIT_59, &CgdtHelperDlg::OnEnChangeEdit59)	
	//ON_EN_CHANGE(IDC_EDIT_60, &CgdtHelperDlg::OnEnChangeEdit60)
	//ON_EN_CHANGE(IDC_EDIT_61, &CgdtHelperDlg::OnEnChangeEdit61)
	//ON_EN_CHANGE(IDC_EDIT_62, &CgdtHelperDlg::OnEnChangeEdit62)
	//ON_EN_CHANGE(IDC_EDIT_63, &CgdtHelperDlg::OnEnChangeEdit63)
	ON_BN_CLICKED(IDC_BUTTON_CTOR, &CgdtHelperDlg::OnBnClickedButtonCtor)
	ON_BN_CLICKED(IDC_BUTTON_DTOR, &CgdtHelperDlg::OnBnClickedButtonDtor)
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
	m_editSegmentBound.SetLimitText(5);
	for (auto i = 0; i < arrCnt(m_editBits); ++i)
	{
		m_editBits[i].SetLimitText(1);
	}
	m_editResLow.SetLimitText(8);
	m_editResHigh.SetLimitText(8);

	// Initialize data.
	m_editSegmentBase.SetWindowText("00000000");
	m_editSegmentBound.SetWindowText("00000");

	m_radioDPL[0].SetCheck(1);
	m_radioType[0].SetCheck(1); 

	for (auto i = 0; i < arrCnt(m_editBits); ++i)
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

void CgdtHelperDlg::OnEnChangeEditSegmentBase() {}
void CgdtHelperDlg::OnEnChangeEditSegmentBound() {}

void CgdtHelperDlg::OnBnClickedCheckG() {}
void CgdtHelperDlg::OnBnClickedCheckDb() {}
void CgdtHelperDlg::OnBnClickedCheckL() {}
void CgdtHelperDlg::OnBnClickedCheckAvl() {}
void CgdtHelperDlg::OnBnClickedCheckP() {}
void CgdtHelperDlg::OnBnClickedCheckS() 
{
	// This flag control type.
	// When set: ("A" is accessed bit, the bit will be set by processor when accessed the segment. Should be initialized to 0)
		// "000A" => data segment, read only.
		// "001A" => data segment, readable, writable.
		// "010A" => data segment, read only, downward expansion.
		// "011A" => data segment, readable, writable, downward expansion.
		// "100A" => code segment, execute only.
		// "101A" => code segment, executable, readable.
		// "110A" => code segment, execute only, compatible.
		// "111A" => code segment, executable, readable, compatible.
	// When non-set:
		// "0010" => LDT descriptor.
		// "0101" => task gate.
		// "10B1" => TSS descriptor. ("B" is busy bit, if "1", means task is running, "0" means free)
		// "1100" => call gate.
	vector<unsigned> radioTypeToShow;		// The wedgit id which to show.
	if (m_checkS.GetCheck() != 0)
	{
		// Set.
		radioTypeToShow.push_back(0x00);
		radioTypeToShow.push_back(0x02);
		radioTypeToShow.push_back(0x04);
		radioTypeToShow.push_back(0x06);
		
		radioTypeToShow.push_back(0x08);
		radioTypeToShow.push_back(0x0a);
		radioTypeToShow.push_back(0x0c);
		radioTypeToShow.push_back(0x0e);
	}
	else
	{
		// Non set.
		radioTypeToShow.push_back(0x02);
		radioTypeToShow.push_back(0x05);
		radioTypeToShow.push_back(0x09), radioTypeToShow.push_back(0x0b);
		radioTypeToShow.push_back(0x0c);
	}

	// Show available wedgit.
	for (auto &i : m_radioType)
	{
		// Hide all.
		i.ShowWindow(SW_HIDE);
	}
	for (const auto &i : radioTypeToShow)
	{
		// Show available.
		m_radioType[i].ShowWindow(SW_SHOW);
	}

	// Check if current selection is in showed wedgit.
	// If not, reselect.
	for (auto i = 0; i < arrCnt(m_radioType); ++i)
	{
		if (m_radioType[i].GetCheck() != 0)
		{
			if (find(radioTypeToShow.begin(), radioTypeToShow.end(), i) == radioTypeToShow.end())
			{
				// Reselect.
				m_radioType[i].SetCheck(0);
				m_radioType[radioTypeToShow[0]].SetCheck(1);
			}
			m_staticTypeDesc.SetWindowText(getTypeDesc().c_str());	// Update type description.

			break;
		}//if (m_radioType
	}//for
}

void CgdtHelperDlg::OnBnClickedRadioDpl00() {}
void CgdtHelperDlg::OnBnClickedRadioDpl01() {}
void CgdtHelperDlg::OnBnClickedRadioDpl10() {}
void CgdtHelperDlg::OnBnClickedRadioDpl11() {}

void CgdtHelperDlg::OnBnClickedRadioType0000() { m_staticTypeDesc.SetWindowText(getTypeDesc().c_str()); }
void CgdtHelperDlg::OnBnClickedRadioType0001() { m_staticTypeDesc.SetWindowText(getTypeDesc().c_str()); }
void CgdtHelperDlg::OnBnClickedRadioType0010() { m_staticTypeDesc.SetWindowText(getTypeDesc().c_str()); }
void CgdtHelperDlg::OnBnClickedRadioType0011() { m_staticTypeDesc.SetWindowText(getTypeDesc().c_str()); }
void CgdtHelperDlg::OnBnClickedRadioType0100() { m_staticTypeDesc.SetWindowText(getTypeDesc().c_str()); }
void CgdtHelperDlg::OnBnClickedRadioType0101() { m_staticTypeDesc.SetWindowText(getTypeDesc().c_str()); }
void CgdtHelperDlg::OnBnClickedRadioType0110() { m_staticTypeDesc.SetWindowText(getTypeDesc().c_str()); }
void CgdtHelperDlg::OnBnClickedRadioType0111() { m_staticTypeDesc.SetWindowText(getTypeDesc().c_str()); }
void CgdtHelperDlg::OnBnClickedRadioType1000() { m_staticTypeDesc.SetWindowText(getTypeDesc().c_str()); }
void CgdtHelperDlg::OnBnClickedRadioType1001() { m_staticTypeDesc.SetWindowText(getTypeDesc().c_str()); }
void CgdtHelperDlg::OnBnClickedRadioType1010() { m_staticTypeDesc.SetWindowText(getTypeDesc().c_str()); }
void CgdtHelperDlg::OnBnClickedRadioType1011() { m_staticTypeDesc.SetWindowText(getTypeDesc().c_str()); }
void CgdtHelperDlg::OnBnClickedRadioType1100() { m_staticTypeDesc.SetWindowText(getTypeDesc().c_str()); }
void CgdtHelperDlg::OnBnClickedRadioType1101() { m_staticTypeDesc.SetWindowText(getTypeDesc().c_str()); }
void CgdtHelperDlg::OnBnClickedRadioType1110() { m_staticTypeDesc.SetWindowText(getTypeDesc().c_str()); }
void CgdtHelperDlg::OnBnClickedRadioType1111() { m_staticTypeDesc.SetWindowText(getTypeDesc().c_str()); }

//void CgdtHelperDlg::OnEnChangeEdit0 () { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit1 () { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit2 () { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit3 () { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit4 () { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit5 () { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit6 () { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit7 () { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit8 () { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit9 () { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit10() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit11() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit12() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit13() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit14() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit15() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit16() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit17() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit18() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit19() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit20() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit21() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit22() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit23() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit24() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit25() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit26() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit27() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit28() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit29() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit30() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit31() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit32() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit33() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit34() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit35() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit36() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit37() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit38() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit39() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit40() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit41() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit42() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit43() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit44() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit45() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit46() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit47() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit48() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit49() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit50() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit51() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit52() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit53() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit54() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit55() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit56() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit57() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit58() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit59() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit60() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit61() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit62() { getRes(); }
//void CgdtHelperDlg::OnEnChangeEdit63() { getRes(); }

// logic.
void CgdtHelperDlg::getRes()
{
	string res;
	for (auto &i : m_editBits)
	{
		char txt[2] = {};
		i.GetWindowText(txt, arrCnt(txt));
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

uint64_t CgdtHelperDlg::getResLeft()
{
	GDT_Entry res;

	// Segment base address.
	char numBase[16] = {};
	m_editSegmentBase.GetWindowText(numBase, arrCnt(numBase));

	// Check input valid.
	if (regex_match(numBase, regex("[0-9a-fA-F]+")))
	{
		// Input correct.
		m_staticBaseWrong.ShowWindow(SW_HIDE);

		res.setAddr(stoul(numBase, nullptr, 16));
	}
	else
	{
		// Input error.
		m_staticBaseWrong.ShowWindow(SW_SHOW);
	}

	// Segment bound.
	char numBound[16] = {};
	m_editSegmentBound.GetWindowText(numBound, arrCnt(numBound));

	// Check input valid.
	if (regex_match(numBound, regex("[0-9a-fA-F]+")))
	{
		// Input correct.
		m_staticBoundWrong.ShowWindow(SW_HIDE);

		res.setLimit(stoul(numBound, nullptr, 16));
	}
	else
	{
		// Input error.
		m_staticBoundWrong.ShowWindow(SW_SHOW);
	}

	// Granularity.
	res.setG(m_checkG.GetCheck());
	// D/B.
	res.setDB(m_checkDB.GetCheck());
	// Long.
	res.setL(m_checkL.GetCheck());
	// Available.
	res.setAVL(m_checkAVL.GetCheck());
	// Present.
	res.setP(m_checkP.GetCheck());
	// Descriptor privilege level.
	for (auto i = 0; i < arrCnt(m_radioDPL); ++i)
	{
		if (m_radioDPL[i].GetCheck() != 0)
		{
			res.setDPL(i);
			break;
		}
	}
	// System.
	res.setS(m_checkS.GetCheck());
	// Type.
	for (auto i = 0; i < arrCnt(m_radioType); ++i)
	{
		if (m_radioType[i].GetCheck() != 0)
		{
			res.setType(i);
			break;
		}
	}

	return res.get_0_64();
}
uint64_t CgdtHelperDlg::getResRight()
{
	GDT_Entry res = 0;

	char bit_0_32[32] = {}, bit_32_64[32] = {};
	m_editResLow.GetWindowText(bit_0_32, arrCnt(bit_0_32));
	m_editResHigh.GetWindowText(bit_32_64, arrCnt(bit_32_64));

	// Check input valid.
	if (regex_match(bit_0_32, regex("[0-9a-fA-F]+")))
	{
		m_staticResLowPartWrong.ShowWindow(SW_HIDE);

		res.set_0_32(w::strToUnsigned(bit_0_32, 16));
	}
	else
	{
		m_staticResLowPartWrong.ShowWindow(SW_SHOW);
	}
	if (regex_match(bit_32_64, regex("[0-9a-fA-F]+")))
	{
		m_staticResHighPartWrong.ShowWindow(SW_HIDE);

		res.set_32_64(w::strToUnsigned(bit_32_64, 16));
	}
	else
	{
		m_staticResHighPartWrong.ShowWindow(SW_SHOW);
	}

	return res.get_0_64();
}
uint64_t CgdtHelperDlg::getResDown()
{
	uint64_t res = 0;

	for (const auto &i : m_editBits)
	{
		char buf[8] = {};
		i.GetWindowText(buf, arrCnt(buf));
		res = (res << 1) | (w::strToUnsigned(buf) != 0 ? 1 : 0);
	}

	return res;
}
//uint64_t CgdtHelperDlg::getResUp() {}

uint64_t CgdtHelperDlg::setResLeft(uint64_t bit_0_64)
{
	uint64_t old = getResLeft();

	GDT_Entry gdt(bit_0_64);
	{
		ostringstream oss;
		oss <<hex <<setw(8) <<setfill('0') <<gdt.getAddr();
		m_editSegmentBase.SetWindowText(oss.str().c_str());
	}
	{
		ostringstream oss;
		oss <<hex <<setw(5) <<setfill('0') <<gdt.getLimit();
		m_editSegmentBound.SetWindowText(oss.str().c_str());
	}
	m_checkG.SetCheck(gdt.getG());
	m_checkDB.SetCheck(gdt.getDB());
	m_checkL.SetCheck(gdt.getL());
	m_checkAVL.SetCheck(gdt.getAVL());
	m_checkP.SetCheck(gdt.getP());
	for (auto i = 0; i < arrCnt(m_radioDPL); ++i)
	{
		m_radioDPL[i].SetCheck(i == gdt.getDPL() ? 1 : 0);
	}
	m_checkS.SetCheck(gdt.getS());
	for (auto i = 0; i < arrCnt(m_radioType); ++i)
	{
		m_radioType[i].SetCheck(i == gdt.getType() ? 1 : 0);
	}

	return old;
}
uint64_t CgdtHelperDlg::setResRight(uint64_t bit_0_64)
{
	uint64_t old = getResRight();

	GDT_Entry gdt(bit_0_64);
	{
		ostringstream oss;
		oss <<hex <<setw(8) <<setfill('0') <<gdt.get_32_64();
		m_editResHigh.SetWindowText(oss.str().c_str());
	}
	{
		ostringstream oss;
		oss <<hex <<setw(8) <<setfill('0') <<gdt.get_0_32();
		m_editResLow.SetWindowText(oss.str().c_str());
	}

	return old;
}
uint64_t CgdtHelperDlg::setResDown(uint64_t bit_0_64)
{
	GDT_Entry old = getResDown();

	for (uint64_t i = 0; i < arrCnt(m_editBits); ++i)
	{
		bool b = (bit_0_64 >> i++) & 1;
		m_editBits[i].SetWindowText(b ? "1" : "0");
	}

	return old.get_0_64();
}
//uint64_t CgdtHelperDlg::setResUp(uint64_t bit_0_64) {}

string CgdtHelperDlg::getTypeDesc(bool s, unsigned type) const
{
	string desc;

	if (s)
	{
		// System bit is set.
		switch (type)
		{
		case 0x00:
			desc = "data: r";
			break;
		case 0x02:
			desc = "data: rw";
			break;
		case 0x04:
			desc = "data: rd";
			break;
		case 0x06:
			desc = "data: rwd";
			break;
		case 0x08:
			desc = "code: e";
			break;
		case 0x0a:
			desc = "code: er";
			break;
		case 0x0c:
			desc = "code: ec";
			break;
		case 0x0e:
			desc = "code: erc";
			break;
		default:
			desc = "unknown";
			break;
		}
	}
	else
	{
		// Non system.
		switch (type)
		{
		case 0x0c:
			desc = "callGate";
			break;
		case 0x02:
			desc = "LDT";
			break;
		case 0x09:
			desc = "TSS: free";
			break;
		case 0x0b:
			desc = "TSS: busy";
			break;
		case 0x05:
			desc = "taskGate";
			break;
		default:
			desc = "unknown";
			break;
		}
	}

	return desc;
}
string CgdtHelperDlg::getTypeDesc() const
{
	string res;
	for (unsigned i = 0; i < arrCnt(m_radioType); ++i)
	{
		if (m_radioType[i].GetCheck() != 0)
		{
			res = getTypeDesc(m_checkS.GetCheck() != 0, i);
			break;
		}
	}

	return res;
}

void CgdtHelperDlg::OnBnClickedButtonCtor() { setResRight(getResLeft()); }

void CgdtHelperDlg::OnBnClickedButtonDtor() { setResLeft(getResRight()); }
