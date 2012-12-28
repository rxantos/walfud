// MenuExImpl.h : Declaration of the CMenuExImpl

#pragma once
#include "resource.h"       // main symbols

#include "MenuEx_i.h"
#include <shlobj.h>


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif



// CMenuExImpl

class ATL_NO_VTABLE CMenuExImpl :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMenuExImpl, &CLSID_MenuExImpl>,
	public IDispatchImpl<IMenuExImpl, &IID_IMenuExImpl, &LIBID_MenuExLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IShellExtInit,
	public IContextMenu
{
	// data.
	HBITMAP m_bitmap;

public:
	CMenuExImpl();
	~CMenuExImpl();

DECLARE_REGISTRY_RESOURCEID(IDR_MENUEXIMPL)


BEGIN_COM_MAP(CMenuExImpl)
	COM_INTERFACE_ENTRY(IMenuExImpl)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IShellExtInit)
	COM_INTERFACE_ENTRY(IContextMenu)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:
	// Interface.
	// IShellExtInit.
	STDMETHOD(Initialize)(PCIDLIST_ABSOLUTE pidlFolder, IDataObject *pdtobj, HKEY hkeyProgID);

    // IContextMenu.
    STDMETHOD(QueryContextMenu)(HMENU hmenu, UINT indexMenu, UINT idCmdFirst, UINT idCmdLast, UINT uFlags);
    STDMETHOD(InvokeCommand)(CMINVOKECOMMANDINFO *pici);
    STDMETHOD(GetCommandString)(UINT_PTR idCmd, UINT uType, UINT *pReserved, LPSTR pszName, UINT cchMax);
};

OBJECT_ENTRY_AUTO(__uuidof(MenuExImpl), CMenuExImpl)
