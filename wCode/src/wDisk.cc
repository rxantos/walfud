

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

	// Remove redundant '\0' on the end of 'buf'.
	char *bufEnd = unique(buf, buf + size);

	// Split into vector.
	drives = w::strSplit(buf, bufEnd, '\0');

	delete []buf;
	return drives;
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