

// wSysUtil.h
//

#ifndef W_SYS_UTIL_H
#define W_SYS_UTIL_H

#include "wCppExt.h"

namespace w
{

/*
 *
 *		Execute a program and wait at most 'timeout' ms.
 *
 *	Param:
 *		'filepath': The executable.
 *		'param': The parameter pass to executable.
 *		'timeout': The maximum micro-second to wait the process finish.
 *
 *	Rtn:
 *		'true': Process has been created; otherwise is 'false'.
 *
 *	Note:
 *		The executable may NOT run correctly as you want, but the process has been created, thus, function
 *	will return true however.
 *
 */
bool runAndWait(const std::string &filepath, const std::string &param, DWORD timeout, bool show);

/*
 *
 *		Limit a single process in running.
 *
 *	Param:
 *		'unionName': The system global name for the process, which is used to identify a unique process.
 *
 *	Rtn:
 *		'true': If no same process is running, otherwise is 'false'.
 *
 */
bool singleProcess(const std::string &unionName);

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


}

#endif // W_SYS_UTIL_H