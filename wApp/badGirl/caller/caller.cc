

// badGirl.cc
//

#include "wCppExt.h"
#include <windows.h>
#include <iostream>
using namespace std;

int main()
{
	cout <<w::remoteInject("notepad++.exe", "badGirl.dll") <<endl;
	//cout <<w::remoteInject("console_test.exe", "E:\\work\\trunk\\badGirl\\Debug\\badGirl.dll") <<endl;
	//cout <<w::remoteInject("window_test.exe", "E:\\work\\trunk\\badGirl\\Debug\\badGirl.dll") <<endl;
	//cout <<w::remoteInject("dll_test.exe", "E:\\work\\trunk\\badGirl\\Debug\\badGirl.dll") <<endl;

	return 0;
}
