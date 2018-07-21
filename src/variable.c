#include "../include/variable.h"

/****************************下面式变量操作*************************************************************/
/*
函数功能：初始化变量
输入：指向variable的指针,变量的名字name
输出：初始化成功的变量
*/
variable* variable_init(char name[])
{
	variable* new_variable=(variable*)malloc(sizeof(variable));
	if (NULL==new_variable)
	{
		printf("memory malloc failed!\n");
		return NULL;
	}
	memset(new_variable->name,'\0',VARIABLE_SIZE);
	if(!variable_give_name(new_variable,name))
	{
		return NULL;
	}
	new_variable->value=0;
	new_variable->isvalid=false;
	new_variable->next=NULL;
	return new_variable;
}


/*
函数功能：函数名合法性检查
输入：变量名,两边没有空格
返回：是否合法
注意：合法的变量名必须是字符或者下划线开头
*/
bool variable_name_check(char *name)
{
	// 检查长度
	if (strlen(name)<=0)
	{
		#if DEBUG_MODE
			printf("no character in name!\n");
		#else
			printf("variable name has errors. or you input 2 continous \"=\"!\n");
		#endif
		return false;
	}
	else if (strlen(name)>VARIABLE_SIZE)
	{
		printf("name is too long:%s\n",name);
		return false;
	}
	//检查字符
	for (int i = 0; i < strlen(name); ++i)
	{
		if (name[i]>='a'&&name[i]<='z'||name[i]>='A'&&name[i]<='Z'||'_'==name[i]||name[i]>='0'&&name[i]<='9')
		{
			// 检查第一个字符
			if (0==i&&name[i]>='0'&&name[i]<='9')
			{
				printf("name's first character is illegal:%s\n",name);
				return false;
			}

		}
		else
		{
			printf("variable name has illegal character:%s\n",name);
			return false;
		}
	}
	#if DEBUG_MODE
		printf("legal name:%s\n",name);
	#endif
	return true;

}

/*
函数功能：给变量名赋值
参数：var--需要命名的变量,已经去掉两边的空格
	name--名字
返回值：是否命名成功
*/
bool variable_give_name(variable* var, char name[])
{
	if (!variable_name_check(name))
	{
		return false;
	}
	if (strlen(name)>VARIABLE_SIZE)
	{
		printf("name is too long:%s\n",name);
		return false;
	}
	strcpy(var->name,name);
	var->name[strlen(name)]='\0';
	return true;
}

/*
函数功能：得到变量的名字
参数:变量var,存放名字的字符串name
返回值：是否得到名字
*/
bool variable_get_name(variable* var,char name[])
{
	if (NULL==var)
	{
		printf("var pointer is NULL,can not get name!\n");
		return false;
	}
	else
	{
		strcpy(name,var->name);
		name[strlen(var->name)]='\0';
		return true;
	}
}

/*
函数功能：变量赋值
参数：需要赋值的变量var，赋值value
返回值：是否赋值成功
*/
bool variable_give_value(variable* var,double value)
{
	if (NULL==var)
	{
		printf("var is NULL,can not give it value\n");
		return false;
	}
	var->value=value;
	var->isvalid=true;
	return true;
}

/*
函数功能：得到变量的值
参数:var 变量,value 接收值
返回值：是否成功得到值
*/
bool variable_get_value(variable* var,double *value)
{
	if (NULL==var)
	{
		printf("var pointer is NULL, can not get its value\n");
		return false;
	}
	else if (false==var->isvalid)
	{
		printf("var has not value\n");
		return false;
	}
	else
	{
		*value=var->value;
		return true;
	}

}
/*
函数功能：删除变量，回收空间
参数：变量var
返回NULL
*/
variable* variable_destroy(variable *var)
{
	if (NULL==var)
	{
		return NULL;
	}
	else
	{
		free(var);
		return NULL;
	}
}

/*
函数功能：变量有效性检查（包括值的有效性和指针的有效性）
参数：var变量
返回值：0---all ok
		1----var is NULL
		2----var has not value
*/
int variable_valid_check(variable *var)
{
	if (NULL==var)
	{
		#if DEBUG_MODE
			printf("var pointer is NULL!so it's not valid!\n");
		#endif
		return 1;
	}
	else if (false==var->isvalid)
	{
		#if DEBUG_MODE
			printf("var has not value!it's not valid\n");
		#endif
		return 2;

	}
	else
		return 0;
}
