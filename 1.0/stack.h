#ifndef STACK_H_
#define STACK_H_
#include <malloc.h>
#define INCREMENT 5
#define INIT_SIZE 10

struct Pos{
	int i;
	int j;
};
struct Stack{
	Pos* base;
	Pos* top;
	int size;
};
int InitStack(Stack&s);
int Push(Stack&,Pos);
int Pop(Stack&,Pos &e);
Pos GetTop(Stack);
Pos GetTopNext(Stack);
int StackEmpty(Stack);
int StackLen(Stack);

#endif