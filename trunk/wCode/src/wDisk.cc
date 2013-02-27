

// wDisk.cc
//

#include "wDisk.h"
using namespace std;

namespace w
{

static vector<string> getSpecifiedTypeDrivesName(unsigned type)
{
	vector<string> specifiedTypeDrives;
	vector<string> allDrives = getDrivesName();

	for_each(allDrives.begin(), allDrives.end(), 
			 [&specifiedTypeDrives, type](const string &driveName)
			 {
				 if (GetDriveType(w::strMakeRight(driveName, "\\").c_str()) == type)
				 {
					 specifiedTypeDrives.push_back(w::strTrimRight(driveName, "\\"));
				 }
			 });

	return specifiedTypeDrives;
}

static vector<string> getSpecifiedFsDrivesName(const string &fs)
{
	vector<string> specifiedFsDrives;
	vector<string> allDrives = getDrivesName();

	for_each(allDrives.begin(), allDrives.end(), 
			 [&specifiedFsDrives, &fs](const string &driveName)
			 {
				 // Get volume information.
				 char volName[MAX_PATH+1] = {}, fsName[MAX_PATH+1] = {};
				 DWORD volNameLen = arrCnt(volName), fsNameLen = arrCnt(fsName);
				 DWORD sn = 0, maxNameLen = 0, fsFlag = 0;
				 GetVolumeInformation(w::strMakeRight(driveName, "\\").c_str(), volName, volNameLen, &sn, &maxNameLen, &fsFlag, fsName, fsNameLen);

				 // Find the speicified filesystem drive.
				 if (w::strICmp(fsName, fs))
				 {
					 specifiedFsDrives.push_back(driveName);				 
				 }
			 });

	return specifiedFsDrives;
}

vector<string> getDrivesName()
{
	vector<string> drives;

	// Allocate enough memory.
	const size_t size = GetLogicalDriveStrings(0, nullptr) + CHARACTER_SIZE;
	char *buf = new char[size];
	fill(buf, buf + size, '\0');

	// Get valid drives in the system.
	GetLogicalDriveStrings(size, buf);

	// Split into vector.
	drives = w::strSplit(buf, buf + size, '\0');

	// Release memory.
	delete []buf;
	buf = nullptr;

	// Remove empty item.
	drives.erase(remove(drives.begin(), drives.end(), string()), drives.end());

	// Remove tailing "\".
	transform(drives.begin(), drives.end(), drives.begin(), [](const string &driveName) -> string { return strTrimRight(driveName, "\\"); });

	return drives;
}

vector<DriveInfo> getDrivesInfo()
{
	vector<DriveInfo> drivesInfo;

	for (auto i : getDrivesName())
	{
		auto di = getDriveInfo(i);
		drivesInfo.push_back(di);
	}

	return drivesInfo;
}
DriveInfo getDriveInfo(const string &driveName)
{
	DriveInfo di = {};

	char ntName[MAX_PATH] = {};
	QueryDosDevice(driveName.c_str(), ntName, arrCnt(ntName));

	char volName[MAX_PATH] = {}, fsType[MAX_PATH] = {};
	DWORD serialNum = 0;
	GetVolumeInformation(driveName.c_str(), volName, arrCnt(volName), &serialNum, nullptr, nullptr, fsType, MAX_PATH);

	di.dosName = driveName;
	di.ntName = ntName;
	di.volName = volName;
	di.fs = fsType;
	di.serialNum = serialNum;

	return di;
}

string ntNameToDosName(const string &ntName)
{
	string dosName;

	return dosName;
}
string dosNameToNtName(const string &dosName)
{
	string ntName = dosName;

	string drive, dir, namePart, extPart;
	pathSplit(dosName, drive, dir, namePart, extPart);

	auto driveInfo = getDriveInfo(drive);

	ntName = driveInfo.ntName + strTrimLeft(ntName, drive);
	return ntName;
}

vector<string> getFixedDrivesName()
{ return getSpecifiedTypeDrivesName(DRIVE_FIXED); }
vector<string> getRemovableDrivesName()
{ return getSpecifiedTypeDrivesName(DRIVE_REMOVABLE); }
vector<string> getRemoteDrivesName()
{ return getSpecifiedTypeDrivesName(DRIVE_REMOTE); }
vector<string> getCdRomDrivesName()
{ return getSpecifiedTypeDrivesName(DRIVE_CDROM); }

vector<string> getNtfsDrivesName()
{ return getSpecifiedFsDrivesName("NTFS"); }
vector<string> getFat32DrivesName()
{ return getSpecifiedFsDrivesName("FAT32"); }
vector<string> getFatDrivesName()
{ return getSpecifiedFsDrivesName("FAT"); }
vector<string> getExFatDrivesName()
{ return getSpecifiedFsDrivesName("exFAT"); }
vector<string> getUdfDrivesName()
{ return getSpecifiedFsDrivesName("UDF"); }

}