

// main.cc
// 

#include "wCppExt.h"
using namespace std;
using namespace w;

int main(/*int argc, char *argv[]*/)
{
	IniHelper ih("c:\\test.ini");

	if (ih.load())
	{
		auto res = ih.get();
		for (auto const &i : res)
		{
			cout <<"'" + i.first + "'" <<endl;
			for (auto const &j : i.second)
			{
				cout <<'\t' <<"'" + j.first + "'" <<" -> " <<"'" + j.second + "'" <<endl;
			}
		}
	}

	return 0;
}
