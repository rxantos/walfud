

// wCppExt.h
//

#ifndef W_CPPEXT_H
#define W_CPPEXT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>
#include <array>
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <utility>
#include <tuple>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <limits>
#include <functional>
#include <thread>
#include <future>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <regex>
#include <random>
#include <cassert>

#include <windows.h>
#include <process.h>
#include <Dbghelp.h>

#include "wStrUtil.h"
#include "wSysUtil.h"
#include "wDir.h"
#include "wProcess.h"
#include "wTimeMeasurer.h"
#include "wHack.h"
#include "wDisk.h"
#include "wFilePermission.h"
#include "wTaskbarProgress.h"
#include "wRpc.h"
#include "wPipe.h"
#include "wOtherUtil.h"
#include "wConsole.h"
#include "wMath.h"
#include "wWindowsExt.h"
#include "wIniHelper.h"

#pragma warning(disable: 4800) 						// 'BOOL' : forcing value to bool 'true' or 'false'.
#pragma warning(disable: 4996)						// 'tmpnam': This function or variable may be unsafe.

namespace w
{

#define arrCnt(arr)	(sizeof(arr)/sizeof(arr[0]))

#define MAX_INT_LEN		(32)
#define CHARACTER_SIZE	(sizeof(char))

}

#endif // W_CPPEXT_H