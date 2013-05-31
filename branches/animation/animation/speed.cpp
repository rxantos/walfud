

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
	++m_var;

	return static_cast<unsigned>(sin((m_var % 360) * M_PI / 180) * 20 + 30);
}
unsigned MySpeed::reset()
{
	return 0;
}