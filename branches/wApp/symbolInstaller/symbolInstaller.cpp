// symbolInstaller.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
using namespace std;
using namespace this_thread;
using namespace chrono;

static const char *s_dlg_classname = "MsiDialogCloseClass";
static const DWORD IDC_BUTTON_BACK = 0x16D,
				   IDC_BUTTON_NEXT = 0x166,

				   IDC_GROUP_ACCEPT_PARENT = 0x1F3,
				   IDC_RADIO_ACCEPT = 0x1B9,

				   IDC_BUTTON_INSTALL = 0x21D,

				   IDC_BUTTON_FINISH = 0x181,

				   IDC_BUTTON_REMOVE = 0x208,
				   IDC_BUTTON_REMOVE2 = 0x226;

void myClick(const string &className, DWORD widgetId)
{
	HWND dlg = nullptr, widget = nullptr;
	while (true)
	{
		dlg = FindWindow(className.c_str(), NULL);
		widget = GetDlgItem(dlg, widgetId);
		if (widget != nullptr)
		{
			PostMessage(dlg, WM_COMMAND, HIWORD(BN_CLICKED) | LOWORD(widgetId), (LPARAM)widget);
			break;
		}
		
		sleep_for(seconds(1));
	}
}
void myClick2(const string &className, DWORD widgetParentId, DWORD widgetId)
{
	HWND dlg = nullptr, widgetParent = nullptr, widget = nullptr;
	while (true)
	{
		dlg = FindWindow(className.c_str(), NULL);
		widgetParent = GetDlgItem(dlg, widgetParentId);
		widget = GetDlgItem(widgetParent, widgetId);
		if (widget != nullptr)
		{
			PostMessage(widgetParent, WM_COMMAND, HIWORD(BN_CLICKED) | LOWORD(widgetId), (LPARAM)widget);
			break;
		}
		
		sleep_for(seconds(1));
	}
}

void installOne(const string &fileFullpath)
{
	ShellExecute(nullptr, "open", fileFullpath.c_str(), nullptr, nullptr, SW_SHOW);

	// Waiting for dialog UI.
	sleep_for(seconds(3));
	myClick("MsiDialogCloseClass",  IDC_BUTTON_NEXT);

	// Accept.
	sleep_for(seconds(3));
	myClick2("MsiDialogCloseClass",  IDC_GROUP_ACCEPT_PARENT, IDC_RADIO_ACCEPT);

	// Next.
	sleep_for(seconds(3));
	myClick("MsiDialogCloseClass",  IDC_BUTTON_NEXT);

	// Next: Location.
	sleep_for(seconds(3));
	myClick("MsiDialogCloseClass",  IDC_BUTTON_NEXT);

	// Install.
	sleep_for(seconds(3));
	myClick("MsiDialogCloseClass",  IDC_BUTTON_INSTALL);

	// Finish.
	sleep_for(seconds(3));
	myClick("MsiDialogCloseClass",  IDC_BUTTON_FINISH);
}
bool installOne2(const string &fileFullpath)
{
	ShellExecute(nullptr, "open", fileFullpath.c_str(), nullptr, nullptr, SW_SHOW);

	while (true)
	{
		HWND dlg = FindWindow(s_dlg_classname, NULL),
			 next = GetDlgItem(dlg, IDC_BUTTON_NEXT), 
			 acceptParent = GetDlgItem(dlg, IDC_GROUP_ACCEPT_PARENT), 
			 accept = GetDlgItem(acceptParent, IDC_RADIO_ACCEPT),
			 install = GetDlgItem(dlg, IDC_BUTTON_INSTALL),
			 finish = GetDlgItem(dlg, IDC_BUTTON_FINISH);

		bool clicked = false;
		if (IsWindowEnabled(next) && !clicked)
		{
			PostMessage(dlg, WM_COMMAND, HIWORD(BN_CLICKED) | LOWORD(IDC_BUTTON_NEXT), (LPARAM)next);
			OutputDebugString("installer: next");
			clicked = true;
		}
		if (IsWindowEnabled(accept) && !clicked)
		{
			PostMessage(acceptParent, WM_COMMAND, HIWORD(BN_CLICKED) | LOWORD(IDC_RADIO_ACCEPT), (LPARAM)accept);
			OutputDebugString("installer: accept");
			clicked = true;
		}
		if (IsWindowEnabled(install) && !clicked)
		{
			PostMessage(dlg, WM_COMMAND, HIWORD(BN_CLICKED) | LOWORD(IDC_BUTTON_INSTALL), (LPARAM)install);
			OutputDebugString("installer: install");
			clicked = true;
		}
		if (IsWindowEnabled(finish) && !clicked)
		{
			PostMessage(dlg, WM_COMMAND, HIWORD(BN_CLICKED) | LOWORD(IDC_BUTTON_FINISH), (LPARAM)finish);
			OutputDebugString("installer: finish");
			clicked = true;
			break;
		}

		// No click.
		if (!clicked)
		{
			OutputDebugString("installer: wait");
		}

		sleep_for(seconds(3));
	}

	return true;
}

vector<string> getFileFullpathInDir(string path)
{
	vector<string> res;

	if (path.rfind("\\") != path.length()-1)
	{
		path += "\\";
	}

	WIN32_FIND_DATA fd = {};
	HANDLE h = FindFirstFile((path + "*").c_str(), &fd);
	if (h != INVALID_HANDLE_VALUE)		// If is directory, append "*".
	{
		while (FindNextFile(h, &fd))
		{
			// 'fullpath' must be a directory.
			if (fd.cFileName != string(".")
				&& fd.cFileName != string(".."))		// Skip "." or "..".
			{
				res.push_back(path + fd.cFileName);
			}
		}

		FindClose(h);
	}

	return res;
}

int _tmain(int argc, char *argv[])
{
	OutputDebugString("installer: begin.");
	for (const auto &i : getFileFullpathInDir(argv[1]))
	{
		OutputDebugString(("installer: " + i).c_str());
		installOne2(i);
	}
	OutputDebugString("installer: done.");

	return 0;
}
