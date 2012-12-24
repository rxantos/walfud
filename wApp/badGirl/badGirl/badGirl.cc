// dllmain.cpp : Defines the entry point for the DLL application.

#include <windows.h>
#include <process.h>
#include <Shellapi.h>
#include <string>
#include "wCppExt.h"
using namespace std;

HANDLE WINAPI myCreateFileA(
  const char * lpFileName,
  DWORD dwDesiredAccess,
  DWORD dwShareMode,
  LPSECURITY_ATTRIBUTES lpSecurityAttributes,
  DWORD dwCreationDisposition,
  DWORD dwFlagsAndAttributes,
  HANDLE hTemplateFile
)
{
	OutputDebugString("CreateFileA() has been intercept.");

	return nullptr;
}
HANDLE WINAPI myCreateFileW(
  const wchar_t * lpFileName,
  DWORD dwDesiredAccess,
  DWORD dwShareMode,
  LPSECURITY_ATTRIBUTES lpSecurityAttributes,
  DWORD dwCreationDisposition,
  DWORD dwFlagsAndAttributes,
  HANDLE hTemplateFile
  )
{
	OutputDebugString("CreateFileW() has been intercept.");

	return nullptr;
}

bool badGirl()
{
	void *originalCreateFileA = CreateFileA, *originalCreateFileW = CreateFileW;

	map<string, w::ModuleInfo> modulesInfo = w::getModulesInfo(w::getCurrentProcessId());
	for (map<string, w::ModuleInfo>::const_iterator it = modulesInfo.begin(); it != modulesInfo.end(); ++it)
	{
		w::interceptFunc(it->first, originalCreateFileA, myCreateFileA) && w::interceptFunc(it->first, originalCreateFileW, myCreateFileW);
	}

	return true;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		badGirl();
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}

	return TRUE;
}