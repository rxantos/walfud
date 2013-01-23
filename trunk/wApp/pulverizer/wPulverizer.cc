

// wPulverizer.cc
//

#include "wPulverizer.h"
#include "wPulverizerTool.h"
#include "wStrUtil.h"
#include <limits>
using namespace std;

bool operator<(const TargetInfo &a, const TargetInfo &b)
{ return lexicographical_compare(a.uncFullpath.begin(), a.uncFullpath.end(),
								 b.uncFullpath.begin(), b.uncFullpath.end(),
								 [](char a, char b) { return tolower(a) < tolower(b); }); }
bool operator==(const TargetInfo &a, const TargetInfo &b)
{ return !(a < b) && !(b < a); }

const chrono::milliseconds MyPulverizeEngine::ms_idleInterval(500);

//// MyPulverizer.
//MyPulverizer::MyPulverizer(PulverizeEngine &pulverizerEngine) : m_pe(pulverizerEngine)
//{}
//MyPulverizer::~MyPulverizer()
//{}
//
//// Interface.
//void MyPulverizer::operator()()
//{}

// MyPulverizerEngine.
MyPulverizeEngine::MyPulverizeEngine() : m_targets(), m_state(State::Idle), m_pulverizeMutex()
{
	m_pulverizeMutex.lock();
	m_pulverizeThreadFuture = async(pulverizeThread, this);
}
MyPulverizeEngine::~MyPulverizeEngine()
{
	// Prepare to quit.
	m_state = State::Quit;
	m_targets.clear();

	// Resume worker thread.
	if (m_pulverizeMutex.try_lock())
	{
		m_pulverizeMutex.unlock();
	}

	// Wait worker thread exits.
	m_pulverizeThreadFuture.get();
}

// Interface.
void MyPulverizeEngine::addTarget(const TargetInfo &targetInfo)
{ m_targets.push_back(targetInfo); }
void MyPulverizeEngine::removeTarget(const TargetInfo &targetInfo)
{ m_targets.erase(find(m_targets.begin(), m_targets.end(), targetInfo)); }
void MyPulverizeEngine::clearTarget()
{ m_targets.clear(); }

void MyPulverizeEngine::foo()
{
	if (m_targets.empty())
	{
		// No target, sleep a while.
		doIdleOnce();
	}
	else
	{
		// Pulverize top element.
		doPulverizeOnce(m_targets[0]);
		m_targets.pop_front();
	}
}

void MyPulverizeEngine::idle()
{
	m_pulverizeMutex.lock();
}
void MyPulverizeEngine::doIt()
{
	m_pulverizeMutex.unlock();
}

// logic.
void MyPulverizeEngine::doIdleOnce()
{ this_thread::sleep_for(ms_idleInterval); }
TargetInfo MyPulverizeEngine::doPulverizeOnce(TargetInfo ti)
{
	cout <<"pulverizing...";

	//// Get permission.
	//grantPermission(ti.uncFullpath);

	//// Release reference in other processes.
	//unloadHandle(ti.uncFullpath);

	//// Destroy data on disk.
	//if (ti.antiRecover)
	//{
	//	multiErase(ti.uncFullpath);
	//	ti.uncFullpath = multiRename(ti.uncFullpath);
	//}

	//// Remove index from disk.
	//pulverize(ti.uncFullpath);

	//// Take up the index in order to avoid other processes create it.
	//if (ti.antiRegenerate)
	//{
	//	antiRegenerate(ti.uncFullpath);
	//}

	this_thread::sleep_for(chrono::seconds(2));
	cout <<ti.uncFullpath <<endl;
	return ti;
}

void MyPulverizeEngine::pulverizeThread(void *param)
{
	MyPulverizeEngine *pe = reinterpret_cast<MyPulverizeEngine *>(param);

	while (pe->m_state != State::Quit)
	{
		pe->m_pulverizeMutex.lock();
		pe->m_pulverizeMutex.unlock();

		pe->foo();
	}
}