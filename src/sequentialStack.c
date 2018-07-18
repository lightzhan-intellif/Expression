#include "../include/sequentialStack.h"
// 下面是数组的实现
stackdata *stack_array_init(datatype data,int size)
{
	stackdata *stack=(stackdata*)malloc(sizeof(stackdata)*size);
	if (NULL==stack)
	{
		/* code */
		printf("memory malloc failed\n");
		return NULL;
	}
	stack[0].data=data;
	stack[0].flag=0;
	return stack;
}
stackdata* stack_array_push(stackdata *stack,datatype data,int *psize)
{
	//判断栈是否已满
	if (stack->flag>=*psize-1)
	{
		int add_count=20;
		printf("stack is full,has been enlarged  automatically!\n");
		stackdata* temp=stack_array_enlarge(stack,psize,*psize+add_count);//栈满自动扩容
		if (NULL==temp)
		{
			/* code */
			printf("enlarge memory failed!\n");
			return NULL;
		}
		stack=temp;
		// *psize+=add_count;
		// return stack;
	}
	// 如果栈为空
	if (-1==stack->flag)
	{
		stack->flag=0;
		stack->data=data;
		return stack;
	}
	(stack+1)->data=data;
	(stack+1)->flag=stack->flag+1;
	stack=stack+1;
	return stack;
}
stackdata* stack_array_pop(stackdata *stack,stackdata *pop)
{
/*
	该函数的返回值:
	如果stack->flag值为-1,表示栈为空,否则不为空(为0时表示栈底,大于0时是序号)
	如果pop->flag值为-1,表示没有数据弹出
 */
	if (0==stack->flag)
	{
		// printf("栈为空\n");
		stack->flag=-1;
		pop->data=stack->data;
		pop->flag=0;
		return stack;
	}
	if (-1==stack->flag)
	{
		// printf("栈为空\n");
		pop->flag=-1;
		return stack;
	}
	pop->flag=0;//说明有值
	pop->data=stack->data;
	stack=stack-1;
	return stack;
}
bool stack_array_isfull(stackdata *stack,int size)
{
	if (stack->flag>=size-1)
	{
		return true;
	}
	else
		return false;
}
bool stack_array_isempty(stackdata *stack)
{
	if (-1==stack->flag)
	{
		return true;
	}
	else
		return false;
}
stackdata* stack_array_enlarge(stackdata *stack,int *psize,int new_size)
{
	//判断新值是否大于久值
	if (new_size<=*psize)
	{
		printf("illegal input\n");
		return NULL;
	}
	//找到起始地址
	int flag=stack->flag;//元素个数
	stackdata *start=stack;
	while(true)
	{
		if (start->flag<=0)//栈为空或者找到起始地址
		{
			break;
		}
		start--;
	}
	//申请新空间
	//注意,该函数会重新找地方申请空间,也就是指针指向会变而原始值会被拷贝
	stack=(stackdata*)realloc(start,sizeof(stackdata)*new_size);
	if (NULL==stack)
	{
		/* code */
		printf("enlarge memory failed!\n");
		return NULL;
	}
	*psize=new_size;
	if (-1==flag)//栈为空
	{
		;
	}
	else
		stack+=flag;
	return stack;
}
/*void stack_array_printf(stackdata* stack)
{
	printf("stack data is:\n");
	if (-1==stack->flag)
	{
		printf("stack is empty\n");
		return ;
	}
	printf("top->");
	for (int i = 0; ; ++i)
	{
		printf("%d->",(stack-i)->data);
		if (0==(stack-i)->flag)
		{
			break;
		}		
	}
	printf("bottom\n");
}
void stack_array_test()
{
	int size=5;//栈的大小
	printf("note:the size of stack is %d!\n",size);
	printf("please input initialization data: ");
	datatype data;
	scanf("%d",&data);
	stackdata *stack=stack_array_init(data,size);
	if(NULL==stack)
	{
		printf("memory malloc failed\n");
		return ;
	}
	while(true)
	{
		stack_array_printf(stack);
		int op=0;
		printf("please choose operation:1.push 2.pop 3.batch push 4.batch pop 5.enlarge 6.isfull 7.isempty 8.exit:");
		scanf("%d",&op);
		if (1==op)
		{
			printf("please input push  data: ");
			scanf("%d",&data);
			stack=stack_array_push(stack,data,&size);
		}
		else if (2==op)
		{
			stackdata* pop_data=(stackdata*)malloc(sizeof(stackdata));
			if (NULL==pop_data)
			{
				printf("memory malloc failed!\n");
				return ;
			}
			pop_data->flag=0;//初始化为栈不为空
			stack=stack_array_pop(stack,pop_data);
			if (-1==stack->flag&&-1==pop_data->flag)
			{
				;
			}
			else
				printf("pop data:%d\n",pop_data->data);
			free(pop_data);
		}
		else if (3==op)//批量压入
		{
			int number=0;//需要压栈的数量
			printf("how many random numbers do you want to push?:");
			scanf("%d",&number);
			for (int i = 0; i < number; ++i)
			{
		
				int data=rand();
				stack=stack_array_push(stack,data,&size);
			
			}
		}
		else if (4==op)//批量弹出
		{
			int number=0;
			printf("how many numbers do you want to pop?:");
			scanf("%d",&number);
			stackdata* pop_data=(stackdata*)malloc(sizeof(stackdata));
			if (NULL==pop_data)
			{
				printf("memory malloc failed\n");
				return ;
			}
			for (int i = 0; i < number; ++i)
			{
				if (-1==stack->flag)
				{
					// free(stack);
					printf("only pop %d numbers successfully,because stack is empty now\n",i);
					break;
				}
				pop_data->flag=0;
				stack=stack_array_pop(stack,pop_data);
			}
			free(pop_data);
			pop_data=NULL;
		}
		else if (5==op)//扩容
		{
			printf("now,size is %d\n",size);
			printf("you want to enlarge it to:?");
			int new_size=0;
			scanf("%d",&new_size);
			stack=stack_array_enlarge(stack,&size,new_size);
			if(NULL!=stack)
			{
				// size=new_size;
				printf("now size is %d\n",size);
			}
		}
		else if (6==op)
		{
			if (stack_array_isfull(stack,size))
			{
				printf("stack is full\n");
			}
			else
				printf("stack is not full\n");
		}
		else if (7==op)
		{
			if (stack_array_isempty(stack))
			{
				printf("stack is empty\n");
			}
			else
				printf("stack is not empty\n");
		}
		else if (8==op)
		{
			//回收空间
			while(true)
			{
				stackdata* pop_data=(stackdata*)malloc(sizeof(stackdata));
				if (NULL==pop_data)
				{
					printf("memory malloc failed!\n");
					return ;
				}
				pop_data->flag=0;//初始化为栈不为空
				stack=stack_array_pop(stack,pop_data);
				if (-1==stack->flag&&-1==pop_data->flag)
				{
					free(stack);
					break;
				}
				free(pop_data);
			}
			break;
		}
		else
			printf("choose error\n");
	}
}*/