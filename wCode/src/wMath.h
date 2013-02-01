

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

bool unsignedNumLess(const std::string &a, const std::string &b);

/*
 *
 *		Add two string witch can be any length.
 *
 *	Example:
 *		'add("3124312", "40149");'
 *		'add("3124312", "40149", 16);'
 *		'add("3124312", "ac", 16);'
 *		'add("3124312", "-40149");'
 *
 *		'add("0.3124312", "-401.49");'
 *		'add("0.3124312", "-401.49", 16);'
 *
 */
std::string add(const std::string &a, const std::string &b, int radix = 10);

}

#endif // W_MATH_H