

// wProcess.h
//

#include "wProcess.h"
#include <Tlhelp32.h>
using namespace std;

namespace w
{

map<string, w::ModuleInfo> getModulesInfo(DWORD processId)
{
	map<string, w::ModuleInfo> modulesInfo;

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE32 | TH32CS_SNAPMODULE, processId);
	if (snapshot != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 me = {};
		me.dwSize = sizeof(me); 
		if (Module32First(snapshot, &me))
		{
			ModuleInfo mi = {};
			mi.name = me.szModule, mi.path = strTrimRight(me.szExePath, me.szModule), mi.baseAddr = me.modBaseAddr, mi.size = me.modBaseSize;
			modulesInfo[me.szModule] = mi;

			while (Module32Next(snapshot, &me))
			{
				ModuleInfo mi = {};
				mi.name = me.szModule, mi.path = me.szExePath, mi.baseAddr = me.modBaseAddr, mi.size = me.modBaseSize;
				modulesInfo[me.szModule] = mi;
			}
		}

		CloseHandle(snapshot);
	}//if (snapshot

	return modulesInfo;
}
vector<int> getThreadsInfo(DWORD processId)
{
	vector<int> threadsId;

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, processId);
	if (snapshot != INVALID_HANDLE_VALUE)
	{
		THREADENTRY32 te = {};
		te.dwSize = sizeof(te); 
		if (Thread32First(snapshot, &te))
		{
			if (te.th32OwnerProcessID == processId)
			{
				threadsId.push_back(te.th32ThreadID);
			}
		
			while (Thread32Next(snapshot, &te))
			{
				if (te.th32OwnerProcessID == processId)
				{
					threadsId.push_back(te.th32ThreadID);
				}
			}//while (Thread32Next
		}//if (Thread32First

		CloseHandle(snapshot);
	}//if (snapshot

	return threadsId;
}

map<int, ProcessInfo> getProcessesInfo()
{
	map<int, ProcessInfo> res;

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
	if (snapshot != INVALID_HANDLE_VALUE)
	{
		// Fill process information.
		PROCESSENTRY32 pe = {};
		pe.dwSize = sizeof(pe);
		if (Process32First(snapshot, &pe))
		{
			ProcessInfo pi = {};
			pi.name = pe.szExeFile;
			pi.id = pe.th32ProcessID;
			pi.parentId = pe.th32ParentProcessID;
			res[pe.th32ProcessID] = pi;

			while (Process32Next(snapshot, &pe))
			{
				ProcessInfo pi = {};
				pi.name = pe.szExeFile;
				pi.id = pe.th32ProcessID;
				pi.parentId = pe.th32ParentProcessID;
				res[pe.th32ProcessID] = pi;		
			}
		}

		// Fill module information.
		for (auto &i : res)
		{
			i.second.modules = getModulesInfo(i.first);
		}

		// Fill thread information.
		for (auto &i : res)
		{
			i.second.threadsId = getThreadsInfo(i.first);
		}

		CloseHandle(snapshot);
	}//if (snapshot

	return res;
}

static map<int, string> getProcessesId()
{
	map<int, string> idName;

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (snapshot != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 pe = {};
		pe.dwSize = sizeof(pe);
		if (Process32First(snapshot, &pe))
		{
			idName[pe.th32ProcessID] = pe.szExeFile;
			while (Process32Next(snapshot, &pe))
			{
				idName[pe.th32ProcessID] = pe.szExeFile;
			}
		}//if (Process32First

		CloseHandle(snapshot);
	}//if (snapshot

	return idName;
}
unordered_set<int> getProcessId(const string &processName)
{
	unordered_set<int> ids;

	map<int, string> idNames = getProcessesId();
	for (map<int, string>::const_iterator it = idNames.begin(); it != idNames.end(); ++it)
	{
		if (strICmp(processName, it->second))
		{
			ids.insert(it->first);
		}
	}
	
	return ids;
}
string getProcessName(DWORD id)
{
	map<int, string> idName = getProcessesId();
	return idName[id];
}

