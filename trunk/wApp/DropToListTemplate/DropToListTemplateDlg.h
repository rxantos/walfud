
// DropToListTemplateDlg.h : header file
//

#pragma once
#include "afxcmn.h"


// CDropToListTemplateDlg dialog
class CDropToListTemplateDlg : public CDialogEx
{
// Construction
public:
	CDropToListTemplateDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_DROPTOLISTTEMPLATE_DIALOG };

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
public:
	CListCtrl m_list;
};
