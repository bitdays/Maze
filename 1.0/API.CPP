#include "API.h"
#include "wincon.h"

void gotoxy(int x, int y){
	HANDLE hd;
	COORD loc;
	loc.X = x;
	loc.Y=y;
	hd = GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ������ڵľ��
	SetConsoleCursorPosition(hd, loc);//���ù���λ��
	CONSOLE_CURSOR_INFO cursor_info;
	GetConsoleCursorInfo(hd, &cursor_info);//��ȡ�����Ϣ,�Ƿ�ɼ��ͳߴ�
	cursor_info.bVisible = false;//�ù�겻�ɼ�
	SetConsoleCursorInfo(hd, &cursor_info);
}
void SetColor(){

	HANDLE hd;
	hd=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hd,0xf9);
}
void SetColorBack()
{

	HANDLE hd;
	hd=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hd,0xf0);
}

int Arrow_Control(int i,int j,const COORD mystack[],char choice[][MAX_CHAR+1]){
	char pattern[5]="->";
	int len=strlen(pattern);
	int OLD_ID=0;//��¼��λ��,���ö�ջ
	int NEW_ID=0;//��¼��λ��
	int temp=OLD_ID;
	int tx=mystack[0].X,ty=mystack[0].Y;//��ʱ���������ڼ�¼
	gotoxy(tx-len,ty);
	printf("%s",pattern);
	char ch;
	const int up=72, down=80, left=75, right=77,EnterKey=13;
	do 
	{
		
		if(ch==up){
			 temp=NEW_ID=  ((OLD_ID-j))>=0 ?(OLD_ID-j ) :   (i-1)*j+ OLD_ID%j  ;
		}//�����ڶ���+��λ�ã�ȡģ��ã�
		else if(ch==down){
			temp=NEW_ID=   (OLD_ID+j)<i*j ?  OLD_ID+j  :      OLD_ID%j ;
		}
		else if(ch==left){
			temp=NEW_ID=  OLD_ID%j==0  ?    (OLD_ID+j-1)  :   (OLD_ID-1)    ;   
		}//�Ƿ�������ߣ��������Ƶ����ұ�
		else if(ch==right){
			temp=NEW_ID=  OLD_ID%j==j-1 ?  (OLD_ID-j+1)  :   (OLD_ID+1)     ;
		}
		//��λ����ǰλ�õ�ǰһ��λ��
		tx=mystack[OLD_ID].X-len,ty=mystack[OLD_ID].Y;
		gotoxy(tx,ty);
		SetColorBack();//�ָ���ɫ
		printf("  ");//ɾ�������ļ�ͷ
		printf("\t\t  ");//ɾ����������
		gotoxy(tx+2,ty);
		printf("%s",choice[OLD_ID]);//���֮ǰ��ѡ��

		//��λ����λ�� ����������ɫ���������� ��ѡ��ͻ����ʾ
		tx=mystack[NEW_ID].X-len,ty=mystack[NEW_ID].Y;
		gotoxy(tx,ty);
		printf("%s",pattern);//��ӡ��ͷ
		

		SetColor();//������ɫ
		printf("  %s",choice[NEW_ID]);//ǰ�������ո��ʾ����
		
		//gotoxy(0,24);
		//printf("[%d]-->[%d]\t\t(%d,%d)--->(%d,%d)",OLD_ID,NEW_ID,mystack[OLD_ID].X,mystack[OLD_ID].Y,mystack[NEW_ID].X,mystack[NEW_ID].Y);
		OLD_ID=temp;
		ch=getch();

		
	} while (ch!=13);
	SetColorBack();
	return NEW_ID;

}


/*------------------------------------------------------------------------------------
	i,j��ʾ��ʾ��ʽ--���м���
	���ڴ������ƣ�char[][MAX_CHAR]���������ʾ4������
	toright��ʾ��ƫ����
	todown��ʾ����ƫ����
	��ʾ���ҿհ׵ı߾�
	����margin��midҪ���ڶ�   ��ΪҪ����->ͼ��
 */
void Dynamic_Show_Menu(int i,int j,char choice[][MAX_CHAR+1],
					   COORD mystack[],int mid,int todown,int toright,int margin)
{
	COORD temp;
	int tx=0,ty=0;
	int ti=0,tj=0,count=0;
	int n=0;
	for (ti=0;ti<i;++ti)
	{
		for (tj=0;tj<j;++tj)
		{
			temp.Y = ti+todown;
			temp.X = toright+margin+(MAX_CHAR+mid)*tj;
			mystack[count++]=temp;
		}
	}
	for (n=0;n<count;++n)
	{
		tx=mystack[n].X;
		ty=mystack[n].Y;
		//printf("(%d\t%d)",tx,ty);
		gotoxy(tx,ty);
		printf("%s",choice[n]);
		
	}
	

}																							

/*																							|
------------------------------------------------------------------------------------------*/
void DrawConsoleBox(int i,int j,int todown,int toright, int cho)
{
	j=(j%2==0)?j:j-1;//�Ʊ����������ֽ�  ��ֹ���ֿո�
	int temp;
	for (temp=toright;temp<toright+j;temp+=2)
	{
		gotoxy(temp,todown);
		if(cho==1)
			printf("��");
		else if(cho==2)
			printf("�x");
		gotoxy(temp,todown+i);
		if (cho==1)
			printf("��");
		else if(cho==2)
			printf("��");

	}
	
	for (temp=todown;temp<todown+i;++temp)
		{
			gotoxy(toright,temp);
			if(cho==1) 
				printf("��");
			else if(cho==2)
				printf("��");
			gotoxy(toright+j,temp);
			if(cho==1)printf("��");
			else if(cho==2)
				printf("��");
	
		}
	gotoxy(toright,todown);
	if(cho==1)printf("��");
	else if(cho==2)
		printf(" ");
	gotoxy(toright,todown+i);
	if(cho==1)printf("��");
	else if(cho==2)
		printf(" ");
	gotoxy(toright+j,todown);
	if(cho==1)printf("��");
	else if(cho==2)
		printf(" ");
	gotoxy(toright+j,todown+i);
	if(cho==1)printf("��");
	else if(cho==2)
		printf(" ");
	
}
