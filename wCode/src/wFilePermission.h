

// wFilePermission.h
//

#ifndef W_FILE_PERMISSION_H
#define W_FILE_PERMISSION_H

#include "wCppExt.h"

namespace w
{

//unsigned long getPermission(const std::string &target, const std::string &usr);
bool setPermission(const std::string &target, const std::string &usr, 
				   unsigned long permission, bool reset, bool recursive);

}

#endif // W_FILE_PERMISSION_H