#include "API.h"
#include "wincon.h"

void gotoxy(int x, int y){
	HANDLE hd;
	COORD loc;
	loc.X = x;
	loc.Y=y;
	hd = GetStdHandle(STD_OUTPUT_HANDLE);//获取输出窗口的句柄
	SetConsoleCursorPosition(hd, loc);//设置光标的位置
	CONSOLE_CURSOR_INFO cursor_info;
	GetConsoleCursorInfo(hd, &cursor_info);//获取光标信息,是否可见和尺寸
	cursor_info.bVisible = false;//让光标不可见
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
	int OLD_ID=0;//记录旧位置,调用堆栈
	int NEW_ID=0;//记录新位置
	int temp=OLD_ID;
	int tx=mystack[0].X,ty=mystack[0].Y;//临时变量，用于记录
	gotoxy(tx-len,ty);
	printf("%s",pattern);
	char ch;
	const int up=72, down=80, left=75, right=77,EnterKey=13;
	do 
	{
		
		if(ch==up){
			 temp=NEW_ID=  ((OLD_ID-j))>=0 ?(OLD_ID-j ) :   (i-1)*j+ OLD_ID%j  ;
		}//倒数第二行+列位置（取模获得）
		else if(ch==down){
			temp=NEW_ID=   (OLD_ID+j)<i*j ?  OLD_ID+j  :      OLD_ID%j ;
		}
		else if(ch==left){
			temp=NEW_ID=  OLD_ID%j==0  ?    (OLD_ID+j-1)  :   (OLD_ID-1)    ;   
		}//是否在最左边，若是则移到最右边
		else if(ch==right){
			temp=NEW_ID=  OLD_ID%j==j-1 ?  (OLD_ID-j+1)  :   (OLD_ID+1)     ;
		}
		//定位到当前位置的前一个位置
		tx=mystack[OLD_ID].X-len,ty=mystack[OLD_ID].Y;
		gotoxy(tx,ty);
		SetColorBack();//恢复颜色
		printf("  ");//删除残留的箭头
		printf("\t\t  ");//删除残留的字
		gotoxy(tx+2,ty);
		printf("%s",choice[OLD_ID]);//输出之前的选项

		//定位到新位置 更改字体颜色，设置缩进 让选项突出显示
		tx=mystack[NEW_ID].X-len,ty=mystack[NEW_ID].Y;
		gotoxy(tx,ty);
		printf("%s",pattern);//打印箭头
		

		SetColor();//更改颜色
		printf("  %s",choice[NEW_ID]);//前面两个空格表示缩进
		
		//gotoxy(0,24);
		//printf("[%d]-->[%d]\t\t(%d,%d)--->(%d,%d)",OLD_ID,NEW_ID,mystack[OLD_ID].X,mystack[OLD_ID].Y,mystack[NEW_ID].X,mystack[NEW_ID].Y);
		OLD_ID=temp;
		ch=getch();

		
	} while (ch!=13);
	SetColorBack();
	return NEW_ID;

}


/*------------------------------------------------------------------------------------
	i,j表示显示方式--几行几列
	由于窗口限制，char[][MAX_CHAR]决定最多显示4个汉字
	toright表示右偏移量
	todown表示向下偏移量
	表示左右空白的边距
	其中margin和mid要大于二   因为要放入->图案
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
	j=(j%2==0)?j:j-1;//制表符是两个字节  防止出现空格
	int temp;
	for (temp=toright;temp<toright+j;temp+=2)
	{
		gotoxy(temp,todown);
		if(cho==1)
			printf("─");
		else if(cho==2)
			printf("▁");
		gotoxy(temp,todown+i);
		if (cho==1)
			printf("─");
		else if(cho==2)
			printf("▔");

	}
	
	for (temp=todown;temp<todown+i;++temp)
		{
			gotoxy(toright,temp);
			if(cho==1) 
				printf("│");
			else if(cho==2)
				printf("▕");
			gotoxy(toright+j,temp);
			if(cho==1)printf("│");
			else if(cho==2)
				printf("▏");
	
		}
	gotoxy(toright,todown);
	if(cho==1)printf("┌");
	else if(cho==2)
		printf(" ");
	gotoxy(toright,todown+i);
	if(cho==1)printf("└");
	else if(cho==2)
		printf(" ");
	gotoxy(toright+j,todown);
	if(cho==1)printf("┐");
	else if(cho==2)
		printf(" ");
	gotoxy(toright+j,todown+i);
	if(cho==1)printf("┘");
	else if(cho==2)
		printf(" ");
	
}

