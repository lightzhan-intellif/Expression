/*
定义可以重用的字符串处理函数
*/
#ifndef _MY_STRING_H_
#define _MY_STRING_H_
#include "common.h" 
bool string_replace(char* dest,char* src,char* str);
bool string_remove_startandend_space(char* str);
#endif