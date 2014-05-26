// crasher.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
using namespace std;
using namespace w;


/**
 *
 *		crasher.exe   -pid:1024   crashee.dll
 *
 */
int _tmain(int argc, _TCHAR* argv[])
{
	auto pid = strToInt(argv[1] + 5);		// Ugly but ok.
	auto dll = argv[2];

	char curDir[MAX_PATH] = {};
	GetModuleFileName(nullptr, curDir, _countof(curDir));
	PathRemoveFileSpec(curDir);
	PathAppend(curDir, dll);

	int rtn = remoteCall(pid, (unsigned long (__stdcall *)(void *))LoadLibrary, (void *)curDir, sizeof(curDir), true)
				? 0 : -1;
	//remoteCall(pid, nullptr, nullptr, 0, false);

	return rtn;
}