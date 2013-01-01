// DropOnTargetImpl.h : Declaration of the CDropOnTargetImpl

#pragma once
#include "resource.h"       // main symbols



#include "DropOnTarget_i.h"
#include <string>
#include <vector>


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CDropOnTargetImpl

class ATL_NO_VTABLE CDropOnTargetImpl :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CDropOnTargetImpl, &CLSID_DropOnTargetImpl>,
	public IDispatchImpl<IDropOnTargetImpl, &IID_IDropOnTargetImpl, &LIBID_DropOnTargetLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IPersistFile,
	public IDropTarget
{
	// data.
	std::wstring m_targetFullpath;
	std::vector<std::wstring> m_dropeesFullpath;

public:
	CDropOnTargetImpl();

DECLARE_REGISTRY_RESOURCEID(IDR_DROPONTARGETIMPL)


BEGIN_COM_MAP(CDropOnTargetImpl)
	COM_INTERFACE_ENTRY(IDropOnTargetImpl)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IPersistFile)
	COM_INTERFACE_ENTRY(IDropTarget)
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
	// IPersistFile.
	STDMETHOD(GetClassID)(CLSID *pClassID);
	STDMETHOD(IsDirty)();
	STDMETHOD(Load)(LPCOLESTR pszFileName, DWORD dwMode);
	STDMETHOD(Save)(LPCOLESTR pszFileName, BOOL fRemember);
	STDMETHOD(SaveCompleted)(LPCOLESTR pszFileName);
	STDMETHOD(GetCurFile)(LPOLESTR *ppszFileName);

	// IDropTarget.
	STDMETHOD(DragEnter)(IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect);
	STDMETHOD(DragOver)( DWORD grfKeyState, POINTL pt, DWORD *pdwEffect);
	STDMETHOD(DragLeave)();
	STDMETHOD(Drop)(IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect);
};

OBJECT_ENTRY_AUTO(__uuidof(DropOnTargetImpl), CDropOnTargetImpl)
