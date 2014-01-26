

// wSleeper.h
// 

#include "wSleeper.h"
using namespace std;

namespace w
{

// SleeperBase.
SleeperBase::Reason SleeperBase::init(void *waiter)
{
	// Release old resource if exists.
	if (m_ownWaiter)
	{
		destroyWaiter(m_waiter);
		m_waiter = nullptr;
	}

	// Acquire new resource.
	if (waiter == nullptr)
	{
		// Use internal quit flag.
		// Internal quit flag will manage the resource myself.
		m_waiter = createWaiter();
		m_ownWaiter = true;
	}
	else
	{
		// Use external quit flag.
		// It is caller's responsibility to make sure the validation of waiter resource while using external quit flag.
		m_waiter = waiter;
		m_ownWaiter = false;
	}

	// Translate `m_waiter` to child class's waiter, 
	// which is a equivalent variable to the former.
	tranlateToChildWaiter(m_waiter);

	return Reason::Suc;
}
SleeperBase::Reason SleeperBase::uninit()
{
	destroyWaiter(m_waiter);

	return Reason::Suc;
}

// BusySleeper.
BusySleeper::Reason BusySleeper::init(volatile long *lQuit, long quitVal)
{
	return SleeperBase::init(createWaiter(lQuit, quitVal));
}
// Interface.
BusySleeper::Reason BusySleeper::sleep(int ms)
{
	Reason reason = Reason::Default;

	reset();

	DWORD begTime = GetTickCount();
	while (true)
	{
		DWORD endTime = GetTickCount();

		if (m_busyWaiter->lQuit == nullptr)
		{
			reason = Reason::Fail;
			break;
		}
		if (InterlockedCompareExchange(m_busyWaiter->lQuit, -1, -1) == m_busyWaiter->quitVal)
		{
			if (m_isWakeUp)
			{
				// If quit by calling `wakeUp`
				reason = Reason::WakeUp;
				m_isWakeUp = false;
			}
			else
			{
				// Quit by other mehtod. NOT by this class.
				reason = Reason::ExternQuit;
			}
			break;
		}
		if (static_cast<int>(endTime - begTime) >= ms)
		{
			reason = Reason::Timeout;
			break;
		}
	}

	return reason;
}
BusySleeper::Reason BusySleeper::wakeUp()
{
	Reason reason = Reason::Default;

	if (m_busyWaiter->lQuit == nullptr)
	{
		return Reason::Fail;
	}

	m_isWakeUp = true;
	InterlockedExchange(m_busyWaiter->lQuit, m_busyWaiter->quitVal);

	return Reason::Suc;
}

// logic.
void BusySleeper::reset()
{
	m_isWakeUp = false;
}
void *BusySleeper::createWaiter()
{
	return createWaiter(nullptr, 0);
}
void *BusySleeper::createWaiter(volatile long *lQuit, long quitVal)
{
	auto p = new BusySleeperWaiter;
	if (lQuit == nullptr)
	{
		p->lQuit = new long;
		*p->lQuit = sc_lQuitInit;
		p->quitVal = sc_lQuitVal;
	}
	else
	{
		p->lQuit = lQuit;
		p->quitVal = quitVal;
	}

	return p;
}
void BusySleeper::destroyWaiter(void *waiter)
{
	auto w = (BusySleeperWaiter *)waiter;
	delete w->lQuit;
	w->lQuit = nullptr;
	delete w;
	w = nullptr;
}
void BusySleeper::tranlateToChildWaiter(void *waiter)
{
	m_busyWaiter = (BusySleeperWaiter *)waiter;
}

// EventSleeper.
EventSleeper::Reason EventSleeper::sleep(int ms)
{
	Reason reason = Reason::Default;

	switch (WaitForSingleObject(m_eventlWaiter->hQuit, static_cast<DWORD>(ms)))
	{
	case WAIT_OBJECT_0:
		if (m_isWakeUp)
		{
			reason = Reason::WakeUp;
			m_isWakeUp = false;
		}
		else
		{
			reason = Reason::ExternQuit;
		}
		break;

	case WAIT_TIMEOUT:
		reason = Reason::Timeout;
		break;

	default:
		reason = Reason::Fail;
		break;
	}

	return reason;
}
EventSleeper::Reason EventSleeper::wakeUp()
{
	Reason reason = Reason::Default;

	SetEvent(m_eventlWaiter->hQuit);

	return reason;
}

// logic.
void *EventSleeper::createWaiter()
{
	auto esw = new EventSleeperWaiter;
	esw->hQuit = CreateEvent(nullptr, TRUE, FALSE, nullptr);

	return esw;
}
void EventSleeper::destroyWaiter(void *waiter)
{
	auto esw = (EventSleeperWaiter *)waiter;
	CloseHandle(esw->hQuit);
	delete esw;
	esw = nullptr;
}
void EventSleeper::tranlateToChildWaiter(void *waiter)
{
	m_eventlWaiter = (EventSleeperWaiter *)waiter;
}

}