#include "../include/expressionEvaluation.h"
//中缀转后缀函数
int infixToPostfix(char *infixExpression, char postfixExpression[])
{
	if (!check_all(infixExpression))
	{
		return 0;
	}
	//申请二维数组,用于切割开多位数,flatten一行一组字符
	char **flatten_input=(char**)malloc(sizeof(char*)*strlen(infixExpression));//申请中间存储空间
	if(NULL==flatten_input)
	{
		printf("memory malloc failed!\n");
		return 0;
	}
	for (int i = 0; i < strlen(infixExpression); ++i)
	{
		*(flatten_input+i)=(char*)malloc(strlen(infixExpression));
		if (NULL==*(flatten_input+i))
		{
			printf("memory malloc failed!\n");
		}
		memset(*(flatten_input+i),'\0',strlen(infixExpression));//初始化便于后面拉直取长度
	}
	// 切割多位数
	// char **temp=flatten_input;
	int flatten_row=0;//行
	int flatten_column=0;//列
	//第一个元素赋值
	*(*(flatten_input+flatten_row)+flatten_column)=infixExpression[0];
	*(*(flatten_input+flatten_row)+flatten_column+1)='\0';
	for (int i = 1; i < strlen(infixExpression); ++i)
	{
		//如果是数字
		if ((infixExpression[i]>='0'&&infixExpression[i]<='9'))
		{
			//如果前一位是非数字并且非小数点,那么到新的一行然后再保存
			if ((infixExpression[i-1]<'0'||infixExpression[i-1]>'9')&&'.'!=infixExpression[i-1])
			{
				flatten_row++;//移到下一行
				flatten_column=0;//列置0
				*(*(flatten_input+flatten_row)+flatten_column)=infixExpression[i];
				*(*(flatten_input+flatten_row)+flatten_column+1)='\0';
			}
			else
			{
				flatten_column++;//列往后移但是行不动
				*(*(flatten_input+flatten_row)+flatten_column)=infixExpression[i];
			}
		}
		//如果不是数字,需要转换行
		else if('*'==infixExpression[i]||'/'==infixExpression[i]||'+'==infixExpression[i]
				||'-'==infixExpression[i]||'('==infixExpression[i]||')'==infixExpression[i])
		{
			flatten_column=0;
			flatten_row++;
			*(*(flatten_input+flatten_row)+flatten_column)=infixExpression[i];
		}
		//小数点，前一位是数字字节拷贝
		else if('.'==infixExpression[i])
		{
			if (infixExpression[i-1]>='0'&&infixExpression[i-1]<='9')
			{
				flatten_column++;//列加1；
				*(*(flatten_input+flatten_row)+flatten_column)=infixExpression[i];
				*(*(flatten_input+flatten_row)+flatten_column+1)='\0';
			}
			else
				printf("error!\n");
		}
		else
		{
			printf("there is char which i can not recognise!\n");
			printf("%c\n", infixExpression[i]);
			return 0;
		}
	}

	//下面进行转换
	//申明算法中的输出
	char **temp_out=(char**)malloc(sizeof(char*)*strlen(infixExpression));
	if (NULL==temp_out)
	{
		/* code */
		printf("memory malloc failed!\n");
		return 0;
	}
	int temp_out_index=0;
	stackdata *stack_top=NULL;//栈指针
	int stack_size=100;
	stackdata *temp_stackdata=(stackdata*)malloc(sizeof(stackdata));//申请空间用于查看栈顶的元素
	for (int i = 0; i < flatten_row+1; ++i)
	{
		// 数字直接输出
		//操作数直接拷贝到temp_out
		if (**(flatten_input+i)>='0'&&**(flatten_input+i)<='9')
		{
			*(temp_out+temp_out_index)=*(flatten_input+i);
			temp_out_index++;
		}
		//"*"或者"/"
		else if ('*'==**(flatten_input+i)||'/'==**(flatten_input+i))
		{
			//栈未初始化,初始化栈并且压入
			if (NULL==stack_top)
			{
				stack_top=stack_array_init(*(flatten_input+i),stack_size);
			}
			//栈为空,直接压栈
			else if (stack_array_isempty(stack_top))
			{
				stack_top=stack_array_push(stack_top,*(flatten_input+i),&stack_size);
			}
			else//否则看看栈顶的元素,如果是+-则输出
			{
				while(true)
				{
					stack_top=stack_array_pop(stack_top,temp_stackdata);
					if (-1!=temp_stackdata->flag)//有数据弹出
					{
						//加号减号(,压栈
						if('+'==*(temp_stackdata->data)||'-'==*(temp_stackdata->data)||'('==*(temp_stackdata->data))
						{
							stack_top=stack_array_push(stack_top,temp_stackdata->data,&stack_size);
							// temp_stackdata=(stackdata*)malloc(sizeof(stackdata));
							stack_top=stack_array_push(stack_top,*(flatten_input+i),&stack_size);
							break;
						}
						//优先级一样,弹出并输出到temp_out;
						else if('*'==*(temp_stackdata->data)||'/'==*(temp_stackdata->data))
						{
							// 此处的*(temp_out+temp_out_index)居然指向栈底
							*(temp_out+temp_out_index)=temp_stackdata->data;//因为已经弹出,
							// temp_stackdata=(stackdata*)malloc(sizeof(stackdata));
							temp_out_index++;
						}
						else
						{
							printf("stack has error char:%c\n",*(temp_stackdata->data));
						}
					}
					else//没有数据,说明栈空,直接压栈
					{
						stack_top=stack_array_push(stack_top,*(flatten_input+i),&stack_size);
						break;
					}
				}
			}
		}
		else if (')'==**(flatten_input+i))//右括号,弹出直到左括号
		{
			/* code */
			while(true)
			{
				stack_top=stack_array_pop(stack_top,temp_stackdata);
				if ('('==*(temp_stackdata->data))//直到弹出左括号
				{
					break;
				}
				*(temp_out+temp_out_index)=temp_stackdata->data;
				// temp_stackdata=(stackdata*)malloc(sizeof(stackdata));
				temp_out_index++;
			}
		}
		else if('+'==**(flatten_input+i)||'-'==**(flatten_input+i))//如果是加减号
		{
			while(true)//直到栈空或者直到碰到(
			{
				//弹出元素
				//如果栈没有初始化
				//栈未初始化,初始化栈并且压入
				if (NULL==stack_top)
				{
					stack_top=stack_array_init(*(flatten_input+i),stack_size);
					break;
				}
				stack_top=stack_array_pop(stack_top,temp_stackdata);
				if (-1==temp_stackdata->flag)//没有元素弹出，直接压栈
				{
					stack_top=stack_array_push(stack_top,*(flatten_input+i),&stack_size);
					break;
				}
				else if ('('==*(temp_stackdata->data))//如果是(，两个都压栈
				{
					stack_top=stack_array_push(stack_top,temp_stackdata->data,&stack_size);
					// temp_stackdata=(stackdata*)malloc(sizeof(stackdata));
					stack_top=stack_array_push(stack_top,*(flatten_input+i),&stack_size);
					break;
				}
				else //其他符号都弹出并且输出
				{
					*(temp_out+temp_out_index)=temp_stackdata->data;
					// temp_stackdata=(stackdata*)malloc(sizeof(stackdata));
					temp_out_index++;
				}
			}
		}
		else if ('('==**(flatten_input+i))
		{
			//栈未初始化,初始化栈并且压入
			if (NULL==stack_top)
			{
				stack_top=stack_array_init(*(flatten_input+i),stack_size);
			}
			else
				stack_top=stack_array_push(stack_top,*(flatten_input+i),&stack_size);
		}
		else
		{
			printf("something wrong!\n");
			return -1;
		}
	}
	//判断栈是否为空，如果不空则弹出并且输出
	while(true)
	{
		if (NULL==stack_top)
		{
			break;
		}
		stack_top=stack_array_pop(stack_top,temp_stackdata);
		if (-1==temp_stackdata->flag)
		{
			break;
		}
		*(temp_out+temp_out_index)=temp_stackdata->data;
		temp_out_index++;
	}
	free(temp_stackdata);

	// 下面把temp_out里面的数据进行拉直输出
	// memset(postfixExpression,'\0',sizeof(postfixExpression))
	int postfixExpression_index=0;
	for (int row = 0; row < temp_out_index; ++row)
	{
		for (int column = 0; column < strlen(*(temp_out+row)); ++column)
		{
			postfixExpression[postfixExpression_index]=temp_out[row][column];
			postfixExpression_index++;
		}
		postfixExpression[postfixExpression_index]=' ';
		postfixExpression_index++; 
	}
	postfixExpression[postfixExpression_index-1]='\0';//回退一位，去掉最后一个空格
	// free memory
	for (int i = 0; i < strlen(infixExpression); ++i)
	{
		free(*(flatten_input+i));
	}
	return true;
}
int getNext(char* postfixExpression,int * index,double* res)
{
/*
return value:		0--- number
			1--- +
			2--- -
			3--- *
			4--- /
*/
	*res=0;
	int isradix=0;//是否是小数,0表示不是小数部分，大于0表示小数第几位
	if ('+'==postfixExpression[*index])
	{
		*index+=2;
		return 1; 
	}
	else if ('-'==postfixExpression[*index])
	{
		*index+=2;
		return 2;
	}
	else if ('*'==postfixExpression[*index])
	{
		*index+=2;
		return 3;
	}
	else if ('/'==postfixExpression[*index])
	{
		*index+=2;
		return 4;
	}
	else if (postfixExpression[*index]>='0'&&postfixExpression[*index]<='9')
	{
		for (int i = *index; i < strlen(postfixExpression); ++i)
		{
			if (' '==postfixExpression[i])//空格结束符
			{
				*index=i+1;
				return 0;
			}
			else if ('.'==postfixExpression[i])//小数点
			{
				isradix++;
			}
			else if(0==isradix)//整数部分
			{
				*res*=10;
				*res+=postfixExpression[i]-'0';
			}
			else if (0<isradix)//小数部分
			{
				double temp=postfixExpression[i]-'0';
				for (int j = 0; j < isradix; ++j)
				{
					temp=(double)(temp)/10;
				}
				*res+=temp;
				isradix++;
			}
			else
			{
				printf("number recognise failed!\n");
				return -1;
			}
		}
		//end all
		*index=strlen(postfixExpression);
		return 0;
	}
	else
	{
		printf("there is char i can not recognise!:%c\n",postfixExpression[*index]);
		return -1;
	}

}
//计算后缀的值
int computeValueFromPostfix(char *postfixExpression, double *value)
{
	int postfixExpression_index=0;
	double str2int=0;
	int res=-1;
	stackdata* stack=NULL;
	int stack_size=100;
	while(true)
	{
		str2int=0;
		res=-1;
		res=getNext(postfixExpression,&postfixExpression_index,&str2int);
		if (0==res)
		{
			// push it to stack
			double *new=(double*)malloc(sizeof(double));//该空间要在下面进行释放，特别重要且容易忽略
			*new=str2int;
			if (NULL==stack)
			{
				stack=stack_array_init((char*)new,stack_size);
			}
			else
				stack=stack_array_push(stack,(char*)new,&stack_size);
		}
		else if (1==res)
		{
			// get two number from stack to cal
			double num_one=0;
			double num_two=0;
			stackdata *temp_one=(stackdata*)malloc(sizeof(stackdata));//这里不应该用指针申请空间
			stackdata *temp_two=(stackdata*)malloc(sizeof(stackdata));
			stack=stack_array_pop(stack,temp_one);
			stack=stack_array_pop(stack,temp_two);
			num_one=*(double*)(temp_one->data);
			num_two=*(double*)(temp_two->data);
			free(temp_one->data);
			free(temp_two->data);
			free(temp_one);
			free(temp_two);
			double *cal=(double*)malloc(sizeof(double));
			*cal=num_one+num_two;
			stack=stack_array_push(stack,(char*)cal,&stack_size);

		}
		else if (2==res)
		{
			/* code */
			double num_one=0;
			double num_two=0;
			stackdata *temp_one=(stackdata*)malloc(sizeof(stackdata));
			stackdata *temp_two=(stackdata*)malloc(sizeof(stackdata));
			stack=stack_array_pop(stack,temp_one);
			stack=stack_array_pop(stack,temp_two);
			num_one=*(double*)(temp_one->data);
			num_two=*(double*)(temp_two->data);
			free(temp_one->data);
			free(temp_two->data);
			free(temp_one);
			free(temp_two);
			double *cal=(double*)malloc(sizeof(double));
			*cal=num_two-num_one;
			stack=stack_array_push(stack,(char*)cal,&stack_size);
		}
		else if (3==res)
		{
			/* code */
			double num_one=0;
			double num_two=0;
			stackdata *temp_one=(stackdata*)malloc(sizeof(stackdata));
			stackdata *temp_two=(stackdata*)malloc(sizeof(stackdata));
			stack=stack_array_pop(stack,temp_one);
			stack=stack_array_pop(stack,temp_two);
			num_one=*(double*)(temp_one->data);
			num_two=*(double*)(temp_two->data);
			free(temp_one->data);
			free(temp_two->data);
			free(temp_one);
			free(temp_two);
			double *cal=(double*)malloc(sizeof(double));
			*cal=(double)num_one*num_two;
			stack=stack_array_push(stack,(char*)cal,&stack_size);
		}
		else if (4==res)
		{
			/* code */
			double num_one=0;
			double num_two=0;
			stackdata *temp_one=(stackdata*)malloc(sizeof(stackdata));
			stackdata *temp_two=(stackdata*)malloc(sizeof(stackdata));
			stack=stack_array_pop(stack,temp_one);
			stack=stack_array_pop(stack,temp_two);
			num_one=*(double*)(temp_one->data);
			num_two=*(double*)(temp_two->data);
			free(temp_one->data);
			free(temp_two->data);
			free(temp_one);
			free(temp_two);
			double *cal=(double*)malloc(sizeof(double));
			if(0==num_one)
			{
				printf("error:divide by zerro! \n");
				return -1;
			}
			else
			{
				*cal=(double)num_two/num_one;
				stack=stack_array_push(stack,(char*)cal,&stack_size);
			}
		}
		else
		{
			printf("wrong return value\n");
			return -1;
		}
		if (strlen(postfixExpression)<=postfixExpression_index)
		{
			stackdata *temp=(stackdata*)malloc(sizeof(stackdata));
			stack=stack_array_pop(stack,(stackdata*)temp);
			*value=*(double*)(temp->data);
			free(temp->data);
			free(temp);
			return true;
		}
	}
}