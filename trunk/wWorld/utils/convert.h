

// convert.h
// 

#ifndef CONVERT_H
#define CONVERT_H

#include <string>

char numToChar(const unsigned num, const unsigned base);
int charToNum(const char c, const unsigned base);

std::string intToStr(int decimal, const unsigned dstBase);
std::string doubleToStr(double decimal, const unsigned fractionLen);

int strToInt(const std::string &src, const unsigned srcBase);

///////////////////////////////////////////////////////////////////////////////

std::string bToD(const std::string &bin);
std::string bToH(const std::string &bin);
std::string dToB(const std::string &decimal);
std::string dToH(const std::string &decimal);
std::string hToB(const std::string &hex);
std::string hToD(const std::string &hex);

#endif // CONVERT_H
