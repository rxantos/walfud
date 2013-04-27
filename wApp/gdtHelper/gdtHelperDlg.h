
// gdtHelperDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "wGdtHelper.h"
#include <string>

// CgdtHelperDlg dialog
class CgdtHelperDlg : public CDialogEx
{
	static const unsigned msc_bitCnt = 64;

private:
	// data.
	GDT_Entry m_res;

// Construction
public:
	CgdtHelperDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_GDTHELPER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CButton m_checkG, m_checkDB, m_checkL, m_checkAVL, m_checkP, m_checkS;

	CEdit m_editSegmentBase;
	CEdit m_editSegmentBound;
	CStatic m_staticBaseWrong;
	CStatic m_staticBoundWrong;

	CButton m_radioDPL[4];
	CButton m_radioType[16];

	CEdit m_editBits[msc_bitCnt];

	CEdit m_editResHigh;
	CEdit m_editResLow;

	CStatic m_staticResHighPartWrong;
	CStatic m_staticResLowPartWrong;

	afx_msg void OnEnChangeEditSegmentBase();
	afx_msg void OnEnChangeEditSegmentBound();
	afx_msg void OnBnClickedCheckG();
	afx_msg void OnBnClickedCheckDb();
	afx_msg void OnBnClickedCheckL();
	afx_msg void OnBnClickedCheckAvl();
	afx_msg void OnBnClickedCheckP();
	afx_msg void OnBnClickedCheckS();

	afx_msg void OnBnClickedRadioDpl00();
	afx_msg void OnBnClickedRadioDpl01();
	afx_msg void OnBnClickedRadioDpl10();
	afx_msg void OnBnClickedRadioDpl11();

	afx_msg void OnBnClickedRadioType0000();
	afx_msg void OnBnClickedRadioType0001();
	afx_msg void OnBnClickedRadioType0010();
	afx_msg void OnBnClickedRadioType0011();
	afx_msg void OnBnClickedRadioType0100();
	afx_msg void OnBnClickedRadioType0101();
	afx_msg void OnBnClickedRadioType0110();
	afx_msg void OnBnClickedRadioType0111();
	afx_msg void OnBnClickedRadioType1000();
	afx_msg void OnBnClickedRadioType1001();
	afx_msg void OnBnClickedRadioType1010();
	afx_msg void OnBnClickedRadioType1011();
	afx_msg void OnBnClickedRadioType1100();
	afx_msg void OnBnClickedRadioType1101();
	afx_msg void OnBnClickedRadioType1110();
	afx_msg void OnBnClickedRadioType1111();

	//afx_msg void OnEnChangeEdit0();
	//afx_msg void OnEnChangeEdit1();
	//afx_msg void OnEnChangeEdit2();
	//afx_msg void OnEnChangeEdit3();
	//afx_msg void OnEnChangeEdit4();
	//afx_msg void OnEnChangeEdit5();
	//afx_msg void OnEnChangeEdit6();
	//afx_msg void OnEnChangeEdit7();
	//afx_msg void OnEnChangeEdit8();
	//afx_msg void OnEnChangeEdit9();
	//afx_msg void OnEnChangeEdit10();
	//afx_msg void OnEnChangeEdit11();
	//afx_msg void OnEnChangeEdit12();
	//afx_msg void OnEnChangeEdit13();
	//afx_msg void OnEnChangeEdit14();
	//afx_msg void OnEnChangeEdit15();
	//afx_msg void OnEnChangeEdit16();
	//afx_msg void OnEnChangeEdit17();
	//afx_msg void OnEnChangeEdit18();
	//afx_msg void OnEnChangeEdit19();
	//afx_msg void OnEnChangeEdit20();
	//afx_msg void OnEnChangeEdit21();
	//afx_msg void OnEnChangeEdit22();
	//afx_msg void OnEnChangeEdit23();
	//afx_msg void OnEnChangeEdit24();
	//afx_msg void OnEnChangeEdit25();
	//afx_msg void OnEnChangeEdit26();
	//afx_msg void OnEnChangeEdit27();
	//afx_msg void OnEnChangeEdit28();
	//afx_msg void OnEnChangeEdit29();
	//afx_msg void OnEnChangeEdit30();
	//afx_msg void OnEnChangeEdit31();
	//afx_msg void OnEnChangeEdit32();
	//afx_msg void OnEnChangeEdit33();
	//afx_msg void OnEnChangeEdit34();
	//afx_msg void OnEnChangeEdit35();
	//afx_msg void OnEnChangeEdit36();
	//afx_msg void OnEnChangeEdit37();
	//afx_msg void OnEnChangeEdit38();
	//afx_msg void OnEnChangeEdit39();
	//afx_msg void OnEnChangeEdit40();
	//afx_msg void OnEnChangeEdit41();
	//afx_msg void OnEnChangeEdit42();
	//afx_msg void OnEnChangeEdit43();
	//afx_msg void OnEnChangeEdit44();
	//afx_msg void OnEnChangeEdit45();
	//afx_msg void OnEnChangeEdit46();
	//afx_msg void OnEnChangeEdit47();
	//afx_msg void OnEnChangeEdit48();
	//afx_msg void OnEnChangeEdit49();
	//afx_msg void OnEnChangeEdit50();
	//afx_msg void OnEnChangeEdit51();
	//afx_msg void OnEnChangeEdit52();
	//afx_msg void OnEnChangeEdit53();
	//afx_msg void OnEnChangeEdit54();
	//afx_msg void OnEnChangeEdit55();
	//afx_msg void OnEnChangeEdit56();
	//afx_msg void OnEnChangeEdit57();
	//afx_msg void OnEnChangeEdit58();
	//afx_msg void OnEnChangeEdit59();
	//afx_msg void OnEnChangeEdit60();
	//afx_msg void OnEnChangeEdit61();
	//afx_msg void OnEnChangeEdit62();
	//afx_msg void OnEnChangeEdit63();

private:
	// logic.
	void getRes();

	uint64_t getResLeft();			// Get result based on left side.
	uint64_t getResRight();
	uint64_t getResDown();
	uint64_t getResUp();

	uint64_t setResLeft(uint64_t bit_0_64);			// Draw result to left based on 'm_res'.
	uint64_t setResRight(uint64_t bit_0_64);
	uint64_t setResDown(uint64_t bit_0_64);
	uint64_t setResUp(uint64_t bit_0_64);

	std::string getTypeDesc(bool s, unsigned type) const;	// "r" -> readable.
															// "w" -> writable.
															// "d" -> downward expansion.
															// "e" -> executable.
															// "c" -> compatible.
	std::string getTypeDesc() const;

public:
	afx_msg void OnBnClickedButtonCtor();
	afx_msg void OnBnClickedButtonDtor();
	CStatic m_staticTypeDesc;
};
