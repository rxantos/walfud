
// sysLockDlg.h : header file
//

#pragma once

#include "wAntiSysLock.h"
#include "afxwin.h"
#include "../animation/animation/animation.h"

// CsysLockDlg dialog
class CsysLockDlg : public CDialogEx
{
	// data.
	w::AntiSysLock m_antiLocker;
	MyAnimation2 m_maLH, m_maLT,
				 m_maRH, m_maRT;

// Construction
public:
	CsysLockDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SYSLOCK_DIALOG };

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
	afx_msg void OnBnClickedButtonActScrSaver();
	afx_msg void OnBnClickedButtonLock();
	afx_msg void OnBnClickedButtonAntiLock();
	afx_msg void OnBnClickedButtonDefaultLock();
};
