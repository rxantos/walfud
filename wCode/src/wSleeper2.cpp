

// wSleeper2.h
// 

#include "wSleeper2.h"
using namespace std;

namespace w
{

// SleeperBase2.
SleeperBase2::SleeperBase2()
{
	m_id = 0;
}
int SleeperBase2::getId()
{
	return m_id.fetch_add(1) + 1;
}

// BusySleeper2.
void BusySleeper2::sleep(int ms, int id)
{
	auto begTime = clock();

	auto blocker = addTask(id);
	while (true)
	{
		// Time out.
		auto endTime = clock();
		if (endTime - begTime >= ms)
		{
			break;
		}

		// Condition quit.
		if (!blocker->sleep.load())
		{
			break;
		}
	}

	removeTask(blocker);
}
void BusySleeper2::wakeup(int id)
{
	lock_guard<mutex> lock(m_blockerMutex);
	for (auto &i : m_blocker)
	{
		if (i.id == id)
		{
			i.sleep = false;
		}		
	}
}
void BusySleeper2::wakeupAll()
{
	lock_guard<mutex> lock(m_blockerMutex);
	for (auto &i : m_blocker)
	{
		i.sleep = false;
	}
}

// logic.
list<BusySleeper2::BusySleeper2Blocker>::iterator BusySleeper2::addTask(int id)
{
	list<BusySleeper2::BusySleeper2Blocker>::iterator res;

	// Find the right node.
	{
		lock_guard<mutex> lock(m_blockerMutex);
		auto emptyBlocker = find_if(m_blocker.begin(), m_blocker.end(),
			[](const BusySleeper2Blocker &b)
		{
			// Find a noused blocker, and reuse it.
			return b.ref == 0;
		});
		if (emptyBlocker == m_blocker.end())
		{
			m_blocker.push_back(BusySleeper2Blocker());
			res = m_blocker.begin();
			advance(res, m_blocker.size() - 1);
		}
		else
		{
			res = emptyBlocker;
		}
	}

	// Fill the blocker.
	res->id = id;
	res->sleep = true;
	res->ref = 1;
	return res;
}
void BusySleeper2::removeTask(list<BusySleeper2Blocker>::iterator blocker)
{
	blocker->ref = 0;
}

}