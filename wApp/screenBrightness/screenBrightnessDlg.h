
// screenBrightnessDlg.h : header file
//

#pragma once
#include "afxcmn.h"


// CscreenBrightnessDlg dialog
class CscreenBrightnessDlg : public CDialogEx
{
	// data.
	DWORD m_originalBrightness;

// Construction
public:
	CscreenBrightnessDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SCREENBRIGHTNESS_DIALOG };

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
	CSliderCtrl m_slider_bright;
//	afx_msg void OnTRBNThumbPosChangingSliderBright(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
