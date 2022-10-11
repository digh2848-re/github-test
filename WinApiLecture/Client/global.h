#pragma once

// 미리 컴파일된 헤더
#include <stdio.h>
#include <Windows.h>
#include <vector>
//#include <queue>
//using std::queue;

using std::vector;

#include <list>
using std::list;

#include <map>
using std::map;
using std::make_pair;

#include <string>
using std::string;
using std::wstring;

#include <math.h>
#include <assert.h>

#pragma comment(lib, "Msimg32.lib")

#include "define.h"
#include "struct.h"
#include "func.h"
#include <time.h>



#include <vfw.h>

#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <io.h>
#include <iostream>


#ifndef DBG_NEW 

#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 

#endif
#endif

using namespace std;