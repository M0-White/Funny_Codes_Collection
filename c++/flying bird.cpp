#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>
#define MAX 100
int high,width;//地图高度与宽度 
int bird_x,bird_y;//小鸟的位置 
int through,wall;//通道的x坐标和墙的起始坐标y 
int map[MAX][MAX];//记录页面的显示 
/*0代表空白，1代表小鸟的位置，2代表墙
3代表上下围墙，4代表左右围墙*/ 
bool book[MAX][MAX];//代表改点有围墙
int score;//记录得分 
bool result = 0;//游戏结果1代表失败，0代表胜利，不过永远赢不了~~ 
void startup()
{
    score = 0;
    high = 20;
    width = 50;
    bird_x = high/2;
    bird_y = width/4;
    through = high/2;
    wall = width/4*3;
}
void startMap()
{
    int i,j;
    for(i=1;i<=high-1;i++)
    {
        map[i][1] = 4;
        for(j=2;j<=width-1;j++)
            map[i][j] = 0;
        map[i][width] = 4;
    }
    //下方围墙的初始化 
    i = high;
    for(j=1;j<=width;j++)
        map[i][j] = 3;
    //小鸟位置的初始化 
    map[bird_x][bird_y] = 1;

    //墙的初始化
    for(i=1;i<=high-1;i++)
    {
        map[i][wall] = 2;
        book[i][wall] = 1;  
    }
    //通道的初始化
    for(i=through-2;i<=through+2;i++)//通道的大小可以自定义.
    {
        map[i][wall] = 0;
        book[i][wall] = 0;
    }
}
void HideCursor()//隐藏光标 
{
    CONSOLE_CURSOR_INFO cursor_info = {1, 0}; 
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
void gotoxy(int x,int y)//清理一部分屏幕 
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle,pos);
}
void UPdatewithOutinput()//与输入无关的更新 
{
    bird_x++;
    wall--;
    if(book[bird_x][bird_y] == 1 || bird_x > high)//当小鸟死亡时 
    {
        result = 1;
    }
    if(wall == bird_y-1)//当小鸟走过墙时得一分 
        score++; 
    if(wall < 1)
    {
        srand(time(NULL));
        through = rand() % high;
        while(through <= 3 || through >= high-2)
        {
            through = rand() % high;
        }
    }
    if(wall < 1)
    {
        wall = width/4*3;
    }

    memset(book,0,sizeof(book));
    Sleep(100);
}
void UPdatewithinput()
{
    char input;
    if(kbhit())//判断是否有键盘输入 
    {
        input = getch();
        if(input == ' ')
            bird_x -= 2;//小鸟向上蹦两格 
    }
}
void show()
{
    gotoxy(0,0);
    int i,j;
    for(i=1;i<=high;i++)
    {
        for(j=1;j<=width;j++)
        {
            switch(map[i][j])
            {
                case 0:
                    printf(" ");
                    break;
                case 1:
                    printf("@");
                    break;
                case 2:
                    printf("*");
                    break;
                case 3:
                    printf("~");
                    break;
                case 4:
                    printf("|");
                    break;
            }
        }
        printf("\n");
    }
    printf("你的分数是:%d\n\n",score);
    printf("操作说明:空格键向上移动\n");
}
int main(void)
{
    startup();
    system("pause");
    while(1)
    {
        HideCursor();
        startMap();
        show();
        UPdatewithOutinput();
        if(result == 1)
            break;
        UPdatewithinput();
    }
    system("cls");
    printf("你的得分是%d\n\n",score);
    printf("再试一次吧");                          
    return 0;
}
