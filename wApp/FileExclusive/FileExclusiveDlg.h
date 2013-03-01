
// FileExclusiveDlg.h : header file
//

#pragma once

#include <vector>
#include <map>
#include <string>

#pragma warning(disable: 4996)

struct TargetInfo
{
	std::string filename;
	HANDLE handle;

	TargetInfo() : filename(), handle(INVALID_HANDLE_VALUE) {}
	TargetInfo(const std::string &fn) : filename(fn), handle(INVALID_HANDLE_VALUE) {}
	TargetInfo(const std::string &fn, HANDLE h) : filename(fn), handle(h) {}
};
bool operator==(const TargetInfo &a, const TargetInfo &b);

class Status
{
public:
	// .
	enum class Key : unsigned
	{
		SUCCESS = ERROR_SUCCESS,
		FILE_NOT_FOUND = ERROR_FILE_NOT_FOUND,
		ACCESS_DENIED = ERROR_ACCESS_DENIED,
		SHARING_VIOLATION = ERROR_SHARING_VIOLATION,
		UNKNOWN = static_cast<unsigned>(-1),
	};

private:
	// data.
	Key m_curStatusKey;
	static std::map<Key, std::string> ms_idDescription;

public:
	Status();
	Status(unsigned id);
	Status &operator==(unsigned id);
	Status(Key key);
	Status &operator==(Key key);
public:
	// Interface.
	std::string toString() const;

private:
	void init();
};

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
	void exclusiveFile(const std::string &fullpath);
	void freeFile(const std::string &fullpath);

	Status tryExclusive(unsigned index);

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
