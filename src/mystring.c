#include "../include/mystring.h"
/*
函数功能：字符串替换函数
输入：dest 被替换的字符串
	src 用于替换的字符串
	str 替换其中的dest字符串，其中该指针已经指向需要替换字符的开始
返回值：是否替换成功
*/
bool string_replace(char* dest,char* src,char* str)
{
	if (NULL==dest||NULL==src||NULL==str)
	{
		printf("there are NULL pointer!I can not repalce\n");
		return false;
	}
	//检查dest和str开始的字符是否相等
	for (int i = 0; i < strlen(dest); ++i)
	{
		if (dest[i]==str[i])
		{
			;
		}
		else
		{
			printf("str \"%s\" do not have dest \"%s\"\n",str,dest);
			return false;
		}
	}
	char temp[MAX_INPUT_LENGTH]={0};
	temp[0]='(';//括号括起来防止负数
	strcpy(&temp[1],src);
	temp[strlen(src)+1]=')';
	temp[strlen(src)+2]='\0';
	// str+=strlen(dest);
	strcpy(&temp[strlen(src)+2],str+strlen(dest));
	memset(str,'\0',strlen(temp)+1);
	strcpy(str,temp);
	#if DEBUG_MODE
		printf("I repalce \"%s\" with \"%s\" .I get \"%s\"\n",dest,src,str,temp);
	#endif
	return true;
}

/*
函数功能：去掉字符串前后的空格
输入：字符串
输出：是否去掉成功
*/
bool string_remove_startandend_space(char* str)
{
	if (NULL==str)
	{
		printf("input ptr is NULL,I can not remove space from it\n");
		return false;
	}
	int start=0;//拷贝开始位置
	int end=0;//拷贝结束指针
	char *ptr=str;
	// 排除只有空格的情况
	int space_num=0;
	for (space_num = 0; space_num < strlen(str); ++space_num)
	{
		if (' '!=str[space_num])
		{
			break;
		}		
	}
	if (space_num==strlen(str))
	{
		#if DEBUG_MODE
			printf("string has nothing except space!\n");
		#endif
		printf("you input continous \'=\'!\n");
		str[0]='\0';
		return false;
	}
	//找到开始指针
	for (int i = 0; i < strlen(str); ++i)
	{
		if (' '!=*(ptr+i))
		{
			start=i;
			break;
		}
	}
	//找到结束指针
	for (int i = strlen(str)-1; i>=0; --i)
	{
		if (' '!=*(ptr+i))
		{
			end=i;
			break;
		}
	}
	if (0==start&&strlen(str)-1==end)
	{
		#if DEBUG_MODE
			printf("no any space at start and end:\"%s\"\n",str);
		#endif
		return true;
	}
	else
	{
		#if DEBUG_MODE
			printf("remove space from \"%s\",", str);
		#endif
		for (int i = 0; i < end-start+1; ++i)
		{
			str[i]=str[i+start];
		}
		str[end-start+1]='\0';
		#if DEBUG_MODE
			printf("get \"%s\"\n", str);
		#endif
		return true;
	}
}