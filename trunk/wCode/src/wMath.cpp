

// wMath.cpp
// 

#include "wMath.h"
using namespace std;

namespace w
{

char digitToChar(unsigned i)
{
	int c = '\0';

	if (i < 10)
	{
		c = i + '0';
	}
	else if (i < 16)
	{
		c = (i - 10) + 'a';
	}
	else
	{}

	return static_cast<char>(c);
}
unsigned charToDigit(char c)
{
	int i = 0;

	c = static_cast<char>(tolower(c));
	if ('0' <= c && c <= '9')
	{
		i = c - '0';
	}
	else if ('a' <= c && c <= 'f')
	{
		i = c - 'a';
		i += 10;
	}
	else
	{}

	return i;
}

	//vector<pair<string, string>> v;
	//v.push_back(make_pair("4444", "4"));
	//v.push_back(make_pair("444.4", "5"));
	//v.push_back(make_pair("4444", "0.45"));
	//v.push_back(make_pair("444.4", "444.4")),
	//v.push_back(make_pair("4444.0", "4444444")),
	//v.push_back(make_pair("4444", "0.0")),
	//v.push_back(make_pair("0.1234", "0.1234")),
	//v.push_back(make_pair("0.1234", "0.12345"));

	//v.push_back(make_pair("b.f", "d.3")),
	//v.push_back(make_pair("bf", "5.1a3fc0a49b6dd625d62cab5432b5b342bca5d235c436bf54663c51d3"));

	//for (auto i : v)
	//{
	//	cout <<getIntegerPartFromDecimal(i.first) <<" : " <<getFractionPartFromDecimal(i.first) <<endl;
	//	cout <<getIntegerPartFromDecimal(i.second) <<" : " <<getFractionPartFromDecimal(i.second) <<endl;
	//}
static string getIntegerPartFromDecimal(const string &decimal)
{ return decimal.substr(0, decimal.find('.')); }
static string getFractionPartFromDecimal(const string &decimal)
{
	const size_t decimalPointPos = decimal.find('.');

	return decimalPointPos == string::npos ? "" : decimal.substr(decimalPointPos + 1, decimal.length());
}

/*
 *
 *		Compare two numbers.
 *
 *	Note:
 *		This function ignores leading '0'.
 *
 *	Example:
 *		   a              b        return value        reason
 *		-------------------------------------------------------
 *		"1234"         "12345"       'true'              <
 *		"1234"         "2234"        'true'              <
 *		"1234"         "1234"        'false'            ==
 *		"1234"         "99"          'false'             >
 *		"01234"        "1234"        'false'            ==
 *		"01234"        "01234"       'false'            ==
 *		"1234"         "01234"       'false'            ==
 *
 */
static bool unsignedIntLess(const string &a, const string &b)
{
	string::const_iterator it = find_if(a.begin(), a.end(), [](char c) -> bool { return c != '0'; }),
						   jt = find_if(b.begin(), b.end(), [](char c) -> bool { return c != '0'; });
	const size_t numLenA = distance(it, a.end()), numLenB = distance(jt, b.end());

	return numLenA < numLenB 
		   || numLenA == numLenB && lexicographical_compare(it, a.end(), jt, b.end(), [](char x, char y){ return charToDigit(x) < charToDigit(y); });
}
	//vector<pair<string, string>> v;
	//v.push_back(make_pair("4444", "4"));
	//v.push_back(make_pair("444.4", "5"));
	//v.push_back(make_pair("4444", "0.45"));
	//v.push_back(make_pair("444.4", "444.4")),
	//v.push_back(make_pair("4444.0", "4444444")),
	//v.push_back(make_pair("4444", "0.0")),
	//v.push_back(make_pair("0.1234", "0.1234")),
	//v.push_back(make_pair("0.1234", "0.12345"));

