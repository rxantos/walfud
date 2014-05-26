

// wSysUtil.h
//

#ifndef W_SYS_UTIL_H
#define W_SYS_UTIL_H

#include "wCppExt.h"

namespace w
{

//Windows 8					6.2
//Windows 7					6.1
//Windows Server 2008 R2	6.1
//Windows Server 2008		6.0
//Windows Vista				6.0
//Windows Server 2003 R2	5.2
//Windows Server 2003		5.2
//Windows XP 64-Bit Edition	5.2
//Windows XP				5.1
//Windows 2000				5.0
//bool osVerCondition(size_t majorVer, size_t minorVer, int condition);
bool isWin8OrLater();
bool isWin7OrLater();
bool isVistaOrLater();
bool isXpOrLater();
bool is2000OrLater();

bool isOs64();

/**
 *		Enable or Disable privilege at target token.
 */
bool setPrivilege(
	HANDLE hToken,          // access token handle
    const std::string &strPrivilege,  // name of privilege to enable/disable
    bool bEnablePrivilege   // to enable or disable privilege
    );
bool setCurTokenPrivilege(const std::string &strPrivilege, bool bEnablePrivilege);

}

#endif // W_SYS_UTIL_H