

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

bool eraseSign(string &num)
{
	bool res = true;

	if (!num.empty())
	{
		switch (num[0])
		{
		case '-':
			res = false;
			// Fallthrouh.
		case '+':
			num.erase(0, 1);
			break;
		default:
			break;
		}
	}

	return res;
}

string standardizeNum(string num, bool alwaysSign)
{
	bool positive = true;

	if (num.empty())
	{
		num = '0';
	}
	else
	{
		// Erase sign symbol.
		positive = eraseSign(num);

		// Divide integer part and decimal part from string.
		const size_t decimalPointPos = num.find('.');
		string integerPart = num.substr(0, decimalPointPos), 
			   fractionPart = decimalPointPos == string::npos ? "0" : num.substr(decimalPointPos + 1, num.length());
		// Erase trivial leading zero.
		integerPart = strTrimLeft(integerPart, "0");
		// Erase trivial tailing zero.
		fractionPart = strTrimRight(fractionPart, "0");
		// Combine back to string.
		integerPart = integerPart.empty() ? "0" : integerPart;
		fractionPart = fractionPart.empty() ? "" : '.' + fractionPart;
		num = integerPart + fractionPart;
	}//if (num.empty()

	// Add sign.
	// 'alwaysSign == true': "0" => "+0", "-0" => "-0", "1234" => "+1234".
	// 'alwaysSign == false': "+0" => "0", "-0" => "0", "+1234" => "1234", "-1234" => "-1234".
	if (alwaysSign)
	{
		num = (positive ? '+' : '-') + num;
	}
	else
	{
		// Only negative has leading "-".
		if (!positive && num != "0")
		{
			num = "-" + num;
		}
	}

	return num;
}

/*
 *
 *		Compare two unsigned integers.
 *
 *	Note:
 *		You should standardize parameter before calling me.
 *
 *	Example:
 *		   a              b        return value        reason
 *		-------------------------------------------------------
 *		"1234"         "12345"       'true'              <
 *		"1234"         "2234"        'true'              <
 *		"1234"         "1234"        'false'            ==
 *		"1234"         "99"          'false'             >
 *		"01234"        "1234"        'false'         undefined
 *		"01234"        "01234"       'false'         undefined
 *		"1234"         "01234"       'false'         undefined
 *
 */
static bool unsignedIntLess(string a, string b)
{
	a = standardizeNum(a), b = standardizeNum(b);

	return a.length() < b.length()
		   || a.length() == b.length() && lexicographical_compare(a.begin(), a.end(), b.begin(), b.end(), [](char x, char y){ return charToDigit(x) < charToDigit(y); }); 
}
/*
 *
 *		Compare two unsigned decimals.
 *
 *	Note:
 *		You should standardize parameter before calling me.
 *
 */
	//vector<pair<string, string>> v;
	//v.push_back(make_pair("4444", "4"));
	//v.push_back(make_pair("444.4", "5"));
	//v.push_back(make_pair("4444", "0.45"));
	//v.push_back(make_pair("444.4", "444.4")),
	//v.push_back(make_pair("0.1234", "0.1234")),
	//v.push_back(make_pair("0.1234", "0.12345"));

	//v.push_back(make_pair("b.f", "d.3")),
	//v.push_back(make_pair("bf", "5.1a3fc0a49b6dd625d62cab5432b5b342bca5d235c436bf54663c51d3"));

	//for (auto i : v)
	//{
	//	cout <<i.first <<" : " <<i.second <<" <=> " <<numLess(i.first, i.second) <<endl;
	//}
	//cout <<endl;
	//for (auto i : v)
	//{
	//	cout <<i.second <<" : " <<i.first <<" <=> " <<numLess(i.second, i.first) <<endl;
	//}
