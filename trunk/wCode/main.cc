

// main.cc
// 

#include "wCppExt.h"
#include <iostream>
using namespace std;

int main(/*int argc, char *argv[]*/)
{
	vector<string> strSplit_tester1 = w::strSplit("asd|1234", "|");
	cout <<"---" <<endl;
	for (vector<string>::const_iterator it = strSplit_tester1.begin(); it != strSplit_tester1.end(); ++it)
	{
		cout <<*it <<endl;
	}
	cout <<"---" <<endl;

	return 0;
}