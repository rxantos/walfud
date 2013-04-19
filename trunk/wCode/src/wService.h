

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
				fullpath;				// Service containing dll fullpath.

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

}

#endif // W_SERVICE_H
