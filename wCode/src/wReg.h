

// wReg.h
//

#ifndef W_REG_H
#define W_REG_H

#include "wCppExt.h"

namespace w
{

// String.
std::string getRegSz(HKEY hKey, const std::string &subKey, const std::string &value);
bool setRegSz(HKEY hKey, const std::string &subKey, const std::string &value, const std::string &data);

std::string getRegExpandSz(HKEY hKey, const std::string &subKey, const std::string &value);
bool setRegExpandSz(HKEY hKey, const std::string &subKey, const std::string &value, const std::string &data);

std::vector<std::string> getRegMultiSz(HKEY hKey, const std::string &subKey, const std::string &value);
bool setRegMultiSz(HKEY hKey, const std::string &subKey, const std::string &value, const std::vector<std::string> &data);

// Integer.
unsigned int getRegDw(HKEY hKey, const std::string &subKey, const std::string &value);
bool setRegDw(HKEY hKey, const std::string &subKey, const std::string &value, unsigned int data);

unsigned long long getRegQw(HKEY hKey, const std::string &subKey, const std::string &value);
bool setRegQw(HKEY hKey, const std::string &subKey, const std::string &value, unsigned long long data);

// Raw.
bool getRegData(HKEY hKey, const std::string &subKey, const std::string &value,
				DWORD *type, void *data, IN OUT int *len);
bool setRegData(HKEY hKey, const std::string &subKey, const std::string &value,
				DWORD type, const void *data, IN OUT int len);

// Other.
std::vector<std::string> enumRegKey(HKEY hKey, const std::string &subKey);
std::vector<std::string> enumRegValue(HKEY hKey, const std::string &subKey);

}

#endif // W_REG_H