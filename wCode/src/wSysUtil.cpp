

// wSysUtil.cc
//

#include "wSysUtil.h"
#include <Tlhelp32.h>
using namespace std;

namespace w
{

static bool osVerCondition(size_t majorVer, size_t minorVer, int condition)
{
    // Initialize.
    OSVERSIONINFOEX osVerInfo = {};
    osVerInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
    osVerInfo.dwMajorVersion = static_cast<DWORD>(majorVer);
    osVerInfo.dwMinorVersion = static_cast<DWORD>(minorVer);

    // Set condition.
    DWORDLONG conditionMask = 0;
    VER_SET_CONDITION(conditionMask, VER_MAJORVERSION, static_cast<BYTE>(condition));
    VER_SET_CONDITION(conditionMask, VER_MINORVERSION, static_cast<BYTE>(condition));

    // Verify.
    return VerifyVersionInfo(&osVerInfo, 
                             VER_MAJORVERSION | VER_MINORVERSION , 
                             conditionMask);
}
bool isWin8OrLater()
{ return osVerCondition(6, 2, VER_GREATER_EQUAL); }
bool isWin7OrLater()
{ return osVerCondition(6, 1, VER_GREATER_EQUAL); }
bool isVistaOrLater()
{ return osVerCondition(6, 0, VER_GREATER_EQUAL); }
bool isXpOrLater()
{ return osVerCondition(5, 1, VER_GREATER_EQUAL); }
bool is2000OrLater()
{ return osVerCondition(5, 0, VER_GREATER_EQUAL); }

bool isOs64()
{
    typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS)(HANDLE, PBOOL);

	BOOL isWow64 = FALSE; 
    auto fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(GetModuleHandle("kernel32"), "IsWow64Process"); 
    if (NULL != fnIsWow64Process) 
    { 
        fnIsWow64Process(GetCurrentProcess(),&isWow64);
    } 

    return isWow64; 
}

bool setPrivilege(HANDLE hToken, const string &strPrivilege, bool bEnablePrivilege)
{
	bool res = false;

	TOKEN_PRIVILEGES tp = {};
	LUID luid = {};
    if (LookupPrivilegeValue( 
			nullptr,		// lookup privilege on local system
            strPrivilege.c_str(),	// privilege to lookup 
            &luid))			// receives LUID of privilege
    {
		tp.PrivilegeCount = 1;
		tp.Privileges[0].Luid = luid;
		tp.Privileges[0].Attributes = bEnablePrivilege ? SE_PRIVILEGE_ENABLED : SE_PRIVILEGE_REMOVED;

		// Enable the privilege or disable all privileges.
		if (AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), (PTOKEN_PRIVILEGES)nullptr, (PDWORD)nullptr))
		{ 
			  res = TRUE;
		} 
    }

	return res;
}
bool setCurTokenPrivilege(const string &strPrivilege, bool bEnablePrivilege)
{
	bool res = false;

	HANDLE hToken = NULL;
	if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken))
	{
		res = setPrivilege(hToken, strPrivilege, bEnablePrivilege);

		CloseHandle(hToken);
	}

	return res;
}

bool copyStringToClipboard(const string &str)
{
	bool res = false;

	HGLOBAL hClipboard = nullptr;
	if (OpenClipboard(nullptr))
	{
		EmptyClipboard();

		hClipboard = GlobalAlloc(GMEM_MOVEABLE, str.length() + 1);
		auto p = (char *)GlobalLock(hClipboard);
		strcpy(p, str.c_str());
		GlobalUnlock(hClipboard);

		SetClipboardData(CF_TEXT, hClipboard);

		CloseClipboard();

		res = true;
	}

	return res;
}
string copyStringFromClipboard()
{
	string res;

	if (OpenClipboard(nullptr))
	{
		HANDLE hClipboard = GetClipboardData(CF_TEXT);
		auto p = (char *)GlobalLock(hClipboard);
		res = p;
		GlobalUnlock(hClipboard);

		CloseClipboard();
	}

	return res;
}

string expandEvnString(const string &str)
{
	string res;

	auto needLen = ExpandEnvironmentStrings(str.c_str(), nullptr, 0);
	if (needLen > 0)
	{
		unique_ptr<char> p(new char[needLen + 1]);
		ExpandEnvironmentStrings(str.c_str(), p.get(), needLen + 1);

		res = p.get();
	}

	return res;
}

}