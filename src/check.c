#include "../include/check.h"
/*
函数功能：判断是否为空表达式（除开空格）
参数：infixExpression：未去掉空格的输入
函数返回值：CHECK_OK：非空表达式
			CHECK_ERROR：空表达式

 */
int check_empty(char *infixExpression)
{
	for (int i = 0; i < strlen(infixExpression); ++i)
	{
		// 存在不为空格的字符，说明非空
		if (' '!=infixExpression[i])
		{
			return CHECK_OK;
		}
	}
	printf("no any number and operation!\n");
	return CHECK_ERROR;
}

/*
函数功能：检查非法字符
输入参数：未去掉空格的输入(经过以上函数的判断)
函数返回值:CHECK_OK：不存在非法字符
			CHECK_ERROR：存在非法字符
 */
int check_illegal_character(char *infixExpression)
{
	for (int i = 0; i < strlen(infixExpression); ++i)
	{
		char temp=infixExpression[i];
		if (temp>='0'&&temp<='9')
		{
			;
		}
		else if ('+'==temp||'-'==temp||'*'==temp||'/'==temp||
			'('==temp||')'==temp||'.'==temp||' '==temp)
		{
			;
		}
		else
		{
			#if VARIABLE_MODE
				printf("there are illegal characters or undefined variables when calculating!\n");
			#else
				printf("illegal character is checked:%c\n",temp);
			#endif
			return CHECK_ERROR;
		}
	}
	return CHECK_OK;
}


/*
函数功能：检查是否两个个操作数之间不存在操作符
参数：未去掉空格的输入(经过上述函数的判断)
输出：CHECK_OK---不存在
		CHECK_ERROR---存在
 */
int check_operation_between_two_number(char *infixExpression)
{
	//寻找空格，查看空格的两边是否都是数字
	for (int i = 0; i < strlen(infixExpression)-1; ++i)
	{
		char temp=infixExpression[i];
		char temp_next=infixExpression[i+1];
		//该字符是数字并且下一个字符是空格，检测空格对岸的字符是否是数字
		if (temp>='0'&&temp<='9'&&' '==temp_next)
		{
			for (int j = i+1; j < strlen(infixExpression); ++j)
			{
				if(' '==infixExpression[j])//跳过多个连续的空格
				{
					;
				}
				else if (infixExpression[j]>='0'&&infixExpression[j]<='9')
				{
					//非法
					printf("lack operator between numbers\n");
					return CHECK_ERROR;
				}
				else
					break;//其它字符则合法
			}
		}
	}
	return CHECK_OK;
}

/*
函数功能：去掉输入里面的空格
参数：未去掉空格的输入（经过上述处理），该指针的地址还会返回结果
输出：CHECK_OK：操作成功
		CHECK_ERROR：操作失败
 */
int check_delete_space(char* infixExpression)
{
	char *temp=(char*)malloc(strlen(infixExpression));
	if (NULL==temp)
	{
		/* code */
		printf("memory malloc failed!\n");
		return CHECK_ERROR;
	}
	memset(temp,'\0',strlen(infixExpression));
	int temp_index=0;
	for (int i = 0; i < strlen(infixExpression); ++i)
	{
		if (' '!=infixExpression[i])
		{
			temp[temp_index]=infixExpression[i];
			temp_index++;			
		}
	}
	// temp[temp_index]='\0';
	memset(infixExpression,'\0',strlen(infixExpression));
	//拷贝结果
	strcpy(infixExpression,temp);
	infixExpression[temp_index]='\0';
	free(temp);
	return CHECK_OK;
}

/*
函数功能：检查表达式的开始第一个数字之前是除了(，+，-，外的)，*，/
参数：去掉空格的输入（经过以上函数检查）
输出：CHECK_OK：成功通过检测
		CHECK_ERROR：未能通过检测
 */
int check_start(char *infixExpression)
{
	for (int i = 0; i < strlen(infixExpression); ++i)
	{
		char temp=infixExpression[i];
		if ('*'==temp||'/'==temp||')'==temp)
		{
			printf("\"%c\" can not be before the first number\n",temp);
			return CHECK_ERROR;
		}
		else if (temp>='0'&&temp<='9')
		{
			return CHECK_OK;
		}
		else
			;
	}
	printf("no number character!\n");
	return CHECK_ERROR;
}

