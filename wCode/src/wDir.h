

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
	//	string drive, path, filename, namePart, extPart;
	//	splitPath(*it, drive, path, namePart, extPart);
	//	cout <<left <<setw(25) <<*it <<" : " 
	//		 <<setw(4) <<drive <<setw(15) <<path <<setw(10) <<filename <<setw(10) <<namePart <<setw(10) <<extPart
	//		 <<endl;
	//}
bool pathSplit(std::string fullpath,
			   std::string &drive, std::string &dir, std::string &namePart, std::string &extPart);

/*
 *
 *		Get one level sub files' fullpath.
 *
 *	Param:
 *		'fullpath': Root fullpath. To represent a directory, tailling with "\".
 *
 */
std::unordered_set<std::string> traverseNextLevel(const std::string &fullpath);
std::unordered_set<std::string> traverseNextLevel(const std::unordered_set<std::string> &fullpath);

/*
 *
 *		Get sub files' name at specified levels.
 *
 *	Param:
 *		'fullpath': Root fullpath. To represent a directory, tailling with "\".
 *		'begLevel/endLevel': The range of specified levels. Half opened.
 *
 *	Note:
 *		Root fullpath is level 0.
 *		'traverseInBreadth(fullpath, 0, 1)' will return 'pair(0, fullpath)'.
 *		'traverseInBreadth(fullpath, 1, 2)' is equal to 'traverseNextLevel(fullpath)'.
 *
 *	Example:
 *		'traverseInBreadth(R"(d:\foo\)", 1, 3)'
 *	-------------------------------------------------------------
 *	    0             1               2                    3     |
 *	          /---  x            helloWorld.cc                   |
 *	         /---   y.txt                                        |
 *	        /---    z                bar          ---  360sd.exe |
 *	d:\foo                                                       |
 *	        \---    a.exe      /--- my.doc                       |
 *	         \---   b      ---                                   |
 *	          \---  c.obj      \--- boot.asm                     |
 *	-------------------------------------------------------------
 *		level('unsigned')			fullpath('string')
 *				1						d:\foo\x\
 *				1						d:\foo\y.txt
 *				1						d:\foo\z\
 *				1						d:\foo\a.exe
 *				1						d:\foo\b\
 *				1						d:\foo\c.obj
 *				2						d:\foo\x\helloWorld.cc
 *				2						d:\foo\z\bar\
 *				2						d:\foo\b\my.doc
 *				2						d:\foo\b\boot.asm
 *	-------------------------------------------------------------
 *		Sequence is NOT guaranteed.
 *
 */
std::unordered_multimap<unsigned, std::string> 
			traverseInBreadth(const std::string &fullpath, 
							  unsigned begLevel = 0, unsigned endLevel = (std::numeric_limits<unsigned>::max)());

}

#endif // W_DIR_H