	//v.push_back(make_pair("b.f", "d.3")),
	//v.push_back(make_pair("bf", "5.1a3fc0a49b6dd625d62cab5432b5b342bca5d235c436bf54663c51d3"));
bool unsignedNumLess(const string &a, const string &b)
{
	bool res = false;

	string integerPart_a = getIntegerPartFromDecimal(a), integerPart_b = getIntegerPartFromDecimal(b);
	if (unsignedIntLess(integerPart_a, integerPart_b))
	{
		res = true;
	}
	else if (unsignedIntLess(integerPart_b, integerPart_a))
	{
		res = false;
	}
	else // integerPart_a == integerPart_b
	{
		string fractionalPart_a = getFractionPartFromDecimal(a), fractionalPart_b = getFractionPartFromDecimal(b);

		res = lexicographical_compare(fractionalPart_a.begin(), fractionalPart_a.end(), 
									  fractionalPart_b.begin(), fractionalPart_b.end());
	}

	return res;
}

/*
 *
 *		Get reference of smaller/larger one between to unsigned number string.
 *
 *	Note:
 *		'getSmallerNumRef' PREFERS TO return 'a' if 'a' == 'b', while 'getLargerNumRef' PREFERS TO return 'b' if 'a' == 'b'.
 *		If you pass 'const' arguments, then return value is constant reference, otherwise, return normal reference.
 *
 */
static string &getSmallerNumRef(string &a, string &b)
{ return unsignedNumLess(b, a) ? b : a; }
static const string &getSmallerNumRef(const string &a, const string &b)
{ return getSmallerNumRef(const_cast<string &>(a), const_cast<string &>(b)); }
static string &getLargerNumRef(string &a, string &b)
{ return unsignedNumLess(b, a) ? a : b; }
static const string &getLargerNumRef(const string &a, const string &b)
{ return getLargerNumRef(const_cast<string &>(a), const_cast<string &>(b)); }

/*
 *
 *		Unsigned integer arithmetic.
 *
 *	Note:
 *		1. The return value is denormal (maybe "000", or "00424"), and without sign ("bf-d3" == "14").
 *		2. All characters in lowercase.
 *
 */
	//vector<pair<string, string>> v;
	//v.push_back(make_pair("4444", "4")),
	//v.push_back(make_pair("4444", "4444")),
	//v.push_back(make_pair("4444", "4444444")),
	//v.push_back(make_pair("4444", "0")),
	//v.push_back(make_pair("4444", ""));			// All right but NOT recommanded.

	//v.push_back(make_pair("bf", "d3")),
	//v.push_back(make_pair("bf", "51a3fc0a49b6dd625d62cab5432b5b342bca5d235c436bf54663c51d3"));

	//for (auto i : v)
	//{
	//	cout <<unsignedInt_add_unsignedInt(i.first, i.second, 16) <<endl;
	//}
	//cout <<endl;
	//for (auto i : v)
	//{
	//	cout <<unsignedInt_add_unsignedInt(i.second, i.first, 16) <<endl;
	//}
static string unsignedInt_add_unsignedInt(const string &a, const string &b, unsigned radix)
{
	string res;
	res.reserve(max(a.length(), b.length()));
	
	int carry = 0;	
	for (string::const_reverse_iterator it = a.rbegin(), jt = b.rbegin();	// Go from most trival bit to most significant bit.
		 it != a.rend() || jt != b.rend();									// If there is any more number in high bit, goes on.
		 it += it == a.rend() ? 0 : 1, jt += jt == b.rend() ? 0 : 1)		// If not end, move forward.
	{
		int iA = it == a.rend() ? 0 : charToDigit(*it),
			iB = jt == b.rend() ? 0 : charToDigit(*jt);

		int iC = iA + iB + carry;
		carry = iC / radix;
		iC %= radix;

		res.push_back(digitToChar(iC));
	}

	// If any carry.
	if (carry != 0)
	{
		res.push_back(digitToChar(carry));
		carry = 0;
	}
	
	reverse(res.begin(), res.end());
	return res;
}
static string unsignedInt_mul_unsignedChar(const string &a, unsigned char b, unsigned radix)
{
	string res;

	int carry = 0;
	for (auto it = a.rbegin(); it != a.rend(); ++it)
	{
		int iA = charToDigit(*it),
			iB = charToDigit(b);

		int iC = iA * iB + carry;
		carry = iC / radix;
		iC %= radix;

		res.push_back(digitToChar(iC));
	}

	if (carry != 0)
	{
		res.push_back(digitToChar(carry));
		carry = 0;
	}

	reverse(res.begin(), res.end());
	return res;
}
	//vector<pair<string, string>> v;
	//v.push_back(make_pair("4444", "4")),
	//v.push_back(make_pair("4444", "4444")),
	//v.push_back(make_pair("4444", "4444444")),
	//v.push_back(make_pair("4444", "0")),
	//v.push_back(make_pair("4444", ""));					// Compiled but may fail. (any 'xxxx_mul_yyyy("1234")' will get nothing)

