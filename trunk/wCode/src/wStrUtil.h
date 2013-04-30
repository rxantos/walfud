

// wStrUtil.h
// 2012/11/8

#ifndef W_STRING_UTILITY_H
#define W_STRING_UTILITY_H

#include "wCppExt.h"

namespace w
{

/*
 *
 *		Trim string.
 *
 *	Param:
 *		'str': The string want to trim.
 *		'delim': The string to be erased from 'src'.
 *
 *	Rtn:
 *		The copy of trimed string.
 *
 */
	//// 'strTrim'.
	//// '-' is delimiter.
	//vector<string> strTrim_tester;
	//strTrim_tester.push_back("-1234");
	//strTrim_tester.push_back("--1234");
	//strTrim_tester.push_back("01234-");
	//strTrim_tester.push_back("01234--");
	//strTrim_tester.push_back("012-4");
	//strTrim_tester.push_back("-");
	//strTrim_tester.push_back("--");
	//strTrim_tester.push_back("");
	//strTrim_tester.push_back("-1234-678--9-");
	//strTrim_tester.push_back("01234");

	//for (vector<string>::const_iterator it = strTrim_tester.begin(); it != strTrim_tester.end(); ++it)
	//{
	//	cout <<setw(15) <<*it <<" : " <<w::strTrim(*it, "-") <<endl;
	//}

	//// 'strTrimLeft'.
	//// '-#$%-' is delimiter.
	//vector<string> strTrimLeft_tester;
	//strTrimLeft_tester.push_back("-#$%-1234");
	//strTrimLeft_tester.push_back("-#$%--#$%-1234");
	//strTrimLeft_tester.push_back("01234-#$%-");
	//strTrimLeft_tester.push_back("01234-#$%--#$%-");
	//strTrimLeft_tester.push_back("012-#$%-4");
	//strTrimLeft_tester.push_back("-#$%-");
	//strTrimLeft_tester.push_back("-#$%--#$%-");
	//strTrimLeft_tester.push_back("");
	//strTrimLeft_tester.push_back("-#$%-1234-#$%-678-#$%--#$%-9-#$%-");
	//strTrimLeft_tester.push_back("01234");

	//for (vector<string>::const_iterator it = strTrimLeft_tester.begin(); it != strTrimLeft_tester.end(); ++it)
	//{
	//	cout <<setw(35) <<*it <<" : " <<w::strTrimLeft(*it, "-#$%-") <<endl;
	//}

	//// 'strTrimRight'.
	//// '-#$%-' is delimiter.
	//vector<string> strTrimRight_tester;
	//strTrimRight_tester.push_back("-#$%-1234");
	//strTrimRight_tester.push_back("-#$%--#$%-1234");
	//strTrimRight_tester.push_back("01234-#$%-");
	//strTrimRight_tester.push_back("01234-#$%--#$%-");
	//strTrimRight_tester.push_back("012-#$%-4");
	//strTrimRight_tester.push_back("-#$%-");
	//strTrimRight_tester.push_back("-#$%--#$%-");
	//strTrimRight_tester.push_back("");
	//strTrimRight_tester.push_back("-#$%");
	//strTrimRight_tester.push_back("-#$%-1234-#$%-678-#$%--#$%-9-#$%-");
	//strTrimRight_tester.push_back("01234");

