#include "stack.h"
#include "api.h"
#include <conio.h>
#include <windows.h>
#include <stdio.h>



struct maze_info
{
	int mx;
	int my;
	Pos start;
	Pos end;
	int **ma;
};
//����8������������һ��ͨ·
Pos NextPos(Pos p,int n);
void InitMatrix(int** &m,int mx,int my);
void Success(Stack& s);
void FindMaze(Pos start,Pos end,int**m,int mode=1);
void SetMatrix(int** &m,int& x,int& my,struct Pos& start,struct Pos& end);
void ShowMatrix(int**m,int mx,int my);
void Find_main(int guimo,Pos start, Pos end);
void Free(int** &m);
void Find_default();
maze_info Find_Load();//û���ͷ��ڴ棬Ҫ�������������ͷ��ڴ�

