

// wReG.h
//

#include "wReg.h"
using namespace std;

namespace w
{

string getRegSz(HKEY hKey, const string &subKey, const string &value)
{
	string res;

	DWORD type = 0;
	int len = 0;
	if (getRegData(hKey, subKey, value, &type, nullptr, &len))
	{
		unique_ptr<unsigned char> p(new unsigned char[len]);
		getRegData(hKey, subKey, value, &type, p.get(), &len);
		
		res = (char *)p.get();
	}

	return res;
}
bool setRegSz(HKEY hKey, const string &subKey, const string &value, const std::string &data)
{
	bool res = setRegData(hKey, subKey, value, REG_SZ, (const BYTE *)data.c_str(), data.length());

	return res;
}

// 
bool getRegData(HKEY hKey, const string &subKey, const string &value,
				DWORD *type, void *data, IN OUT int *len)
{
	bool res = false;

	HKEY phkResult;
	if (RegOpenKeyEx(hKey, subKey.c_str(), 0, KEY_QUERY_VALUE, &phkResult)
		== ERROR_SUCCESS)
	{
		res = RegQueryValueEx(phkResult, value.c_str(), 0, type, (BYTE *)data, (DWORD *)len)
				== ERROR_SUCCESS;

		RegCloseKey(phkResult);
	}
	
	return res;
}
bool setRegData(HKEY hKey, const string &subKey, const string &value,
				DWORD type, const void *data, IN int len)
{
	bool res = false;

	HKEY phkResult;
	if (RegOpenKeyEx(hKey, subKey.c_str(), 0, KEY_SET_VALUE, &phkResult)
		== ERROR_SUCCESS)
	{
		res = RegSetValueEx(phkResult, value.c_str(), 0, type, (BYTE *)data, static_cast<DWORD>(len))
				== ERROR_SUCCESS;

		RegCloseKey(phkResult);
	}
	
	return res;
}

}