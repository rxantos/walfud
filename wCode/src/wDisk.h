

// W_DISK_H
//

#ifndef W_DISK_H
#define W_DISK_H

#include "wCppExt.h"

namespace w
{

/*
 *
 *		Get all valid logic dirves' dos name.
 *
 *	Rtn:
 *		Like {"C:", "D:" ...}.
 *
 */
std::vector<std::string> getDrivesName();

struct DriveInfo
{
	std::string dosName, ntName, volName;
	std::string fs;

	unsigned serialNum;
};

/*
 *
 *		More information than 'getDrivesName'. 
 *
 *	Param:
 *		'driveName': is dos name of drive. Such as ""\\MyServer\MyShare\", or the C drive as "C:\".
 *
 */
DriveInfo getDriveInfo(const std::string &driveName);
std::vector<DriveInfo> getDrivesInfo();

std::string ntNameToDosName(const std::string &ntName);
std::string dosNameToNtName(const std::string &dosName);

/*
 *
 *		Get drives name by type.
 *
 */
std::vector<std::string> getFixedDrivesName();
std::vector<std::string> getRemovableDrivesName();
std::vector<std::string> getRemoteDrivesName();
std::vector<std::string> getCdRomDrivesName();

/*
 *
 *		Get drive name by file system.
 *
 */
std::vector<std::string> getNtfsDrivesName();
std::vector<std::string> getFat32DrivesName();
std::vector<std::string> getFatDrivesName();
std::vector<std::string> getExFatDrivesName();
std::vector<std::string> getUdfDrivesName();

}

#endif // W_DISK_H