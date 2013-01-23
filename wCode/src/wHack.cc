

// wHack.cc
//

#include "wHack.h"
#include <Dbghelp.h>
using namespace std;

#pragma comment(lib, "Dbghelp.lib")

namespace w
{

bool remoteCall(unsigned targetProcessId, unsigned long (__stdcall *func)(void *), void *param, unsigned paramSize, bool paramIsPtr)
{
	// Open remote process.
	HANDLE hRemoteProcess = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE, 
										FALSE, 
										targetProcessId);

	void *remoteParam = nullptr;
	if (paramIsPtr)
	{
		// Parameter is a remote address.
		// Allocate memory and set to zero at remote process.
		if (void *remoteMemory 
			= VirtualAllocEx(hRemoteProcess,									// 'PROCESS_VM_OPERATION'.
							 nullptr, paramSize, 
							 MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE))
		{
			// Remote write.
			DWORD written = 0;
			if (WriteProcessMemory(hRemoteProcess,								// 'PROCESS_VM_OPERATION | PROCESS_VM_WRITE'.
								   remoteMemory, 
								   param, paramSize, 
								   &written))
			{
				remoteParam = remoteMemory;
			}
		}//if (void *
	}
	else
	{
		// Parameter is a value.
		remoteParam = param;
	}//if (paramIsPtr

	// Remote call.
	HANDLE remoteThread = CreateRemoteThread(hRemoteProcess, nullptr, 
											 0, func, remoteParam, 
											 0, nullptr);

	CloseHandle(remoteThread);
	CloseHandle(hRemoteProcess);
	return remoteThread != nullptr;
}
bool remoteCall(const string &targetProcessName, unsigned long (__stdcall *func)(void *), void *param, unsigned paramSize, bool paramIsPtr)
{ return remoteCall(w::getProcessId(targetProcessName)[0], func, param, paramSize, paramIsPtr); }

bool remoteInject(unsigned targetProcessId, const string &injectedDllFullpath)
{ 
	char buf[MAX_PATH] = {};
	copy(injectedDllFullpath.begin(), injectedDllFullpath.end(), buf);

	return remoteCall(targetProcessId, 
					  reinterpret_cast<unsigned long (__stdcall *)(void *)>(LoadLibraryA), 
					  const_cast<char *>(injectedDllFullpath.c_str()), injectedDllFullpath.length() * sizeof(injectedDllFullpath[0]),
					  true); 
}
bool remoteInject(const string &targetProcessName, const string &injectedDllFullpath)
{ return remoteInject(w::getProcessId(targetProcessName)[0], injectedDllFullpath); }

bool remoteAntiinject(unsigned targetProcessId, const string &antiinjectedDllModuleName)
{
	map<string, ModuleInfo> modulesInfo = getModulesInfo(targetProcessId);
	HMODULE baseAddr = static_cast<HMODULE>(modulesInfo[antiinjectedDllModuleName].baseAddr);

	void *funcFreeLibrary = GetProcAddress(GetModuleHandle("kernel32.dll"), "FreeLibrary");

	return remoteCall(targetProcessId, 
					  reinterpret_cast<unsigned long (__stdcall *)(void *)>(funcFreeLibrary), 
					  baseAddr, sizeof(baseAddr), false);
}
bool remoteAntiinject(const string &targetProcessName, const string &antiinjectedDllFullpath)
{ return remoteAntiinject(w::getProcessId(targetProcessName)[0], antiinjectedDllFullpath); }

bool interceptFunc(HMODULE callerModule, void *originalFunc, void *myFunc)
{
	unsigned char *callerBaseAddr = reinterpret_cast<decltype(callerBaseAddr)>(callerModule);

	// Travel all import modules.
	unsigned long ideSize = 0;	
	bool found = false, res = false;
	for (PIMAGE_IMPORT_DESCRIPTOR pId = static_cast<PIMAGE_IMPORT_DESCRIPTOR>(
										ImageDirectoryEntryToData(callerBaseAddr, 
																  TRUE, 
																  IMAGE_DIRECTORY_ENTRY_IMPORT, 
																  &ideSize));
		 !found && pId != nullptr && pId->Name != 0; 
		 ++pId)
	{
		// Traval all import function in the module.
		for (PIMAGE_THUNK_DATA pThunk = reinterpret_cast<PIMAGE_THUNK_DATA>(callerBaseAddr + pId->FirstThunk); 
			 !found && pThunk->u1.Function != 0; 
			 ++pThunk)
		{
			// If find the specified function, replace it with 'myFunc'.
			if (reinterpret_cast<void *>(pThunk->u1.Function)
				== originalFunc)
			{
				// Strip memory protection.
				DWORD oldProtect = 0;
				if (VirtualProtect(&pThunk->u1.Function, sizeof(void *), PAGE_EXECUTE_WRITECOPY, &oldProtect) != 0)
				{
					// Replace Windows Api with my function.
					res = WriteProcessMemory(GetCurrentProcess(), &pThunk->u1.Function, &myFunc, sizeof(void *), nullptr) != 0;

					// Restore the original memory protection.
					VirtualProtect(&pThunk->u1.Function, sizeof(void *), oldProtect, &oldProtect);
				}

				found = true;
			}
		}
	}

	return res;
}
bool interceptFunc(const string &callerModuleName, void *originalFunc, void *myFunc)
{ return interceptFunc(GetModuleHandle(callerModuleName.c_str()), originalFunc, myFunc); }

}