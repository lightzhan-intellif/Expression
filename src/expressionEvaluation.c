#include "../include/expressionEvaluation.h"
#include "../include/sequentialStack.h"
//中缀转后缀函数
int infixToPostfix(char *infixExpression, char postfixExpression[])
{
	//申请二维数组,用于切割开多位数,flatten一行一组字符
	char **flatten_input=(char**)malloc(sizeof(char*)*strlen(infixExpression));//申请中间存储空间
	if(NULL==flatten_input)
	{
		printf("memory malloc failed!\n");
		return NULL;
	}
	for (int i = 0; i < strlen(infixExpression); ++i)
	{
		*(flatten_input+i)=(char*)malloc(strlen(infixExpression));
		if (NULL==*(flatten_input+i))
		{
			printf("memory malloc failed!\n");
		}
		memset(*(flatten_input+i),'\0',sizeof(infixExpression));//初始化便于后面拉直取长度
	}
	// 切割多位数
	// char **temp=flatten_input;
	int flatten_row=0;//行
	int flatten_column=0;//列
	//第一个元素赋值
	*(*(flatten_input+flatten_row)+flatten_column)=infixExpression[0];
	for (int i = 1; i < strlen(infixExpression); ++i)
	{
		//如果是数字
		if (infixExpression[i]>='0'&&infixExpression[i]<='9')
		{
			//如果前一位是非数字,那么到新的一行然后再保存
			if (infixExpression[i-1]<'0'||infixExpression[i-1]>'9')
			{
				flatten_row++;//移到下一行
				flatten_column=0;//列置0
				*(*(flatten_input+flatten_row)+flatten_column)=infixExpression[i];
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
		else
		{
			printf("there is char which i can not recognise!\n");
			printf("%c\n", infixExpression[i]);
			return NULL;
		}
	}

	//下面进行转换
	//申明算法中的输出
	char **temp_out=(char**)malloc(sizeof(char*)*sizeof(infixExpression));
	if (NULL==temp_out)
	{
		/* code */
		printf("memory malloc failed!\n");
		return NULL;
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
						/* code */
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
		stack_top=stack_array_pop(stack_top,temp_stackdata);
		if (-1==temp_stackdata->flag)
		{
			break;
		}
		*(temp_out+temp_out_index)=temp_stackdata->data;
		temp_out_index++;
	}
	// free(temp_stackdata);

	// 下面把temp_out里面的数据进行拉直输出
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
	return true;
}
//计算后缀的值
int computeValueFromPostfix(char *postfixExpression, double *value)
{

}