

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
	MODULEENTRY32 me = {};
	me.dwSize = sizeof(me); 
	if (Module32First(snapshot, &me))
	{
		ModuleInfo mi = {};
		mi.name = me.szModule, mi.path = trimRight(me.szExePath, me.szModule), mi.baseAddr = me.modBaseAddr, mi.size = me.modBaseSize;
		modulesInfo[me.szModule] = mi;

		while (Module32Next(snapshot, &me))
		{
			ModuleInfo mi = {};
			mi.name = me.szModule, mi.path = me.szExePath, mi.baseAddr = me.modBaseAddr, mi.size = me.modBaseSize;
			modulesInfo[me.szModule] = mi;
		}
	}

	return modulesInfo;
}
vector<DWORD> getThreadsInfo(DWORD processId)
{
	vector<DWORD> threadsId;

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, processId);
	THREADENTRY32 te = {};
	te.dwSize = sizeof(te); 
	if (Thread32First(snapshot, &te))
	{
		threadsId.push_back(te.th32ThreadID);
		
		while (Thread32Next(snapshot, &te))
		{
			threadsId.push_back(te.th32ThreadID);
		}
	}

	return threadsId;
}

map<DWORD, ProcessInfo> getProcessesInfo()
{
	map<DWORD, ProcessInfo> res;

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);

	// Fill process information.
	PROCESSENTRY32 pe = {};
	pe.dwSize = sizeof(pe);
	if (Process32First(snapshot, &pe))
	{
		ProcessInfo pi = {};
		pi.name = pe.szExeFile;
		pi.id = pe.th32ProcessID, pi.parentId = pe.th32ParentProcessID;
		res[pe.th32ProcessID] = pi;

		while (Process32Next(snapshot, &pe))
		{
			ProcessInfo pi = {};
			pi.name = pe.szExeFile;
			pi.id = pe.th32ProcessID, pi.parentId = pe.th32ParentProcessID;
			res[pe.th32ProcessID] = pi;		
		}
	}

	// Fill module information.
	for (map<DWORD, ProcessInfo>::iterator it = res.begin(); it != res.end(); ++it)
	{
		it->second.modules = getModulesInfo(pe.th32ProcessID);		
	}

	// Fill thread information.
	for (map<DWORD, ProcessInfo>::iterator it = res.begin(); it != res.end(); ++it)
	{
		it->second.threadsId = getThreadsInfo(pe.th32ProcessID);		
	}

	CloseHandle(snapshot);
	return res;
}

static map<DWORD, string> getProcessesId()
{
	map<DWORD, string> idName;

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
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
	return idName;
}
vector<DWORD> getProcessId(const string &processName)
{
	vector<DWORD> ids;

	map<DWORD, string> idNames = getProcessesId();
	for (map<DWORD, string>::const_iterator it = idNames.begin(); it != idNames.end(); ++it)
	{
		if (strICmp(processName, it->second))
		{
			ids.push_back(it->first);
		}
	}
	
	return ids;
}
string getProcessName(DWORD id)
{
	map<DWORD, string> idName = getProcessesId();
	return idName[id];
}

DWORD getCurrentProcessId()
{ return ::GetCurrentProcessId(); }
std::string getCurrentProcessName()
{
	char moduleName[MAX_PATH] = {};
	::GetModuleFileName(nullptr, moduleName, ArrLen(moduleName));

	return moduleName;
}

}