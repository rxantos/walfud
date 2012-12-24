// runByTime.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../wCode/wSysUtil.h"
#include <windows.h>
#include <iostream>
#include <ctime>
using namespace std;

void __stdcall timeWork(PTP_CALLBACK_INSTANCE instance, void *param, PTP_WORK work)
{
	w::runAndWait(static_cast<wchar_t *>(param), L"", INFINITE, false);
}

/*
 *
 *	Param:
 *		1: Interval to run a new process. In second.
 *		2: Executable name.
 *
 *	Note:
 *		Run children process asynchronously.
 *
 */
int wmain(int argc, wchar_t *argv[])
{
	if (argc != 3)
	{
		return -1;
	}

	PTP_WORK work = CreateThreadpoolWork(timeWork, argv[2], nullptr);
	int interval = _wtoi(argv[1]);

	while (true)
	{
		// Call a executable every 'interval' micro-second.
		// Asynchronously.
		SubmitThreadpoolWork(work);
		Sleep(interval / 1000);
	}

	CloseThreadpoolWork(work);
	return 0;
}