	//for (vector<string>::const_iterator it = strTrimRight_tester.begin(); it != strTrimRight_tester.end(); ++it)
	//{
	//	cout <<setw(35) <<*it <<" : " <<w::strTrimRight(*it, "-#$%-") <<endl;
	//}
std::string strTrim(const std::string &str, const std::string &delim);
std::string strTrimLeft(const std::string &str, const std::string &delim);
std::string strTrimRight(const std::string &str, const std::string &delim);

/*
 *
 *		Make sure there must be a string at left/right edge of 'str'.
 *
 *	Param:
 *		'str': The string wanted to add a edge.
 *		'left/right': The edge string added to 'str'.
 *
 *	Rtn:
 *		'str' added with 'left/right'.
 *	
 *	Note:
 *		'strMakeXXX()' only make sure there is a string a the edge, if not, add to 'str', if exists, keep 'str'
 *	unchange. It say:
 *		strMakeLeft("xxxxx", "yy")   -> "xxxxxyy",
 *		strMakeLeft("xxxxxyy", "yy") -> "xxxxxyy".
 *
 */
	//const string ending = "^_^";
	//vector<string> strMakeTailing_tester;
	//strMakeTailing_tester.push_back("xxxxYYYYzzzz^_^");
	//strMakeTailing_tester.push_back("xxxxYYYYzzzz^_");
	//strMakeTailing_tester.push_back("xxxxYYYYzzzz^^");
	//strMakeTailing_tester.push_back("xxxxYYYYzzzz_^");
	//strMakeTailing_tester.push_back("xxxxYYYYzzzz^");
	//strMakeTailing_tester.push_back("xxxxYYYYzzzz");
	//strMakeTailing_tester.push_back("");
	//strMakeTailing_tester.push_back("xxxxYYYYzzzz^_^^_^");
	//strMakeTailing_tester.push_back("xxxxYYYYzzzz^__^");

	//cout <<"left:" <<endl;
	//for_each(strMakeTailing_tester.begin(), strMakeTailing_tester.end(), [&ending](const string &str){ cout <<strMakeLeft(string(str.rbegin(), str.rend()), ending) <<endl; });

	//cout <<right <<setw(30) <<"right:" <<endl;
	//for_each(strMakeTailing_tester.begin(), strMakeTailing_tester.end(), [&ending](const string &str){ cout <<setw(30) <<strMakeRight(str, ending) <<endl; });
std::string strMakeLeft(const std::string &str, const std::string &left);
std::string strMakeRight(const std::string &str, const std::string &right);

/*
 *
 *		Convert between std::string & std::wstring. Also suit to char * & wchar_t.
 *
 *	Param:
 *		'(w)str': The source string in corresponsible code format.
 *
 *	Rtn:
 *		The string in otherside code format.
 *
 *	Note:
 *		Do NOT suit to NON ASCII code.
 *
 */
	//vector<string> strToWStr_tester;
	//strToWStr_tester.push_back("asdf");
	//strToWStr_tester.push_back("1234");
	//strToWStr_tester.push_back("qwer1234");
	//strToWStr_tester.push_back("a1!@.");
	//strToWStr_tester.push_back("你好");						// Illegal.
	//strToWStr_tester.push_back("你好，世界！");				// Illegal.
	//strToWStr_tester.push_back("asdf...你好！1234	+-*/");		// Illegal.

	//for (vector<string>::const_iterator it = strToWStr_tester.begin(); it != strToWStr_tester.end(); ++it)
	//{
	//	cout <<setw(30) <<*it <<" : ";
	//	wcout <<w::strToWStr(*it);
	//	cout <<endl; 
	//}


	//vector<wstring> wStrToStr_tester;
	//wStrToStr_tester.push_back(L"asdf");
	//wStrToStr_tester.push_back(L"1234");
	//wStrToStr_tester.push_back(L"qwer1234");
	//wStrToStr_tester.push_back(L"a1!@.");
	//wStrToStr_tester.push_back(L"新建文件夹");					// Bug fixed: 17.
	//wStrToStr_tester.push_back(L"你好");						// Illegal.
	//wStrToStr_tester.push_back(L"你好，世界！");				// Illegal.
	//wStrToStr_tester.push_back(L"asdf...你好！1234	+-*/");		// Illegal.

