

// wAntiSysLock.cpp
//

#include "wAntiSysLock.h"
#include <chrono>
using namespace std;

namespace w
{

// AntiSysLock.
AntiSysLock::AntiSysLock(unsigned actInterval) : m_keeper(), m_stat(Stat::DefaultLock), m_pause()
{
	//m_stat = Stat::DefaultLock;
	m_pause.lock();

	m_keeper = async(&AntiSysLock::Keeper, this, KeeperParam(m_stat, m_pause, actInterval));
}
AntiSysLock::~AntiSysLock()
{
	m_stat = Stat::Quit;
	m_keeper.wait();
}

// Interface.
void AntiSysLock::KeepWorking(unsigned atLeastMS)
{
	Stat old = m_stat;

	m_stat = Stat::AntiLock;

	if (old != Stat::AntiLock)
	{
		m_pause.unlock();
	}
}
void AntiSysLock::StopKeeping()
{
	Stat old = m_stat;

	m_stat = Stat::DefaultLock;

	if (old != Stat::DefaultLock)
	{
		m_pause.lock();
	}
}

// private.
void AntiSysLock::Keeper(KeeperParam param)
{
	while (bool running = true)
	{
		param.pause.lock();

		Stat s = param.stat;
		switch (s)
		{
		case Stat::DefaultLock:
			SetThreadExecutionState(ES_CONTINUOUS);
			break;
		case Stat::AntiLock:
			SetThreadExecutionState(ES_CONTINUOUS | ES_DISPLAY_REQUIRED);
			break;
		case Stat::Quit:
			running = true;
			break;
		default:
			break;
		}

		param.pause.unlock();
		this_thread::sleep_for(chrono::milliseconds(param.interval));
	}

	return;
}

}