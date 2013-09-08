

// track.h
//

#ifndef TRACK_H
#define TRACK_H

#include "coordinate.h"

template <typename D>
class Track
{
protected:
	// data.

public:
	virtual ~Track() {}

public:
	// Interface.
	virtual D prev() = 0;
	virtual D next() = 0;
	virtual D reset() = 0;

	virtual Track *clone() const = 0;

protected:
	// logic.
};
template <typename D>
class Track2 : virtual public Track<Coordinate_2D>
{
public:
	virtual bool isCycleDone() = 0;
};

class MyTrack : virtual public Track<Coordinate_2D>
{
protected:
	// data.
	Coordinate_2D m_trackCenter;

public:
	MyTrack();
	virtual ~MyTrack();

public:
	// Interface.
	virtual Coordinate_2D prev() override;
	virtual Coordinate_2D next() override;
	virtual Coordinate_2D reset() override { return m_trackCenter; }

	virtual Track *clone() const override { auto _type(*this); return new decltype(_type)(*this); }

protected:
	// logic.
};
class MyTrack2 : public Track2<Coordinate_2D>, public MyTrack
{
protected:
	// data.
	bool m_cycleDone;				// When a whole cycle is done, the value is `true`, otherwise is 'false'.
	unsigned m_step;

public:
	MyTrack2();

public:
	// Interface.
	virtual Coordinate_2D next() override;
	virtual bool isCycleDone() override { return m_cycleDone; }

	virtual Track *clone() const override { auto _type(*this); return new decltype(_type)(*this); }
};

#endif // TRACK_H