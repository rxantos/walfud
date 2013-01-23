

// wPulverizerTool.h
//

#ifndef W_PULVERIZER_TOOL_H
#define W_PULVERIZER_TOOL_H

#include <string>

/*
 *
 */
void grantPermission(const std::string &fullpath);

/*
 *
 */
void unloadHandle(const std::string &handleName);

/*
 *
 *		Write the disk with meaningless data multiple times, avoid recovering data from disk.
 *
 */
void multiErase(const std::string &fullpath);

/*
 *
 *		Rename the file with meaningless string multiple times, avoid retriving information from disk.
 *	Rtn:
 *		The last random name.
 *
 */
std::string multiRename(const std::string &fullpath);

/*
 *
 *		Pulverize a single object.
 *
 *	Note:
 *		The target must be of permission to delete.
 *
 */
void pulverize(const std::string &fullpath);

/*
 *
 *		Make a virtual file to hold the place, avoid the file be regenerated.
 *
 */
void antiRegenerate(const std::string &fullpath);


#endif // W_PULVERIZER_TOOL_H