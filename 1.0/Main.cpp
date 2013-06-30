#include "API.H"
#include "maze.h"
#include <stdlib.h>
#include <time.h>
//�״ν���
int Once=1;
char Main_choice[4][9]={
	{"�����Թ�"},{"��������"},{"�鿴����"},{"������"}
};
char Yes_No[2][9]={
	{"ȷ��"},{"����"}
};
int i,j;//��ʱ�ļ�
//�û���ѡ��ѡ��
int i_cho=0;

//�ڶ����Ĳ˵�
	int sec_cho;
	COORD sec_pos[3]={0};
	char sec_tmp_cho[3][9]={{"�������"},{"ģ�����"},{"��Ϸģʽ"}};
	
	//�������˵�
	int thi_cho;
	COORD thi_pos[2]={0};
	char thi_tmp_cho[2][9]={{"����"},{"����"}};

//��¼�����˵�ѡ��λ��
COORD menu_pos[8]={0};
void menu_enter(int mode=1);		//ѡ�� ����
void menu_about();		//ѡ�� ����
void menu_help();		//ѡ�� ����
void menu_exit();		//ѡ�� �˳�
void menu_switch(int);  //��ѡ������
void Run()
{
	system("color f0");
	SetConsoleTitle("�Թ����Demo");
	
	//�������ο򣬶�̬���ɲ˵����ò˵��ɿ���
	DrawConsoleBox(23,78);
	gotoxy(28,5);
	printf("�� �� �� �� �� �� ʾ");
	gotoxy(38,6);
	printf("����̨��");
	DrawConsoleBox(8,44,10,15);
	gotoxy(25,17);
	printf("�����ƶ�     enterȷ��");
	Dynamic_Show_Menu(4,1,Main_choice,menu_pos,12,12,24,9);
	i_cho=Arrow_Control(4,1,menu_pos,Main_choice)+1;
	menu_switch(i_cho);
}
void main(){

	Run();
}

//��Ϸģʽ�Ŀ���
void game(maze_info minfo)
{
	//��Ϸģʽ�µı�������
	char ch=0;
	const int up=72, down=80, left=75, right=77,EscKey=27;
	//��ʼ���������ʼ��
	COORD tmp;//ǰһλ��
	COORD cur;//��ǰλ��
	cur.X=tmp.X=minfo.start.i;
	cur.Y=tmp.Y=minfo.start.j;
	gotoxy(2*tmp.Y,2*tmp.X-1);
	printf("��");
	do 
	{
		//����·�����Ϣ��
		gotoxy(0,20);
		printf("-------��Ϣ��------\n              \n             \n            ");

	/*ע��:��ǰ�Թ����ܶ��Ѿ��ܷ���ˣ����ý����±�Խ���顣
		������ܶ��ǿ��ŵģ�һ��һ��Ҫ�����±���*/

		//���û�������
		if(ch==up)
		{
			
			if(minfo.ma[cur.X-1][cur.Y]==1)
			{
				gotoxy(0,21);
				printf("����ǽ��!");
			}
			else 
			{
				//���浱ǰ��λ��
				tmp.X=cur.X;
				tmp.Y=cur.Y;
				//���µ�ǰ��λ��
				cur.X=cur.X-1;
				gotoxy(2*tmp.Y,tmp.X);
				printf("  ");
				gotoxy(2*cur.Y,cur.X);
				printf("��");
			}
		
		}
		
		else if(ch==down)
		{
			if((int)cur.X+1> minfo.mx-1 || minfo.ma[cur.X+1][cur.Y]==1)
			{
				gotoxy(0,21);
				printf("����ǽ��!");
			}
			else 
			{
				//���浱ǰ��λ��
				tmp.X=cur.X;
				tmp.Y=cur.Y;
				//���µ�ǰ��λ��
				cur.X=cur.X+1;
				gotoxy(2*(int)tmp.Y,(int)tmp.X);
				printf("  ");
				gotoxy(2*(int)cur.Y,(int)cur.X);
				printf("��");
			}
		
		}
		else if(ch==left)
		{
			if(minfo.ma[cur.X][cur.Y-1]==1)
			{
				gotoxy(0,21);
				printf("����ǽ��!");
			}
			else 
			{
				//���浱ǰ��λ��
				tmp.X=cur.X;
				tmp.Y=cur.Y;
				//���µ�ǰ��λ��
				cur.Y=cur.Y-1;
				gotoxy((int)2*tmp.Y,(int)tmp.X);
				printf("  ");
				gotoxy(2*(int)cur.Y,(int)cur.X);
				printf("��");
			}
		}//�Ƿ�������ߣ��������Ƶ����ұ�
		else if(ch==right)
		{
			if(minfo.ma[cur.X][cur.Y+1]==1)
			{
				printf("\n");
				gotoxy(0,20);
				printf("\n����ǽ��!");
			}
			else 
			{
				//���浱ǰ��λ��
				tmp.X=cur.X;
				tmp.Y=cur.Y;
				//���µ�ǰ��λ��
				cur.Y=cur.Y+1;
				gotoxy(2*tmp.Y,tmp.X);
				printf("  ");
				gotoxy(2*cur.Y,cur.X);
				printf("��");
			}
		}
		gotoxy(0,22);
		printf("��ǰλ��:(%d,%d)\nĿ��λ��(%d,%d)",cur.X,cur.Y,minfo.end.i,minfo.end.j);
		if((int)cur.X==(int)minfo.end.i&&(int)cur.Y==(int)minfo.end.j)
		{
			gotoxy(0,21);
			printf("��ϲ��!���Ѿ��ɹ������յ�");
			break;
		}
		ch=getch();
		
} while (ch!=EscKey);

}

