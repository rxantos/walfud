

// wMath.h
//

#ifndef W_MATH_H
#define W_MATH_H

#include "wCppExt.h"

namespace w
{

/*
 *
 *		Switch between digit and single character.
 *
 *	Note:
 *		Only support within hexidicimal.
 *
 */
	//vector<int> digits;
	//digits.push_back(0),
	//digits.push_back(1),
	//digits.push_back(5),
	//digits.push_back(9),

	//digits.push_back(10),
	//digits.push_back(13),
	//digits.push_back(15),

	//digits.push_back(16),
	//digits.push_back(2000);

	//for (auto i : digits)
	//{
	//	cout <<digitToChar(i) <<endl;
	//}
char digitToChar(unsigned i);
	//vector<char> digits;
	//digits.push_back('0'),
	//digits.push_back('1'),
	//digits.push_back('5'),
	//digits.push_back('9'),

	//digits.push_back('a'),
	//digits.push_back('c'),
	//digits.push_back('f'),

	//digits.push_back('q'),
	//digits.push_back('@');

	//for (auto i : digits)
	//{
	//	cout <<charToDigit(i) <<endl;
	//}
unsigned charToDigit(char c);

/*
 *
 *		Standardize a number.
 *
 *	Param:
 *		'alwaysSign': if 'true', all return value will have a sign symbol, even zero (will be "+0" or "-0");
 *	otherwise, only negative value will have leading "-".
 *
 *	Note:
 *		Erase trivial leading/tailing zero: "001234" => "1234", "0.1234000" => "0.1234".
 *		Erase trivial decimal point: "1234.0" => "1234", "0.0" => "0".
 *
 *		Add non-trivial zero and decimal piont: ".1234" => "0.1234".
 *		
 */
	//vector<string> standardizeNum_tester;
	//standardizeNum_tester.push_back("1234");
	//standardizeNum_tester.push_back("001234");
	//standardizeNum_tester.push_back("123400");
	//standardizeNum_tester.push_back("12.34");
	//standardizeNum_tester.push_back("1234.");
	//standardizeNum_tester.push_back(".1234");
	//standardizeNum_tester.push_back("1234.12340");
	//standardizeNum_tester.push_back("1234.000");
	//standardizeNum_tester.push_back("000.1234");
	//standardizeNum_tester.push_back("0");
	//standardizeNum_tester.push_back("0.0");
	//standardizeNum_tester.push_back("000.000");
	//standardizeNum_tester.push_back("");

	//standardizeNum_tester.push_back("+1234");
	//standardizeNum_tester.push_back("+12.34");
	//standardizeNum_tester.push_back("+1234.");
	//standardizeNum_tester.push_back("+.1234");
	//standardizeNum_tester.push_back("+1234.12340");
	//standardizeNum_tester.push_back("+1234.000");
	//standardizeNum_tester.push_back("+000.1234");
	//standardizeNum_tester.push_back("+0");
	//standardizeNum_tester.push_back("+0.0");
	//standardizeNum_tester.push_back("+000.000");
	//standardizeNum_tester.push_back("+");

	//standardizeNum_tester.push_back("-1234");
	//standardizeNum_tester.push_back("-12.34");
	//standardizeNum_tester.push_back("-1234.");
	//standardizeNum_tester.push_back("-.1234");
	//standardizeNum_tester.push_back("-1234.12340");
	//standardizeNum_tester.push_back("-1234.000");
	//standardizeNum_tester.push_back("-000.1234");
	//standardizeNum_tester.push_back("-0");
	//standardizeNum_tester.push_back("-0.0");
	//standardizeNum_tester.push_back("-000.000");
	//standardizeNum_tester.push_back("-");

	//for (auto i : standardizeNum_tester)
	//{
	//	cout <<i <<" : " <<standardizeNum(i) <<endl;
	//}
	//cout <<endl;
	//for (auto i : standardizeNum_tester)
	//{
	//	cout <<i <<" : " <<standardizeNum(i, true) <<endl;
	//}
std::string standardizeNum(std::string num, bool alwaysSign = false);

/*
 *
 *		Basic arithmetic on two strings, witch can be any length.
 *
 */
	//unordered_multimap<string, string> m;
	//m.insert(make_pair("12345678", "9"));
	//m.insert(make_pair("12345678", "+9"));
	//m.insert(make_pair("12345678", "-9"));

