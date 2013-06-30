#include "API.H"
#include "maze.h"
#include <stdlib.h>
#include <time.h>
//首次进入
int Once=1;
char Main_choice[4][9]={
	{"进入迷宫"},{"关于作者"},{"查看帮助"},{"主界面"}
};
char Yes_No[2][9]={
	{"确定"},{"返回"}
};
int i,j;//临时文件
//用户所选的选项
int i_cho=0;

//第二级的菜单
	int sec_cho;
	COORD sec_pos[3]={0};
	char sec_tmp_cho[3][9]={{"快速求解"},{"模拟遍历"},{"游戏模式"}};
	
	//第三级菜单
	int thi_cho;
	COORD thi_pos[2]={0};
	char thi_tmp_cho[2][9]={{"继续"},{"返回"}};

//记录各个菜单选项位置
COORD menu_pos[8]={0};
void menu_enter(int mode=1);		//选择 进入
void menu_about();		//选择 关于
void menu_help();		//选择 帮助
void menu_exit();		//选择 退出
void menu_switch(int);  //主选择命令
void Run()
{
	system("color f0");
	SetConsoleTitle("迷宫求解Demo");
	
	//画出矩形框，动态生成菜单，让菜单可控制
	DrawConsoleBox(23,78);
	gotoxy(28,5);
	printf("☆ 迷 宫 求 解 演 示");
	gotoxy(38,6);
	printf("控制台版");
	DrawConsoleBox(8,44,10,15);
	gotoxy(25,17);
	printf("↑↓移动     enter确认");
	Dynamic_Show_Menu(4,1,Main_choice,menu_pos,12,12,24,9);
	i_cho=Arrow_Control(4,1,menu_pos,Main_choice)+1;
	menu_switch(i_cho);
}
void main(){

	Run();
}

//游戏模式的控制
void game(maze_info minfo)
{
	//游戏模式下的变量定义
	char ch=0;
	const int up=72, down=80, left=75, right=77,EscKey=27;
	//初始化光标在起始点
	COORD tmp;//前一位置
	COORD cur;//当前位置
	cur.X=tmp.X=minfo.start.i;
	cur.Y=tmp.Y=minfo.start.j;
	gotoxy(2*tmp.Y,2*tmp.X-1);
	printf("●");
	do 
	{
		//清除下方的信息栏
		gotoxy(0,20);
		printf("-------信息栏------\n              \n             \n            ");

	/*注意:当前迷宫四周都已经密封好了，不用进行下标越界检查。
		如果四周都是开放的，一定一定要进行下标检查*/

		//当用户按下上
		if(ch==up)
		{
			
			if(minfo.ma[cur.X-1][cur.Y]==1)
			{
				gotoxy(0,21);
				printf("遇到墙壁!");
			}
			else 
			{
				//保存当前的位置
				tmp.X=cur.X;
				tmp.Y=cur.Y;
				//更新当前的位置
				cur.X=cur.X-1;
				gotoxy(2*tmp.Y,tmp.X);
				printf("  ");
				gotoxy(2*cur.Y,cur.X);
				printf("●");
			}
		
		}
		
		else if(ch==down)
		{
			if((int)cur.X+1> minfo.mx-1 || minfo.ma[cur.X+1][cur.Y]==1)
			{
				gotoxy(0,21);
				printf("遇到墙壁!");
			}
			else 
			{
				//保存当前的位置
				tmp.X=cur.X;
				tmp.Y=cur.Y;
				//更新当前的位置
				cur.X=cur.X+1;
				gotoxy(2*(int)tmp.Y,(int)tmp.X);
				printf("  ");
				gotoxy(2*(int)cur.Y,(int)cur.X);
				printf("●");
			}
		
		}
		else if(ch==left)
		{
			if(minfo.ma[cur.X][cur.Y-1]==1)
			{
				gotoxy(0,21);
				printf("遇到墙壁!");
			}
			else 
			{
				//保存当前的位置
				tmp.X=cur.X;
				tmp.Y=cur.Y;
				//更新当前的位置
				cur.Y=cur.Y-1;
				gotoxy((int)2*tmp.Y,(int)tmp.X);
				printf("  ");
				gotoxy(2*(int)cur.Y,(int)cur.X);
				printf("●");
			}
		}//是否在最左边，若是则移到最右边
		else if(ch==right)
		{
			if(minfo.ma[cur.X][cur.Y+1]==1)
			{
				printf("\n");
				gotoxy(0,20);
				printf("\n遇到墙壁!");
			}
			else 
			{
				//保存当前的位置
				tmp.X=cur.X;
				tmp.Y=cur.Y;
				//更新当前的位置
				cur.Y=cur.Y+1;
				gotoxy(2*tmp.Y,tmp.X);
				printf("  ");
				gotoxy(2*cur.Y,cur.X);
				printf("●");
			}
		}
		gotoxy(0,22);
		printf("当前位置:(%d,%d)\n目标位置(%d,%d)",cur.X,cur.Y,minfo.end.i,minfo.end.j);
		if((int)cur.X==(int)minfo.end.i&&(int)cur.Y==(int)minfo.end.j)
		{
			gotoxy(0,21);
			printf("恭喜你!你已经成功到达终点");
			break;
		}
		ch=getch();
		
} while (ch!=EscKey);

}

