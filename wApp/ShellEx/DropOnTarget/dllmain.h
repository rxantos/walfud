// dllmain.h : Declaration of module class.

class CDropOnTargetModule : public CAtlDllModuleT< CDropOnTargetModule >
{
public :
	DECLARE_LIBID(LIBID_DropOnTargetLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_DROPONTARGET, "{7ACE8E01-DDEE-49EE-8B50-E22F904E9C54}")
};

extern class CDropOnTargetModule _AtlModule;
