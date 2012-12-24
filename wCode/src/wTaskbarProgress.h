

// wTaskbarProgress.h
//

#ifndef W_TASKBAR_PROGRESS_H
#define W_TASKBAR_PROGRESS_H

#include <shobjidl.h>
#include "wCppExt.h"

namespace w
{

//void foo(HWND hwnd)
//{
//	w::TaskbarProgress tp;
//	tp.init(hwnd);
//	tp.setRange(0, 100);
//
//	for (int i = 0; i < 100 + 1; ++i)
//	{
//		tp.setPos(i);
//		Sleep(77);
//	}
//
//	tp.release();
//}
//
//void bar(HWND hwnd)
//{
//	w::TaskbarProgress tp;
//	tp.init(hwnd);
//	tp.setRange(0, 100);
//	tp.setStep(1);
//
//	while (tp.go())
//	{
//		Sleep(77);
//
//		if (tp.getPos() == 33)
//		{
//			tp.pause();
//			Sleep(500);
//			tp.normal();
//		}
//		else if (tp.getPos() == 50)
//		{
//			tp.confuse();
//			Sleep(500);
//			tp.normal();
//		}
//		else if (tp.getPos() == 60)
//		{
//			tp.err();
//			Sleep(500);
//		}
//	}
//
//	tp.release();
//}
//
//int main(int argc, char *argv[])
//{
//	Sleep(1000);			// Wait for taskbar creation.
//
//	char moduleFullpath[MAX_PATH] = {};
//	GetModuleFileName(nullptr, moduleFullpath, arrLen(moduleFullpath));
//	HWND hwnd = FindWindow(nullptr, moduleFullpath);
//
//	foo(hwnd);
//	//bar(hwnd);
//
//	return 0;
//}
//
// For details: http://www.codeproject.com/Articles/42345/Windows-7-Goodies-in-C-Taskbar-Progress-and-Status
class TaskbarProgress
{
	// data.
	ITaskbarList3 *m_progress;
	HWND m_hwnd;
	unsigned m_min, m_max, m_cur;
	int m_step;
	TBPFLAG m_state;

public:
	TaskbarProgress();
	~TaskbarProgress();
	TaskbarProgress(const TaskbarProgress &other);
	TaskbarProgress &operator=(const TaskbarProgress &other);
public:
	// interface.
	void init(HWND hwnd);
	void release();

	void setRange(unsigned min, unsigned max);
	std::pair<unsigned, unsigned> getRange() const;

	void setPos(unsigned cur);
	unsigned getPos() const;

	void setStep(int step);		// Can be negative value.
	int getStep() const;
	bool go();					// Forward or back by 'm_step'. 
								// 'true' is 'm_cur' is in range ('m_min', 'm_max').

	void normal();				// Green.				'TBPF_NORMAL'.
	void pause();				// Yello.				'TBPF_PAUSED'.
	void err();					// Red.					'TBPF_ERROR'.
	void confuse();				// Green, go around.	'TBPF_INDETERMINATE'.
	void clear();				// None.				'TBPF_NOPROGRESS'

	TBPFLAG getState() const;	

private:
	// logic.
	void setState(TBPFLAG state);
};

}

#endif // W_TASKBAR_PROGRESS_H