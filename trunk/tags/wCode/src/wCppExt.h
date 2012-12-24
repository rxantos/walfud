

// wCppExt.h
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <map>
#include <iomanip>
#include <algorithm>
#include <limits>

#include <windows.h>

#include "wStrUtil.h"
#include "wSysUtil.h"
#include "wDir.h"
#include "wProcess.h"
#include "wTimeMeasurer.h"
#include "wHack.h"

#pragma warning(disable: 4800)						// 'BOOL' : forcing value to bool 'true' or 'false'.

namespace w
{

#define ArrLen(arr)	(sizeof(arr)/sizeof(arr[0]))

#define MAX_INT_LEN	(32)

}