

// wHack.h
// 

#ifndef W_HACK_H
#define W_HACK_H

#include "wCppExt.h"

namespace w
{
bool remoteCall(unsigned targetProcessId, unsigned long (__stdcall *func)(void *), void *param, unsigned paramSize, bool paramIsPtr);
bool remoteCall(const std::string &targetProcessName, unsigned long (__stdcall *func)(void *), void *param, unsigned paramSize, bool paramIsPtr);

bool remoteInject(unsigned targetProcessId, const std::string &injectedDllFullpath);
bool remoteInject(const std::string &targetProcessName, const std::string &injectedDllFullpath);

bool remoteAntiinject(unsigned targetProcessId, const std::string &antiinjectedDllFullpath);
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

}

#endif // W_HACK_H