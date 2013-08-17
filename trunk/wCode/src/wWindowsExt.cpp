

// wWindowsExt.cpp
//

#include "wWindowsExt.h"
using namespace std;

namespace w
{

static HMODULE s_ntdll = LoadLibrary("ntdll.dll");
static HMODULE s_advapi32 = LoadLibrary("advapi32.dll");

decltype(FuncZwQuerySystemInformation) *ZwQuerySystemInformation = reinterpret_cast<decltype(FuncZwQuerySystemInformation) *>(GetProcAddress(s_ntdll, "ZwQuerySystemInformation"));
decltype(FuncZwQueryInformationFile) *ZwQueryInformationFile = reinterpret_cast<decltype(FuncZwQueryInformationFile) *>(GetProcAddress(s_ntdll, "ZwQueryInformationFile"));
decltype(FuncZwQueryObject) *ZwQueryObject = reinterpret_cast<decltype(FuncZwQueryObject) *>(GetProcAddress(s_ntdll, "ZwQueryObject"));

decltype(FuncI_QueryTagInformation) *I_QueryTagInformation = reinterpret_cast<decltype(I_QueryTagInformation)>(GetProcAddress(s_advapi32, "I_QueryTagInformation"));

decltype(FuncNtQueryInformationProcess) *NtQueryInformationProcess = reinterpret_cast<decltype(NtQueryInformationProcess)>(GetProcAddress(s_ntdll, "NtQueryInformationProcess"));
decltype(FuncNtWow64QueryInformationProcess64) *NtWow64QueryInformationProcess64 = reinterpret_cast<decltype(NtWow64QueryInformationProcess64)>(GetProcAddress(s_ntdll, "NtWow64QueryInformationProcess64"));
decltype(FuncNtQueryInformationThread) *NtQueryInformationThread = reinterpret_cast<decltype(NtQueryInformationThread)>(GetProcAddress(s_ntdll, "NtQueryInformationThread"));

decltype(FuncNtReadVirtualMemory) *NtReadVirtualMemory = reinterpret_cast<decltype(NtReadVirtualMemory)>(GetProcAddress(s_ntdll, "NtReadVirtualMemory"));
decltype(FuncNtWow64ReadVirtualMemory64) *NtWow64ReadVirtualMemory64 = reinterpret_cast<decltype(NtWow64ReadVirtualMemory64)>(GetProcAddress(s_ntdll, "NtWow64ReadVirtualMemory64"));

}