

// wWindowsExt.cpp
//

#include "wWindowsExt.h"
using namespace std;

namespace w
{

static HMODULE s_ntdll = LoadLibrary("ntdll.dll");
decltype(FuncZwQuerySystemInformation) *ZwQuerySystemInformation = reinterpret_cast<decltype(FuncZwQuerySystemInformation) *>(GetProcAddress(s_ntdll, "ZwQuerySystemInformation"));
decltype(FuncZwQueryInformationFile) *ZwQueryInformationFile = reinterpret_cast<decltype(FuncZwQueryInformationFile) *>(GetProcAddress(s_ntdll, "ZwQueryInformationFile"));
decltype(FuncZwQueryObject) *ZwQueryObject = reinterpret_cast<decltype(FuncZwQueryObject) *>(GetProcAddress(s_ntdll, "ZwQueryObject"));

}