

// wProcess.h
//

#ifndef W_PROCESS_H
#define W_PROCESS_H

#include "wCppExt.h"

namespace w
{

struct ModuleInfo
{
	std::string name, path;

	void *baseAddr;
	size_t size;
};

struct ProcessInfo
{
	std::string name, path;

	DWORD id, parentId;
	std::vector<DWORD> threadsId;

	std::map<std::string, ModuleInfo> modules;
};

/*
 *
 *		Get all information about process you want.
 *
 *	Note:
 *		This function is expensive and hard to use. if you want to processName <-> id, use
 *	'getProcessId()' or 'getProcessName()' instead.
 *
 */
std::map<std::string, w::ModuleInfo> getModulesInfo(DWORD processId);
std::vector<DWORD> getThreadsInfo(DWORD processId);
std::map<DWORD, ProcessInfo> getProcessesInfo();

/*
 *
 *		Convert between process id and process name.
 *
 *	Note:
 *		One id maps to one process, while one name maps to one or more processes.
 *
 */
std::vector<DWORD> getProcessId(const std::string &processName);
std::string getProcessName(DWORD id);

DWORD getCurrentProcessId();
std::string getCurrentProcessName();

}

#endif // W_PROCESS_H