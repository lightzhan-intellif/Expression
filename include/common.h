#ifndef _COMMON_H_
#define _COMMON_H_

/*
	改动以下标志位请重新编译程序
*/
#define DEBUG_MODE 0			//DEBUG模式,打开会输出很多调试信息
#define TERMINAL_MODE 0			//终端模式，开启可以在终端连续输入表达式进行测试
#define VARIABLE_MODE 0			//变量模式，开启可以在终端模式中定义变量和使用变量
#define VARIABLE_POOL_PRINT 0	//打印变量池，开启可以在每次输入计算式后查看已经定义的变量以及他们的值

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