
// HandleUnlockDlg.h : header file
//

#pragma once
#include <vector>
#include <string>
#include "afxcmn.h"

// CHandleUnlockDlg dialog
class CHandleUnlockDlg : public CDialogEx
{
	// data.
	std::vector<std::string> m_filesFullpath;

// Construction
public:
	CHandleUnlockDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_HANDLEUNLOCK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	DECLARE_MESSAGE_MAP()

private:
	// logic.
public:
	CListCtrl m_list;
};
