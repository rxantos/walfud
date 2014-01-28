

// wSleeper2.h
// 

#include "wSleeper2.h"
using namespace std;

namespace w
{

// SleeperBase2.
void SleeperBase2::sleep(int ms, int id)
{
	auto blocker = addTask(ms, id);
	(*blocker)->sleep();
	removeTask(blocker);
}
void SleeperBase2::wakeup(int id)
{
	lock_guard<mutex> lock(m_blockerMutex);
	for (auto &i : m_blocker)
	{
		if (i->id == id)
		{
			i->wakeup();
		}
	}
}
void SleeperBase2::wakeupAll()
{
	lock_guard<mutex> lock(m_blockerMutex);
	for (auto &i : m_blocker)
	{
		i->wakeup();
	}
}

// logic.
list<SleeperBase2::SleeperBase2Blocker *>::iterator SleeperBase2::addTask(int ms, int id)
{
	list<SleeperBase2Blocker *>::iterator res;

	lock_guard<mutex> lock(m_blockerMutex);
	m_blocker.push_back(createBlocker(ms, id));
	res = m_blocker.begin();
	advance(res, m_blocker.size() - 1);

	return res;
}
void SleeperBase2::removeTask(list<SleeperBase2Blocker *>::iterator blocker)
{
	lock_guard<mutex> lock(m_blockerMutex);

	destroyBlocker(*blocker);
	m_blocker.erase(blocker);
}

// BusySleeper2.
void BusySleeper2::BusySleeper2Blocker::sleep()
{
	auto begTime = clock();

	while (true)
	{
		// Time out.
		auto endTime = clock();
		if (endTime - begTime >= time)
		{
			break;
		}

		// Condition quit.
		if (!sleeping)
		{
			break;
		}
	}
}
void BusySleeper2::BusySleeper2Blocker::wakeup()
{
	sleeping = false;
}

BusySleeper2::SleeperBase2Blocker *BusySleeper2::createBlocker(int ms, int id)
{
	auto *p = new BusySleeper2Blocker;
	p->id = id;
	p->time = ms;
	p->sleeping = true;

	return p;
}
void BusySleeper2::destroyBlocker(SleeperBase2Blocker *blocker)
{
	delete blocker;
}

// EventSleeper2.
void EventSleeper2::EventSleeper2Blocker::sleep()
{
	sleeping = true;
	WaitForSingleObject(sleepEvent, static_cast<DWORD>(time));
}
void EventSleeper2::EventSleeper2Blocker::wakeup()
{
	SetEvent(sleepEvent);
	sleeping = false;
}

EventSleeper2::SleeperBase2Blocker *EventSleeper2::createBlocker(int ms, int id)
{
	auto *p = new EventSleeper2Blocker;
	p->id = id;
	p->time = ms;
	p->sleeping = true;
	p->sleepEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);

	return p;
}
void EventSleeper2::destroyBlocker(SleeperBase2Blocker *blocker)
{
	if (auto p = dynamic_cast<EventSleeper2Blocker *>(blocker))
	{
		CloseHandle(p->sleepEvent);
		p->sleepEvent = nullptr;
	}

	delete blocker;
}

}