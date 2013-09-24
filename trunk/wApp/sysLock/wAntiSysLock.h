

// wAntiSysLock.h
//

#ifndef W_ANTI_SYS_LOCK_H
#define W_ANTI_SYS_LOCK_H

#include <windows.h>
#include <thread>
#include <future>
#include <atomic>

namespace w
{

class AntiSysLock
{
	// data.
	DWORD m_originalState;

public:
	AntiSysLock();
	~AntiSysLock();

public:
	// Interface.
	void KeepWorking();
	void StopKeeping();

private:
	// logic.
};

}

#endif // W_ANTI_SYS_LOCK_H