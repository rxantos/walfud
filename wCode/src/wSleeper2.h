

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
	virtual void sleep(int ms, int id = 0) = 0;
	virtual void wakeup(int id = 0) = 0;
	virtual void wakeupAll() = 0;
};

/**
 *		Framework provide task management facility.
 *		You just need to following the method below:
			1, You main class inherit the `SleeperBase2`, such as `Sleeper2`.
				1.1, implement `Sleeper::createBlocker` / `Sleeper::destroyBlocker`. 
				The former is to create and intialize a blocker object; the latter function give you a chance to release the resource. 
			2, An inner class inherit the `SleeperBase2Blocker`, such as `Blocker`.
				2.1, implement `Blocker::sleep` / `Blocker::wakeup`, which is to block execution and stop blocking function.

		Now, you can use class `Sleep` to sleep and time and wake up by id. 
		Enjoy it.
 *
 */
class SleeperBase2 : public ISleeper2
{
public:
	struct SleeperBase2Blocker
	{
		int id = 0;
		int time = 0;

		virtual ~SleeperBase2Blocker() = 0 {}

		virtual void sleep() = 0;
		virtual void wakeup() = 0;
	};
private:
	// data.
	std::list<SleeperBase2Blocker *> m_blocker;
	std::mutex m_blockerMutex;

public:
	// Interface.
	virtual void sleep(int ms, int id = 0) override;
	virtual void wakeup(int id = 0) override;
	virtual void wakeupAll() override;

private:
	// logic.
	std::list<SleeperBase2Blocker *>::iterator addTask(int ms, int id);
	void removeTask(std::list<SleeperBase2Blocker *>::iterator blocker);

protected:
	virtual SleeperBase2Blocker *createBlocker(int ms, int id) = 0;
	virtual void destroyBlocker(SleeperBase2Blocker *blocker) = 0;
};

/**
 *		Sleeper based on busy loop, which is suitable for very short 
 *	period blocking.
 */
class BusySleeper2 : public SleeperBase2
{
public:
	struct BusySleeper2Blocker : SleeperBase2Blocker
	{
		std::atomic_bool sleeping;

		virtual void sleep() override;
		virtual void wakeup() override;
	};

protected:
	virtual SleeperBase2Blocker *createBlocker(int ms, int id) override;
	virtual void destroyBlocker(SleeperBase2Blocker *blocker) override;
};
/**
 *		Event sleeper is suitable for long time sleeping, since the 
 *	operation will sink into kernel, which has to switch between user
 *	mode and kernel mode.
 */
class EventSleeper2 : public SleeperBase2
{
public:
	struct EventSleeper2Blocker : SleeperBase2Blocker
	{
		HANDLE sleepEvent;
		std::atomic_bool sleeping;

		virtual void sleep() override;
		virtual void wakeup() override;
	};

protected:
	virtual SleeperBase2Blocker *createBlocker(int ms, int id) override;
	virtual void destroyBlocker(SleeperBase2Blocker *blocker) override;
};

}

#endif // W_SLEEPER2_H