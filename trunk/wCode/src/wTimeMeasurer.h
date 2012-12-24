

// wTimeMeasurer.h
//

#ifndef W_TIME_MEASURER_H
#define W_TIME_MEASURER_H

#include "wCppExt.h"

namespace w
{

/*
 *		Used to test the performance by elapse.
 *
 *	Story:
 *		I was assigned to optimize sd 4.0 UI, for being stuck by some I/O operations.
 *		I have to measure the time used by codes.
 *											2012/10/22.
 *		The original class is not used at all, and I redesigned it today, saving me code for the 
 *	future use. That's wCode.
 *											2012/11/8
 */
class TimeMeasurer
{
	enum GRANULARITY
	{
		S,								// Second.
		MS,								// Milli-second.
		NS,								// Nano-second.
	};

	// data.
	static LARGE_INTEGER m_cnt;			// Performance counter.
	LARGE_INTEGER m_beg, m_end;

public:
	TimeMeasurer();
	~TimeMeasurer();
private:
	// No need.
	TimeMeasurer(const TimeMeasurer &other);
	TimeMeasurer &operator=(const TimeMeasurer &other);

public:
	// Interface.
	LARGE_INTEGER &begin();				// 'begin(); ... end(); ... end(); ... end(); ' can count multiple times.
	LARGE_INTEGER &end();				// 'begin() = end()' can set a new round.

	size_t s() const;
	size_t ms() const;
	size_t ns() const;

private:
	// logic.
	LARGE_INTEGER granularity(GRANULARITY g) const;
};

}

#endif // W_TIME_MEASURER_H