

// wAntiSysLock.cpp
//

#include "wAntiSysLock.h"
#include <chrono>
using namespace std;

namespace w
{

// AntiSysLock.
AntiSysLock::AntiSysLock() { m_originalState = SetThreadExecutionState(ES_CONTINUOUS); }
AntiSysLock::~AntiSysLock() { SetThreadExecutionState(m_originalState); }

// Interface.
void AntiSysLock::KeepWorking() { SetThreadExecutionState(ES_DISPLAY_REQUIRED); }
void AntiSysLock::StopKeeping() { SetThreadExecutionState(ES_CONTINUOUS); }

// private.

}