#ifndef _COMMON_H_
#define _COMMON_H_
#include "stdio.h"
#include "stdlib.h"
#include "memory.h"
#define DEBUG_MODE 1//DEBUG模式开关标志
#ifdef __GNUC__
	#include "stdbool.h"
	#include "malloc.h"
#endif
#ifdef _MSC_VER
	typedef enum {false,true} bool;
#endif
#endif