//�ֶ�ģʽ
void enter_manual()
{
	
	
	
	system("cls");
	//�ֶ�ģʽ�£�������ļ��м�������
	maze_info minfo;
	minfo=Find_Load();
	
	//��ʾ�����˵�
	DrawConsoleBox(10,20,6,55);
	Dynamic_Show_Menu(3,1,sec_tmp_cho,sec_pos,0,10,60);
	sec_cho=Arrow_Control(3,1,sec_pos,sec_tmp_cho)+1;
	
	
	switch(sec_cho)
	{
		/*������ʾ*/
		case 1:
		FindMaze(minfo.start,minfo.end,minfo.ma);
		//��̬���ɲ˵�
		Dynamic_Show_Menu(1,2,thi_tmp_cho,thi_pos,8,19,55);
		//�ò˵��ɿ���
		thi_cho=Arrow_Control(1,2,thi_pos,thi_tmp_cho)+1;
		switch(thi_cho)
		{
		case 1:
			//����
			Free(minfo.ma);
			enter_manual();
			break;
		case 2:
			//�����Թ�
			Free(minfo.ma);
			menu_enter();
			break;
		}
		break;
		/*ģ�����*/
		case 2:
			FindMaze(minfo.start,minfo.end,minfo.ma,2);
			//��̬���ɲ˵�
			Dynamic_Show_Menu(1,2,thi_tmp_cho,thi_pos,8,19,55);
			//�ò˵��ɿ���
			thi_cho=Arrow_Control(1,2,thi_pos,thi_tmp_cho)+1;
			switch(thi_cho)
			{
			case 1:
				//����
				Free(minfo.ma);
				enter_manual();
				break;
			case 2:
				//�����Թ�
				Free(minfo.ma);
				menu_enter();
				break;
			}
			break;
			/*��Ϸģʽ*/
			case 3:
			game(minfo);
			Dynamic_Show_Menu(1,2,thi_tmp_cho,thi_pos,8,19,55);
			//�ò˵��ɿ���
			thi_cho=Arrow_Control(1,2,thi_pos,thi_tmp_cho)+1;
			switch(thi_cho)
			{
			case 1:
				//����
				Free(minfo.ma);
				enter_manual();
				break;
			case 2:
			//�����Թ�
				Free(minfo.ma);
			menu_enter();
			break;
		}
				
				
	break;
	}
	
				
}


//�Զ�ģʽ
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

	
	
	//�ڶ����Ĳ˵�
	int sec_cho;
	COORD sec_pos[3]={0};
	char sec_tmp_cho[3][9]={{"�������"},{"������"},{"��  ��"}};
	
	
	//��ʾ�����˵�
	DrawConsoleBox(10,20,6,55);
	Dynamic_Show_Menu(3,1,sec_tmp_cho,sec_pos,0,10,60);
	sec_cho=Arrow_Control(3,1,sec_pos,sec_tmp_cho)+1;
	
	
	switch(sec_cho)
	{
		/*������ʾ*/
		case 1:
		FindMaze(minfo.start,minfo.end,ma);
		//��̬���ɲ˵�
		Dynamic_Show_Menu(1,2,thi_tmp_cho,thi_pos,8,19,55);
		//�ò˵��ɿ���
		thi_cho=Arrow_Control(1,2,thi_pos,thi_tmp_cho)+1;
		switch(thi_cho)
		{
		case 1:
			//����
			Free(ma);
			enter_auto();
			break;
		case 2:
			//�����Թ�
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
	//����ǵ�һ�����У���ģ����ؽ�����
	if(Once)
	{
		Once=0;
		DrawConsoleBox(2,44,20,15);
		gotoxy(17,21);
		for(i=0; i<40; ++i)
		{
			//��Ϻ������ȿ����
			Sleep( 4*i+(i*i)/40);
			if(i==2)
			{
				SetColor();
				gotoxy(23,19);
				printf("���ؼ�¼�ļ�..");
				SetColorBack();
			}
			else if(i==20)
			{
				SetColor();
				gotoxy(23,19);
				printf("�����Թ�·��..");
				SetColorBack();
			}
			else if(i==30)
			{
				SetColor();
				gotoxy(23,19);
				printf("    ���ڽ���..");
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
	
	//��һ���Ĳ˵�
	int cho=0;
	COORD pos[3]={0};
	char tmp_cho[3][9]={{"�ֶ���ʽ"},{"�Զ�����"},{"��    ��"}};
	
	
	
	
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
	printf("�� ��  ��  ��  ��");
	gotoxy(30,8);
	printf("����Ա��");
	//������ɫ
	HANDLE hd;
	hd=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hd,0xF2);
	
	printf("��̿�");
	SetColorBack();
	gotoxy(30,9);
	printf("�ĵ�Ա��");
	//������ɫ
	
	hd=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hd,0xF2);
	printf("۳  ��");
	SetColorBack();
	gotoxy(30,10);
	printf("����Ա��");
	SetConsoleTextAttribute(hd,0xF2);
	printf("������");
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
	printf("�� ��  �� & ��  ��");
	gotoxy(14,7);
	printf("������˵����");
	//������ɫ
	HANDLE hd;
	hd=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hd,0xF2);
	gotoxy(12,8);
	printf("1.ʹ�ù���ƶ�ѡ��س�ȷ�ϡ�");
	gotoxy(12,9);
	printf("2.����Ϸģʽ�£�����Esc���˳�");
	gotoxy(12,10);
	printf("3.�Զ�����ģʽ���ܺ��ֶ����ƣ�����ֱ����ʾ·����");
	
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
		//�����Թ�
		//��ע���˴���������
		menu_enter();
		break;
	case 2:
		//��������
		
		menu_about();
		break;
	case 3:
		//�鿴����
		menu_help();
		break;
	case 4:
		system("cls");
		Run();
		break;
	}
}