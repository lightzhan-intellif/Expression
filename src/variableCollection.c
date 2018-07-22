#include "../include/variableCollection.h"
/*
函数功能：创建结合
参数：
返回值：集合指针
*/
variable_collection* variable_collection_init()
{
	variable_collection* new_collection=(variable_collection*)malloc(sizeof(variable_collection));
	if (NULL==new_collection)
	{
		printf("memory malloc failed!\n");
		return NULL;
	}
	new_collection->variable_head=NULL;
	new_collection->num=0;
	return new_collection;
}

/*
函数功能：往集合里面加入变量 要判断是否已经存在变量，如果存在则直接赋值即可
参数:集合 变量
返回值：是否加入成功
注意：该函数可能会释放掉var变量的空间,因此var的空间最好是独立申请的
*/
bool variable_collection_add_variable(variable_collection* collection,variable* var)
{
	//检查变量有效性
	if (1==variable_valid_check(var))
	{
		printf("not valid var\n");
		return false;
	}
	//检查是否变量已经存在
	int num=0;
	variable_collection_get_num(collection,&num);
	variable* temp_var=collection->variable_head;
	// bool isexist=false;
	for (int i = 0; i < num; ++i)
	{
		if (!strcmp(var->name,temp_var->name))
		{
			/*temp_var->value=var->value;
			temp_var->isvalid=true;*/
			double value=0;
			variable_get_value(var,&value);
			variable_give_value(temp_var,value);
			#if DEBUG_MODE
				printf("It is an existing variable，free var\n");
			#endif
			// isexist=true;
			free(var);
			return true;
		}
		temp_var=temp_var->next;
	}
	var->next=collection->variable_head;
	collection->variable_head=var;
	collection->num++;
	#if DEBUG_MODE
		printf("creating a new variable\n");
	#endif
		return true;
}

/*
函数功能：在集合中寻找变量
输入:集合 变量名 存放变量值的变量
输出：是否找到变量
*/
bool variable_collection_find(variable_collection* collection,char *name,double *value,int *index)
{
	if (!variable_name_check(name))
	{
		/* code */
		#if DEBUG_MODE
			printf("not valid name\n");
		#endif
		return false;
	}
	if (NULL==collection)
	{
		/* code */
		printf("collection pointer is NULL\n");
		return false;
	}
	variable* var=collection->variable_head;
	if (NULL==var)
	{
		/* code */
		#if DEBUG_MODE
			printf("collection is empty\n");
		#endif
		return false;
	}
	for (int i = 0; i < collection->num; ++i)
	{
		if (!strcmp(var->name,name))
		{
			*value=var->value;
			*index=i;
			return true;
		}
	}
	#if DEBUG_MODE
		printf("do not find variable\n");
	#endif
	return false;
}


/*
函数功能：删除变量
输入：集合 变量名字
返回值：是否删除成功
*/
bool variable_collection_delete(variable_collection *collection,char name[])
{
	double value=0;
	int index=0;
	if(variable_collection_find(collection,name,&value,&index))
	{
		// 删除第一个
		if (0==index)
		{
			variable* var=collection->variable_head;
			collection->variable_head=var->next;
			#if DEBUG_MODE
				printf("delete variable:%s\n",var->name);
			#endif
			free(var);
			return true;
		}
		// 删除最后一个
		if (index=collection->num-1)
		{
			variable *var=collection->variable_head;
			for (int i = 0; i < collection->num-1; ++i)
			{
				var=var->next;
			}
			#if DEBUG_MODE
				printf("delete variable:%s\n",var->next->name);
			#endif
			free(var->next);
			var->next=NULL;
			return true;
		}
		variable *var=collection->variable_head;
		variable *var_next=collection->variable_head;//下一个变量
		for (int i = 0; i < index+1; ++i)
		{
			var_next=var_next->next;
			if (i!=index-1)
			{
				var=var->next;
			}

		}
		#if DEBUG_MODE
			printf("delete variable:%s\n",var_next->name);
		#endif
		var->next=var_next->next;
		free(var_next);
		return true;
	}
	else
		return false;
}

/*
函数功能：销毁变量集合
输入：集合
输出：是否销毁成功
*/
bool variable_collection_destroy(variable_collection* collection)
{
	if (NULL==collection)
	{
		#if DEBUG_MODE
			printf("destroy collection successfully!It is NULL\n");
		#endif
			return true;
	}
	variable* var=collection->variable_head;
	for (int i = 0; i < collection->num; ++i)
	{
		collection->variable_head=var->next;
		free(var);
		var=collection->variable_head;
	}
	free(collection);
	#if DEBUG_MODE
		printf("destroy collection successfully!\n");
	#endif
	return true;
}

