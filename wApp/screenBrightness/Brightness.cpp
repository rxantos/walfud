

// Brightness.cpp
//

#include "stdafx.h"
#include "Brightness.h"
#include <cmath>
using namespace std;

// Unit translation.
static time_t h2m(time_t h) { return h * 60; }
static time_t h2s(time_t h) { return h * 60 * 60; }
static time_t m2s(time_t m) { return m * 60; }

static time_t s2m(time_t s) { return s / 60; }
static time_t s2h(time_t s) { return s / 60 / 60; }
static time_t m2h(time_t m) { return m / 60; }

// Day or night.
static bool isDay(time_t secondInDay) { return secondInDay < 60*60*24/2; }
static bool isNight(time_t secondInDay) { return !isDay(secondInDay); }


// MyBrightness.
MyBrightness::MyBrightness()
{}
MyBrightness::~MyBrightness()
{}

// Interface.
unsigned MyBrightness::getVal()
{
	double val = 0;

	time_t t = getSecond();
	tm *lt = localtime(&t);

	time_t s = lt->tm_sec,
		   m = lt->tm_min,
		   h = lt->tm_hour;
	if (0 <= h && h < 12)
	{
		// Is day time( [0, 12) in hour ).
		val = static_cast<unsigned>(30 + (-cos(M_PI * h / 12) + 1) * 50);
	}
	else
	{
		// Is night( [12, 24) in hour ).
		val = static_cast<unsigned>((5/48) * h*h - (25/6) * h + 100);
	}

OutputDebugString(("-" + to_string(val) + "=" + to_string(h)).c_str());
	return val;
}

// private.
time_t MyBrightness::getSecond()
{ return time(nullptr) % (60*60*24); }