
// DropToListTemplateDlg.h : header file
//

#pragma once
#include "afxcmn.h"

#include <string>
#include <vector>
#include <map>
#include <unordered_set>
#include <unordered_map>

class Status
{
public:
	enum class ErrId : int
	{
		success = ERROR_SUCCESS,
		fileNotFound = ERROR_FILE_NOT_FOUND,
		unknownFail = INT_MAX,
	};
private:
	// data.
	ErrId m_id;
	static std::map<ErrId, std::string> ms_idStr;

public:
	Status();
	Status &operator=(const Status &other);
	Status(ErrId errId);
public:
	// Interface.
	ErrId toId() const;
	std::string toStr() const;

private:
	// logic.
	void init();
};

class Res
{
	// data.
	//int m_size;	// TODO: 
	Status m_status;

public:
	Res();
	Res &operator=(const Res &other);
	//Res(int size, Status status);	// TODO: 
public:
	// Interface.
	std::string toStr() const;
};

// CDropToListTemplateDlg dialog
class CDropToListTemplateDlg : public CDialogEx
{
	// data.
	std::unordered_map<std::string, Res> m_res;
	static const int sc_colIndex_targetFullpath;
					 //sc_colIndex_targetSize;	// TODO: 
	static const char *sc_colTitle_targetFullpath;
					  //*sc_colTitle_targetSize;	// TODO: 
	static const int sc_colWidth_targetFullpath;
					 //sc_colWidth_targetSize;	// TODO: 

private:
	// logic.
	void handleAll();
	Res handleOne(const std::string &target);
	void updateList();

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
	afx_msg void OnBnClickedButtonHandle();
};
