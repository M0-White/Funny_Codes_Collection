#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>
#define MAX 100
int high,width;//��ͼ�߶������ 
int bird_x,bird_y;//С���λ�� 
int through,wall;//ͨ����x�����ǽ����ʼ����y 
int map[MAX][MAX];//��¼ҳ�����ʾ 
/*0�����հף�1����С���λ�ã�2����ǽ
3��������Χǽ��4��������Χǽ*/ 
bool book[MAX][MAX];//�����ĵ���Χǽ
int score;//��¼�÷� 
bool result = 0;//��Ϸ���1����ʧ�ܣ�0����ʤ����������ԶӮ����~~ 
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
    //�·�Χǽ�ĳ�ʼ�� 
    i = high;
    for(j=1;j<=width;j++)
        map[i][j] = 3;
    //С��λ�õĳ�ʼ�� 
    map[bird_x][bird_y] = 1;

    //ǽ�ĳ�ʼ��
    for(i=1;i<=high-1;i++)
    {
        map[i][wall] = 2;
        book[i][wall] = 1;  
    }
    //ͨ���ĳ�ʼ��
    for(i=through-2;i<=through+2;i++)//ͨ���Ĵ�С�����Զ���.
    {
        map[i][wall] = 0;
        book[i][wall] = 0;
    }
}
void HideCursor()//���ع�� 
{
    CONSOLE_CURSOR_INFO cursor_info = {1, 0}; 
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
void gotoxy(int x,int y)//����һ������Ļ 
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle,pos);
}
void UPdatewithOutinput()//�������޹صĸ��� 
{
    bird_x++;
    wall--;
    if(book[bird_x][bird_y] == 1 || bird_x > high)//��С������ʱ 
    {
        result = 1;
    }
    if(wall == bird_y-1)//��С���߹�ǽʱ��һ�� 
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
    if(kbhit())//�ж��Ƿ��м������� 
    {
        input = getch();
        if(input == ' ')
            bird_x -= 2;//С�����ϱ����� 
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
    printf("��ķ�����:%d\n\n",score);
    printf("����˵��:�ո�������ƶ�\n");
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
    printf("��ĵ÷���%d\n\n",score);
    printf("����һ�ΰ�");                          
    return 0;
}
