#ifndef _SPLIT_EQUATION_H_
#define _SPLIT_EQUATION_H_
#define VARIABLE_SIZE 20 //变量最大长度 
/*
该文件需要对变量进行管理，主要的功能有：
1.从输入里面得到变量
2.检查变量的合法性
3.用变量的值替换计算表达式里面的变量
4.保存和维护变量
5.删除变量
*/
#include "common.h"
// 定义变量
struct var
{
	char name[VARIABLE_SIZE+1];//变量名
	double value;//变量值
	bool isvalid;//变量值是否有效（是否赋值）
	struct var *next;
};
typedef struct var variable;
variable* variable_init(char name[]);
bool variable_name_check(char *name);
bool variable_give_name(variable* var, char name[]);
bool variable_get_name(variable* var,char name[]);
bool variable_give_value(variable* var,double value);
bool variable_get_value(variable* var,double *value);
variable* variable_destroy(variable *var);
int variable_valid_check(variable *var);
// bool variable_valid_check(variable *var);
#endif