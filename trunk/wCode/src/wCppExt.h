

// wCppExt.h
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <array>
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <utility>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <functional>
#include <thread>
#include <future>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <regex>

#include <windows.h>

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

#pragma warning(disable: 4800)						// 'BOOL' : forcing value to bool 'true' or 'false'.

namespace w
{

#define arrCnt(arr)	(sizeof(arr)/sizeof(arr[0]))

#define MAX_INT_LEN		(32)
#define CHARACTER_SIZE	(sizeof(char))

}