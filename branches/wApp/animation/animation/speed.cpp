

// speed.cpp
//

#define	_USE_MATH_DEFINES

#include "../stdafx.h"
#include "speed.h"
#include <cmath>
#include <string>
using namespace std;

MySpeed::MySpeed() : Speed(), m_var(0)
{}
MySpeed::~MySpeed()
{}

// Interface.
unsigned MySpeed::prev()
{
	return 0;
}
unsigned MySpeed::next()
{
	m_var += 1;

	return static_cast<unsigned>(cos((m_var % 360) * M_PI / 180) * 30 + 40);
}
unsigned MySpeed::reset()
{
	return 0;
}

// MySpeed2.
// Interface.
unsigned MySpeed2::next()
{
	return 10;
}