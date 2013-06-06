

// wAntiSysLock.h
//

#ifndef W_ANTI_SYS_LOCK_H
#define W_ANTI_SYS_LOCK_H

#include <windows.h>
#include <thread>
#include <future>
#include <atomic>
#include <mutex>
#include <memory>

namespace w
{

class AntiSysLock
{
	enum class Stat : unsigned
	{
		DefaultLock,
		AntiLock,
		Quit,
	};
	struct KeeperParam
	{
		std::atomic<Stat> &stat;
		std::mutex &pause;
		unsigned interval;

		KeeperParam(std::atomic<Stat> &s, std::mutex &p, unsigned i) : stat(s), pause(p), interval(i) {}
		~KeeperParam() {}
	};

	// data.
	std::future<void> m_keeper;
	std::atomic<Stat> m_stat;
	std::mutex m_pause;

public:
	AntiSysLock(unsigned actInterval = 1000);		// Active working state interval.
	~AntiSysLock();

public:
	// Interface.
	void KeepWorking();
	void StopKeeping();

private:
	// logic.
	void Keeper(std::shared_ptr<KeeperParam> param);
};

}

#endif // W_ANTI_SYS_LOCK_H