int getCurrentProcessId()
{ return static_cast<int>(GetCurrentProcessId()); }
string getCurrentProcessName()
{
	char moduleName[MAX_PATH] = {};
	GetModuleFileName(nullptr, moduleName, COUNTOF(moduleName));

	return PathFindFileName(moduleName);
}

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

vector<string> getArgv()
{
	vector<string> args;

	if (wchar_t *p = GetCommandLineW())
	{
		int argc = 0;
		if (wchar_t **argv = CommandLineToArgvW(p, &argc))
		{
			for (int i = 0; i < argc && argv[i] != nullptr; ++i)
			{
				args.push_back(w::wStrToStr(argv[i]));
			}
		}
	}

	return args;
}

bool SetPrivilege(const string &privilege, bool grant)
{
	bool res = false;

	HANDLE token;
	if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &token))
		
	{
		LUID luid = {};
		if (LookupPrivilegeValue(nullptr, privilege.c_str(), &luid))
		{
			TOKEN_PRIVILEGES tp = {};
			tp.PrivilegeCount = 1;
			tp.Privileges[0].Luid = luid;
			tp.Privileges[0].Attributes = grant ? SE_PRIVILEGE_ENABLED : SE_PRIVILEGE_REMOVED;

			if (AdjustTokenPrivileges(token, FALSE, &tp, sizeof(tp), nullptr, nullptr))
			{
				res = true;
			}
		}
	}

	return res;
}

bool TakeOwnership(const string &target)
{
	bool res = false;

	// Get privilege.
	if (SetPrivilege(SE_TAKE_OWNERSHIP_NAME, true))
	{
		char username[MAX_PATH] = {};
		DWORD usernameLen = COUNTOF(username);
		char sid[1024] = {};
		DWORD sidLen = sizeof(sid);
		ZeroMemory(sid, sidLen);
		char domain[MAX_PATH] = {};
		DWORD domainLen = MAX_PATH;
		SID_NAME_USE snu = {};
	
		if (GetUserName(username, &usernameLen) 
			&& LookupAccountName(nullptr, username, sid, &sidLen, domain, &domainLen, &snu))
		{
			char obj[MAX_PATH] = {};
			strcpy(obj, target.c_str());
			if (SetNamedSecurityInfo(obj, SE_FILE_OBJECT, OWNER_SECURITY_INFORMATION, 
									 sid, nullptr, nullptr, nullptr) == ERROR_SUCCESS)
			{
				res = true;
			}
		}

		// Release privilege.
		SetPrivilege(SE_TAKE_OWNERSHIP_NAME, false);
	}

	return res;
}

/**
 *
 *		Read specified process information.
 *
 */
static _RTL_USER_PROCESS_PARAMETERS getUserProcParam(int pid)
{
	_RTL_USER_PROCESS_PARAMETERS res = {};

	if (HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid))
	{
		PROCESS_BASIC_INFORMATION pbi = {};
		ULONG rtnLen = 0;
		w::NTSTATUS rtn = w::NtQueryInformationProcess(hProcess, ProcessBasicInformation, &pbi, sizeof(pbi), &rtnLen);
		if (rtn >= 0)
		{
			// 1. Find the Process Environment Block.
			PEB peb = {};
			if (NtReadVirtualMemory(hProcess, pbi.PebBaseAddress, &peb, sizeof(peb), &rtnLen) == ERROR_SUCCESS)
			{
				// 2. From this PEB, get the address of the block containing a pointer to the executable fullpath.
				NtReadVirtualMemory(hProcess, reinterpret_cast<PVOID>(peb.ProcessParameters), &res, sizeof(res), &rtnLen);
			}//if 1
		}//if rtn
		CloseHandle(hProcess);
	}//if (hProcess

	return res;
}
static bool getPebData(HANDLE hProcess, PVOID data, void *buf, size_t bufSize)
{
	bool res = false;

	ULONG rtnLen = 0;
	if (NtReadVirtualMemory(hProcess, data, buf, bufSize, &rtnLen) == ERROR_SUCCESS)
	{
		res = true;
	}

	return res;
}
static string getPebData(int pid, UNICODE_STRING ustr)
{
	wchar_t buf[MAX_PATH] = {};

	if (HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid))
	{
		// `ustr.Buffer` is the remote address.
		getPebData(hProcess, ustr.Buffer, buf, sizeof(buf));

		CloseHandle(hProcess);
	}

	return wStrToStr(buf);
}

