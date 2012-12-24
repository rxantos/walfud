

// wStrUtil.cc
// 

#include "wStrUtil.h"
using namespace std;

namespace w
{

string strTrim(const string &str, const string &delim)
{
	string res(str);

	size_t pos = 0;
	while ((pos = res.find(delim)) != string::npos)
	{
		res.erase(pos, delim.size());
	}

	return res;
}
string strTrimLeft(const string &str, const string &delim)
{
	string res(str);

	size_t pos = 0;
	while ((pos = res.find(delim)) == 0)
	{
		res.erase(0, delim.size());
	}

	return res;
}
string strTrimRight(const string &str, const string &delim)
{
	string res(str);

	size_t pos = 0;
	while ((pos = res.rfind(delim)) == (res.size() - delim.size()))
	{
		res.erase(pos, delim.size());
	}

	return res;
}

string strMakeLeft(const string &str, const string &left)
{ return (str.empty() || str.length() < left.length() || str.find(left) != 0 ? left : "") + str; }
string strMakeRight(const string &str, const string &right)
{ return str + (str.empty() || str.length() < right.length() || str.rfind(right) != str.length() - right.length() ? right : ""); }

std::wstring strToWStr(const std::string &str)
{
	wstring wstr;
	wchar_t *buf = new wchar_t[str.size()];
	fill(buf, buf + str.size(), L'\0');

	if (const int len = MultiByteToWideChar(CP_ACP, 0,
											str.c_str(), str.size(), 
											buf, str.size()))
	{
		wstr.assign(buf, buf + len);
	}
	
	delete []buf;
	buf = nullptr;
	return wstr;
}
std::string wStrToStr(const std::wstring &wstr)
{
	string str;
	const size_t bufLen = wstr.length() * 4;
	char *buf = new char[bufLen];
	fill(buf, buf + bufLen, '\0');

	if (const int len = WideCharToMultiByte(CP_ACP, 0, 
											wstr.c_str(), wstr.length(), 
											buf, bufLen, 
											nullptr, nullptr))
	{
		str.assign(buf, buf + len);
	}
	
	delete []buf;
	buf = nullptr;
	return str;
}

string intToStr(int num, int base)
{
	//ostringstream oss;
	//oss <<(base == 10 ? dec : base == 16 ? hex : base == 8 ? oct : ???) <<num;

	string str;
	do
	{
		int reminder = num % base;
		str.push_back(static_cast<char>(reminder < 10 ? reminder + '0' : reminder - 10 + 'a'));
	} while (num /= base);

	reverse(str.begin(), str.end());
	return str;
}
int strToInt(const string &str)
{
	int i = 0;

	istringstream iss(str);
	iss >>i;

	return i;
}

vector<string> strSplit(const string &str, const char delim)
{
	vector<string> res;
	
	size_t p = 0, q = 0;
	for (; q != str.length(); ++q)
	{
		if (str[q] == delim)
		{
			res.push_back(str.substr(p, q - p));

			p = q+1;
		}
	}
	if (p < str.length())
	{
		res.push_back(str.substr(p, q - p));
	}

	return res;
}
vector<string> strSplit(const char *strBeg, const char *strEnd, const char delim)
{ return strSplit(string(strBeg, strEnd), delim); }
vector<string> strSplit(const string &str, const string &delim)
{
	vector<string> res;
	
	size_t p = 0, q = 0;
	while ((q = str.find(delim, p)) != string::npos)
	{
		res.push_back(str.substr(p, q - p));

		p = q+1;
	}
	if (p < str.length())
	{
		res.push_back(str.substr(p, q - p));
	}

	return res;
}
vector<string> strSplit(const char *strBeg, const char *strEnd, const char *delimBeg, const char *delimEnd)
{ return strSplit(string(strBeg, strEnd), string(delimBeg, delimEnd)); }

bool strICmp(const string &a, const string &b)
{
	return !lexicographical_compare(a.begin(), a.end(), b.begin(), b.end(), [](const char a, const char b){ return tolower(a) < tolower(b); })
		   && !lexicographical_compare(b.begin(), b.end(), a.begin(), a.end(), [](const char a, const char b){ return tolower(a) < tolower(b); });
}

}