	//v.push_back(make_pair("bf", "d3")),
	//v.push_back(make_pair("bf", "51a3fc0a49b6dd625d62cab5432b5b342bca5d235c436bf54663c51d3"));

	//for (auto i : v)
	//{
	//	cout <<unsignedInt_mul_unsignedInt(i.first, i.second, 16) <<endl;
	//}
	//cout <<endl;
	//for (auto i : v)
	//{
	//	cout <<unsignedInt_mul_unsignedInt(i.second, i.first, 16) <<endl;
	//}
static string unsignedInt_mul_unsignedInt(const string &a, const string &b, unsigned radix)
{
	string res;

	for (auto i : b)
	{
		string tmp = unsignedInt_mul_unsignedChar(a, i, radix);
		res = unsignedInt_add_unsignedInt(res + "0", tmp, radix);
	}

	return res;
}
	//vector<pair<string, string>> v;
	//v.push_back(make_pair("4444", "4")),
	//v.push_back(make_pair("4444", "4444")),
	//v.push_back(make_pair("4444", "4444444")),
	//v.push_back(make_pair("4444", "0")),
	//v.push_back(make_pair("4444", ""));			// All right but NOT recommanded.

	//v.push_back(make_pair("bf", "d3")),
	//v.push_back(make_pair("bf", "51a3fc0a49b6dd625d62cab5432b5b342bca5d235c436bf54663c51d3"));

	//for (auto i : v)
	//{
	//	cout <<unsignedInt_sub_unsignedInt(i.first, i.second, 16) <<endl;
	//}
	//cout <<endl;
	//for (auto i : v)
	//{
	//	cout <<unsignedInt_sub_unsignedInt(i.second, i.first, 16) <<endl;
	//}
static string unsignedInt_sub_unsignedInt(const string &a, const string &b, unsigned radix)
{
	string res;

	const string &smaller = getSmallerNumRef(a, b), 
				 &larger = getLargerNumRef(a, b);
	int carry = 0;
	for (string::const_reverse_iterator it = larger.rbegin(), jt = smaller.rbegin();	// Go from most trival bit to most significant bit.
		 it != larger.rend() || jt != smaller.rend();									// If there is any more number in high bit, goes on.
		 it += it == larger.rend() ? 0 : 1, jt += jt == smaller.rend() ? 0 : 1)			// If not end, move forward.
	{
		int iA = it == larger.rend() ? 0 : charToDigit(*it),
			iB = jt == smaller.rend() ? 0 : charToDigit(*jt);

		int iC = iA - iB + carry;
		carry = 0;
		if (iC < 0)
		{
			iC += radix;
			carry = -1;
		}

		res.push_back(digitToChar(iC));
	}

	// If 'a < b', insert a '-' int the front of 'res'.
	if (&a == &smaller
		&& a != b)
	{
		res.push_back('-');
		carry = 0;
	}
	
	reverse(res.begin(), res.end());
	return res;
}
	//vector<pair<string, string>> v;
	//v.push_back(make_pair("4444", "4"));
	//v.push_back(make_pair("4444", "5"));
	//v.push_back(make_pair("4444", "45"));
	//v.push_back(make_pair("4444", "4444")),
	//v.push_back(make_pair("4444", "4444444")),
	//v.push_back(make_pair("4444", "1"));

	//v.push_back(make_pair("bf", "d3")),
	//v.push_back(make_pair("bf", "51a3fc0a49b6dd625d62cab5432b5b342bca5d235c436bf54663c51d3"));

