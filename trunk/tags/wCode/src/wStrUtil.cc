

// wStrUtil.cc
// 

#include "wStrUtil.h"
using namespace std;

namespace w
{

string trim(const string &str, const string &delim)
{
	string res(str);

	size_t pos = 0;
	while ((pos = res.find(delim)) != string::npos)
	{
		res.erase(pos, delim.size());
	}

	return res;
}
string trimLeft(const string &str, const string &delim)
{
	string res(str);

	size_t pos = 0;
	while ((pos = res.find(delim)) == 0)
	{
		res.erase(0, delim.size());
	}

	return res;
}
string trimRight(const string &str, const string &delim)
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

	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED,				// Beware about NON ASCII!
						str.c_str(), str.size(), 
						buf, str.size());
	wstr.assign(buf, buf + str.size());
	
	delete []buf;
	buf = nullptr;
	return wstr;
}
std::string wStrToStr(const std::wstring &wstr)
{
	string str;
	char *buf = new char[wstr.length()];
	fill(buf, buf + wstr.length(), '\0');

	WideCharToMultiByte(CP_ACP, 0, 							// Beware about NON ASCII!
						wstr.c_str(), wstr.length(), 
						buf, wstr.length(), 
						nullptr, nullptr);
	str.assign(buf, buf + wstr.size());
	
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

vector<string> strSplit(const string &str, const string &delim)
{
	vector<string> res;
	
	size_t p = 0, q = 0;
	while ((q = str.find(delim, p)) != string::npos)
	{
		res.push_back(str.substr(p, q - p));

		p = q+1;
	}

	return res;
}
vector<string> strSplit(const char *str, size_t strLen, const char *delim, size_t delimLen)
{
	return strSplit(string(str, strLen), string(delim, delimLen));
}

bool strICmp(const string &a, const string &b)
{
	return !lexicographical_compare(a.begin(), a.end(), b.begin(), b.end(), [](const char a, const char b){ return tolower(a) < tolower(b); })
		   && !lexicographical_compare(b.begin(), b.end(), a.begin(), a.end(), [](const char a, const char b){ return tolower(a) < tolower(b); });
}

}