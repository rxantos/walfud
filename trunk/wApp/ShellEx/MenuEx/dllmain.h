// dllmain.h : Declaration of module class.

class CMenuExModule : public ATL::CAtlDllModuleT< CMenuExModule >
{
	// data.
	HINSTANCE m_instance;

public:
	CMenuExModule();
	~CMenuExModule();

	DECLARE_LIBID(LIBID_MenuExLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_MENUEX, "{E5F52F54-8A07-48F6-BC5A-9CB41ADABD33}")

	// Interface.
	// 2. Design interface to access module address.
	HINSTANCE GetModuleInstance() const;
	void SetModuleInstance(HINSTANCE instance);
};

extern class CMenuExModule _AtlModule;