/*
函数功能：得到集合里面变量的个数
输入：集合 存放个数的指针
返回：是否成功得到值(注意：该函数永远返回为真)
*/
bool variable_collection_get_num(variable_collection *collection,int* num)
{
	if (NULL==collection)
	{
		*num=0;
		#if DEBUG_MODE
			printf("collection pointer is NULL,I set num to 0\n");
		#endif
		return true;
	}
	else
	{
		*num=collection->num;
		return true;
	}
}
/*
函数功能：给集合里面的所有元素赋相同的值，用于a=b=value的赋值
输入：集合 值
输出：是否赋值成功
*/
bool variable_collection_set_all_value(variable_collection* collection,double value)
{
	int num=0;
	if (NULL==collection)
	{
		/* code */
		#if DEBUG_MODE
			printf("collection pointer is NULL!no value to set\n");
		#endif
		return false;
	}
	variable_collection_get_num(collection,&num);
	variable* var=collection->variable_head;
	for (int i = 0; i < num; ++i)
	{
		variable_give_value(var,value);
		var=var->next;
	}
	return true;
}
/*
函数功能：将两个集合里面的变量结合到一个集合里面（集合到结合1里面）
参数 集合1 集合2
返回值 是否结合成功
注意：该函数执行后collection2被释放
*/
bool variable_collection_fuse(variable_collection* collection1,variable_collection *collection2)
{
	int num=0;
	if (NULL==collection1)
	{
		printf("error:pool is not initialized\n");
		return false;
	}
	if (NULL==collection2)
	{
		#if DEBUG_MODE
			printf("there is no variable to set value!\n");
		#endif
		return false;
	}
	variable_collection_get_num(collection2,&num);
	variable *var=collection2->variable_head;
	// collection2->variable_head=NULL;
	for (int i = 0; i < num; ++i)
	{
		char name[VARIABLE_SIZE]={0};
		double value=0;
		variable_get_name(var,name);
		variable_get_value(var,&value);
		variable* new_var=variable_init(name);
		if (!new_var)
		{
			/* code */
			#if DEBUG_MODE
				printf("initialize variable failed!\n");
			#endif
			return false;
		}
		variable_give_value(new_var,value);
		if(!variable_collection_add_variable(collection1,new_var))
		{
			#if DEBUG_MODE
				printf("add variable failed\n");
			#endif
			return false;
		}
		// free memory
		variable* var_next=var->next;
		free(var);
		var=var_next;
	}
	free(collection2);
	return true;
}
/*
函数功能：得到变量(通过等号的存在判断)
参数：infixExpress:原始输入(没有经过任何处理) 
		state 返回状态0 表示不能再往下计算
					1 表示可以往下继续
输出：返回值:存在变量----变量集合
			不存在----NULL
	infixExpression:不存在变量的计算表达式
注意：可能会有多个变量在同一个等式里面，比如"a=b=1",但是我们只支持一个变量;
*/
variable_collection* variable_collection_get_variable(char* infixExpression,int* state)
{
	//去掉首尾的空格
	string_remove_startandend_space(infixExpression);
	if (0==strlen(infixExpression))
	{
		printf("you input nothing or only space\n");
		*state=0;
		return NULL;
	}
	// 检测第一个字符是不是等号
	if ('='==infixExpression[0])
	{
		printf("\'=\' left has no variable. It is illegal!\n");
		*state=0;
		return NULL;
	}
	// 我们先反向寻找，切割出计算表达式
	char *calculation_equation=(char*)malloc(strlen(infixExpression));
	int variable_end=0;//变量的结束序号
	for (int i=strlen(infixExpression)-1; i>=0; --i)
	{
		if (0==i)//没有变量
		{
			#if DEBUG_MODE
				printf("no variable!\n");
			#endif
			free(calculation_equation);
			*state=1;
			return NULL;
		}
		if ('='==infixExpression[i])
		{
			strncpy(calculation_equation,infixExpression+i+1,strlen(infixExpression)-i);
			calculation_equation[strlen(infixExpression)-i+1]='\0';
			#if DEBUG_MODE
				printf("I get calculation_equation:%s\n",calculation_equation);
			#endif
			variable_end=i;
			break;
		}
	}
	//去掉计算式的首尾空格
	string_remove_startandend_space(calculation_equation);
	if (0==strlen(calculation_equation))
	{
		printf("no value to be calculated,please make sure you have input variable or calculation on the right of \'=\'\n");
		*state=0;
		return NULL;
	}
	// 下面切割变量
	variable_collection* collection=variable_collection_init();
	int variable_start=0;//下一个变量的开始点
	for (int i = 0; i < variable_end+1; ++i)
	{
		char name[VARIABLE_SIZE]={0};
		if ('='==infixExpression[i])
		{
			strncpy(name,infixExpression+variable_start,i-variable_start);
			if(false==string_remove_startandend_space(name))//去掉前后的空格
			{
				printf("you input continous \'=\'\n");
				*state=0;
				return NULL;
			}
			variable *new_variable=variable_init(name);
			if (NULL==new_variable)
			{
				free(calculation_equation);
				variable_destroy(new_variable);
				variable_collection_destroy(collection);
				collection=NULL;
				*state=0;
				return NULL;
				// break;
			}
			#if DEBUG_MODE
				printf("I get a variable:%s\n",name);
			#endif
			variable_start=i+1;
			if(!variable_collection_add_variable(collection,new_variable))
			{
				*state=0;
				return NULL;
			}
		}
	}
	memset(infixExpression,'\0',strlen(calculation_equation)+1);
	strcpy(infixExpression,calculation_equation);
	infixExpression[strlen(calculation_equation)]='\0';
	#if DEBUG_MODE
		int num=0;
		variable_collection_get_num(collection,&num);
		printf("I get total %d value\n", num);
	#endif
	//free memory
	free(calculation_equation);
	*state=1;
	return collection;
}

