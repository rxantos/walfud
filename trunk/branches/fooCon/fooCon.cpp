// fooCon.cpp : Defines the entry point for the console application.
//

#include <windows.h>
#include <iostream>
#include <ctime>
#include <windows.h>
#include <algorithm>
using namespace std;


int main(int argc, char *argv[])
{
	wstring str = L"我是 aBc 1234 新建文件夹";
	wchar_t buf[123] = {};
	transform(str.begin(), str.end(), buf, tolower);

	wcout <<buf <<endl;
}

