#include<iostream>
#include<cstdlib>
#include<ctime>
#include<conio.h>//�����е�getche()�����ͷ�ļ��ֻȡһ���ַ�
#include<windows.h>//�������õ��˲���windowsAPI����
#define LANDMINE 16
using namespace std;
int field[16][16],show[16][16]={{0}};//field������ָ������ͼ��ʵ�������show������ָ��ͼ��̽�������0-δ������δ��ǣ�1-������2-���
char answer[16][16];//��ȷ�𰸣����û�ʧ��ʱ���
int mine[40];//mine�������ڴ洢����λ�ã�����Ϊ16*����+����
void gotoxy(int x,int y)/*�ú��������ƶ���꣬����SetConsoleCursorPosition�����뿴����<a target=_blank href="http://baike.sogou.com/v73182107.htm?fromTitle=SetConsoleCursorPosition">http://baike.sogou.com/v73182107.htm?fromTitle=SetConsoleCursorPosition</a> */
{
	COORD pos;
	pos.X=2*x;
	pos.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}
void color(int a)/*�ú������ڸı�����ַ���ɫ������SetConsoleTextAttribute�����뿴����<a target=_blank href="http://baike.sogou.com/v72432554.htm?fromTitle=SetConsoleTextAttribute">http://baike.sogou.com/v72432554.htm?fromTitle=SetConsoleTextAttribute</a> */
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),a);
}
int once(int mine[],int key,int j)//����ʱ�õ����ۿ�ȡ�������֮ǰ�Ƿ���ֹ������ֹ��򷵻�0������Ϊ1
{
	int i;
	for(i=0;i<j;i++)
	{
		if(mine[i]==key)
		return 0;
	}
	return 1;
}
int count(int field[][16],int i,int j)/*���������֪����д�ĺ��鷳= =���ڵõ����׺���׸��Ӷ�Ӧ�����֣������м䲿�֡���Ե�Ͷ�����һЩ��С�Ĳ������ͷ��˺ö��������*/
{
	int d=0;
	int k,l;
	if(i>0&&i<15&&j>0&&j<15)
	{
		for(k=i-1;k<=i+1;k++)
		{
			for(l=j-1;l<=j+1;l++)
			{
				if(field[k][l]==LANDMINE)
				d++;
			}
		}
	}
	else if(i==0&&j>0&&j<15)
	{
		for(k=i;k<=i+1;k++)
		{
			for(l=j-1;l<=j+1;l++)
			{
				if(field[k][l]==LANDMINE)
				d++;
			}
		}
	}
	else if(i==15&&j>0&&j<15)
	{
		for(k=i-1;k<=i;k++)
		{
			for(l=j-1;l<=j+1;l++)
			{
				if(field[k][l]==LANDMINE)
				d++;
			}
		}
	}
	else if(j==0&&i>0&&i<15)
	{
		for(k=i-1;k<=i+1;k++)
		{
			for(l=j;l<=j+1;l++)
			{
				if(field[k][l]==LANDMINE)
				d++;
			}
		}
	}
	else if(j==15&&i>0&&i<15)
	{
		for(k=i-1;k<=i+1;k++)
		{
			for(l=j-1;l<=j;l++)
			{
				if(field[k][l]==LANDMINE)
				d++;
			}
		}
	}
	else if(i==0&&j==0)
	{
		for(k=0;k<=1;k++)
		{
			for(l=0;l<=1;l++)
			{
				if(field[k][l]==LANDMINE)
				d++;
			}
		}
	}
	else if(i==0&&j==15)
	{
		for(k=0;k<=1;k++)
		{
			for(l=14;l<=15;l++)
			{
				if(field[k][l]==LANDMINE)
				d++;
			}
		}
	}
	else if(i==15&&j==0)
	{
		for(k=14;k<=15;k++)
		{
			for(l=0;l<=1;l++)
			{
				if(field[k][l]==LANDMINE)
				d++;
			}
		}
	}
	else if(i==15&&j==15)
	{
		for(k=14;k<=15;k++)
		{
			for(l=14;l<=15;l++)
			{
				if(field[k][l]==LANDMINE)
				d++;
			}
		}
	}
	return d;
}
void Arrange()//���ڵõ������ͼ�����
{
	int i,j;
	for(i=0;i<16;i++)
	{
		for(j=0;j<16;j++)
		field[i][j]=0;
	}
	srand((unsigned)time(NULL)); 
	for(i=0;i<40;i++)
	{
		int t=rand()%256;
		while(once(mine,t,i)==0)
		t=rand()%256;
		mine[i]=t;//ÿȡһ�����������һ���ж������ǰ����ֹ�������ȡ�������ȡ����
	}
	for(i=0;i<40;i++)
	field[mine[i]/16][mine[i]%16]=LANDMINE;
	for(i=0;i<16;i++)
	{
		for(j=0;j<16;j++)
		{
			if(field[i][j]!=LANDMINE)
			field[i][j]=count(field,i,j);
		}
	}
}
void an(int field[][16])//�õ��𰸾���
{
	int i,j;
	for(i=0;i<16;i++)
	{
		for(j=0;j<16;j++)
		{
			if(field[i][j]==LANDMINE)
			answer[i][j]='L';
			else
			answer[i][j]=(char)(field[i][j]+48);
		}
	}
}
void point(int i,int j)//�㿪����ʱ�Ĵ���
{
	int k,l;
	if(show[i][j]==2)
	show[i][j]==2;
	else if(field[i][j]==LANDMINE)//��������ֱ��gg�������ԣ�Ӧ�ý���ʾʧ�ܣ��������ȷ�𰸣�Ȼ��ֱ���˳�
	{
		cout<<"������˼�������ˣ��´����ˣ�"<<endl;
		an(field);
		cout<<"��ȷ��Ϊ��"<<endl;
		for(int p=0;p<16;p++)
		{
			for(int q=0;q<16;q++)
			{
				if(answer[p][q]=='L')
				{
					color(12);
					cout<<"��";
				}
				else
				{
					color(10);
					cout<<answer[p][q]<<" ";
				}
			}
			cout<<endl;
		} 
		color(15);
		system("pause");
		exit(0);
	}
	else if(field[i][j]==0)//���㿪Ϊ�ո�����ʼ�ݹ��㷨
	{
		show[i][j]=1;
		if(i>0&&i<15&&j>0&&j<15)
		{
			for(k=i-1;k<=i+1;k++)
			{
				for(l=j-1;l<=j+1;l++)
				{
					if(show[k][l]==0) 
					{
						if(field[k][l]!=LANDMINE)
						{
							show[k][l]=1;
							point(k,l);
						}
					}
				}
			}
		}//��Χδ�㿪�ķ��׸���ȫ���㿪���ݹ飬����ͬ��ֻ�ǲ�ͬλ�õĲ�ͬ�������
		else if(i==0&&j>0&&j<15)
		{
			for(k=i;k<=i+1;k++)
			{
				for(l=j-1;l<=j+1;l++)
				{
					if(show[k][l]==0) 
					{
						if(field[k][l]!=LANDMINE)
						{
							show[k][l]=1;
							point(k,l);
						}
					}
				}
			}
		}
		else if(i==15&&j>0&&j<15)
		{
			for(k=i-1;k<=i;k++)
			{
				for(l=j-1;l<=j+1;l++)
				{
					if(show[k][l]==0) 
					{
						if(field[k][l]!=LANDMINE)
						{
							show[k][l]=1;
							point(k,l);
						}
					}
				}
			}
		}
		else if(j==0&&i>0&&i<15)
		{
			for(k=i-1;k<=i+1;k++)
			{
				for(l=j;l<=j+1;l++)
				{
					if(show[k][l]==0) 
					{
						if(field[k][l]!=LANDMINE)
						{
							show[k][l]=1;
							point(k,l);
						}
					}
				}
			}
		}
		else if(j==15&&i>0&&i<15)
		{
			for(k=i-1;k<=i+1;k++)
			{
				for(l=j-1;l<=j;l++)
				{
					if(show[k][l]==0) 
					{
						if(field[k][l]!=LANDMINE)
						{
							show[k][l]=1;
							point(k,l);
						}
					}
				}
			}
		}
		else if(i==0&&j==0)
		{
			for(k=0;k<=1;k++)
			{
				for(l=0;l<=1;l++)
				{
					if(show[k][l]==0) 
					{
						if(field[k][l]!=LANDMINE)
						{
							show[k][l]=1;
							point(k,l);
						}
					}
				}
			}
		}
		else if(i==0&&j==15)
		{
			for(k=0;k<=1;k++)
			{
				for(l=14;l<=15;l++)
				{
					if(show[k][l]==0) 
					{
						if(field[k][l]!=LANDMINE)
						{
							show[k][l]=1;
							point(k,l);
						}
					}
				}
			}
		}
		else if(i==15&&j==0)
		{
			for(k=14;k<=15;k++)
			{
				for(l=0;l<=1;l++)
				{
					if(show[k][l]==0) 
					{
						if(field[k][l]!=LANDMINE)
						{
							show[k][l]=1;
							point(k,l);
						}
					}
				}
			}
		}
		else if(i==15&&j==15)
		{
			for(k=14;k<=15;k++)
			{
				for(l=14;l<=15;l++)
				{
					if(show[k][l]==0) 
					{
						if(field[k][l]!=LANDMINE)
						{
							show[k][l]=1;
							point(k,l);
						}
					}
				}
			}
		}
	}
	else
	show[i][j]=1;//��Ϊ������׸�����ֱ�ӵ㿪�ø���
}
int judge(int mind[],int show[][16])//�ж�ʤ������
{
	int i,j;
	int ans=0,flag=0;
	for(i=0;i<40;i++)
	{
		if(show[mind[i]/16][mind[i]%16]==2)
		ans++;
	}
	for(i=0;i<16;i++)
	{
		for(j=0;j<16;j++)
		{
			if(show[i][j]==2)
			flag++;
		}
	}
	if(ans==40&&flag==40)
	return 1;
	else
	return 0;//����˼��Ϊ����ǵĸ�������׵ĸ�������򷵻�1�����򷵻�0
}
void draw(int show[][16])//�ú����������������ͼ
{
	gotoxy(1,0);
	color(10);
	cout<<'A'<<" "<<'B'<<" "<<'C'<<" "<<'D'<<" "<<'E'<<" "<<'F'<<" "<<'G'<<" "<<'H'<<" "<<'I'<<" "<<'J'<<" "<<'K'<<" "<<'L'<<" "<<'M'<<" "<<'N'<<" "<<'O'<<" "<<'P'<<" ";
	gotoxy(0,1);
	int i,j;
	for(i=0;i<16;i++)
	{
		gotoxy(0,i+1);
		color(10);
		cout<<(char)(i+65)<<" ";
		for(j=0;j<16;j++)
		{
			if(show[i][j]==0)
			{
				color(11);
				cout<<"��";
			}
			else if(show[i][j]==1)
			{
				color(14);
				cout<<field[i][j]<<" ";
			}
			else if(show[i][j]==2)
			{
				color(12);
				cout<<"��";
			}
		}
	}
}
int main()
{
	Arrange();
	char ch,c;
	int row=8,col=8;
	int i,j;
	PlaySound("�����ķ-���޵��ǿ�����.wav",NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);/*PlaySound�������ڲ�����Ƶ������������<a target=_blank href="http://baike.sogou.com/v10930259.htm?fromTitle=playsound">http://baike.sogou.com/v10930259.htm?fromTitle=playsound</a> */
	MessageBox(NULL,"�����ˣ����\n�������֣������ķ-���޵��ǿ�����","ɨ�� V1.0",MB_OK);
	MessageBox(NULL,"��F��L����������ǵ��׻���ֱ��̽��\nż���α�ǵ���ȡ�����\n֮��WSAD�ļ����ƶ����ӣ�������ȷ������λ��\n����ȫ�������ȷ���ʤ\nע�����ִ�Сд��\nף��ɹ���","��Ϸ����",MB_OK);/*MessageBox����������ʾ�Ի�������������<a target=_blank href="http://baike.sogou.com/v7685382.htm?fromTitle=messagebox">http://baike.sogou.com/v7685382.htm?fromTitle=messagebox</a> */
	clock_t start,finish;//���ڼ�ʱ
	long long totaltime;
	start=clock();
	while(judge(mine,show)!=1)
	{   
		gotoxy(0,0);
		draw(show);
		color(15);
		gotoxy(20,3);	
		cout<<"��ǵ��׻���ֱ��̽�⣿";
		gotoxy(20,4);
		cout<<"F--��ǵ���";
		gotoxy(20,5);
		cout<<"L--ֱ��̽��";
		gotoxy(20,6);
		ch=getche();
		while(ch!='F'&&ch!='L')
		{
			gotoxy(20,7);
			cout<<"��������";
			gotoxy(20,6);
			ch=getche();
		}
		if(ch=='F')
		{
			gotoxy(20,7);
			cout<<"��������"; 
			gotoxy(20,10);
			cout<<"��W A S D�ƶ����,��������������"; 
			gotoxy(0,18);
			c=getche();
			while(c=='W'||c=='A'||c=='S'||c=='D')
			{
				switch(c)//WASD����ѡ��ĸ���λ��
				{
					case 'W':row=row-1<0?0:row-1;break;
					case 'A':col=col-1<0?0:col-1;break;
					case 'S':row=row+1>15?15:row+1;break;
					case 'D':col=col+1>15?15:col+1;break;
				}
				gotoxy(20,15);
			    cout<<"��ǰ����λ�ã�"<<(char)(row+65)<<" "<<(char)(col+65);
				gotoxy(0,18);
				c=getche();
			}
			show[row][col]=2-show[row][col];
			if(judge(mine,show)==1)
			{
				cout<<"��ϲ��������ʤ�ˣ�"<<endl;
				gotoxy(0,20);
				finish=clock();
				totaltime=finish-start;
				cout<<"������ɨ����ʱ��"<<(long long)(totaltime/CLOCKS_PER_SEC)<<"s"<<endl;//ʤ������ʾ��ʱ
				system("pause");
				exit(0);
			}
		}
		else if(ch=='L')
		{
			gotoxy(20,7);
			cout<<"��������"; 
			gotoxy(20,10);
			cout<<"��W A S D�ƶ����,��������������"; 
			gotoxy(20,15);
			cout<<"��ǰ����λ�ã�"<<(char)(row+65)<<" "<<(char)(col+65);
			gotoxy(0,18);
			c=getche();
			while(c=='W'||c=='A'||c=='S'||c=='D')
			{
				switch(c)
				{
					case 'W':row=row-1<0?0:row-1;break;
					case 'A':col=col-1<0?0:col-1;break;
					case 'S':row=row+1>15?15:row+1;break;
					case 'D':col=col+1>15?15:col+1;break;
				}
				gotoxy(20,15);
			    cout<<"��ǰ����λ�ã�"<<(char)(row+65)<<" "<<(char)(col+65);
				gotoxy(0,18);
				c=getche();
			}
			point(row,col);
		}
	}
	system("pause");
	return 0;
}