/*
函数功能：替换计算等式里面的变量值
输入：全局变量池 计算表达式(没有等号)
输出：替换个数 -1表示右错误发生
注意：同一个变量在同一个表达式里面可能有多个出现
	返回值负数阻止下面的操作，不一定代表有错误
*/
int variable_collection_replace(variable_collection *collection,char* infixExpression)
{
	int num=0;
	if (NULL==collection)
	{
		#if DEBUG_MODE
			printf("collection pool has not initialized\n");
		#endif
		return -1;
	}
	variable_collection_get_num(collection,&num);
	variable* var=collection->variable_head;
	if (NULL==var)
	{
		/* code */
		return 0;
	}
	int replace_num=0;
	//判断是否可以替换（匹配到的式一个独立变量，前后不是数字和字符以及下划线）
	for (int infixExpression_index = 0; infixExpression_index < strlen(infixExpression);)
	{
		char *ptr=strstr(infixExpression+infixExpression_index,var->name);
		//如果有，那么检查前后是否是空格
		if (ptr)
		{
			if (strlen(var->name)==strlen(infixExpression))//变量名和字符串等长，说明只是输入一个变量名
			{
				/* code */
				#if DEBUG_MODE
					printf("only variable,no calculation equation!\n");
				#endif
				char svalue[NUM_LENGTH]={0};
				sprintf(svalue,"%g",var->value);
				string_replace(var->name,svalue,infixExpression);
				return 1;//返回-2阻止后面的操作
			}
			if (infixExpression!=ptr)//不在第一个位置，则检查前一个位置
			{
				ptr--;
				if (*ptr>='0'&&*ptr<='9'||*ptr>='a'&&*ptr<='z'||
					*ptr>='A'&&*ptr<='Z'||'_'==*ptr) //不是变量
				{
					infixExpression_index++;
					continue;
				}
				ptr++;
				// infixExpression_index++;
			}
			// 检查字符串后面的字符
			char* ptr_end=ptr+strlen(var->name);
			if (*ptr_end>='0'&&*ptr_end<='9'||*ptr_end>='a'&&*ptr_end<='z'||
					*ptr_end>='A'&&*ptr_end<='Z'||'_'==*ptr_end)//不是变量
			{
				// ptr++;
				infixExpression_index++;
			}
			else//找到一个
			{
				//替换该变量
				char svalue[NUM_LENGTH]={0};
				sprintf(svalue,"%g",var->value);
				// ptr++;
				if(!string_replace(var->name,svalue,ptr))
				{
					return false;
				}
				replace_num++;

			}
		}
		else
		{
			var=var->next;
			if (NULL==var)
				break;
		}
	}
	#if DEBUG_MODE
		printf("%d variable is replaced\n", replace_num);
		printf("infixExpression after replace:%s\n",infixExpression);
	#endif
	return true;
}

/*
函数功能：打印变量集合里面所有变量
输入：变量集合
*/
void variable_collection_printf(variable_collection *collection)
{
	printf("******variable pool********\n\n");
	if (NULL==collection)
	{
		printf("\tno variable\n");
		printf("\n***************************\n\n");
		return ;
	}
	int num=0;
	variable_collection_get_num(collection,&num);
	if (0==num)
	{
		printf("\tno variable\n");
		printf("\n***************************\n\n");
		return ;
	}
	variable* var=collection->variable_head;
	// printf("variable in collection:\n");
	for (int i = 0; i < num; ++i)
	{
		printf("\t%s:%g\n",var->name,var->value);
		var=var->next;
	}
	printf("\n***************************\n\n");
	return ;
}