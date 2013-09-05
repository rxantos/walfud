

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
	D m_graphCenter;

public:
	Graph() : m_graphCenter() {}
	Graph(const D &d) : m_graphCenter(d) {}
	virtual ~Graph() {}

public:
	// Interface.
	virtual void draw() = 0;
	virtual void rotate() = 0;
	virtual void zoom() = 0;

	virtual D setCoordinate(const D &d) = 0;
	virtual D getCoordinate() const = 0;

protected:
	// logic.
};

class MyGraph : public Graph<Coordinate_2D>
{
	// data.
	HDC m_hDc;
	COLORREF m_color;

public:
	MyGraph(HDC dc, COLORREF color);
	virtual ~MyGraph();

public:
	// Interface.
	virtual void draw();
	virtual void rotate();
	virtual void zoom();

	virtual Coordinate_2D setCoordinate(const Coordinate_2D &newCenter);
	virtual Coordinate_2D getCoordinate() const;

protected:
	// logic.
};

#endif // GRAPH_H