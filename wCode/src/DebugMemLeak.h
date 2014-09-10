

// DebugMemLeak.h
// Recommand include me in stdafx.h to enable memory check in debug moode. 
// For more details: http://msdn.microsoft.com/en-us/library/x98tx3cf.aspx

#pragma once

#define _CRTDBG_MAP_ALLOC		// When the _CRTDBG_MAP_ALLOC flag is defined in the debug version of an application, 
								// the base version of the heap functions are directly mapped to their debug versions. 
								// The flag is used in Crtdbg.h to do the mapping. This flag is only available 
								// when the _DEBUG flag has been defined in the application.

// For the CRT functions to work correctly, the #include statements must follow the order shown here.
#include <stdlib.h>		
#include <crtdbg.h>				// Including crtdbg.h maps the malloc and the free functions to their debug versions, _malloc_dbg and free, 
								// which track memory allocation and deallocation. This mapping occurs only in debug builds, which have _DEBUG. 
								// Release builds use the ordinary malloc and free functions.

#ifdef _DEBUG
	#define DBG_NEW new ( _CLIENT_BLOCK , __FILE__ , __LINE__ )	// The #define statement maps a base version of the CRT heap functions
																// to the corresponding debug version. If you omit the #define statement, 
																// the memory leak dump will be less detailed.
	//#define new DBG_NEW
#endif  // _DEBUG



//
//#include "DebugMemLeak.h"
//
//int _tmain(int argc, _TCHAR* argv[])
//{
//    // Leak!
//    auto pI = new int[1];
//    pI = nullptr;
//
//
//    // Dump the memory leak. Result as follow:
//    /*************
//            Detected memory leaks!
//            Dumping objects ->
//            e:\work\memleakdemo\memleakdemo.cpp(27) : {120} client block at 0x003DB448, subtype 0, 4 bytes long.
//             Data: <    > CD CD CD CD 
//            Object dump complete.
//    **************/
//    _CrtDumpMemoryLeaks();      // After you have enabled the debug heap functions by using these statements, 
//                                // you can place a call to _CrtDumpMemoryLeaks before an application exit point 
//                                // to display a memory-leak report when your application exits.
//                                // By default, _CrtDumpMemoryLeaks outputs the memory-leak report to the Debug pane of 
//                                // the Output window. You can use _CrtSetReportMode to redirect the report to another 
//                                // location: `_CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_DEBUG );`
//
//    return 0;
//}


//
//#include "DebugMemLeak.h"
//
//void foo()
//{
//	new int[1];
//}
//
//int _tmain(int argc, _TCHAR* argv [])
//{
//	_CrtMemState cmsBefore = {}, cmsAfter = {};
//
//	// Snapshot memory usage before you function.
//	_CrtMemCheckpoint(&cmsBefore);				
//
//	// Call you function.
//	foo();
// 
//	// Snapshot memory usage after you function.
//	_CrtMemCheckpoint(&cmsAfter);				
//
//	// Compare the difference.
//	_CrtMemState cmsDiff = {};
//	if (_CrtMemDifference(&cmsDiff, &cmsBefore, &cmsAfter))	
//	{
//		// Dump the memory leak.
//		_CrtMemDumpStatistics(&cmsDiff);		
//	}
//
//	return 0;
//}
//
