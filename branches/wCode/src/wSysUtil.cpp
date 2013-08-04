

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

}