	//for (auto i : v)
	//{
	//	cout <<unsignedInt_div_unsignedInt(i.first, i.second, 10) <<endl;
	//}
	//cout <<endl;
	//for (auto i : v)
	//{
	//	cout <<unsignedInt_div_unsignedInt(i.second, i.first, 16) <<endl;
	//}
static string unsignedInt_div_unsignedInt(const string &a, const string &b, unsigned radix)
{
	string res;

	// Prepare. 
	vector<string> floors;
	floors.push_back("");				// '[0]' is invalid floor, should not be used.
	for (unsigned i = 1; i < radix; ++i)
	{
		floors.push_back(unsignedInt_mul_unsignedChar(b, digitToChar(i), radix));
	}

	string dividend = a.substr(0, b.length());
	size_t i = b.length() - 1; 
	while (i < a.length())
	{
		// Try divisor from 'floors'.
		bool foundDivisor = false;
		for (unsigned j = radix - 1; j > 0; --j)
		{
			const string &floor = floors[j];
			if (!unsignedIntLess(dividend, floor))
			{
				// Find a valid divisor.
				dividend = unsignedInt_sub_unsignedInt(dividend, floor, radix);
				res.push_back(digitToChar(j));
				foundDivisor = true;

				break;
			}
		}
		if (!foundDivisor)
		{
			res.push_back(digitToChar(0));
		}

		if (++i < a.length())
		{
			dividend = strTrimLeft(dividend, "0") + a[i];
		}
	}

	return res.empty() ? "0" : res;
}

/*
 *
 *		Unsigned decimal arithmetic.
 *
 */
	//vector<pair<string, string>> v;
	//v.push_back(make_pair("4444", "4"));
	//v.push_back(make_pair("444.4", "5"));
	//v.push_back(make_pair("4444", "0.45"));
	//v.push_back(make_pair("444.4", "444.4")),
	//v.push_back(make_pair("4444.0", "4444444")),
	//v.push_back(make_pair("4444", "0.0"));

	//v.push_back(make_pair("b.f", "d.3")),
	//v.push_back(make_pair("bf", "5.1a3fc0a49b6dd625d62cab5432b5b342bca5d235c436bf54663c51d3"));

	//for (auto i : v)
	//{
	//	cout <<unsigned_add_unsigned(i.first, i.second, 16) <<endl;
	//}
	//cout <<endl;
	//for (auto i : v)
	//{
	//	cout <<unsigned_add_unsigned(i.second, i.first, 16) <<endl;
	//}
static string unsigned_add_unsigned(const string &a, const string &b, unsigned radix)
{
	string res;

	string fractionalCarry;
	// Fractional part.
	{
		string fractionalPart_a = getFractionPartFromDecimal(a), fractionalPart_b = getFractionPartFromDecimal(b);

		// Fractional part alignment.
		fractionalPart_a.resize(max(fractionalPart_a.length(), fractionalPart_b.length()), '0'),
		fractionalPart_b.resize(max(fractionalPart_a.length(), fractionalPart_b.length()), '0');

		// Save fractional part result and carry information.
		string fractionalPart_res = unsignedInt_add_unsignedInt(fractionalPart_a, fractionalPart_b, radix);
		if (fractionalPart_a.length() < fractionalPart_res.length())
		{
			fractionalCarry = "1";
			res = fractionalPart_res.substr(1, fractionalPart_res.length());
		}
		else
		{
			fractionalCarry = "0";
			res = fractionalPart_res.substr(0, fractionalPart_res.length());
		}
	}

	// Integer part.
	{
		string integerPart_a = getIntegerPartFromDecimal(a), integerPart_b = getIntegerPartFromDecimal(b);

		// Combine with fractional part.
		string integerPart_res = unsignedInt_add_unsignedInt(integerPart_a, integerPart_b, radix);
		res = unsignedInt_add_unsignedInt(integerPart_res, fractionalCarry, radix) + "." + res;
	}

	return res;
}
	//vector<pair<string, string>> v;
	//v.push_back(make_pair("4444", "4"));
	//v.push_back(make_pair("444.4", "5"));
	//v.push_back(make_pair("4444", "0.45"));
	//v.push_back(make_pair("444.4", "444.4")),
	//v.push_back(make_pair("4444.0", "4444444")),
	//v.push_back(make_pair("4444", "0.0"));

	//v.push_back(make_pair("b.f", "d.3")),
	//v.push_back(make_pair("bf", "5.1a3fc0a49b6dd625d62cab5432b5b342bca5d235c436bf54663c51d3"));

