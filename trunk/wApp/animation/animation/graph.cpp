

// graph.cpp
//

#include "../stdafx.h"
#include "graph.h"

MyGraph::MyGraph(HDC dc, COLORREF color) : m_hDc(dc), m_color(color)
{}
MyGraph::~MyGraph()
{}

// Interface.
void MyGraph::draw()
{
	SetPixel(m_hDc, m_trackCenter.x, m_trackCenter.y, m_color);
}
void MyGraph::rotate()
{}
void MyGraph::zoom()
{}

void MyGraph::setDC(HDC dc)
{
	m_hDc = dc;
}

Coordinate_2D MyGraph::setCoordinate(const Coordinate_2D &newCenter)
{
	Coordinate_2D old = m_trackCenter;

	m_trackCenter = newCenter;

	return old;
}
Coordinate_2D MyGraph::getCoordinate() const
{ return m_trackCenter; }