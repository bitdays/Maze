#include "maze.h"
#include "api.h"
//按照8个方向搜索下一个通路
Pos NextPos(Pos p,int n)
{
	Pos t;
	Pos vector[9]={{0,0},
	{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1}
	};
	t.i=p.i+vector[n].i;
	t.j=p.j+vector[n].j;
	return t;
}
void InitMatrix(int** &m,int n,int p)
{
	int i,j;
	m=(int* *)malloc(sizeof(int*)*n);
	for(i=0;i<n;++i)
		m[i]=(int*)malloc(sizeof(int)*p);
		
	for(i=0;i<n;++i)
		for(j=0;j<p;++j)
				m[i][j]=0;
	for(i=0;i<n; ++i)
	{
		m[i][p-1]=1;
		m[i][0]=1;
	}
	for(j=0; j<p; ++j)
	{
		m[0][j]=1;
		m[n-1][j]=1;
	}
	

}
void Success(Stack& s)
{
	//映射路径方向
	int map[3][3]={ 0,1,2,
					3,4,5,
					6,7,8};
	char charset[9][3]={"↖","↑","↗",
						"←","？","→",
						"↙","↓","↘"};
	Pos e;
	Pos e_next;
	//t为实际的路径
	Stack t;
	InitStack(t);
	gotoxy(0,20);
	// 颠倒路径的方向
	while(!StackEmpty(s))
	{
		Pop(s,e);
		Push(t,e);
	}
	printf("\n\n");
	while(!StackEmpty(t))
	{
		Pop(t,e);
		gotoxy(2*e.j,e.i);
		if(StackLen(t)>=1)
		{
			e_next=GetTop(t);
			int a,b;
			a=e_next.i-e.i;
			b=e_next.j-e.j;
			printf("%s",charset[ map[a+1][b+1] ]);
		}
		else printf("◆");
		Sleep(10);
	}

}
void FindMaze(Pos start,Pos end,int**m,int mode)
{
	Stack s;
	InitStack(s);
	Pos iFind=start;
	int bFind=1;
	int k;
	do
	{
		if(mode==2)
		{
		gotoxy(2*iFind.j,iFind.i);
		printf("●");
		Sleep(100);
		gotoxy(2*iFind.j,iFind.i);
		printf("  ");
		gotoxy(2*start.j,start.i);
		printf("_");
		gotoxy(2*end.j,end.i);
		printf("_");
		}



		Pos tpt;//temp point
		int ii=iFind.i,ij=iFind.j;
		if(bFind)
		{
			Push(s,iFind);
			m[ii][ij]=-1;
			if(iFind.i==end.i && iFind.j==end.j)
			{
				gotoxy(0,20);
				printf("\n\n搜索成功!\n");
				if(mode==1) Success(s);
				gotoxy(0,20);
				//清除文字
				printf("\n\n          \n");
				return ;
			}
		}
		bFind=1;
		for(k=1; k<=8; ++k )
		{

			tpt=NextPos(iFind,k);
			if(m[tpt.i][tpt.j]==0)
			{
				bFind=1;
				iFind=tpt;
				break;
			}
			else bFind=0;
		}
		if(!bFind)//back trace
		{
			Pos e;
			Pop(s,e);
			iFind=GetTop(s);
		}
	}
	while(!StackEmpty(s));
	gotoxy(0,20);
	printf("搜索失败");


}



void ShowMatrix(int**m,int mx,int my)
{
	int i,j;
	for(i=0; i<mx; ++i)
	{
		for(j=0; j<my; ++j)
			if(m[i][j]==0)
				printf("  ");
			else 
				printf("█");
		printf("\n");
	}
}

void Free(int**&m)
{
	free(m);
}
maze_info Find_Load()
{
	maze_info minfo;
	int **ma=NULL;
	int mx=20,my=20;
	Pos start,end;
	InitMatrix(ma,mx,my);
	SetMatrix(ma,mx,my,start,end);
	ShowMatrix(ma,mx,my);
	gotoxy(2*start.j,start.i);
	printf("_");
	gotoxy(2*end.j,end.i);
	printf("_");
	minfo.start=start;
	minfo.end=end;
	minfo.mx=mx;
	minfo.my=my;
	minfo.ma=ma;
	return minfo;
	FindMaze(start,end,ma);
	

	//Free(ma);
	
}

//用来生成画面的,无搜索操作
void Find_default()
{
	int **ma=NULL;
	Pos start,end;
	system("cls");
	int mx=20,my=20;
	InitMatrix(ma,mx,my);
	
	SetMatrix(ma,mx,my,start,end);
	ShowMatrix(ma,mx,my);
	gotoxy(0,20);
	
	gotoxy(2*start.j,start.i);
	printf("_");
	gotoxy(2*end.j,end.i);
	printf("_");
	Free(ma);
	
	
}

void SetMatrix(int** &m,int& mx,int& my,Pos &start, Pos& end)
{
	int i=1,j=1;
	FILE *fp=NULL;
	fp=fopen("wall.txt","r");
	if(fp==NULL)
	{
		MessageBox(NULL,"文件读取失败","错误",NULL);
		
		exit(0);
	}
	fscanf(fp,"%d%d",&mx,&my);
	fscanf(fp,"%d%d",&start.i,&start.j);
	fscanf(fp,"%d%d",&end.i,  &end.j);

	if(fp!=NULL){
		while(i!=-1)
		{
			fscanf(fp,"%d%d",&i,&j);
			if(i>0&&i<mx-1&&j>0&&j<my-1)
				m[i][j]=1;
		}
	}
	else
	{
		MessageBox(NULL,"文件读取失败","错误",NULL);
	}

	fclose(fp);	
}