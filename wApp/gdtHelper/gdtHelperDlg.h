
// gdtHelperDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CgdtHelperDlg dialog
class CgdtHelperDlg : public CDialogEx
{
	static const unsigned msc_bitCnt = 64;
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
	CEdit m_editSegmentBase;
	CEdit m_editSegmentBound;
	CButton m_checkG, m_checkDB, m_checkL, m_checkAVL, m_checkP, m_checkS;

	CButton m_radioDPL_00, m_radioDPL_01, m_radioDPL_10, m_radioDPL_11;
	CButton m_radioType_0000, m_radioType_0010, m_radioType_0100, m_radioType_0110,		// Data segment.
			m_radioType_1000, m_radioType_1010, m_radioType_1100, m_radioType_1110;		// Code segment.

	CEdit m_editBits[msc_bitCnt];
	afx_msg void OnEnChangeEditSegmentBase();
	afx_msg void OnEnChangeEditSegmentBound();
	afx_msg void OnBnClickedCheckG();
	afx_msg void OnBnClickedCheckDb();
	afx_msg void OnBnClickedCheckL();
	afx_msg void OnBnClickedCheckAvl();
	afx_msg void OnBnClickedCheckP();
	afx_msg void OnBnClickedCheckS();
};
