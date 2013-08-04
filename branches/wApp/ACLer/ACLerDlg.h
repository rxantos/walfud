
// ACLerDlg.h : header file
//

#pragma once
#include "afxcmn.h"

#include <string>
#include <vector>
#include <map>
#include <unordered_set>
#include <unordered_map>

// CDropToListTemplateDlg dialog
class CDropToListTemplateDlg : public CDialogEx
{
	enum class Res : int
	{
		UNKNOWN = 0,
		GRANT,
		STRIP,
	};

	// data.
	std::unordered_map<std::string, Res> m_res;
	static const int sc_colIndex_targetFullpath,
					 sc_colIndex_permission;
	static const char *sc_colTitle_targetFullpath,
					  *sc_colTitle_permission;
	static const int sc_colWidth_targetFullpath,
					 sc_colWidth_permission;

private:
	// logic.
	void grantAll();
	void stripAll();
	Res handleOne(const std::string &target, bool grant);
	void updateList();

// Construction
public:
	CDropToListTemplateDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_ACLer_DIALOG };

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
	afx_msg void OnBnClickedButtonGrant();
	afx_msg void OnBnClickedButtonStrip();
};
