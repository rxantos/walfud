

// track.h
//

#ifndef TRACK_H
#define TRACK_H

#include "coordinate.h"

template <typename D>
class Track
{
	// data.

public:
	virtual ~Track() {}

public:
	// Interface.
	virtual D prev() = 0;
	virtual D next() = 0;
	virtual D reset() = 0;

protected:
	// logic.
};

class MyTrack : public Track<Coordinate_2D>
{
protected:
	// data.
	Coordinate_2D m_graphCenter;

public:
	MyTrack();
	virtual ~MyTrack();

public:
	// Interface.
	Coordinate_2D prev();
	Coordinate_2D next();
	Coordinate_2D reset();

protected:
	// logic.
};
class MyTrack2 : public MyTrack
{
	// data.
	int m_direction;

public:
	MyTrack2();

public:
	// Interface.
	virtual Coordinate_2D next();
};

#endif // TRACK_H