// dllmain.h : Declaration of module class.

class CDropOnTargetModule : public ATL::CAtlDllModuleT< CDropOnTargetModule >
{
public :
	DECLARE_LIBID(LIBID_DropOnTargetLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_DROPONTARGET, "{E2AD5750-9F52-4CD0-BA30-2C1F867C8878}")
};

extern class CDropOnTargetModule _AtlModule;
