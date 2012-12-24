

// wDir.h
//

#ifndef W_DIR_H
#define W_DIR_H

#include "wCppExt.h"

namespace w
{

/*
 *
 *
 *	Note:
 *		Treat "windows" as a file.
 *
 */
 	//vector<string> pathSplit_tester;
	//pathSplit_tester.push_back("c:\\win\\run.exe");
	//pathSplit_tester.push_back("c:\\win\\run");
	//pathSplit_tester.push_back("c:\\win\\");
	//pathSplit_tester.push_back("c:\\win");
	//pathSplit_tester.push_back("c:\\");
	//pathSplit_tester.push_back("c:");

	//pathSplit_tester.push_back("c:\\win\\..\\run.exe");
	//pathSplit_tester.push_back("c:\\win\\.");
	//pathSplit_tester.push_back("c:\\win\\..");
	//pathSplit_tester.push_back("c:\\.");
	//pathSplit_tester.push_back("c:\\..");
	//pathSplit_tester.push_back(".");
	//pathSplit_tester.push_back("..");

	//pathSplit_tester.push_back("c:\\win\\foo.bar\\run.exe");
	//pathSplit_tester.push_back("c:\\win\\foo..bar\\run.exe");

	//pathSplit_tester.push_back("c:\\win\\run.exe.bak");
	//pathSplit_tester.push_back("\\win\\run.exe");
	//pathSplit_tester.push_back("win\\run.exe");
	//pathSplit_tester.push_back("run.exe");
	//pathSplit_tester.push_back("run");
	////pathSplit_tester.push_back(".exe");							// Invalid.

	//pathSplit_tester.push_back("c:\\win\\..exe");
	//pathSplit_tester.push_back("c:\\win\\...exe");
	//pathSplit_tester.push_back("c:\\..exe");
	//pathSplit_tester.push_back("c:\\...exe");
	//pathSplit_tester.push_back("\\..exe");
	//pathSplit_tester.push_back("\\...exe");
	//pathSplit_tester.push_back("..exe");
	//pathSplit_tester.push_back("...exe");
	//
	//for (vector<string>::const_iterator it = pathSplit_tester.begin(); it != pathSplit_tester.end(); ++it)
	//{
	//	string driver, path, filename, namePart, extPart;
	//	splitPath(*it, driver, path, namePart, extPart);
	//	cout <<left <<setw(25) <<*it <<" : " 
	//		 <<setw(4) <<driver <<setw(15) <<path <<setw(10) <<filename <<setw(10) <<namePart <<setw(10) <<extPart
	//		 <<endl;
	//}
bool pathSplit(std::string fullpath,
			   std::string &driver, std::string &dir, std::string &namePart, std::string &extPart);

}

#endif // W_DIR_H