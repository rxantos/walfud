
// animationDlg.h : header file
//

#pragma once

#include "animation/animation.h"
#include <mutex>

// CanimationDlg dialog
class CanimationDlg : public CDialogEx
{
	MyAnimation2 m_maH, m_maT,
				 m_maLH, m_maLT;			// Left animation.
	std::once_flag m_distance;

// Construction
public:
	CanimationDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_ANIMATION_DIALOG };

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
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonPause();
	afx_msg void OnBnClickedButtonStop();
};