static bool unsignedNumLess(string a, string b)
{
	bool res = false;

	string integerPartA = a.substr(0, a.find('.')), integerPartB = b.substr(0, b.find('.'));
	if (unsignedIntLess(integerPartA, integerPartB))
	{
		res = true;
	}
	else if (unsignedIntLess(integerPartB, integerPartA))
	{
		res = false;
	}
	else // integerPartA == integerPartB
	{
		const size_t decimalPointPosA = a.find('.'), decimalPointPosB = b.find('.');
		string fractionPartA = decimalPointPosA == string::npos ? "0" : a.substr(decimalPointPosA + 1, a.length()), 
			   fractionPartB = decimalPointPosB == string::npos ? "0" : b.substr(decimalPointPosB + 1, b.length());

		res = unsignedIntLess(fractionPartA, fractionPartB);
	}

	return res;
}
bool numLess(string a, string b)
{
	bool res = false;

	bool positiveA = eraseSign(a), positiveB = eraseSign(b);
	if (positiveA && positiveB)
	{
		res = unsignedNumLess(a, b);
	}
	else if (positiveA && !positiveB)
	{
		res = false;
	}
	else if (!positiveA && positiveB)
	{
		res = true;
	}
	else // !positiveA && !positiveB
	{
		res = unsignedNumLess(b, a);
	}

	return res;
}

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
	//	cout <<uiAddUI(i.first, i.second, 16) <<endl;
	//}
	//cout <<endl;
	//for (auto i : v)
	//{
	//	cout <<uiAddUI(i.second, i.first, 16) <<endl;
	//}
