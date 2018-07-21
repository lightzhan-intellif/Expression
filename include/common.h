#ifndef _COMMON_H_
#define _COMMON_H_

#define DEBUG_MODE 1//DEBUG模式开关标志
#define TERMINAL_MODE 1//终端模式
#define VARIABLE_MODE 1//变量模式
#define VARIABLE_POOL_PRINT 1//打印变量池

#define NUM_LENGTH 20//数字最多位数
#define MAX_INPUT_LENGTH 100//输入字符串的最大长度
#include "stdio.h"
#include "stdlib.h"
#include "memory.h"
#ifdef __GNUC__
	#include "stdbool.h"
	#include "malloc.h"
#endif
#ifdef _MSC_VER
	typedef enum {false,true} bool;
#endif
#endif