

// wHack.h
// 

#ifndef W_HACK_H
#define W_HACK_H

#include "wCppExt.h"

namespace w
{
bool remoteCall(int targetProcessId, unsigned long (__stdcall *func)(void *), void *param, unsigned paramSize, bool paramIsPtr);
bool remoteCall(const std::string &targetProcessName, unsigned long (__stdcall *func)(void *), void *param, unsigned paramSize, bool paramIsPtr);

bool remoteInject(int targetProcessId, const std::string &injectedDllFullpath);
bool remoteInject(const std::string &targetProcessName, const std::string &injectedDllFullpath);

bool remoteAntiinject(int targetProcessId, const std::string &antiinjectedDllFullpath);
bool remoteAntiinject(const std::string &targetProcessName, const std::string &antiinjectedDllFullpath);

/*
 *
 *
 *
 */
	//// Intercept all 'CreateFileA' in current process.
	//void *originalFunc = CreateFileA;						// This statement is necessary! If you put 'CreateFileA' in 'w::interceptFunc', NOT all
	//														// modules are intercept.
	//														// Because the second time you call 'w::interceptFunc' with 'CreateFileA', this 'CreateFileA'
	//														// has been changed to your function address!
	//map<string, w::ModuleInfo> modulesInfo = w::getModulesInfo(w::getCurrentProcessId());
	//for (map<string, w::ModuleInfo>::const_iterator it = modulesInfo.begin(); it != modulesInfo.end(); ++it)
	//{
	//	w::interceptFunc(it->first, originalFunc, myCreateFileA);
	//}
bool interceptFunc(HMODULE callerModule, void *originalFunc, void *myFunc);
bool interceptFunc(const std::string &callerModuleName, void *originalFunc, void *myFunc);

/*
 *
 *		Get all process handles from current OS.
 *
 *	Rtn:
 *		'.first': the process id.
 *		'.second': the handle of that id.
 *
 *	Note:
 *		If this function fail in some case, try to increase 'sc_maxHandleCnt'.
 *
 */
std::unordered_multimap<int, void *> getIdHandleMap();

/*
 *
 *		Get the handle name of other process.
 *
 *	Note:
 *		The method used here is to duplicate the handle from other process to current process, and then 
 *	get handle information from current process.
 *
 */
std::string getNameFromHandle(HANDLE h, int processId);

/*
 *
 *		Query a handle information in all processes.
 *
 *	Param
 *		'idHandleMap.first': process id.
 *		'idHandleMap.second': handle in that process.
 *
 *	Rtn:
 *		'<0>' is process id; '<1>' is handle value in that process, '<2>' is handle name.
 *
 */
	//// Close a handle at from all processes.
	//string handlename = "testDir";

	//auto idHandle_all = getIdHandleMap();
	//auto idValName = getIdHandlevalueHandlename(idHandle_all);

	//for (auto i : idValName)
	//{
	//	int processId = get<0>(i);
	//	HANDLE val = get<1>(i);
	//	string name = get<2>(i);
	//	if (name.find(handlename) != string::npos)
	//	{
	//		cout <<processId <<" : " <<name <<"\t...";

	//		// Close the handle from specified process..
	//		if (HANDLE processHandle = OpenProcess(PROCESS_DUP_HANDLE, FALSE, processId))
	//		{
	//			if (DuplicateHandle(processHandle, val, GetCurrentProcess(), nullptr, 0, false, DUPLICATE_CLOSE_SOURCE))
	//			{
	//				cout <<"ok.";
	//			}
	//			else
	//			{
	//				cout <<"fail.";
	//			}

	//			CloseHandle(processHandle);
	//		}

	//		cout <<endl;
	//	}
	//}
std::vector<std::tuple<int, void *, std::string>> getIdHandlevalueHandlename(const std::unordered_multimap<int, void *> &idHandleMap);

}

#endif // W_HACK_H