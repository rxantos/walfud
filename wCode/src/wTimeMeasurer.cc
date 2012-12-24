

// TimeMeasurer.cc
//

#include "wTimeMeasurer.h"
using namespace std;

namespace w
{

LARGE_INTEGER TimeMeasurer::m_cnt = {};

TimeMeasurer::TimeMeasurer()
{ 
	m_beg.QuadPart = m_end.QuadPart = 0; 

	if (m_cnt.QuadPart == 0)
	{
		QueryPerformanceFrequency(&m_cnt);
	}
}
TimeMeasurer::~TimeMeasurer()
{}

// Interface.
LARGE_INTEGER &TimeMeasurer::begin()
{
	QueryPerformanceCounter(&m_beg);

	return m_beg;
}
LARGE_INTEGER &TimeMeasurer::end()
{
	QueryPerformanceCounter(&m_end);

	return m_end;
}

size_t TimeMeasurer::s() const
{ return static_cast<size_t>(granularity(TimeMeasurer::S).QuadPart); }
size_t TimeMeasurer::ms() const
{ return static_cast<size_t>(granularity(TimeMeasurer::MS).QuadPart); }
size_t TimeMeasurer::ns() const
{ return static_cast<size_t>(granularity(TimeMeasurer::NS).QuadPart); }

// logic.
LARGE_INTEGER TimeMeasurer::granularity(GRANULARITY g) const
{
	LARGE_INTEGER li = {};
	li.QuadPart = (m_end.QuadPart - m_beg.QuadPart)
				   * (g == S ? 1 : g == MS ? 1000 : g == NS ? 1000000 : m_cnt.QuadPart)
				   / (m_cnt.QuadPart);

	return li;
}

}