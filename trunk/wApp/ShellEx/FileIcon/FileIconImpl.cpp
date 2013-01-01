// FileIconImpl.cpp : Implementation of CFileIconImpl

#include "stdafx.h"
#include "FileIconImpl.h"
#include "dllmain.h"
using namespace std;

// CFileIconImpl
CFileIconImpl::CFileIconImpl()
	: m_fileFullpath(), 
	  m_green(nullptr), m_red(nullptr)
{

}
CFileIconImpl::~CFileIconImpl()
{}

// Interface.
// IPersistFile.
HRESULT CFileIconImpl::GetClassID(CLSID *pClassID){ return E_NOTIMPL; }
HRESULT CFileIconImpl::IsDirty(){ return E_NOTIMPL; }
HRESULT CFileIconImpl::Load(LPCOLESTR pszFileName, DWORD dwMode)
{
//	m_fileFullpath = pszFileName;
	MessageBox(nullptr, L"", L"Load()", MB_OK);
	return S_OK;
}
HRESULT CFileIconImpl::Save(LPCOLESTR pszFileName, BOOL fRemember){ return E_NOTIMPL; }
HRESULT CFileIconImpl::SaveCompleted(LPCOLESTR pszFileName){ return E_NOTIMPL; }
HRESULT CFileIconImpl::GetCurFile(LPOLESTR *ppszFileName){ return E_NOTIMPL; }

// IExtractIcon.
HRESULT CFileIconImpl::GetIconLocation(UINT uFlags, PWSTR pszIconFile, UINT cchMax, int *piIndex, UINT *pwFlags)
{
	//// Use 'Extract()' to draw icon.
	//*pwFlags = GIL_NOTFILENAME | GIL_DONTCACHE;		// Always draw icon.
	MessageBox(nullptr, L"", L"GetIconLocation()", MB_OK);
	return S_OK;
}
HRESULT CFileIconImpl::Extract(PCWSTR pszFile, UINT nIconIndex, HICON *phiconLarge, HICON *phiconSmall, UINT nIconSize)
{
	//wchar_t dllFullpath[MAX_PATH] = {};
	//GetModuleFileName(_AtlModule.GetModuleInstance(), dllFullpath, sizeof(dllFullpath)/sizeof(dllFullpath[0]));
	//PathRemoveFileSpec(dllFullpath);

	//wchar_t greenFullpath[MAX_PATH] = {}, redFullpath[MAX_PATH] = {};
	//PathAppend(greenFullpath, L"green.bmp"), PathAppend(redFullpath, L"red.bmp");

	//m_green = reinterpret_cast<HICON>(LoadImage(nullptr, greenFullpath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE)),
	//m_red = reinterpret_cast<HICON>(LoadImage(nullptr, redFullpath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE));

	//*phiconLarge = m_green;
	MessageBox(nullptr, L"", L"Extract()", MB_OK);
	return S_OK;
}