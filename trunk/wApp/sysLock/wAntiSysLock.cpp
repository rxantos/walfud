

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
	m_pause.lock();

	m_keeper = async(&AntiSysLock::Keeper, this, shared_ptr<KeeperParam>(new KeeperParam(m_stat, m_pause, actInterval)));
}
AntiSysLock::~AntiSysLock()
{
	switch (m_stat)
	{
	case Stat::DefaultLock:
		m_stat = Stat::Quit;
		m_pause.unlock();
		break;
	case Stat::AntiLock:
		break;
	case Stat::Quit:
		break;
	default:
		break;
	}

	m_keeper.wait();
}

// Interface.
void AntiSysLock::KeepWorking()
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
void AntiSysLock::Keeper(shared_ptr<KeeperParam> param)
{
	bool running = true;
	while (running)
	{
		param->pause.lock();

		switch (param->stat)
		{
		case Stat::DefaultLock:
			SetThreadExecutionState(ES_CONTINUOUS);
			break;
		case Stat::AntiLock:
			SetThreadExecutionState(ES_CONTINUOUS | ES_DISPLAY_REQUIRED);
			break;
		case Stat::Quit:
			running = false;
			break;
		default:
			break;
		}

		param->pause.unlock();
		this_thread::sleep_for(chrono::milliseconds(param->interval));
	}
}

}