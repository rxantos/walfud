

// track.cpp
//

#define	_USE_MATH_DEFINES

#include "../stdafx.h"
#include "track.h"
#include <cmath>
using namespace std;

// MyTrack.
MyTrack::MyTrack()
{}
MyTrack::~MyTrack()
{}

// Interface.
Coordinate_2D MyTrack::prev()
{
	// NOT impl.
	Coordinate_2D pos;
	return pos;
}
Coordinate_2D MyTrack::next()
{
	m_trackCenter.x += 1;
	m_trackCenter.y = static_cast<unsigned>(-cos((m_trackCenter.x % 360) * M_PI / 180) * 30 + 100);

	return m_trackCenter;
}

// MyTrack2.
MyTrack2::MyTrack2() : MyTrack(), m_step(0)
{
	m_trackCenter.x = 240;
	m_trackCenter.y = 120;
}

// Interface.
Coordinate_2D MyTrack2::next()
{
	Coordinate_2D pos;

	if (0 <= m_step && m_step < 180)
	{
		pos.x = m_trackCenter.x + m_step;
		pos.y = m_trackCenter.y - static_cast<int>(sin(m_step*M_PI/180)  * 100);
	}
	else // (180 <= m_step && m_step < 360)
	{
		pos.x = m_trackCenter.x + (360 - m_step);
		pos.y = m_trackCenter.y - static_cast<int>(sin(m_step*M_PI/180)  * 100);
	}

	++m_step;
	m_step %= 360;
	m_cycleDone = m_step == 0;
	return pos;
}