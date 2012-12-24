

// TaskbarProgress.cc
//

#include "wTaskbarProgress.h"
using namespace std;

namespace w
{

TaskbarProgress::TaskbarProgress()
	: m_progress(nullptr), m_hwnd(nullptr),
	  m_min(0), m_max(0), m_cur(0),
	  m_step(0),
	  m_state(TBPF_NOPROGRESS)
{ CoInitializeEx(nullptr, COINIT_MULTITHREADED); }
TaskbarProgress::~TaskbarProgress()
{ CoUninitialize(); }

// Interface.
void TaskbarProgress::init(HWND hwnd)
{
	CoCreateInstance(CLSID_TaskbarList, 
					 nullptr, 
					 CLSCTX_ALL, 
					 __uuidof(ITaskbarList3), 
					 reinterpret_cast<void **>(&m_progress));

	m_hwnd = hwnd;
}
void TaskbarProgress::release()
{
	// Release resources.
	m_progress->Release();
	m_progress = nullptr;

	// Reset state.
	m_hwnd = nullptr;
	m_min = m_max = m_cur = 0;
	m_step = 0;
	m_state = TBPF_NOPROGRESS;
}

void TaskbarProgress::setRange(unsigned min, unsigned max)
{ m_min = min, m_max = max; }
std::pair<unsigned, unsigned> TaskbarProgress::getRange() const
{ return make_pair(m_min, m_max); }

void TaskbarProgress::setPos(unsigned cur)
{
	if ((m_cur = cur) <= m_min)
	{
		// Current position is less equal than minimum.
		// No progress is necessary.
		clear();
	}
	else
	{
		// Draw progress to taskbar.
		m_progress->SetProgressValue(m_hwnd, cur - m_min, m_max - m_min);
	}
}
unsigned TaskbarProgress::getPos() const
{ return m_cur; }

void TaskbarProgress::setStep(int step)
{ m_step = step; }
int TaskbarProgress::getStep() const
{ return m_step; }
bool TaskbarProgress::go()
{
	setPos(m_cur += m_step);

	return m_min < m_cur && m_cur < m_max;
}

void TaskbarProgress::normal()
{ setState(TBPF_NORMAL); }
void TaskbarProgress::pause()
{ setState(TBPF_PAUSED); }
void TaskbarProgress::err()
{ setState(TBPF_ERROR); }
void TaskbarProgress::confuse()
{ setState(TBPF_INDETERMINATE); }
void TaskbarProgress::clear()
{ setState(TBPF_NOPROGRESS); }

TBPFLAG TaskbarProgress::getState() const
{ return m_state; }

// logic.
void TaskbarProgress::setState(TBPFLAG state)
{ m_progress->SetProgressState(m_hwnd, m_state = state); }

}