// DropOnTargetImpl.cpp : Implementation of CDropOnTargetImpl

#include "stdafx.h"
#include "DropOnTargetImpl.h"
using namespace std;

// CDropOnTargetImpl
CDropOnTargetImpl::CDropOnTargetImpl()
	: m_targetFullpath(), m_dropeesFullpath()
{}

// Interface.
// IPersistFile.
HRESULT CDropOnTargetImpl::GetClassID(CLSID *pClassID){ return E_NOTIMPL; }
HRESULT CDropOnTargetImpl::IsDirty(){ return E_NOTIMPL; }
HRESULT CDropOnTargetImpl::Load(LPCOLESTR pszFileName, DWORD dwMode)
{
	// Save target full path.
	m_targetFullpath = pszFileName;
	return S_OK;
}
HRESULT CDropOnTargetImpl::Save(LPCOLESTR pszFileName, BOOL fRemember){ return E_NOTIMPL; }
HRESULT CDropOnTargetImpl::SaveCompleted(LPCOLESTR pszFileName){ return E_NOTIMPL; }
HRESULT CDropOnTargetImpl::GetCurFile(LPOLESTR *ppszFileName){ return E_NOTIMPL; }

// IDropTarget.
HRESULT CDropOnTargetImpl::DragEnter(IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
{
	// Get all dragee items.
	FORMATETC etc = {CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL};
	STGMEDIUM stg = {TYMED_HGLOBAL};
	pDataObj->GetData(&etc, &stg);
	
	m_dropeesFullpath.clear();
	HDROP hDrop = reinterpret_cast<HDROP>(stg.hGlobal);
	for (unsigned i = 0; i < DragQueryFile(hDrop, 0xFFFFFFFF, NULL, 0); ++i)
	{
		wchar_t fileFullpath[MAX_PATH] = {};
		DragQueryFile(hDrop, i, fileFullpath, sizeof(fileFullpath)/sizeof(fileFullpath[0]));

		// Each selected item is here.
		m_dropeesFullpath.push_back(fileFullpath);
	}

	ReleaseStgMedium(&stg);
	return S_OK;
}
HRESULT CDropOnTargetImpl::DragOver( DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
{ return E_NOTIMPL; }
HRESULT CDropOnTargetImpl::DragLeave()
{ return S_OK; }
HRESULT CDropOnTargetImpl::Drop(IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
{
	for (vector<wstring>::const_iterator it = m_dropeesFullpath.begin(); it != m_dropeesFullpath.end(); ++it)
	{
		OutputDebugString((*it + L" => " + m_targetFullpath).c_str());
	}
	
	return S_OK;
}