	//for (auto i : v)
	//{
	//	cout <<unsigned_mul_unsigned(i.first, i.second, 16) <<endl;
	//}
	//cout <<endl;
	//for (auto i : v)
	//{
	//	cout <<unsigned_mul_unsigned(i.second, i.first, 16) <<endl;
	//}
static string unsigned_mul_unsigned(string a, string b, unsigned radix)
{
	string res;

	// Find decmal point.
	string::iterator decimalPointPos_a = find(a.begin(), a.end(), '.'), decimalPointPos_b = find(b.begin(), b.end(), '.');
	const size_t decimalLen_a = distance(decimalPointPos_a + (decimalPointPos_a == a.end() ? 0 : 1), a.end()), 
				 decimalLen_b = distance(decimalPointPos_b + (decimalPointPos_b == b.end() ? 0 : 1), b.end());

	// Erase decimal point.
	a.erase(decimalPointPos_a), b.erase(decimalPointPos_b);

	// Multiple as integer.
	res = unsignedInt_mul_unsignedInt(a, b, radix);

	// Insert decimal point.
	res.insert(res.length() - (decimalLen_a + decimalLen_b), ".");

	return res;
}
	//vector<pair<string, string>> v;
	//v.push_back(make_pair("4444", "4"));
	//v.push_back(make_pair("444.4", "5"));
	//v.push_back(make_pair("4444", "0.45"));
	//v.push_back(make_pair("444.4", "444.4")),
	//v.push_back(make_pair("4444.0", "4444444")),
	//v.push_back(make_pair("4444", "0.0")),
	//v.push_back(make_pair("0.1234", "0.1234")),
	//v.push_back(make_pair("0.1234", "0.12345"));

	//v.push_back(make_pair("b.f", "d.3")),
	//v.push_back(make_pair("bf", "5.1a3fc0a49b6dd625d62cab5432b5b342bca5d235c436bf54663c51d3"));
static string unsigned_sub_unsigned(string a, string b, unsigned radix)
{
	string res;

	// Fractional part align.
	string fractionPart_a = getFractionPartFromDecimal(a), fractionPart_b = getFractionPartFromDecimal(b);
	fractionPart_a.resize(max(fractionPart_a.length(), fractionPart_b.length()), '0'), 
	fractionPart_b.resize(max(fractionPart_a.length(), fractionPart_b.length()), '0');

	// Combine new dicimal.
	a = getIntegerPartFromDecimal(a) + fractionPart_a;
	b = getIntegerPartFromDecimal(b) + fractionPart_b;

	// Decimal point.
	res = unsignedInt_sub_unsignedInt(a, b, radix);
	res.insert(res.length() - max(fractionPart_a.length(), fractionPart_b.length()), ".");

	return res;
}
	//vector<pair<string, string>> v;
	//v.push_back(make_pair("4444", "4"));
	//v.push_back(make_pair("444.4", "5"));
	//v.push_back(make_pair("4444", "0.45"));
	//v.push_back(make_pair("444.4", "444.4")),
	//v.push_back(make_pair("4444.0", "4444444")),
	//v.push_back(make_pair("4444", "0.0")),			// CAUTION: Divide zero is undefined!
	//v.push_back(make_pair("0.1234", "0.1234")),
	//v.push_back(make_pair("0.1234", "0.12345"));

	//for (auto i : v)
	//{
	//	cout <<unsigned_div_unsigned(i.first, i.second, 4, 10) <<endl;
	//}
	//cout <<endl;
	//for (auto i : v)
	//{
	//	cout <<unsigned_div_unsigned(i.second, i.first, 4, 10) <<endl;
	//}
static string unsigned_div_unsigned(string a, string b, unsigned precision, unsigned radix)
{
	string res;

	// Fractional part align.
	string fractionPart_a = getFractionPartFromDecimal(a), fractionPart_b = getFractionPartFromDecimal(b);
	fractionPart_a.resize(fractionPart_b.length() + precision, '0');

	// Combine new dicimal.
	a = getIntegerPartFromDecimal(a) + fractionPart_a;
	b = getIntegerPartFromDecimal(b) + fractionPart_b;

	// Decimal point.
	res = unsignedInt_div_unsignedInt(a, b, radix);
	if (res.length() < precision)
	{
		// "0.xxxxx".
		reverse(res.begin(), res.end());
		res.resize(precision, '0');
		res += ".0";
		reverse(res.begin(), res.end());
	}
	else
	{
		res.insert(res.length() - precision, ".");
	}

	return res;
}

}