	//for (vector<wstring>::const_iterator it = wStrToStr_tester.begin(); it != wStrToStr_tester.end(); ++it)
	//{
	//	wcout <<setw(30) <<*it <<" : ";
	//	cout <<w::wStrToStr(*it);
	//	cout <<endl; 
	//}
std::wstring strToWStr(const std::string &str);
std::string wStrToStr(const std::wstring &wstr);

/*
 *
 *		Convert between integer and string. 
 *
 *	Note:
 *		You'd bettern use 'to_string()' in C++11 instead. 
 *		More details: http://en.cppreference.com/w/cpp/string/basic_string/to_string.
 *
 */
template <typename T>
std::string numToStr(T num, unsigned radix = 10)
{
	string str;
	do
	{
		T reminder = num % radix;
		str.push_back(static_cast<char>(reminder < 10 ? reminder + '0' : reminder - 10 + 'a'));
	} while (num /= radix);

	std::reverse(str.begin(), str.end());
	return str;
}
std::string intToStr(int num, int radix = 10);
std::string unsignedToStr(unsigned num, unsigned radix = 10);

template <typename T>
T strToNum(const std::string &str, unsigned radix = 10)
{
	T t = 0;

	unsigned base = 1;
	for (std::string::const_reverse_iterator it = str.rbegin(); it != str.rend(); ++it)
	{
		t += base * charToDigit(*it);

		base *= radix;
	}

	return t;
}
int strToInt(const std::string &str, unsigned radix = 10);
unsigned strToUnsigned(const std::string &str, unsigned radix = 10);
double strToDouble(const std::string &str, unsigned radix = 10);

/*
 *
 *		Split the 'str' by 'delim', save result to a vector.
 *
 *	Param:
 *		'strBeg': Pointer to the first character.
 *		'strEnd': Pointer to one past the last character.
 *
 *	Rtn:
 *		Each item divided by 'delim'.
 *
 */
	//vector<string> strSplit_tester;
	//strSplit_tester.push_back("key=val");
	//strSplit_tester.push_back("key=");
	//strSplit_tester.push_back("=val");
	//strSplit_tester.push_back("=");
	//strSplit_tester.push_back("");
	//strSplit_tester.push_back("key==val");
	//strSplit_tester.push_back("===");
	//strSplit_tester.push_back("keyval");

	//for (auto i : strSplit_tester)
	//{
	//	//auto res = strSplit(i, '=');
	//	auto res = strSplit(i, "=");
	//	cout <<"|";
	//	for (auto j : res)
	//	{
	//		cout <<j <<"|";
	//	}
	//	cout <<endl;
	//}
std::vector<std::string> strSplit(const std::string &str, const char delim);
std::vector<std::string> strSplit(const char *strBeg, const char *strEnd, const char delim);
std::vector<std::string> strSplit(const std::string &str, const std::string &delim);
std::vector<std::string> strSplit(const char *strBeg, const char *strEnd, const char *delimBeg, const char *delimEnd);

/*
 *
 */
	//vector<pair<string, string>> strCmp_tester;
	//strCmp_tester.push_back(make_pair("abcdef", "ABCDEF"));
	//strCmp_tester.push_back(make_pair("abcdef", "ABcDEf"));
	//strCmp_tester.push_back(make_pair("aBcdEf", "ABCDEF"));
	//strCmp_tester.push_back(make_pair("aBcdEf", "AbCDeF"));
	//strCmp_tester.push_back(make_pair("abcdef1234", "ABCDEF1234"));
	//strCmp_tester.push_back(make_pair("abcdef!@#$", "ABCDEF!@#$"));
	//strCmp_tester.push_back(make_pair("", ""));

	//strCmp_tester.push_back(make_pair("aBcdEf", "ABCDE"));
	//strCmp_tester.push_back(make_pair("abcdef", "ABCDEFG"));
	//strCmp_tester.push_back(make_pair("abcdef", "ABcDE"));
	//strCmp_tester.push_back(make_pair("abcdef", "ABcDEFG"));
	//strCmp_tester.push_back(make_pair("abcdef", "ABCDEF"));
	//strCmp_tester.push_back(make_pair("abcdef", "abcde"));
	//strCmp_tester.push_back(make_pair("abcdef", "abcdefg"));
	//strCmp_tester.push_back(make_pair("abcdef", ""));

