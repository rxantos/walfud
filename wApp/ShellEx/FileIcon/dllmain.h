// dllmain.h : Declaration of module class.

class CFileIconModule : public ATL::CAtlDllModuleT< CFileIconModule >
{
	// data.
	HINSTANCE m_instance;

public :
	CFileIconModule();
	~CFileIconModule();

	DECLARE_LIBID(LIBID_FileIconLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_FILEICON, "{669723B1-4390-4DCC-9C8E-5CECFBC1AA01}")

	// Interface.
	HINSTANCE GetModuleInstance() const;
	void SetModuleInstance(HINSTANCE instance);
};

extern class CFileIconModule _AtlModule;
