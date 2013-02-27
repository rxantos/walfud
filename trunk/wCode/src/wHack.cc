

// wHack.cc
//

#include "wHack.h"
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
					  baseAddr, sizeof(baseAddr), 
					  false);
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

//========================= Query handle from other processes.

static const unsigned sc_searchTimeout = 50;		// ms.
static const unsigned sc_maxPathLen = 1024;	
static const unsigned sc_maxHandleCnt = 128 * 1024;	// Maximum allowable number of handle in current OS.

unordered_multimap<int, void *> getIdHandleMap()
{
	unordered_multimap<int, void *> res;			// '.first' is process id; '.second' is handle.

	const unsigned long needed = sizeof(SYSTEM_HANDLE_INFORMATION_EX) + sc_maxHandleCnt*sizeof(SYSTEM_HANDLE_INFORMATION);
	unsigned char *buf = new unsigned char[needed];
	memset(buf, 0, needed);

	unsigned long writenSize = 0;
	if (ZwQuerySystemInformation(SystemHandleInformation, static_cast<void *>(buf), needed, &writenSize) == 0)
	{
		// Save handles information.
		SYSTEM_HANDLE_INFORMATION_EX *shie = reinterpret_cast<SYSTEM_HANDLE_INFORMATION_EX *>(buf);
		SYSTEM_HANDLE_INFORMATION *shi = shie->Information;
		for (unsigned long i = 0; i < shie->NumberOfHandles; ++i)
		{
			res.insert(make_pair(shi[i].ProcessId, reinterpret_cast<void *>(shi[i].Handle)));
		}
	}

	delete []buf;
	buf = nullptr;

	return res;
}

string getNameFromHandle(HANDLE h, int processId)
{
	string res;

	if (HANDLE processHandle = OpenProcess(PROCESS_DUP_HANDLE, false, processId))
	{
		HANDLE duplicatedHandle;
		if (DuplicateHandle(processHandle, h, GetCurrentProcess(), &duplicatedHandle, 0, false, 0))
		{
			//IO_STATUS_BLOCK ioStatus = {};
			const unsigned needed = sizeof(KOBJECT_NAME_INFORMATION) + sc_maxPathLen*sizeof(wchar_t);
			unsigned char buf[needed] = {};
			memset(buf, 0, needed);

			// 'ZwQueryInformationFile' may cause stuck.
			//if (ZwQueryInformationFile(duplicatedHandle, &ioStatus, static_cast<void *>(buf), needed, FileNameInformation) == 0)
			if (ZwQueryObject(duplicatedHandle, 1, static_cast<void *>(buf), needed, nullptr) >= 0)
			{
				PKOBJECT_NAME_INFORMATION oni = reinterpret_cast<PKOBJECT_NAME_INFORMATION>(buf);
				res = wStrToStr(oni->FileName);
			}

			CloseHandle(duplicatedHandle);
		}//if (DuplicateHandle

		CloseHandle(processHandle);
	}//if (HANDLE

	return res;
}
void getNameFromHandleWrapper(void *param)
{
	tuple<string &, int, void *> *handlenameIdHandlevalue = reinterpret_cast<tuple<string &, int, void *> *>(param);
	string &handleName = get<0>(*handlenameIdHandlevalue);
	int processId = get<1>(*handlenameIdHandlevalue);
	HANDLE handle = get<2>(*handlenameIdHandlevalue);

	handleName = getNameFromHandle(handle, processId);
}

vector<tuple<int, void *, string>> getIdHandlevalueHandlename(const unordered_multimap<int, void *> &idHandleMap)
{
	vector<tuple<int, void *, string>> res;		// '<0>' is process id; '<1>' is handle value in that process, '<2>' is handle name.

	this_thread::sleep_for(chrono::seconds(1));
	for (auto i : idHandleMap)
	{
		string handleName;
		tuple<string &, int, void *> param(handleName, i.first, i.second);
		HANDLE h = reinterpret_cast<HANDLE>(_beginthread(getNameFromHandleWrapper, 0, &param));
		switch (WaitForSingleObject(h, sc_searchTimeout))
		{
		case WAIT_OBJECT_0:
			if (!handleName.empty())
			{
				res.push_back(make_tuple(i.first, i.second, handleName));
			}
			break;
		default:
			TerminateThread(h, 1);
			break;
		}

		// The C++11 implementation has drawback caused by 'async'.
		// For details: http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2012/n3451.pdf
		//auto idNamePair = async(getNameFromHandle, i.second, i.first);
		//switch (idNamePair.wait_for(chrono::milliseconds(sc_searchTimeout)))
		//{
		//case future_status::ready:
		//	{
		//		string handleName = idNamePair.get();
		//		if (!handleName.empty())
		//		{
		//			res.insert(make_pair(i.first, handleName));
		//		}
		//		break;
		//	}
		//case future_status::timeout:
		//	// We'd better find a way to kill the halting thread,
		//	// otherwise there will be more and more halting threads, 
		//	// which is a danger.
		//	break;
		//case future_status::deferred:
		//	break;
		//default:
		//	break;
		//}
	}

	return res;
}

}