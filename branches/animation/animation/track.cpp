

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
	Coordinate_2D pos;
	return pos;
}
Coordinate_2D MyTrack::next()
{
	m_graphCenter.x += 1;
	m_graphCenter.y = static_cast<unsigned>(-cos((m_graphCenter.x % 360) * M_PI / 180) * 30 + 50);

	return m_graphCenter;
}
Coordinate_2D MyTrack::reset()
{
	Coordinate_2D pos;
	return pos;
}

// MyTrack2.
MyTrack2::MyTrack2() : MyTrack(), m_direction(0)
{}

// Interface.
Coordinate_2D MyTrack2::next()
{
	if (m_graphCenter.x == 0)
	{
		m_direction = 1;
	}
	else if (m_graphCenter.x == 360)
	{
		m_direction = -1;
	}
	else
	{}

	m_graphCenter.x += m_direction;
	m_graphCenter.y = static_cast<unsigned>(-sin((m_graphCenter.x % 360) * M_PI / 180) * m_direction * 100 + 200);


	return m_graphCenter;
}