	//m.insert(make_pair("999", "0"));
	//m.insert(make_pair("999", "+0"));
	//m.insert(make_pair("999", "-0"));
	//m.insert(make_pair("1234.5678", "0.0"));
	//m.insert(make_pair("1234.5678", "+0.0"));
	//m.insert(make_pair("1234.5678", "-0.0"));

	//m.insert(make_pair("999", "9"));
	//m.insert(make_pair("1234.5678", "0.99"));
	//m.insert(make_pair("1234.5678", "0.00009"));

	//m.insert(make_pair("+1234", "+1"));
	//m.insert(make_pair("+1234", "-1"));
	//m.insert(make_pair("-1234", "+1"));
	//m.insert(make_pair("-1234", "-1"));

	//for (auto i : m)
	//{
	//	cout <<setw(10) <<i.first <<" + " <<setw(7) <<i.second <<" == " <<add(i.first, i.second) <<" <=> " <<add(i.second, i.first) <<endl;
	//}
std::string add(std::string a, std::string b, unsigned radix = 10);
	//unordered_multimap<string, string> m;
	//m.insert(make_pair("12345678", "9"));
	//m.insert(make_pair("12345678", "+9"));
	//m.insert(make_pair("12345678", "-9"));

	//m.insert(make_pair("999", "0"));
	//m.insert(make_pair("999", "+0"));
	//m.insert(make_pair("999", "-0"));
	//m.insert(make_pair("1234.5678", "0.0"));
	//m.insert(make_pair("1234.5678", "+0.0"));
	//m.insert(make_pair("1234.5678", "-0.0"));

	//m.insert(make_pair("999", "9"));
	//m.insert(make_pair("1234.5678", "0.99"));
	//m.insert(make_pair("1234.5678", "0.00009"));

	//m.insert(make_pair("+1234", "+1"));
	//m.insert(make_pair("+1234", "-1"));
	//m.insert(make_pair("-1234", "+1"));
	//m.insert(make_pair("-1234", "-1"));

	//for (auto i : m)
	//{
	//	cout <<setw(10) <<i.first <<" - " <<setw(7) <<i.second <<" == " <<sub(i.first, i.second) <<" <=> " <<sub(i.second, i.first) <<endl;
	//}
std::string sub(std::string a, std::string b, unsigned radix = 10);
	//unordered_multimap<string, string> m;
	//m.insert(make_pair("12345678", "9"));
	//m.insert(make_pair("12345678", "+9"));
	//m.insert(make_pair("12345678", "-9"));

	//m.insert(make_pair("999", "0"));
	//m.insert(make_pair("999", "+0"));
	//m.insert(make_pair("999", "-0"));
	//m.insert(make_pair("1234.5678", "0.0"));
	//m.insert(make_pair("1234.5678", "+0.0"));
	//m.insert(make_pair("1234.5678", "-0.0"));

	//m.insert(make_pair("999", "9"));
	//m.insert(make_pair("1234.5678", "0.99"));
	//m.insert(make_pair("1234.5678", "0.00009"));

	//m.insert(make_pair("+1234", "+1"));
	//m.insert(make_pair("+1234", "-1"));
	//m.insert(make_pair("-1234", "+1"));
	//m.insert(make_pair("-1234", "-1"));

	//for (auto i : m)
	//{
	//	cout <<setw(10) <<i.first <<" * " <<setw(7) <<i.second <<" == " <<mul(i.first, i.second) <<" <=> " <<mul(i.second, i.first) <<endl;
	//}
std::string mul(std::string a, std::string b, unsigned radix = 10);
	//unordered_multimap<string, string> m;
	//m.insert(make_pair("12345678", "9"));
	//m.insert(make_pair("12345678", "+9"));
	//m.insert(make_pair("12345678", "-9"));

	//m.insert(make_pair("999", "9"));
	//m.insert(make_pair("1234.5678", "0.99"));
	//m.insert(make_pair("1234.5678", "0.00009"));

	//m.insert(make_pair("+1234", "+1"));
	//m.insert(make_pair("+1234", "-1"));
	//m.insert(make_pair("-1234", "+1"));
	//m.insert(make_pair("-1234", "-1"));

	//for (auto i : m)
	//{
	//	cout <<setw(10) <<i.first <<" / " <<setw(7) <<i.second <<" == " <<div(i.first, i.second) <<" <=> " <<div(i.second, i.first) <<endl;
	//}
std::string div(std::string a, std::string b, unsigned radix = 10, unsigned precision = 6);

}

#endif // W_MATH_H