/*
函数功能：检查表达式的结尾倒数第一个数字之后是否是除了右括号而外的字符
输入：去掉空格的输入
输出：CHECK_OK：成功通过检测
		CHECK_ERROR：未能通过检测
 */
int check_end(char *infixExpression)
{
	for (int i = strlen(infixExpression)-1; i >=0; --i)
	{
		if (')'==infixExpression[i])
		{
			;
		}
		else if (infixExpression[i]>='0'&&infixExpression[i]<='9')
		{
			return CHECK_OK;
		}
		else
		{
			printf("the last \'%c\' is illegal\n",infixExpression[i]);
			return CHECK_ERROR;
		}
	}
	printf("no number character!\n");
	return CHECK_ERROR;
}

/*
函数功能：检查是否存在两个连续的操作符
输入：去掉空格的输入
输出：CHECK_OK：成功通过检测
		CHECK_ERROR：未能通过检测
 */
int check_two_continuous_operator(char* infixExpression)
{
	for (int i = 0; i < strlen(infixExpression)-1; ++i)
	{
		char temp=infixExpression[i];
		char temp_next=infixExpression[i+1];
		if ('*'==temp||'/'==temp||'+'==temp||'-'==temp)
		{
			if ('*'==temp_next||'/'==temp_next||'+'==temp_next||'-'==temp_next)
			{
				printf("there are two continuous operator!It is illegal\n");
				return CHECK_ERROR;
			}
		}
	}
	return CHECK_OK;
}

/*
函数功能：括号配对检查(使用栈)
输入：去掉空格的输入
输出：CHECK_OK：成功通过检测
		CHECK_ERROR：未能通过检测
 */
int check_brackets_pair(char *infixExpression)
{

	stackdata *stack=NULL;
	for (int i = 0; i < strlen(infixExpression); ++i)
	{
		char temp=infixExpression[i];
		int stack_size=strlen(infixExpression);
		if ('('==temp)//左括号入栈
		{
			char* left_brackets=(char*)malloc(sizeof(char));
			*left_brackets='(';
			if (NULL==stack)//初始化栈
			{
				stack=stack_array_init(left_brackets,stack_size);
				if (NULL==stack)
				{
					/* code */
					printf("memory malloc failed!\n");
					return CHECK_ERROR;
				}
			}
			else
				stack=stack_array_push(stack,left_brackets,&stack_size);
		}
		else if (')'==temp)//右括号出栈
		{
			if (NULL==stack)//没有左括号
			{
				printf("barckets are not pairs\n");
				return CHECK_ERROR;
			}
			stackdata temp_stackdata;
			stack=stack_array_pop(stack,&temp_stackdata);
			free(temp_stackdata.data);//释放掉上面申请的空间
			if (-1==temp_stackdata.flag)//没有左括号，出错
			{
				printf("barckets are not pairs\n");
				return CHECK_ERROR;
			}
		}
		else
			;
	}
	// 检查是否栈空
	if (NULL==stack)
	{
		;
	}
	else if (!stack_array_isempty(stack))
	{
		//释放空间
		stackdata temp_stackdata;
		while(!stack_array_isempty(stack))
		{
			stack=stack_array_pop(stack,&temp_stackdata);
			free(temp_stackdata.data);
		}
		free(stack);
		stack=NULL;
		printf("barckets are not pairs\n");
		return CHECK_ERROR;
	}
	else
	return CHECK_OK;
}

/*
检查是否存在“(*”和“(/”
输入:去掉空格的输入
输入：去掉空格的输入(经过上面的处理)
输出：CHECK_OK：成功通过检测
		CHECK_ERROR：未能通过检测
 */
int check_leftbracket_operator(char* infixExpression)
{
	for (int i = 0; i < strlen(infixExpression)-1; ++i)
	{
		char temp=infixExpression[i];
		char temp_next=infixExpression[i+1];
		if ('('==temp&&('*'==temp_next||'/'==temp_next))
		{
			printf("left barcket can not be follow by \'%c\'\n",temp_next);
			return CHECK_ERROR;
		}
	}
	return CHECK_OK;
}

/*
检查是否存在操作符+“)”
输入：去掉空格的输入(经过上面函数的处理和检查)
输出：CHECK_OK：成功通过检测
		CHECK_ERROR：未能通过检测
 */
