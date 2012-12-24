
//
//

#include <windows.h>
#include <process.h>
#include <iostream>
using namespace std;

void foo(void *param)
{
	while (true)
	{
		CloseHandle(CreateFileA("test.txt", 0, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr));
		cout <<"done." <<endl;

		Sleep(1000);
	}
}

int main()
{
	//HANDLE h = reinterpret_cast<HANDLE>(_beginthread(foo, 0, nullptr));
	//WaitForSingleObject(h, INFINITE);

	LoadLibrary("E:\\work\\trunk\\badGirl\\Debug\\dll_test.dll");

	Sleep(100000);

	//foo(nullptr);

	return 0;
}