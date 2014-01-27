

// wSleeper.h
// 

#ifndef W_SLEEPER2_H
#define W_SLEEPER2_H

#include "wCppExt.h"

namespace w
{

class ISleeper2
{
public:
	virtual ~ISleeper2() {}

	// Interface.
	virtual int getId() = 0;
	virtual void sleep(int ms, int id = 0) = 0;
	virtual void wakeup(int id) = 0;
	virtual void wakeupAll() = 0;
};
class SleeperBase2 : public ISleeper2
{
	// data.
	std::atomic_int m_id;

public:
	// 
	SleeperBase2();
	virtual int getId();			// Get valid id, which can pass to `sleep/wakeup` to identify the target operation.
};

class BusySleeper2 : public SleeperBase2
{
public:
	struct BusySleeper2Blocker
	{
		int id = 0;
		std::atomic_bool sleep;
		int ref = 0;

		BusySleeper2Blocker()
		{
			std::atomic_init(&sleep, false);
		}
	};
private:
	// data.
	std::list<BusySleeper2Blocker> m_blocker;
	std::mutex m_blockerMutex;

public:
	// Interface.
	virtual void sleep(int ms, int id = 0);
	virtual void wakeup(int id = 0);
	virtual void wakeupAll();

private:
	// logic.
	std::list<BusySleeper2Blocker>::iterator addTask(int id);
	void removeTask(std::list<BusySleeper2Blocker>::iterator blocker);
};

}

#endif // W_SLEEPER2_H