

// ParseService.cpp
//

#include "wService.h"
using namespace std;

namespace w
{

bool operator<(const ServiceInfo &a, const ServiceInfo &b)
{ return a.name < b.name; }

#define REG_PATH_SERVICE	"SYSTEM\\CurrentControlSet\\services"
#define	REG_VALUE_SERVICE	"ServiceDll"

/*
 *
 *		Get fullpath of service belonged dll file.
 *
 *	Rtn:
 *		Plain fullpath of the dll.
 *
 */
static string getServiceDllByName(const string &name)
{
	string fullpath;

	HKEY hKey;
	LONG rtn = RegOpenKeyEx(HKEY_LOCAL_MACHINE, REG_PATH_SERVICE, 0, KEY_READ, &hKey);
	if (rtn == ERROR_SUCCESS)
	{
		// Read register of that service, find key of "Parameters", value of "ServiceDll".
		char buf[MAX_PATH] = {};
		DWORD bufLen = sizeof(buf);
		RegGetValue(hKey, (name + "\\Parameters").c_str(), REG_VALUE_SERVICE, REG_EXPAND_SZ,
					NULL, buf, &bufLen);

		fullpath = buf;
	}

	return fullpath;
}

vector<ServiceInfo> getServicesInfo()
{
	vector<ServiceInfo> res;

	if (SC_HANDLE sc = OpenSCManager(NULL, SERVICES_ACTIVE_DATABASE, SC_MANAGER_ENUMERATE_SERVICE))
	{
		// Enumerate all services.
		DWORD neededByte = 0, cnt = 0;
		EnumServicesStatusEx(sc, SC_ENUM_PROCESS_INFO, SERVICE_WIN32, SERVICE_ACTIVE, 
							 NULL, 0, 
							 &neededByte, &cnt, 0, NULL);

		unsigned servicesInfoSize = neededByte;
		ENUM_SERVICE_STATUS_PROCESS *servicesInfo = reinterpret_cast<ENUM_SERVICE_STATUS_PROCESS *>(new unsigned char[servicesInfoSize]);
		memset(servicesInfo, 0, servicesInfoSize);
		EnumServicesStatusEx(sc, SC_ENUM_PROCESS_INFO, SERVICE_WIN32, SERVICE_ACTIVE, 
							 reinterpret_cast<BYTE *>(servicesInfo), servicesInfoSize, 
							 &neededByte, &cnt, 0, NULL);

		// Get services information.
		for (unsigned i = 0; i < cnt; ++i)
		{
			ServiceInfo si = {};
			si.name = servicesInfo[i].lpServiceName;
			si.desc = servicesInfo[i].lpDisplayName;
			si.type = servicesInfo[i].ServiceStatusProcess.dwServiceType;
			si.status = servicesInfo[i].ServiceStatusProcess.dwCurrentState;
			si.pid = servicesInfo[i].ServiceStatusProcess.dwProcessId;
			si.fullpath = getServiceDllByName(servicesInfo[i].lpServiceName);

			res.push_back(si);
		}
		
		delete []servicesInfo;
		servicesInfo = NULL;
		CloseServiceHandle(sc);
	}//if (SC_HANDLE

	return res;
}

/*
 *
 *		Get services which are directly based on 'name' service. 
 *
 */
static set<ServiceInfo> doGetDependentServicesInfo(SC_HANDLE hMgr, const string &name)
{
	set<ServiceInfo> dependsInfo;

	if (SC_HANDLE hSvc = OpenService(hMgr, name.c_str(), SERVICE_ENUMERATE_DEPENDENTS | SERVICE_STOP))
	{
		DWORD neededByte = 0, cnt = 0;
		EnumDependentServices(hSvc, SERVICE_ACTIVE, NULL, 0, &neededByte, &cnt);

		unsigned servicesInfoSize = neededByte;
		ENUM_SERVICE_STATUS *servicesInfo = reinterpret_cast<ENUM_SERVICE_STATUS *>(new unsigned char[servicesInfoSize]);
		memset(servicesInfo, 0, servicesInfoSize);
		EnumDependentServices(hSvc, SERVICE_ACTIVE, servicesInfo, neededByte, &neededByte, &cnt);
		for (unsigned i = 0; i < cnt; ++i)
		{
			ServiceInfo si = {};
			si.name = servicesInfo[i].lpServiceName;
			si.desc = servicesInfo[i].lpDisplayName;
			si.type = servicesInfo[i].ServiceStatus.dwServiceType;
			si.status = servicesInfo[i].ServiceStatus.dwCurrentState;

			dependsInfo.insert(si);
		}

		delete []servicesInfo;
		servicesInfo = NULL;
		CloseServiceHandle(hSvc);
	}

	return dependsInfo;
}



set<ServiceInfo> getDependentServicesInfo(const string &name)
{
	set<ServiceInfo> depends;

	if (SC_HANDLE hMgr = OpenSCManager(NULL, SERVICES_ACTIVE_DATABASE, SC_MANAGER_ENUMERATE_SERVICE))
	{
		// Search all services which are based on 'name' service.
		depends = doGetDependentServicesInfo(hMgr, name);
		for (set<ServiceInfo>::const_iterator it = depends.begin(); it != depends.end(); ++it)
		{
			set<ServiceInfo> moreDepends = getDependentServicesInfo(it->name);
			depends.insert(moreDepends.begin(), moreDepends.end());
		}

		CloseServiceHandle(hMgr);
	}//if (SC_HANDLE

	return depends;
}


map<unsigned, set<ServiceInfo>> getServiceInfoByPids(const set<unsigned> &pids)
{
	map<unsigned, set<ServiceInfo>> res;

	vector<ServiceInfo> servicesInfo = getServicesInfo();
	for (vector<ServiceInfo>::const_iterator it = servicesInfo.begin(); it != servicesInfo.end(); ++it)
	{
		// Get services information of specified pid.
		if (pids.find(it->pid) != pids.end())
		{
			res[it->pid].insert(*it);
		}
	}

	return res;
}

set<ServiceInfo> getServiceInfoByPid(unsigned pid)
{
	set<unsigned> pids;
	pids.insert(pid);
	map<unsigned, set<ServiceInfo>> servicesInfo = getServiceInfoByPids(pids);

	return servicesInfo[pid];
}

}