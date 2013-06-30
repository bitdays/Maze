#include "stack.h"
#include "stdio.h"
int InitStack(Stack&s)
{
	int ret=1;
	s.base=(Pos*)malloc(INIT_SIZE*sizeof(Pos));
	if(!s.base)
	{
		printf("allocing memory failed!\n");
		ret=0;
		return ret;
	}
	s.top=s.base;
	s.size=INIT_SIZE;
	return ret;
}
int Push(Stack&s,Pos e)
{
	int ret=1;
	if(s.top-s.base==s.size)//Stack if full
	{
		s.base=(Pos*)realloc(s.base, (s.size+INCREMENT)*sizeof(Pos));
		if(!s.base)
		{
			printf("allocing memory failed!\n");
			ret=0;
			return ret;
		}
		s.top=s.base+s.size;
		s.size+=INCREMENT;
	}


	*s.top++=e;
	return ret;
}
int Pop(Stack&s,Pos& e)
{
	int ret=0;
	if(!StackEmpty(s))
	{
		e=*--s.top;
		ret=1;
	}
	return ret;
}
Pos GetTop(Stack s)
{
	return *(s.top-1);
}
int StackEmpty(Stack s)
{
	if(s.top==s.base)
		return 1;
	else return 0;
}
int StackLen(Stack s)
{
	return s.top-s.base;
}