//手动模式
void enter_manual()
{
	
	
	
	system("cls");
	//手动模式下，程序从文件中加载数据
	maze_info minfo;
	minfo=Find_Load();
	
	//显示二级菜单
	DrawConsoleBox(10,20,6,55);
	Dynamic_Show_Menu(3,1,sec_tmp_cho,sec_pos,0,10,60);
	sec_cho=Arrow_Control(3,1,sec_pos,sec_tmp_cho)+1;
	
	
	switch(sec_cho)
	{
		/*快速显示*/
		case 1:
		FindMaze(minfo.start,minfo.end,minfo.ma);
		//动态生成菜单
		Dynamic_Show_Menu(1,2,thi_tmp_cho,thi_pos,8,19,55);
		//让菜单可控制
		thi_cho=Arrow_Control(1,2,thi_pos,thi_tmp_cho)+1;
		switch(thi_cho)
		{
		case 1:
			//继续
			Free(minfo.ma);
			enter_manual();
			break;
		case 2:
			//返回迷宫
			Free(minfo.ma);
			menu_enter();
			break;
		}
		break;
		/*模拟遍历*/
		case 2:
			FindMaze(minfo.start,minfo.end,minfo.ma,2);
			//动态生成菜单
			Dynamic_Show_Menu(1,2,thi_tmp_cho,thi_pos,8,19,55);
			//让菜单可控制
			thi_cho=Arrow_Control(1,2,thi_pos,thi_tmp_cho)+1;
			switch(thi_cho)
			{
			case 1:
				//继续
				Free(minfo.ma);
				enter_manual();
				break;
			case 2:
				//返回迷宫
				Free(minfo.ma);
				menu_enter();
				break;
			}
			break;
			/*游戏模式*/
			case 3:
			game(minfo);
			Dynamic_Show_Menu(1,2,thi_tmp_cho,thi_pos,8,19,55);
			//让菜单可控制
			thi_cho=Arrow_Control(1,2,thi_pos,thi_tmp_cho)+1;
			switch(thi_cho)
			{
			case 1:
				//继续
				Free(minfo.ma);
				enter_manual();
				break;
			case 2:
			//返回迷宫
				Free(minfo.ma);
			menu_enter();
			break;
		}
				
				
	break;
	}
	
				
}


//自动模式
void enter_auto()
{
	system("cls");
	maze_info minfo;
	int **ma,i,j;
	int mx=20,my=20;
	Pos start={1,1};
	Pos end={mx-2,my-2};
	minfo.start=start;
	minfo.end=end;
	minfo.ma=ma;
	InitMatrix(ma,mx,my);
	int tmp=0;
	srand(time(0));
	for(i=1; i<mx-1; ++i)
		for(j=1; j<my-1; ++j)
		{
			tmp=rand()%30;
			if(tmp%2 || tmp>10)
				tmp=0;
			ma[i][j]=tmp;
		}
			
	ma[1][1]=0,ma[mx-2][my-2]=0;
	ShowMatrix(ma,mx,my);

	
	
	//第二级的菜单
	int sec_cho;
	COORD sec_pos[3]={0};
	char sec_tmp_cho[3][9]={{"快速求解"},{"主界面"},{"退  出"}};
	
	
	//显示二级菜单
	DrawConsoleBox(10,20,6,55);
	Dynamic_Show_Menu(3,1,sec_tmp_cho,sec_pos,0,10,60);
	sec_cho=Arrow_Control(3,1,sec_pos,sec_tmp_cho)+1;
	
	
	switch(sec_cho)
	{
		/*快速显示*/
		case 1:
		FindMaze(minfo.start,minfo.end,ma);
		//动态生成菜单
		Dynamic_Show_Menu(1,2,thi_tmp_cho,thi_pos,8,19,55);
		//让菜单可控制
		thi_cho=Arrow_Control(1,2,thi_pos,thi_tmp_cho)+1;
		switch(thi_cho)
		{
		case 1:
			//继续
			Free(ma);
			enter_auto();
			break;
		case 2:
			//返回迷宫
			Free(ma);
			menu_enter(2);
			break;
		}
		break;
		
		case 2:
			Free(ma);
			system("cls");
			Run();
			break;
		
			case 3:
				
			break;
	}
	

	
}



