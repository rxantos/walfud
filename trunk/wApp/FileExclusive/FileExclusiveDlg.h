
// FileExclusiveDlg.h : header file
//

#pragma once
#include <map>
#include <string>

// CFileExclusiveDlg dialog
class CFileExclusiveDlg : public CDialogEx
{
	// data.
	std::map<std::wstring, HANDLE> m_filenameHandle;

public:
	// Interface.
	void GetArgsFromCmdLine();

private:
	// logic.
	void exclusiveFile(const std::wstring &fullpath);

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
	DECLARE_MESSAGE_MAP()
};
