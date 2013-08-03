

// ParseService.h
//

#ifndef W_SERVICE_H
#define W_SERVICE_H

#include "wCppExt.h"

namespace w
{

struct ServiceInfo
{
	std::string name,					// Service name.
				desc,					// Service description.
				fullpath;				// Service DLL fullpath.

	unsigned type,					// Service type. See: http://msdn.microsoft.com/en-us/library/windows/desktop/ms685992(v=vs.85).aspx.
			 status,				// Service status. See: http://msdn.microsoft.com/en-us/library/windows/desktop/ms685992(v=vs.85).aspx.
			 pid;					// Service belonging process id.
};

bool operator<(const ServiceInfo &a, const ServiceInfo &b);

/*
 *
 *		Get all services information.
 *
 */
std::vector<ServiceInfo> getServicesInfo();

/*
 *
 *		Get services information of specified process id(s).
 *
 */
std::map<unsigned, std::set<ServiceInfo>> getServiceInfoByPids(const std::vector<unsigned> &pids);
std::set<ServiceInfo> getServiceInfoByPid(unsigned pid);

/*
 *
 *		Get services information base on specified service.
 *
 *	Example:
		set<ServiceInfo> s = GetServiceInfoByPid(xxx);
		for (set<ServiceInfo>::const_iterator it = s.begin(); it != s.end(); ++it)
		{
			set<ServiceInfo> depends = getDependentServicesInfo(it->name);
			depends = depends;
		}
 *
 */
std::set<ServiceInfo> getDependentServicesInfo(const std::string &name);

/*
 *
 *		Get service name from ProcessIdentifier and SubProcessTag. 
 *	For details: http://wj32.org/wp/2010/03/30/howto-use-i_querytaginformation/.
 *
 *	Note:
 *		Architecture sensitive!. You MUST use 32 bit app on 32 bit OS, and 64 bit 
 *	app on 64 bit OS.
 *
 */
std::string getServiceNameFromPidTid(unsigned pid, unsigned tid);
/*
 *
 *		The function will enumerate all process information, find the pid which 
 *	the tid belongs to. 
 *		This function is low efficiency than 'getServiceNameFromPidSpt(unsigned pid, unsigned tid)'.
 *
 */
std::string getServiceNameFromTid(unsigned tid);

}

#endif // W_SERVICE_H
