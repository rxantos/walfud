
// FileExclusiveDlg.h : header file
//

#pragma once

#include <vector>
#include <string>

#pragma warning(disable: 4996)

struct TargetInfo
{
	std::wstring filename;
	HANDLE handle;

	TargetInfo() : filename(), handle(INVALID_HANDLE_VALUE) {}
	TargetInfo(const std::wstring &fn) : filename(fn), handle(INVALID_HANDLE_VALUE) {}
	TargetInfo(const std::wstring &fn, HANDLE h) : filename(fn), handle(h) {}
};
inline bool operator==(const TargetInfo &a, const TargetInfo &b) { return _wcsicmp(a.filename.c_str(), b.filename.c_str()) == 0; }

// CFileExclusiveDlg dialog
class CFileExclusiveDlg : public CDialogEx
{
	// data.
	std::vector<TargetInfo> m_targetsInfo;

public:
	// Interface.
	void getArgsFromCmdLine();
	void checkHandle();

private:
	// logic.
	void exclusiveFile(const std::wstring &fullpath);
	void freeFile(const std::wstring &fullpath);
	void refreshFile(const std::wstring &fullpath);

	bool lockedByMe(const std::wstring &fullpath);

// Construction
public:
	CFileExclusiveDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_FILEEXCLUSIVE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CListCtrl m_listFile;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonRefresh();
};
