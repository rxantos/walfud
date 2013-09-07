

// coordinate.h
//

#ifndef COORDINATE_H
#define COORDINATE_H

struct Coordinate {};
struct Coordinate_1D : public Coordinate
{
	int x;

	Coordinate_1D(unsigned a = 0) : x(a) {}
};
struct Coordinate_2D : public Coordinate_1D
{
	int y;

	Coordinate_2D(unsigned a = 0, unsigned b = 0) : Coordinate_1D(a), y(b) {}
};

#endif // COORDINATE_H