int check_operator_rightbracket(char *infixExpression)
{
	for (int i = 0; i < strlen(infixExpression)-1; ++i)
	{
		char temp=infixExpression[i];
		char temp_next=infixExpression[i+1];
		if (('+'==temp||'-'==temp||'*'==temp||'/'==temp)&&')'==temp_next)
		{
			printf("lack a number behind \"%c\"\n",temp);
			return CHECK_ERROR;
		}
	}
	return CHECK_OK;
}

/*
函数功能：检查是否存在括号加数字,如")8","8("
输入：去掉空格的输入(经过上面函数处理和检查)
输出：CHECK_OK：成功通过检测
		CHECK_ERROR：未能通过检测
*/
int check_bracket_number(char* infixExpression)
{
	for (int i = 0; i < strlen(infixExpression)-1; ++i)
	{
		if (')'==infixExpression[i]&&'0'<=infixExpression[i+1]&&'9'>=infixExpression[i+1])
		{
			printf("lack an operator between right barcket and number\n");
			return CHECK_ERROR;
		}
		if ('('==infixExpression[i]&&i>0&&'0'<=infixExpression[i-1]&&'9'>=infixExpression[i-1])
		{
			printf("lack an operator between number and left barcket\n");
			return CHECK_ERROR;
		}

	}
	return CHECK_OK;
}

/*
函数功能：检查是否存在"(+","(-"有的话括号后面填0以支持负数运算,同时检查表达式是否是+ -开头的
函数输入：去掉空格后的输入(经过上面函数的处理和检查)，以及填'0'修改后的输入
输出：CHECK_OK：成功通过检测
		CHECK_ERROR：未能通过检测
*/
int check_negative_number(char *infixExpression)
{
	char *temp=(char*)malloc(strlen(infixExpression)*2);
	if (NULL==temp)
	{
		/* code */
		printf("memory malloc failed!\n");
		return CHECK_ERROR;
	}
	int temp_index=0;
	for (int i = 0; i < strlen(infixExpression)-1; ++i)
	{
		if (0==i&&('+'==infixExpression[i]||'-'==infixExpression[i]))
		{
			temp[temp_index]='0';
			temp_index++;
		}
		if ('('==infixExpression[i]&&('+'==infixExpression[i+1]||'-'==infixExpression[i+1]))
		{
			temp[temp_index]=infixExpression[i];
			temp_index++;
			temp[temp_index]='0';
			temp_index++;
			// temp[++temp_index]=infixExpression[i+1]
		}
		else
		{
			temp[temp_index]=infixExpression[i];
			temp_index++;
		}

	}
	temp[temp_index]=infixExpression[strlen(infixExpression)-1];
	temp_index++;
	temp[temp_index]='\0';
	//拷贝
	memset(infixExpression,'\0',strlen(temp)+1);
	strncpy(infixExpression,temp,temp_index);
	infixExpression[temp_index]='\0';
	#if DEBUG_MODE
	printf("check_negative_number function output string:%s\n",infixExpression);
	#endif
	free(temp);
	return CHECK_OK;
}


/*
函数功能：依次调用上面的函数
输入：原始输入
输出：CHECK_OK：成功通过检测
		CHECK_ERROR：未能通过检测
*/
int check_calculaion(char* infixExpression)
{
	if (!check_empty(infixExpression))
	{
		return CHECK_ERROR;
	}
	if (!check_illegal_character(infixExpression))
	{
		return CHECK_ERROR;
	}
	if (!check_operation_between_two_number(infixExpression))
	{
		return CHECK_ERROR;
	}
	if (!check_delete_space(infixExpression))
	{
		return CHECK_ERROR;
	}
	if (!check_start(infixExpression))
	{
		return CHECK_ERROR;
	}
	if (!check_end(infixExpression))
	{
		return CHECK_ERROR;
	}
	if (!check_two_continuous_operator(infixExpression))
	{
		return CHECK_ERROR;
	}
	if (!check_brackets_pair(infixExpression))
	{
		return CHECK_ERROR;
	}
	if (!check_leftbracket_operator(infixExpression))
	{
		return CHECK_ERROR;
	}
	if (!check_operator_rightbracket(infixExpression))
	{
		return CHECK_ERROR;
	}
	if (!check_bracket_number(infixExpression))
	{
		return CHECK_ERROR;
	}
	if (!check_negative_number(infixExpression))
	{
		return CHECK_ERROR;
	}
	return CHECK_OK;
}