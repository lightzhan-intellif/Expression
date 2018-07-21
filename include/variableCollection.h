/*
定义变量集合
*/
#ifndef _VARIABLE_COLLECTION_
#define _VARIABLE_COLLECTION_ 
#include "variable.h"
#include "mystring.h"
// 定义变量集，用于保存变量
typedef struct
{
	variable* variable_head;//使用链表保存
	long num;//池中变量个数
}variable_collection;

variable_collection* variable_collection_init();
bool variable_collection_add_variable(variable_collection* collection,variable* var);
bool variable_collection_find(variable_collection* collection,char *name,double *value,int *index);
bool variable_collection_delete(variable_collection *collection,char name[]);
variable_collection* variable_collection_get_variable(char* infixExpression);
bool variable_collection_destroy(variable_collection* variable_collection);
bool variable_collection_set_all_value(variable_collection* collection,double value);
bool variable_collection_get_num(variable_collection *collection,int* num);
void variable_collection_printf(variable_collection *collection);
int variable_collection_replace(variable_collection *collection,char* infixExpression);
bool variable_collection_fuse(variable_collection* collection1,variable_collection *collection2);
#endif