void menu_enter(int isFirst)
{
	//如果是第一次运行，则模拟加载进度条
	if(Once)
	{
		Once=0;
		DrawConsoleBox(2,44,20,15);
		gotoxy(17,21);
		for(i=0; i<40; ++i)
		{
			//拟合函数，先快后慢
			Sleep( 4*i+(i*i)/40);
			if(i==2)
			{
				SetColor();
				gotoxy(23,19);
				printf("加载记录文件..");
				SetColorBack();
			}
			else if(i==20)
			{
				SetColor();
				gotoxy(23,19);
				printf("加载迷宫路径..");
				SetColorBack();
			}
			else if(i==30)
			{
				SetColor();
				gotoxy(23,19);
				printf("    正在进入..");
				SetColorBack();
			}
			gotoxy(41,19);
			printf("%0.0f%%",(i)*1.0/39.0*100);
			gotoxy(17+i,21);
			printf(">");
		}
	}
	system("cls");
	Pos ss={1,1},se={16,17};
	Find_default();
	DrawConsoleBox(10,20,6,55);
	
	//第一级的菜单
	int cho=0;
	COORD pos[3]={0};
	char tmp_cho[3][9]={{"手动方式"},{"自动生成"},{"返    回"}};
	
	
	
	
	Dynamic_Show_Menu(3,1,tmp_cho,pos,0,10,60);
	cho=Arrow_Control(3,1,pos,tmp_cho)+1;
	switch(cho)
	{
	case 1:
		enter_manual();
		break;
	case 2:
		enter_auto();
		break;
	case 3:
		system("cls");
		Run();
		return;
		break;
		
	}
	
}
void menu_about()
{
	system("cls");
	DrawConsoleBox(23,78);
	gotoxy(28,5);
	printf("☆ 关  于  作  者");
	gotoxy(30,8);
	printf("程序员：");
	//更改颜色
	HANDLE hd;
	hd=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hd,0xF2);
	
	printf("徐继开");
	SetColorBack();
	gotoxy(30,9);
	printf("文档员：");
	//更改颜色
	
	hd=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hd,0xF2);
	printf("鄢  栋");
	SetColorBack();
	gotoxy(30,10);
	printf("测试员：");
	SetConsoleTextAttribute(hd,0xF2);
	printf("葛琼琼");
	SetColorBack();
	
	Dynamic_Show_Menu(1,4,Main_choice,menu_pos,8,15,10,4);
	i_cho=Arrow_Control(1,4,menu_pos,Main_choice)+1;
	menu_switch(i_cho);
}
void menu_help()
{
	system("cls");
	DrawConsoleBox(23,78);
	gotoxy(28,2);
	printf("☆ 帮  助 & 资  料");
	gotoxy(14,7);
	printf("帮助及说明：");
	//更改颜色
	HANDLE hd;
	hd=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hd,0xF2);
	gotoxy(12,8);
	printf("1.使用光标移动选项，回车确认。");
	gotoxy(12,9);
	printf("2.在游戏模式下，按下Esc可退出");
	gotoxy(12,10);
	printf("3.自动生成模式功能和手动类似，所以直接显示路径了");
	
	SetColorBack();
	
	Dynamic_Show_Menu(1,4,Main_choice,menu_pos,8,15,10,4);
	i_cho=Arrow_Control(1,4,menu_pos,Main_choice)+1;
	menu_switch(i_cho);
}


void menu_switch(int i_cho)
{
	switch(i_cho)
	{
	case 1:
		//进入迷宫
		//备注：此处不能清屏
		menu_enter();
		break;
	case 2:
		//关于作者
		
		menu_about();
		break;
	case 3:
		//查看帮助
		menu_help();
		break;
	case 4:
		system("cls");
		Run();
		break;
	}
}