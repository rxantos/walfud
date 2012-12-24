

// wSysUtil.cc
//

#include "wSysUtil.h"
#include <Tlhelp32.h>
using namespace std;

namespace w
{

bool runAndWait(const string &file, const string &param, DWORD timeout, bool show)
{
	// Set environment.
	SHELLEXECUTEINFO sei = {};
	sei.cbSize = sizeof(sei);
	sei.lpVerb = "open";
	sei.lpFile = file.c_str();
	sei.lpParameters = param.c_str();
	sei.nShow = show ? SW_SHOWNORMAL : SW_HIDE;
	sei.fMask = SEE_MASK_NOCLOSEPROCESS;

	// Run.
	ShellExecuteEx(&sei);

	// Wait until finish or timeout.
	WaitForSingleObject(sei.hProcess, timeout);
	CloseHandle(sei.hProcess);

	return reinterpret_cast<int>(sei.hInstApp) >= 32;
}

bool singleProcess(const string &unionName)
{
	HANDLE single = CreateMutex(nullptr, FALSE, unionName.c_str());
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		CloseHandle(single);
		return false;
	}

	return true;
}

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


}