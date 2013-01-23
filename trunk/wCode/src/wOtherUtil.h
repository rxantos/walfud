

// wOtherUtil.h
//

#ifndef W_OTHER_UTIL_H
#define W_OTHER_UTIL_H

#include "wCppExt.h"

namespace w
{

/*
 *
 *		Read ini file.
 *
 *
 */
std::vector<std::string> getIniData(const std::string &fullpath, const char *sectionName = NULL, const char *keyName = NULL);
std::vector<std::string> getIniSetionsName(const std::string &fullpath);
std::vector<std::string> getIniKeysName(const std::string &fullpath);
std::vector<std::string> getIniVal(const std::string &fullpath);
std::multimap<std::string, std::string> getIniData(const std::string &fullpath, const std::string &sectionName, const std::string &keyName);

}

#endif // W_OTHER_UTIL_H