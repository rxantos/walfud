

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
	while ((pos = res.rfind(delim)) != string::npos
		   && pos == (res.size() - delim.size()))
	{
		res.erase(pos, delim.size());
	}

	return res;
}

string strMakeLeft(const string &str, const string &left)
{ return (str.empty() || str.length() < left.length() || str.find(left) != 0 ? left : "") + str; }
string strMakeRight(const string &str, const string &right)
{ return str + (str.empty() || str.length() < right.length() || str.rfind(right) != str.length() - right.length() ? right : ""); }

wstring strToWStr(const string &str)
{
	wstring wstr;
	wchar_t *buf = new wchar_t[str.size()];
	fill(buf, buf + str.size(), L'\0');

	if (const int size = MultiByteToWideChar(CP_ACP, 0,
											str.c_str(), static_cast<int>(str.size()), 
											buf, static_cast<int>(str.size())))
	{
		wstr.assign(buf, buf + size);
	}
	
	delete []buf;
	buf = nullptr;
	return wstr;
}
string wStrToStr(const wstring &wstr)
{
	string str;
	const size_t bufSize = wstr.length() * 4;
	char *buf = new char[bufSize];
	fill(buf, buf + bufSize, '\0');

	if (const int size = WideCharToMultiByte(CP_ACP, 0, 
											 wstr.c_str(), static_cast<int>(wstr.length()), 
											 buf, static_cast<int>(bufSize), 
											 nullptr, nullptr))
	{
		str.assign(buf, buf + size);
	}
	
	delete []buf;
	buf = nullptr;
	return str;
}

string intToStr(int num, int radix)
{ return numToStr<int>(num, radix); }
string unsignedToStr(unsigned num, unsigned radix)
{ return numToStr<unsigned>(num, radix); }

int strToInt(const string &str, unsigned radix)
{ return strToNum<int>(str, radix); }
unsigned strToUnsigned(const std::string &str, unsigned radix)
{ return strToNum<unsigned>(str, radix); }
double strToDouble(const string &str, unsigned radix)
{ return strToNum<double>(str, radix); }

vector<string> strSplit(const string &str, const char delim)
{
	vector<string> res;
	
	for (size_t partBeg = 0, partEnd = 0; partBeg < str.length(); partBeg = partEnd + 1)
	{
		partEnd = str.find(delim, partBeg);
		partEnd = partEnd == string::npos ? str.length() : partEnd;

		res.push_back(str.substr(partBeg, partEnd - partBeg));

		if (partEnd == str.length() - 1)
		{
			// Tailing delimiter.
			res.push_back(string());
		}
	}

	return res;
}
vector<string> strSplit(const char *strBeg, const char *strEnd, const char delim)
{ return strSplit(string(strBeg, strEnd), delim); }
vector<string> strSplit(const string &str, const string &delim)
{
	vector<string> res;
	
	for (size_t partBeg = 0, partEnd = 0; partBeg < str.length(); partBeg = partEnd + 1)
	{
		partEnd = str.find(delim, partBeg);
		partEnd = partEnd == string::npos ? str.length() : partEnd;

		res.push_back(str.substr(partBeg, partEnd - partBeg));

		if (partEnd == str.length() - 1)
		{
			// Tailing delimiter.
			res.push_back(string());
		}
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

unsigned strContinuousCnt(const string &str, 
						  const string &continuousStr, size_t pos, 
						  bool reverse)
{
	unsigned cnt = 0;

	while (0 <= pos && pos < str.length())
	{
		if (str.substr(pos, continuousStr.length()) == continuousStr)
		{
			pos += reverse ? -1*continuousStr.length() : continuousStr.length();

			++cnt;
		}
		else
		{
			break;
		}
	}

	return cnt;
}

bool isEscaped(const string &str, size_t pos, const char *esc)
{ return esc != nullptr && strContinuousCnt(str, esc, pos - strlen(esc), true) % 2 == 1; }

size_t strFind(const string &str, 
			   const string &toFind, size_t pos, 
			   const char *esc, bool reverse)
{
	bool found = false;

	for (; 0 <= pos && pos < str.length(); pos += reverse ? -1 : 1)
	{
		if (str.substr(pos, toFind.length()) == toFind)
		{
			// 'str[pos]' contains 'toFind', but is it be escaped?
			if (!isEscaped(str, pos, esc))
			{
				// NOT escaped.
				// Real 'toFind' is here.
				found = true;
				break;
			}//if (esc
		}//if (str.substr
	}

	return found ? pos : str.length();
}

size_t strPairSide(const string &str, const pair<string, string> &pairStr, 
				   const string &toFind, size_t pos, 
				   const char *esc, bool reverse)
{
	bool found = false;

	const string &openStr = pairStr.first,
				 &closeStr = pairStr.second;
	for (unsigned openCnt = 0, closeCnt = 0; 0 <= pos && pos < str.length(); )
	{
		if (isEscaped(str, pos, esc))
		{
			pos += reverse ? -1 : 1;
			continue;
		}

		// 
		if (str.substr(pos, toFind.length()) == toFind)
		{
			if (openCnt == closeCnt)
			{
				// Get the first unpaired boundary string.
				found = true;
				break;
			}
		}

		// 
		if (str.substr(pos, openStr.length()) == openStr)
		{
			++openCnt;
			pos += reverse ? -1*openStr.length() : openStr.length();
		}
		else if (str.substr(pos, closeStr.length()) == closeStr)
		{
			++closeCnt;
			pos += reverse ? -1*closeStr.length() : closeStr.length();
		}
		else
		{
			pos += reverse ? -1 : 1;
		}		
	}//for (unsigned openCnt

	return found ? pos : str.length();
}

pair<size_t, size_t> strPairAround(const string &str, 
								   const string &openStr, const string &closeStr, size_t pos, 
								   const char *esc)
{
	size_t openSidePos = strPairSide(str, make_pair(openStr, closeStr), openStr, pos, esc, true);
	return make_pair(openSidePos == str.length() ? openSidePos : openSidePos + 1, 
					 strPairSide(str, make_pair(openStr, closeStr), closeStr, pos, esc, false));
}

string strRandom(unsigned cnt)
{
	string meaningless(cnt, '\0');

	static default_random_engine dre;
	uniform_int_distribution<char> nd('a', 'z');

	for (unsigned i = 0; i < 100; ++i)
	{
		meaningless.push_back(nd(dre));
	}

	return meaningless;
}

}