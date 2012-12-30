// MenuExImpl.cpp : Implementation of CMenuExImpl

#include "stdafx.h"
#include "MenuExImpl.h"
#include "dllMain.h"

// CMenuExImpl
CMenuExImpl::CMenuExImpl()
	: m_bitmap(nullptr)
{
	// 2. Initialize bitmap resource. (16 * 16 for vista or above)
	// Get picture fullpath.(Same directory with dll file)
	wchar_t iconFullpath[MAX_PATH] = {};
	GetModuleFileName(_AtlModule.GetModuleInstance(), iconFullpath, sizeof(iconFullpath)/sizeof(iconFullpath[0]));
	PathRemoveFileSpec(iconFullpath);
	PathAppend(iconFullpath, L"icon.bmp");
	OutputDebugString(iconFullpath);

	// 2. Load image from file.
	m_bitmap = reinterpret_cast<HBITMAP>(LoadImage(nullptr, iconFullpath, IMAGE_BITMAP, 16, 16, LR_LOADFROMFILE));
	// 2. Load image from inner source.
	//m_bitmap = reinterpret_cast<HBITMAP>(LoadBitmap(_AtlModule.GetModuleInstance(), MAKEINTRESOURCE(IDB_BITMAP_ICON)));
}
CMenuExImpl::~CMenuExImpl()
{
	// 2. Release image resource.
	DeleteObject(m_bitmap);
}

// IShellExtInit.
HRESULT CMenuExImpl::Initialize(PCIDLIST_ABSOLUTE pidlFolder, IDataObject *pdtobj, HKEY hkeyProgID)
{
	// Get all selected item.
	FORMATETC etc = {CF_HDROP, nullptr, DVASPECT_CONTENT, -1, TYMED_HGLOBAL};
	STGMEDIUM stg = {TYMED_HGLOBAL};
	pdtobj->GetData(&etc, &stg);
	
	HDROP hDrop = reinterpret_cast<HDROP>(stg.hGlobal);
	for (unsigned i = 0; i < DragQueryFile(hDrop, -1, nullptr, 0); ++i)
	{
		wchar_t protecteeFullpath[MAX_PATH] = {};
		DragQueryFile(hDrop, i, protecteeFullpath, sizeof(protecteeFullpath)/sizeof(protecteeFullpath[0]));

		// Each selected item is here.
		// Save them for future use.
	}

	ReleaseStgMedium(&stg);
	return S_OK;
}

// IContextMenu.
HRESULT CMenuExImpl::QueryContextMenu(HMENU hmenu, UINT indexMenu, UINT idCmdFirst, UINT idCmdLast, UINT uFlags)
{
	int i = 0;

	//// 1. Different style.
	//InsertMenu(hmenu, indexMenu + i, MF_BYPOSITION, idCmdFirst + i, L"-");
	//++i;
	//InsertMenu(hmenu, indexMenu + i, MF_BYPOSITION | MF_SEPARATOR, idCmdFirst + i, L"MF_SEPARATOR");
	//++i;
	//InsertMenu(hmenu, indexMenu + i, MF_BYPOSITION | MF_CHECKED, idCmdFirst + i, L"MF_CHECKED");
	//++i;
	//InsertMenu(hmenu, indexMenu + i, MF_BYPOSITION | MF_UNCHECKED, idCmdFirst + i, L"MF_UNCHECKED");
	//++i;
	//InsertMenu(hmenu, indexMenu + i, MF_BYPOSITION | MF_HILITE, idCmdFirst + i, L"MF_HILITE");
	//++i;
	//InsertMenu(hmenu, indexMenu + i, MF_BYPOSITION | MF_UNHILITE, idCmdFirst + i, L"MF_UNHILITE");
	//++i;
	//InsertMenu(hmenu, indexMenu + i, MF_BYPOSITION | MF_MENUBREAK, idCmdFirst + i, L"MF_MENUBREAK");
	//++i;

	// 2. Item with icon.	
	InsertMenu(hmenu, indexMenu + i, MF_BYPOSITION, idCmdFirst + i, L"With icon.");
	SetMenuItemBitmaps(hmenu, indexMenu + i, MF_BYPOSITION, m_bitmap, nullptr);
	++i;

	return MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_NULL, i);
}

HRESULT CMenuExImpl::InvokeCommand(CMINVOKECOMMANDINFO *pici)
{
	MessageBox(nullptr, L"", L"", MB_OK);
	return S_OK;
}

HRESULT CMenuExImpl::GetCommandString(UINT_PTR idCmd, UINT uType, UINT *pReserved, LPSTR pszName, UINT cchMax)
{ return E_NOTIMPL; }