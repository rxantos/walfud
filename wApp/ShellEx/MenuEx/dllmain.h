// dllmain.h : Declaration of module class.

class CMenuExModule : public CAtlDllModuleT< CMenuExModule >
{
	// data.
	HINSTANCE m_instance;

public:
	CMenuExModule();
	~CMenuExModule();

	DECLARE_LIBID(LIBID_MenuExLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_MENUEX, "{662E2ADD-0629-4E72-967F-B399022363B2}")

	// Interface.
	// 2. Design interface to access module address.
	HINSTANCE GetModuleInstance() const;
	void SetModuleInstance(HINSTANCE instance);
};

extern class CMenuExModule _AtlModule;
