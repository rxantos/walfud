

// wAntiSysLock.cpp
//

#include "wAntiSysLock.h"
#include <chrono>
using namespace std;

namespace w
{

// AntiSysLock.
AntiSysLock::AntiSysLock()
{}
AntiSysLock::~AntiSysLock()
{
	m_antiLock = false;
	if (m_keeper.valid())
	{
		m_keeper.wait();
	}
}

// Interface.
void AntiSysLock::KeepWorking()
{
	if (!m_antiLock)
	{
		m_keeper = async(&AntiSysLock::Keeper, this, nullptr);
	}
}
void AntiSysLock::StopKeeping()
{
	m_antiLock = false;
}

// private.
void AntiSysLock::Keeper(void *param)
{
	m_antiLock = true;

	while (m_antiLock)
	{
		SetThreadExecutionState(ES_CONTINUOUS | ES_DISPLAY_REQUIRED);
		this_thread::sleep_for(chrono::seconds(1));
	}

	// Restore normal default lock.
	SetThreadExecutionState(ES_CONTINUOUS);

	m_antiLock = false;
}

}