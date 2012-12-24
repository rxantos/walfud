

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
std::string intToStr(int num, int base = 10);
int strToInt(const std::string &str);

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


}

#endif // W_STRING_UTILITY_H