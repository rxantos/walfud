// FileIconImpl.h : Declaration of the CFileIconImpl

#pragma once
#include "resource.h"       // main symbols



#include "FileIcon_i.h"
#include <Shlobj.h>
#include <string>


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CFileIconImpl

class ATL_NO_VTABLE CFileIconImpl :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CFileIconImpl, &CLSID_FileIconImpl>,
	public IDispatchImpl<IFileIconImpl, &IID_IFileIconImpl, &LIBID_FileIconLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IPersistFile,
	public IExtractIcon
{
	// data.
	std::wstring m_fileFullpath;

	HICON m_green, m_red;

public:
	CFileIconImpl();
	~CFileIconImpl();

DECLARE_REGISTRY_RESOURCEID(IDR_FILEICONIMPL)


BEGIN_COM_MAP(CFileIconImpl)
	COM_INTERFACE_ENTRY(IFileIconImpl)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IPersistFile)
	COM_INTERFACE_ENTRY(IExtractIcon)
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
	// IPersistFile.
	STDMETHOD(GetClassID)(CLSID *pClassID);
	STDMETHOD(IsDirty)();
	STDMETHOD(Load)(LPCOLESTR pszFileName, DWORD dwMode);
	STDMETHOD(Save)(LPCOLESTR pszFileName, BOOL fRemember);
	STDMETHOD(SaveCompleted)(LPCOLESTR pszFileName);
	STDMETHOD(GetCurFile)(LPOLESTR *ppszFileName);

	// IExtractIcon.
    STDMETHOD(GetIconLocation)(UINT uFlags, PWSTR pszIconFile, UINT cchMax, int *piIndex, UINT *pwFlags);
    STDMETHOD(Extract)(PCWSTR pszFile, UINT nIconIndex, HICON *phiconLarge, HICON *phiconSmall, UINT nIconSize);
};

OBJECT_ENTRY_AUTO(__uuidof(FileIconImpl), CFileIconImpl)
