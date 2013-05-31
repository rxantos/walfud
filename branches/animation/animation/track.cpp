

// track.cpp
//

#define	_USE_MATH_DEFINES

#include "../stdafx.h"
#include "track.h"
#include <cmath>
using namespace std;

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
	++m_graphCenter.x;
	m_graphCenter.y = static_cast<unsigned>(-sin((m_graphCenter.x % 360) * M_PI / 180) * 30 + 50);

	return m_graphCenter;
}
Coordinate_2D MyTrack::reset()
{
	Coordinate_2D pos;
	return pos;
}