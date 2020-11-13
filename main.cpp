#if       _WIN32_WINNT < 0x0500
  #undef  _WIN32_WINNT
  #define _WIN32_WINNT   0x0500
#endif
#include <windows.h>
#include <iostream>
#include<string>
#include<conio.h>
#include <ctime>
using namespace std;
const int width=20;
const int height=20;
int Score=0;
void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}
struct hinhdang{
    char hinhdang[3][3];
};
struct toado{
  int x;
  int y;
};
struct enemy{
  toado td;
  hinhdang enemyhd;
};
enemy xedich;
struct mycar{
  toado td;
  hinhdang mycarhd;
};
mycar xenguoichoi;
void textcolor(int x)
{
	HANDLE mau;
	mau=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau,x);
}

void gotoxy(int x,int y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = {x-1,y-1};
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput , Cursor_an_Pos);
}
void XoaManHinh()
{
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}
void Display()
{
    char a[20][20];
    for(int i=1;i<=width;i++)
    {
        for(int j=1;j<=height;j++)
        {
            if(i==height||i==1)
            {
                cout<<" ";
            }
            else if((j==width/2)&&(xedich.td.y%2==0)&&(i%2==0))
            {
                cout<<"|";
            }
            else if((j==width/2)&&(xedich.td.y%2!=0)&&(i%2!=0))
            {
                cout<<"|";
            }
            else if(j==1||j==width)
            {
                textcolor(102);
                cout<<" ";
                textcolor(7);
            }
            else
            {
                cout<<" ";
            }
        }
        cout<<"\n";
    }
    gotoxy(24,6);
    cout<<"W"<<"\n";
    gotoxy(22,7);
    cout<<"A S D";
    gotoxy(12,21);
    cout<<" Doan Tan Loc";
}
void Dichuyenxedich()
{
    if(xedich.td.y<height+1)
    {
        xedich.td.y++;
        Sleep(100-Score);
    }
    else
    {
        xedich.td.y=1;
    }
}
void Movemycar()
{
    if(kbhit())
    {
        switch(_getch())
        {
        case 'a':
            {
               xenguoichoi.td.x--;
               if(xenguoichoi.td.x==1)
               {
                   xenguoichoi.td.x++;
               }
               break;
            }
        case 'd':
            {
               xenguoichoi.td.x++;
               if(xenguoichoi.td.x==width-2)
               {
                   xenguoichoi.td.x--;
               }
               break;
            }
        case 'w':
            {
               xenguoichoi.td.y--;
               if(xenguoichoi.td.y==1)
               {
                   xenguoichoi.td.y++;
               }
               break;
            }
        case 's':
            {
               xenguoichoi.td.y++;
               if(xenguoichoi.td.y==height-2)
               {
                   xenguoichoi.td.y--;
               }
               break;
            }
        }
    }
}
void Gameover()
{
    gotoxy(6,5);
    cout<<"GAME OVER!";
}
void Win()
{
    gotoxy(4,5);
    cout<<"YOU ARE WINNER!";
}
void Winner()
{
    if(Score==100)
    {
        Win();
        Sleep(1000);
        system("cls");
        Score=0;
    }
}
void Xedich(enemy &xedich)
{
    if(xedich.td.y<height-1)
    {
    xedich.enemyhd.hinhdang[0][0]='O';
    xedich.enemyhd.hinhdang[0][2]='O';
    xedich.enemyhd.hinhdang[2][2]='O';
    xedich.enemyhd.hinhdang[2][0]='O';
    xedich.enemyhd.hinhdang[0][1]='-';
    xedich.enemyhd.hinhdang[2][1]='-';
    xedich.enemyhd.hinhdang[1][0]='|';
    xedich.enemyhd.hinhdang[1][2]='|';
    xedich.enemyhd.hinhdang[1][1]='X';
    for(int i=0;i<=2;i++)
    {
        for(int j=0;j<=2;j++)
        {
            gotoxy(xedich.td.x+j,xedich.td.y+i);
            cout<<xedich.enemyhd.hinhdang[i][j];
        }
        cout<<"\n";
    }
    }
    else
    {
        Score++;
    }
}
void Xenguoichoi(mycar &xenguoichoi)
{
    textcolor(10);
    xenguoichoi.mycarhd.hinhdang[0][0]='O';
    xenguoichoi.mycarhd.hinhdang[0][2]='O';
    xenguoichoi.mycarhd.hinhdang[2][2]='O';
    xenguoichoi.mycarhd.hinhdang[2][0]='O';
    xenguoichoi.mycarhd.hinhdang[0][1]='-';
    xenguoichoi.mycarhd.hinhdang[2][1]='-';
    xenguoichoi.mycarhd.hinhdang[1][0]='|';
    xenguoichoi.mycarhd.hinhdang[1][2]='|';
    xenguoichoi.mycarhd.hinhdang[1][1]='H';
    for(int i=0;i<=2;i++)
    {
        for(int j=0;j<=2;j++)
        {
            gotoxy(xenguoichoi.td.x+j,xenguoichoi.td.y+i);
            cout<<xenguoichoi.mycarhd.hinhdang[i][j];
        }
        cout<<"\n";
    }
    textcolor(7);
}
void Xulivacham()
{
    if((xedich.td.y+2==xenguoichoi.td.y||xedich.td.y==xenguoichoi.td.y||xedich.td.y+1==xenguoichoi.td.y)&&((xedich.td.x==xenguoichoi.td.x)||(xedich.td.x==xenguoichoi.td.x-1)||(xedich.td.x==xenguoichoi.td.x-2)||(xedich.td.x==xenguoichoi.td.x+1)||(xedich.td.x==xenguoichoi.td.x+2)))
    {
        Gameover();
        Sleep(2000);
        Score=0;
        system("cls");
        cout<<"GOOD BYE!";
        exit (0);
    }
}
void Play()
{
    int b;
    cout<<"Press any key + enter to start game!";
    cin>>b;
    system("cls");
    resizeConsole(250,400);
    xenguoichoi.td.x=width/2;
    xenguoichoi.td.y=height-3;
    xedich.td.x=width/2;
    xedich.td.y=2;
    while(true)
    {
        if(xedich.td.y==height)
        {
	        srand(time(NULL));
            int ran=rand()%(17-2+1)+2;
            xedich.td.x=ran;
        }
        XoaManHinh();
        Display();
        Xenguoichoi(xenguoichoi);
        if(xedich.td.y<height)
        {
            if(xedich.td.x>=1&&xedich.td.x<15)
            {
                textcolor(xedich.td.x);
            }
            Xedich(xedich);
            textcolor(7);
        }
        Movemycar();
        Dichuyenxedich();
        gotoxy(2,21);
        cout<<"SCORE: "<<Score;
        Winner();
        Xulivacham();
        Sleep(20);
    }
}
int main()
{
    Play();
    /*for(int i=1;i<=200;i++)
    {
        textcolor(i);
        cout<<"00000   "<<i<<"\n";
    }*/
    return 0;
}
