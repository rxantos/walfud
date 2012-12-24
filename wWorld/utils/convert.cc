

// convert.h
// 

#include "utilsConst.h"
#include "../infrastructure/exception.h"
#include <algorithm>

char numToChar(const unsigned num, const unsigned base)
{
	if (num >= base || num >= gc_maxBase)
	{
		// We support only within 16.
		throw exception_overflow(num);
	}

	return num < 10 ? num + static_cast<int>('0') 
					: num-10 + static_cast<int>('a');
}
int charToNum(const char c, const unsigned base)
{
	int num = static_cast<int>(c);
	if ('0' <= c && c <= '9')
	{
		num -= static_cast<int>('0');
	}
	else if ('a' <= c && c <= 'f')
	{
		num = num - static_cast<int>('a') + 10;
	}
	else
	{
		std::string ch;
		ch.push_back(c);
		throw exception_argument(ch);
	}

	if (num >= static_cast<int>(base))
	{
		std::string ch;
		ch.push_back(c);
		throw exception_argument(ch);
	}

	return num;
}

std::string intToStr(int decimal, const unsigned dstBase)
{
	if (dstBase > static_cast<int>(gc_maxBase))
	{
		// We support only within 16.
		throw exception_argument("dstBase should <= " 
								 + intToStr(gc_maxBase, 10));
	}

	std::string hex;

	// Treat all number as positive.
	bool negative = decimal < 0;
	if (negative)
	{
		decimal = -decimal;
	}

	// Convert to hex in std::string.
	do 
	{
		hex.push_back(numToChar(decimal % dstBase, dstBase));
	} while (decimal /= dstBase);

	if (negative)
	{
		hex.push_back('-');
	}

	reverse(hex.begin(), hex.end());
	return hex;
}
std::string doubleToStr(double decimal, const unsigned fractionLen)
{
	std::string num;

	return num;
}

int strToInt(const std::string &src, const unsigned srcBase)
{
	int res = 0;

	bool negative = false;
	if (src[0] == '-')
	{
		negative = true;
	}

	for_each(src.begin() + (negative ? 1 : 0), src.end(), 
			 [&res, srcBase](const char &c)
			 { res = res * static_cast<int>(srcBase)
			 			 + charToNum(c, srcBase); });

	return negative ? -res : res;
}

///////////////////////////////////////////////////////////////////////////////

std::string bToD(const std::string &bin)
{ return intToStr(strToInt(bin, 2), 10); }
std::string bToH(const std::string &bin)
{ return intToStr(strToInt(bin, 2), 16); }
std::string dToB(const std::string &decimal)
{ return intToStr(strToInt(decimal, 10), 2); }
std::string dToH(const std::string &decimal)
{ return intToStr(strToInt(decimal, 10), 16); }
std::string hToB(const std::string &hex)
{ return intToStr(strToInt(hex, 16), 2); }
std::string hToD(const std::string &hex)
{ return intToStr(strToInt(hex, 16), 10); }
