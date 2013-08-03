

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

	int id, parentId;
	std::vector<int> threadsId;

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
std::vector<int> getThreadsInfo(DWORD processId);
std::map<int, ProcessInfo> getProcessesInfo();

/*
 *
 *		Convert between process id and process name.
 *
 *	Note:
 *		One id maps to one process, while one name maps to one or more processes.
 *
 */
std::unordered_set<int> getProcessId(const std::string &processName);
std::string getProcessName(DWORD id);

int getCurrentProcessId();
std::string getCurrentProcessName();

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
 *		'unionName': The name can have a "Global\" or "Local\" prefix to explicitly create the object in the global or session name space. 
 *	The remainder of the name can contain any character EXCEPT the backslash character (\). 
 *
 *	Rtn:
 *		'true': If no same process is running, otherwise is 'false'.
 *
 */
bool singleProcess(const std::string &unionName);

}

#endif // W_PROCESS_H