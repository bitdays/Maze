#ifndef DIY_API_H
#define DIY_API_H
#include"stdio.h"
#include"windows.h"
#include"string.h"
#include "conio.h"


#define MAX_CHOICE 16
#define MAX_CHAR 8

void gotoxy(int x,int y);
void SetColor();
void SetColorBack();
int Arrow_Control(int i,int j,const COORD mystack[],char choice[][MAX_CHAR+1]);
void Dynamic_Show_Menu(int i,int j,char choice[][MAX_CHAR+1],COORD mystack[],int mid=6,int todown=0,int toright=0,int margin=0);
void DrawConsoleBox(int i,int j,int todown=0,int toright=0,int cho=1);
#endif