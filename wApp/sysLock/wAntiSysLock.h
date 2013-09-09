

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
	std::future<void> m_keeper;
	std::atomic<bool> m_antiLock;

public:
	AntiSysLock();
	~AntiSysLock();

public:
	// Interface.
	void KeepWorking();
	void StopKeeping();

private:
	// logic.
	void Keeper(void *param);
};

}

#endif // W_ANTI_SYS_LOCK_H