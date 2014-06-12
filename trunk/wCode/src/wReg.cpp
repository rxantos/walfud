

// wReG.h
//

#include "wReg.h"
using namespace std;

namespace w
{

// String.
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
bool setRegSz(HKEY hKey, const string &subKey, const string &value, const string &data)
{
	bool res = setRegData(hKey, subKey, value, REG_SZ, (const BYTE *)data.c_str(), data.length());

	return res;
}

string getRegExpandSz(HKEY hKey, const string &subKey, const string &value)
{
	string res = getRegSz(hKey, subKey, value);
	res = expandEvnString(res);

	return res;
}
bool setRegExpandSz(HKEY hKey, const string &subKey, const string &value, const string &data)
{
	bool res = setRegData(hKey, subKey, value, REG_EXPAND_SZ, (const BYTE *)data.c_str(), data.length());

	return res;
}

// Integer.
unsigned int getRegDw(HKEY hKey, const string &subKey, const string &value)
{
	DWORD res = 0;

	int len = sizeof(res);
	getRegData(hKey, subKey, value, nullptr, &res, &len);

	return res;
}
bool setRegDw(HKEY hKey, const string &subKey, const string &value, unsigned int data)
{
	bool res = false;

	setRegData(hKey, subKey, value, REG_DWORD, &data, sizeof(data));

	return res;
}

unsigned long long getRegQw(HKEY hKey, const string &subKey, const string &value)
{
	unsigned long long res = 0;

	int len = sizeof(res);
	getRegData(hKey, subKey, value, nullptr, &res, &len);

	return res;
}
bool setRegQw(HKEY hKey, const string &subKey, const string &value, unsigned long long data)
{
	bool res = false;

	setRegData(hKey, subKey, value, REG_QWORD, &data, sizeof(data));

	return res;
}

// Raw.
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

// Other.
vector<string> enumRegKey(HKEY hKey, const string &subKey)
{
	vector<string> res;

	HKEY phkResult;
	if (RegOpenKeyEx(hKey, subKey.c_str(), 0, KEY_QUERY_VALUE | KEY_ENUMERATE_SUB_KEYS, &phkResult)
		== ERROR_SUCCESS)
	{
		DWORD subKeyCnt = 0, valueCnt = 0,
				maxKeyLen = 0, maxValueLen = 0;
		RegQueryInfoKey(phkResult, nullptr, nullptr, nullptr, &subKeyCnt, &maxKeyLen, nullptr, &valueCnt, &maxValueLen, nullptr, nullptr, nullptr);

		for (auto i = 0u; i < subKeyCnt; ++i)
		{
			auto dataLen = maxKeyLen + 1;		// Terminal '\0'.
			unique_ptr<char> p(new char[dataLen]);
			RegEnumKeyEx(phkResult, i, p.get(), &dataLen, nullptr, nullptr, nullptr, nullptr);

			res.push_back(p.get());
		}

		RegCloseKey(phkResult);
	}

	return res;
}
vector<string> enumRegValue(HKEY hKey, const string &subKey)
{
	vector<string> res;

	HKEY phkResult;
	if (RegOpenKeyEx(hKey, subKey.c_str(), 0, KEY_QUERY_VALUE, &phkResult)
		== ERROR_SUCCESS)
	{
		DWORD subKeyCnt = 0, valueCnt = 0,
				maxKeyLen = 0, maxValueLen = 0;
		RegQueryInfoKey(phkResult, nullptr, nullptr, nullptr, &subKeyCnt, &maxKeyLen, nullptr, &valueCnt, &maxValueLen, nullptr, nullptr, nullptr);

		for (auto i = 0u; i < valueCnt; ++i)
		{
			auto dataLen = maxValueLen + 1;		// Terminal '\0'.
			unique_ptr<char> p(new char[dataLen]);
			RegEnumValue(phkResult, i, p.get(), &dataLen, nullptr, nullptr, nullptr, nullptr);

			res.push_back(p.get());
		}

		RegCloseKey(phkResult);
	}

	return res;
}

}