
// HandleUnlockDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <tuple>
#include "afxwin.h"

// CHandleUnlockDlg dialog
class CHandleUnlockDlg : public CDialogEx
{
	struct HandleRefInfo
	{
		static const int sc_invalidId = 0;

		int processId;
		void *val;

		HandleRefInfo() : processId(sc_invalidId), val(static_cast<void *>(INVALID_HANDLE_VALUE)) {}
		HandleRefInfo(int pi, void *v) : processId(pi), val(v) {}
	};

	// data.
	std::vector<std::tuple<int, void *, std::string>> m_handleState;
	std::unordered_multimap<std::string, HandleRefInfo> m_handleRefInfo;

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
	void query();
	void updateList();

public:
	CListCtrl m_list;
	afx_msg void OnBnClickedButtonCloseHandle();
	CButton m_checkRefreshPerQuery;
	afx_msg void OnBnClickedButtonQuery();
};
