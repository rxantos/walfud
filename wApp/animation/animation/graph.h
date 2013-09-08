

// graph.h
//

#ifndef GRAPH_H
#define GRAPH_H

#include "coordinate.h"
#include <windows.h>

template <typename D>
class Graph
{
protected:
	// data.
	D m_trackCenter;

public:
	Graph() : m_trackCenter() {}
	Graph(const D &d) : m_trackCenter(d) {}
	virtual ~Graph() {}

public:
	// Interface.
	virtual void draw(HDC dc) = 0;
	virtual void rotate() = 0;
	virtual void zoom() = 0;

	virtual D setCoordinate(const D &d) = 0;
	virtual D getCoordinate() const = 0;

protected:
	// logic.
};

class MyGraph : public Graph<Coordinate_2D>
{
protected:
	// data.
	COLORREF m_color;

public:
	MyGraph(COLORREF color);
	virtual ~MyGraph();

public:
	// Interface.
	virtual void draw(HDC dc);
	virtual void rotate();
	virtual void zoom();

	virtual Coordinate_2D setCoordinate(const Coordinate_2D &newCenter);
	virtual Coordinate_2D getCoordinate() const;

protected:
	// logic.
};

#endif // GRAPH_H