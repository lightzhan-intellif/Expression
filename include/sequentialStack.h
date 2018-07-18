#ifndef _SEQUENTIAL_STACK
#define _SEQUENTIAL_STACK
#include "common.h"
//定义数据
typedef char* datatype;

//通用数据结构
struct datastruct
{
	int flag;
	datatype data;
	struct  datastruct *next;
};

typedef struct datastruct stackdata;
// 下面是栈的数组实现
// flag=0表示该元素为栈底,大于0表示序号
// flag=-1表示栈空
stackdata *stack_array_init(datatype data,int size);
stackdata *stack_array_push(stackdata *stack,datatype data,int *psize);
stackdata *stack_array_pop(stackdata *stack,stackdata* pop);
bool stack_array_isfull(stackdata *stack,int size);//判断栈是否已满
bool stack_array_isempty(stackdata *stack);//判断栈是否为空
stackdata* stack_array_enlarge(stackdata *stack,int *psize,int new_size);//size为以前的大小,new_size为新申请的空间大小
/*void stack_array_printf(stackdata *stack);
void stack_array_test();*/
#endif