// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

class CMainDlg : public CDialogImpl<CMainDlg>,
				public CMessageFilter
{
public:
	enum { IDD = IDD_MAINDLG };

	BEGIN_MSG_MAP(CMainDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)

		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)

		NOTIFY_HANDLER(IDC_LIST_PROC, LVN_COLUMNCLICK, OnProcListHeadClick)
		NOTIFY_HANDLER(IDC_LIST_PROC, NM_DBLCLK, OnProcListItemClick)
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnKeyDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		DestroyWindow();
		::PostQuitMessage(wID);

		return 0;
	}

	//LRESULT OnBnClickedButtonCrashit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnProcListHeadClick(int /*idCtrl*/, LPNMHDR /*pNMHDR*/, BOOL& /*bHandled*/);
	LRESULT OnProcListItemClick(int /*idCtrl*/, LPNMHDR /*pNMHDR*/, BOOL& /*bHandled*/);

	virtual BOOL PreTranslateMessage(MSG* pMsg);

private:
	// logic.
	enum class Sort {
		Default = 0,

		ProcName_Asc,
		ProcName_Desc,

		Pid_Asc,
		Pid_Desc,
	};
	void drawWithSort();
	void drawProcList();

	void crashIt(int index);

	Sort m_sort;
	std::vector<w::ProcessInfo> m_procInfo;

	void crashByProcname();
	void crashByPid();
};