string getProcessFullpath(int pid)
{
	string res;

	auto upp = getUserProcParam(pid);

	return getPebData(pid, upp.ImagePathName);
}
string getProcessCmdLine(int pid)
{
	string res;

	auto upp = getUserProcParam(pid);

	return getPebData(pid, upp.CommandLine);
}
string getProcessCurrentDirectory(int pid)
{
	string res;

	auto upp = getUserProcParam(pid);


	if (HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid))
	{
		// `ustr.Buffer` is the remote address.
		wchar_t buf[MAX_PATH] = {};
		auto ustr = reinterpret_cast<UNICODE_STRING *>(reinterpret_cast<char *>(&upp.ImagePathName) - sizeof(UNICODE_STRING64) - sizeof(HANDLE));
		getPebData(hProcess, ustr->Buffer, buf, sizeof(buf));
		res = wStrToStr(buf);

		CloseHandle(hProcess);
	}	
	
	return res;
}
// Read 64-bit process information from 32-bit process.
static _RTL_USER_PROCESS_PARAMETERS64 getUserProcParam64(int pid)
{
	_RTL_USER_PROCESS_PARAMETERS64 res = {};

	if (HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, static_cast<DWORD>(pid)))
	{
		PROCESS_BASIC_INFORMATION64 pbi64 = {};
		UINT64 rtnLen = 0;
		w::NTSTATUS rtn = w::NtWow64QueryInformationProcess64(hProcess, ProcessBasicInformation, &pbi64, sizeof(pbi64), &rtnLen);
		if (rtn >= 0)
		{
			// 1. Find the Process Environment Block.
			__PEB64 peb64 = {};
			if (NtWow64ReadVirtualMemory64(hProcess, pbi64.PebBaseAddress, &peb64, sizeof(peb64), &rtnLen) == ERROR_SUCCESS)
			{
				// 2. From this PEB, get the address of the block containing a pointer to the executable fullpath.
				NtWow64ReadVirtualMemory64(hProcess, reinterpret_cast<PVOID64>(peb64.ProcessParameters), &res, sizeof(res), &rtnLen);
			}//if 1
		}//if rtn
		CloseHandle(hProcess);
	}//if (hProcess

	return res;
}
static bool getPeb64Data(HANDLE hProcess, PVOID64 data, void *buf, size_t bufSize)
{
	bool res = false;

	UINT64 rtnLen64 = 0;
	if (NtWow64ReadVirtualMemory64(hProcess, data, buf, bufSize, &rtnLen64) == ERROR_SUCCESS)
	{
		res = true;
	}

	return res;
}
static string getPeb64Data(int pid, UNICODE_STRING64 ustr)
{
	wchar_t buf[MAX_PATH] = {};

	if (HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, static_cast<DWORD>(pid)))
	{
		// `ustr.Buffer` is the remote address.
		getPeb64Data(hProcess, ustr.Buffer, buf, sizeof(buf));

		CloseHandle(hProcess);
	}

	return wStrToStr(buf);
}

string getProcessFullpath64(int pid)
{
	string res;

	auto upp64 = getUserProcParam64(pid);

	return getPeb64Data(pid, upp64.ImagePathName);
}
string getProcessCmdLine64(int pid)
{
	string res;

	auto upp64 = getUserProcParam64(pid);

	return getPeb64Data(pid, upp64.CommandLine);
}
string getProcessCurrentDirectory64(int pid)
{
	string res;

	auto upp64 = getUserProcParam64(pid);

	return getPeb64Data(pid, upp64.CurrentDirectory);
}

}