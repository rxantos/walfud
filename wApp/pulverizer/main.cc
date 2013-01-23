// pulverizer.cpp : Defines the entry point for the console application.
//

#include "wPulverizer.h"
#include "wStrUtil.h"
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
using namespace std;

int main(int argc, char *argv[])
{
	MyPulverizeEngine pe;
	TargetInfo ti;
	ti.uncFullpath = "E:\\walfud\\trunk\\wApp\\pulverizer\\test.txt";

	for (int i = 0; i < 10; ++i)
	{
		pe.addTarget(ti);
	}

	string i;

	pe.doIt();
	cout <<"doIt()." <<endl;
	cin >>i;

	pe.idle();
	cout <<"idle()." <<endl;
	cin >>i;


	pe.doIt();
	cout <<"doIt()." <<endl;
	cin >>i;

	return 0;
}