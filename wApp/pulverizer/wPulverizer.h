

// wPulverizer.h
// 

#ifndef W_PULVERIZER_H
#define W_PULVERIZER_H

#include <vector>
#include <deque>
#include <string>
#include <chrono>
#include <mutex>
#include <future>
#include <condition_variable>

struct TargetInfo
{
	std::string uncFullpath;
	bool antiRecover, antiRegenerate;

	bool res;
	std::chrono::time_point<std::chrono::system_clock> begTime, endTime;
};

bool operator<(const TargetInfo &a, const TargetInfo &b);
bool operator==(const TargetInfo &a, const TargetInfo &b);

class PulverizeEngine;

//class Pulverizer
//{
//public:
//	virtual ~Pulverizer(){}
//
//public:
//	// Interface.
//	virtual void operator()() = 0;
//};
//class MyPulverizer : public Pulverizer
//{
//	// data.
//	PulverizeEngine &m_pe;
//
//public:
//	MyPulverizer(PulverizeEngine &pulverizerEngine);
//	virtual ~MyPulverizer();
//
//public:
//	// Interface.
//	virtual void operator()();
//};

class PulverizerEngine
{};
class MyPulverizeEngine : public PulverizerEngine
{
	enum class State
	{
		Idle = 0,
		Doing,
		Quit, 
	};

	// data.
	std::deque<TargetInfo> m_targets;
	State m_state;
    std::mutex m_pulverizeMutex;

	std::future<void> m_pulverizeThreadFuture;

	static const std::chrono::milliseconds ms_idleInterval;

public:
	MyPulverizeEngine();
	virtual ~MyPulverizeEngine();

public:
	// Interface.
	void addTarget(const TargetInfo &targetInfo);
	void removeTarget(const TargetInfo &targetInfo);
	void clearTarget();

	// Worker.
	virtual void foo();

	// Control.
	void idle();
	void doIt();

protected:
	// logic.
	virtual void doIdleOnce();
	virtual TargetInfo doPulverizeOnce(TargetInfo ti);

	static void pulverizeThread(void *param);
};

#endif // W_PULVERIZER_H