	//for (vector<pair<string, string>>::const_iterator it = strCmp_tester.begin(); it != strCmp_tester.end(); ++it)
	//{
	//	cout <<(stricmp(it->first.c_str(), it->second.c_str()) == 0) <<" -> " <<w::strICmp(it->first, it->second) <<" : " <<w::strICmp(it->second, it->first) <<endl;
	//}
bool strICmp(const std::string &a, const std::string &b);

/*
 *		
 *		Count the number of continuous string.
 *
 *	Param:
 *		'str': String to search from.
 *		'continuousStr': String to search for.
 *		'pos': Zero based index, where to begin with.
 *		'reverse': 'false' if go ahead, otherwise, go reversely.
 *
 */
unsigned strContinuousCnt(const std::string &str, 
						  const std::string &continuousStr, size_t pos, 
						  bool reverse = false);

/*
 *
 *		Is string at current position be escaped?
 *
 *	Rtn:
 *		true: If 'esc' is nullptr or there is odd escape string behind;
 *		false: Otherwise.
 *
 *	Note:
 *		For argument 'esc', you should put 'nullptr' INSTAND of '""' for no escape string.
 *
 */
bool isEscaped(const std::string &str, size_t pos, const char *esc);

/*
 *
 *		Find a substring, take escape character into account.
 *
 */
size_t strFind(const std::string &str, 
			   const std::string &toFind, size_t pos, 
			   const char *esc = nullptr, bool reverse = false);

/*
 *
 */
	////							 0         1         2         3         4         5
	////							 01234567890123456789012345678901234567890123456789
	//string strPairSide_tester = "012345<678<9_ab<<c~e>fgh_!@#$%>>>^&*()>>_____";

	//cout <<w::strPairSide(strPairSide_tester, make_pair("<", ">"), "<", 8, nullptr, true) <<endl;
	//cout <<w::strPairSide(strPairSide_tester, make_pair("<", ">"), "<", 22, nullptr, true) <<endl;
	//cout <<w::strPairSide(strPairSide_tester, make_pair("<", ">"), "<", 22, "e", true) <<endl;
	//cout <<w::strPairSide(strPairSide_tester, make_pair("<", ">"), "<", 22, "~e", true) <<endl;
	//cout <<w::strPairSide(strPairSide_tester, make_pair("<", ">"), "<", 22, "z", true) <<endl;

	//cout <<endl;

	//cout <<w::strPairSide(strPairSide_tester, make_pair("<", ">"), ">", 0, nullptr, false) <<endl;
	//cout <<w::strPairSide(strPairSide_tester, make_pair("<", ">"), ">", 0, "12345", false) <<endl;
	//cout <<w::strPairSide(strPairSide_tester, make_pair("<", ">"), ">", 0, "#$%>", false) <<endl;
	//cout <<w::strPairSide(strPairSide_tester, make_pair("<<", ">>"), ">>", 0, nullptr, false) <<endl;
	//cout <<w::strPairSide(strPairSide_tester, make_pair("<<", ">>"), ">>", 0, "$%", false) <<endl;
	//cout <<w::strPairSide(strPairSide_tester, make_pair("<<", ">>"), ">>", 0, "$%>", false) <<endl;
size_t strPairSide(const std::string &str, const std::pair<std::string, std::string> &pairStr, 
				   const std::string &toFind, size_t pos, 
				   const char *esc = nullptr, bool reverse = false);

/*
 *
 *		Find wrapper of the string indicated by 'pos'.
 *
 */
	////							   0         1         2         3         4         5
	////							   012345678901234567890123456789012345678901234567890123456789
	//// '!' is escape character.
	//string strPairAround_tester = "<beg> I miss you. ~!>!<~... </beg>";

	//pair<size_t, size_t> pos = w::strPairAround(strPairAround_tester, ">", "<", 25, "!");
	//cout <<pos.first <<" : " <<pos.second <<endl;
std::pair<size_t, size_t> strPairAround(const std::string &str, 
										const std::string &openStr, const std::string &closeStr, size_t pos, 
										const char *esc = nullptr);

/*
 *
 *		Get a random string of 'cnt' element.
 *
 */
std::string strRandom(unsigned cnt);


}

#endif // W_STRING_UTILITY_H