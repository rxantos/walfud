

// wDir.h
//

#include "wDir.h"
using namespace std;

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
	//	string drive, path, filename, namePart, extPart;
	//	splitPath(*it, drive, path, namePart, extPart);
	//	cout <<left <<setw(25) <<*it <<" : " 
	//		 <<setw(4) <<drive <<setw(15) <<path <<setw(10) <<filename <<setw(10) <<namePart <<setw(10) <<extPart
	//		 <<endl;
	//}
bool pathSplit(string fullpath,
			   string &drive, string &dir, string &namePart, string &extPart)
{
	// drive.
	if (fullpath.length() > 1
		&& isalpha(fullpath[0]) != 0
		&& fullpath[1] == ':')
	{
		drive = fullpath.substr(0, 2);
		fullpath.erase(0, 2);
	}

	// Path.
	size_t pathEnd = fullpath.rfind('\\') == string::npos ? 0 : fullpath.rfind('\\') + 1;
	pathEnd = fullpath.find_first_not_of('.', pathEnd) == string::npos ? fullpath.length() : pathEnd;
	dir = strMakeRight(fullpath.substr(0, pathEnd), "\\");
	fullpath.erase(0, pathEnd);

	// Name part.
	const size_t nameEnd = fullpath.rfind('.');
	namePart = fullpath.substr(0, nameEnd);
	fullpath.erase(0, nameEnd + 1);

	// Extend part.
	extPart = fullpath;

	return true;
}

}