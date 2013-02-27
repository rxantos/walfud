

// main.cc
// 

#include "wCppExt.h"
using namespace std;
using namespace w;

int main(/*int argc, char *argv[]*/)
{
	IniHelper ini("C:\\Users\\songdeming\\Desktop\\test.ini");

	ini.load();
	ini.save();


	return 0;
}