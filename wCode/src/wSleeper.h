

// wSleeper.h
// 

#ifndef W_SLEEPER_H
#define W_SLEEPER_H

#include "wCppExt.h"

namespace w
{

class ISleeper
{
public:
	virtual ~ISleeper() = 0 {}

public:
	// Interface.
	enum class Reason : int
	{
		Default = 0,
		// Common return value.
		Suc,
		Fail,

		// Status.
		Timeout,		// I promise `sleep` has blocked your program at least some time you specified in argument.
		ExternQuit,		// The quit flag meet it's end condition, but NOT through the `wakeUp` method.
		WakeUp,			// `wakeUp` has been called. 
	};
	virtual Reason sleep(int ms) = 0;
	virtual Reason wakeUp() = 0;

	virtual Reason init(void *waiter = nullptr) = 0;
	virtual Reason uninit() = 0;
};

/**
*
*		`SleeperBase` provide an easy framework for `XxxxSleeper`.
*
*/
class SleeperBase : public ISleeper
{
	void *m_waiter = nullptr;
	bool m_ownWaiter = false;
protected:
	bool m_isWakeUp = false;

public:
	virtual Reason init(void *waiter = nullptr) override;
	virtual Reason uninit() override;

protected:
	virtual void *createWaiter() = 0;
	virtual void destroyWaiter(void *waiter) = 0;

	virtual void tranlateToChildWaiter(void *waiter) {}
};

// BusySleeper.
class BusySleeper : public SleeperBase
{
public:
	struct BusySleeperWaiter
	{
		volatile long *lQuit = nullptr;
		long quitVal = 0;
	};
private:
	BusySleeperWaiter *m_busyWaiter = nullptr;

public:
	// Interface.
	virtual Reason sleep(int ms) override;
	virtual Reason wakeUp() override;

	Reason init(volatile long *lQuit, long quitVal);

private:
	// logic.
	void reset();

	static const long sc_lQuitInit = 0, sc_lQuitVal = 1;
	virtual void *createWaiter() override;
	void *createWaiter(volatile long *lQuit, long quitVal);
	virtual void destroyWaiter(void *waiter) override;
	virtual void tranlateToChildWaiter(void *waiter) override;
};

// EventSleeper.
class EventSleeper : public SleeperBase
{
public:
	struct EventSleeperWaiter
	{
		HANDLE hQuit;
	};
private:
	EventSleeperWaiter *m_eventlWaiter;

public:
	// Interface.
	virtual Reason sleep(int ms) override;
	virtual Reason wakeUp() override;

private:
	// logic.
	virtual void *createWaiter() override;
	virtual void destroyWaiter(void *waiter) override;
	virtual void tranlateToChildWaiter(void *waiter) override;
};

}

#endif // W_SLEEPER_H