static string uiAddUI(string a, string b, unsigned radix)
{
	string res;
	res.reserve(max(a.length(), b.length()));
	a = standardizeNum(a), b = standardizeNum(b);
	
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
	return standardizeNum(res);
}
static string uiMulUC(string a, char b, unsigned radix)
{
	string res;
	a = standardizeNum(a);

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
	return standardizeNum(res);
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
	//	cout <<uiMulUI(i.first, i.second, 16) <<endl;
	//}
	//cout <<endl;
	//for (auto i : v)
	//{
	//	cout <<uiMulUI(i.second, i.first, 16) <<endl;
	//}
static string uiMulUI(string a, string b, unsigned radix)
{
	string res;
	a = standardizeNum(a), b = standardizeNum(b);

	for (auto i : b)
	{
		string tmp = uiMulUC(a, i, radix);
		res = uiAddUI(res + "0", tmp, radix);
	}

	return standardizeNum(res);
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
	//	cout <<uiSubUI(i.first, i.second, 16) <<endl;
	//}
	//cout <<endl;
	//for (auto i : v)
	//{
	//	cout <<uiSubUI(i.second, i.first, 16) <<endl;
	//}
static string uiSubUI(string a, string b, unsigned radix)
{
	string res;
	a = standardizeNum(a), b = standardizeNum(b);

	const string &smaller = unsignedIntLess(b, a) ? b : a,
				 &larger = unsignedIntLess(b, a) ? a : b;
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
	return standardizeNum(res);
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
	//	cout <<uiDivUI(i.first, i.second, 10) <<endl;
	//}
	//cout <<endl;
	//for (auto i : v)
	//{
	//	cout <<uiDivUI(i.second, i.first, 16) <<endl;
	//}
static string uiDivUI(string a, string b, unsigned radix)
{
	string res;
	a = standardizeNum(a), b = standardizeNum(b);

	if (b == "0")
	{
		assert(false && "dividor should NOT be 0.");
	}

	// Prepare. 
	vector<string> floors;
	floors.push_back("");				// '[0]' is invalid floor, should not be used.
	for (unsigned ii = 1; ii < radix; ++ii)
	{
		floors.push_back(uiMulUC(b, digitToChar(ii), radix));
	}

	string dividend = a.substr(0, b.length());
	for (size_t i = b.length()-1; i < a.length(); )
	{
		// Try divisor from 'floors'.
		bool foundDivisor = false;
		for (unsigned j = radix - 1; j > 0; --j)
		{
			const string &floor = floors[j];
			if (!unsignedIntLess(dividend, floor))
			{
				// Find a valid divisor.
				dividend = uiSubUI(dividend, floor, radix);
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

	return standardizeNum(res);
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
	//	cout <<uAddU(i.first, i.second, 16) <<endl;
	//}
	//cout <<endl;
	//for (auto i : v)
	//{
	//	cout <<uAddU(i.second, i.first, 16) <<endl;
	//}
static string uAddU(string a, string b, unsigned radix)
{
	string res;
	a = standardizeNum(a), b = standardizeNum(b);

	string fractionCarry;
	// Fraction part.
	{
		const size_t decimalPointPosA = a.find('.'), decimalPointPosB = b.find('.');
		string fractionPartA = decimalPointPosA == string::npos ? "0" : a.substr(decimalPointPosA + 1, a.length()), 
			   fractionPartB = decimalPointPosB == string::npos ? "0" : b.substr(decimalPointPosB + 1, b.length());

		// Fraction part alignment.
		fractionPartA.resize(max(fractionPartA.length(), fractionPartB.length()), '0'),
		fractionPartB.resize(max(fractionPartA.length(), fractionPartB.length()), '0');

		// Save fraction part result and carry information.
		string fractionPart_res = uiAddUI(fractionPartA, fractionPartB, radix);
		if (fractionPartA.length() < fractionPart_res.length())
		{
			fractionCarry = "1";
			res = fractionPart_res.substr(1, fractionPart_res.length());
		}
		else
		{
			fractionCarry = "0";
			res = fractionPart_res.substr(0, fractionPart_res.length());
		}
	}

	// Integer part.
	{
		string integerPartA = a.substr(0, a.find('.')), 
			   integerPartB = b.substr(0, b.find('.'));

		// Combine with fraction part.
		string integerPart_res = uiAddUI(integerPartA, integerPartB, radix);
		res = uiAddUI(integerPart_res, fractionCarry, radix) + "." + res;
	}

	return standardizeNum(res);
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
	//	cout <<uMulU(i.first, i.second, 16) <<endl;
	//}
	//cout <<endl;
	//for (auto i : v)
	//{
	//	cout <<uMulU(i.second, i.first, 16) <<endl;
	//}
static string uMulU(string a, string b, unsigned radix)
{
	string res;
	a = standardizeNum(a), b = standardizeNum(b);

	// Find decmal point.
	string::iterator decimalPointPosA = find(a.begin(), a.end(), '.'), decimalPointPosB = find(b.begin(), b.end(), '.');
	const size_t fractionLenA = distance(decimalPointPosA + (decimalPointPosA == a.end() ? 0 : 1), a.end()), 
				 fractionLenB = distance(decimalPointPosB + (decimalPointPosB == b.end() ? 0 : 1), b.end());

	// Erase decimal point.
	a.erase(decimalPointPosA), b.erase(decimalPointPosB);
	a = standardizeNum(a), b = standardizeNum(b);

	// Multiple as integer.
	res = uiMulUI(a, b, radix);

	// Insert decimal point.
	const size_t fractionLen = fractionLenA + fractionLenB;
	if (fractionLen < res.length())
	{
		res.insert(res.length() - fractionLen, ".");
	}
	else
	{
		string filling(fractionLen - res.length(), '0');
		res = "0." + filling + res;
	}

	return standardizeNum(res);
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
static string uSubU(string a, string b, unsigned radix)
{
	string res;
	a = standardizeNum(a), b = standardizeNum(b);

	// Fractional part align.
	const size_t decimalPointPosA = a.find('.'), decimalPointPosB = b.find('.');
	string fractionPartA = decimalPointPosA == string::npos ? "0" : a.substr(decimalPointPosA + 1, a.length()), 
		   fractionPartB = decimalPointPosB == string::npos ? "0" : b.substr(decimalPointPosB + 1, b.length());
	fractionPartA.resize(max(fractionPartA.length(), fractionPartB.length()), '0'), 
	fractionPartB.resize(max(fractionPartA.length(), fractionPartB.length()), '0');

	// Combine new dicimal.
	a = a.substr(0, a.find('.')) + fractionPartA;
	b = b.substr(0, b.find('.')) + fractionPartB;

	// Decimal point.
	res = uiSubUI(a, b, radix);
	res.insert(res.length() - max(fractionPartA.length(), fractionPartB.length()), ".");

	return standardizeNum(res);
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
	//	cout <<uDivU(i.first, i.second, 4, 10) <<endl;
	//}
	//cout <<endl;
	//for (auto i : v)
	//{
	//	cout <<uDivU(i.second, i.first, 4, 10) <<endl;
	//}
static string uDivU(string a, string b, unsigned radix, unsigned precision)
{
	string res;
	a = standardizeNum(a), b = standardizeNum(b);

	// fraction part align.
	const size_t decimalPointPosA = a.find('.'), decimalPointPosB = b.find('.');
	string fractionPartA = decimalPointPosA == string::npos ? "0" : a.substr(decimalPointPosA + 1, a.length()), 
		   fractionPartB = decimalPointPosB == string::npos ? "0" : b.substr(decimalPointPosB + 1, b.length());
	fractionPartA.resize(fractionPartB.length() + precision, '0');

	// Combine new dicimal.
	a = a.substr(0, a.find('.')) + fractionPartA;
	b = b.substr(0, b.find('.')) + fractionPartB;

	// Decimal point.
	res = uiDivUI(a, b, radix);
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

	return standardizeNum(res);
}

string add(string a, string b, unsigned radix)
{
	string res;
	a = standardizeNum(a), b = standardizeNum(b);

	bool positiveA = eraseSign(a), positiveB = eraseSign(b);
	if (positiveA && positiveB)
	{
		// "(+a) + (+b)".
		res = uAddU(a, b, radix);
	}
	else if (positiveA && !positiveB)
	{
		// "(+a) + (-b)".
		res = uSubU(a, b, radix);
	}
	else if (!positiveA && positiveB)
	{
		// "(-a) + (+b)".
		res = uSubU(b, a, radix);
	}
	else // !positiveA && !positiveB
	{
		// "(-a) + (-b)".
		res = '-' + uAddU(a, b, radix);
	}

	return standardizeNum(res);
}
string sub(string a, string b, unsigned radix)
{
	string res;
	a = standardizeNum(a), b = standardizeNum(b);

	bool positiveA = eraseSign(a), positiveB = eraseSign(b);
	if (positiveA && positiveB)
	{
		// "(+a) - (+b)".
		res = uSubU(a, b, radix);
	}
	else if (positiveA && !positiveB)
	{
		// "(+a) - (-b)".
		res = uAddU(a, b, radix);
	}
	else if (!positiveA && positiveB)
	{
		// "(-a) - (+b)".
		res = '-' + uAddU(a, b, radix);
	}
	else // !positiveA && !positiveB
	{
		// "(-a) - (-b)".
		res = uSubU(b, a, radix);
	}

	return standardizeNum(res);
}
string mul(string a, string b, unsigned radix)
{
	string res;
	a = standardizeNum(a), b = standardizeNum(b);

	bool positiveA = eraseSign(a), positiveB = eraseSign(b);
	if (positiveA && positiveB
		|| !positiveA && !positiveB)
	{
		// "(+a) * (+b)" or
		// "(-a) * (-b)".
		res = uMulU(a, b, radix);
	}
	else if (positiveA && !positiveB
			 || !positiveA && positiveB)
	{
		// "(+a) * (-b)" or
		// "(-a) * (+b)".
		res = '-' + uMulU(a, b, radix);
	}
	else
	{}

	return standardizeNum(res);
}
string div(string a, string b, unsigned radix, unsigned precision)
{
	string res;
	a = standardizeNum(a), b = standardizeNum(b);

	bool positiveA = eraseSign(a), positiveB = eraseSign(b);
	if (positiveA && positiveB
		|| !positiveA && !positiveB)
	{
		// "(+a) / (+b)" or
		// "(-a) / (-b)".
		res = uDivU(a, b, radix, precision);
	}
	else if (positiveA && !positiveB
			 || !positiveA && positiveB)
	{
		// "(+a) / (-b)" or
		// "(-a) / (+b)".
		res = '-' + uDivU(a, b, radix, precision);
	}
	else
	{}

	return standardizeNum(res);
}

}