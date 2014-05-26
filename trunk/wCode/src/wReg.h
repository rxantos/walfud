

// wReg.h
//

#ifndef W_REG_H
#define W_REG_H

#include "wCppExt.h"

namespace w
{

std::string getRegSz(HKEY hKey, const std::string &subKey, const std::string &value);
bool setRegSz(HKEY hKey, const std::string &subKey, const std::string &value, const std::string &data);

bool getRegData(HKEY hKey, const std::string &subKey, const std::string &value,
				DWORD *type, void *data, IN OUT int *len);
bool setRegData(HKEY hKey, const std::string &subKey, const std::string &value,
				DWORD type, const void *data, IN OUT int len);

}

#endif // W_REG_H