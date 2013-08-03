

// wFilePermission.cc
//

#include "wFilePermission.h"
#include <Aclapi.h>
using namespace std;

namespace w
{

//unsigned long getPermission(const string &target, const string &usr)
//{
//
//}
bool setPermission(const string &target, const string &usr,
				   unsigned long permission, bool reset, bool recursive)
{
	bool res = false;

	// Open file.
	HANDLE file = CreateFile(target.c_str(),
							 STANDARD_RIGHTS_WRITE | WRITE_DAC,
							 FILE_SHARE_READ | FILE_SHARE_WRITE,
							 nullptr,
							 OPEN_EXISTING,
							 FILE_FLAG_BACKUP_SEMANTICS,				// This flag must be set.
							 nullptr);
	if (file != INVALID_HANDLE_VALUE)
	{
		// Get old acl.
		PSECURITY_DESCRIPTOR pSd = nullptr;
		PACL pOldDacl = nullptr, pNewDacl = nullptr;
		GetSecurityInfo(file, SE_FILE_OBJECT, DACL_SECURITY_INFORMATION, nullptr, nullptr, &pOldDacl, nullptr, &pSd);

		// Construct new acl.
		EXPLICIT_ACCESS ea = {};
		ea.grfAccessMode = SET_ACCESS;
		ea.grfAccessPermissions = permission;
		ea.grfInheritance = recursive ? SUB_CONTAINERS_AND_OBJECTS_INHERIT : NO_INHERITANCE;
		ea.Trustee.TrusteeForm = TRUSTEE_IS_NAME;
		ea.Trustee.TrusteeType = TRUSTEE_IS_USER;
		ea.Trustee.ptstrName = const_cast<char *>(usr.c_str());
		if (SetEntriesInAcl(1, &ea, reset ? nullptr : pOldDacl, &pNewDacl) == ERROR_SUCCESS)
		{
			// Bind new acl to target.
			res = SetSecurityInfo(file, 
								  SE_FILE_OBJECT, 
								  DACL_SECURITY_INFORMATION, 
								  nullptr, nullptr, 
								  pNewDacl, nullptr) == ERROR_SUCCESS;

			LocalFree(pNewDacl);
		}
	
		LocalFree(pSd);
		CloseHandle(file);
	}

	return res;
}

}