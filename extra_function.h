#include<windows.h>
#include<iostream>
#include<conio.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<iomanip>
#define down 80
#define up 72
#define right 77
#define left 75
using namespace std;
void color(int val)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), val);
}
void gotoxy(int colum,int line)
{
COORD coord;
coord.X=colum;
coord.Y=line;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
int wherex()
{
CONSOLE_SCREEN_BUFFER_INFO csbi;
if(!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&csbi))
return -1;
return csbi.dwCursorPosition.X;
}
int wherey()
{
CONSOLE_SCREEN_BUFFER_INFO csbi;
if(!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&csbi))
return -1;
return csbi.dwCursorPosition.Y;
}
//------------------------------------------------------------------------------------------------------------------------------------
void getspasswd(char str[],int n)
{
    int i=0,flag;
    while(i<n-1)
    {
        flag=1;
        str[i]=getch();
        if(str[i]!=13 && str[i]!=8)
        cout<<"*";

        if(str[i]==13)
        break;

        else if(str[i]==8)
        {
                     if(i!=0)
            {
                cout<<"\b \b";

            if(i>0)
            {
                i--;
                str[i]='\0';
                flag=0;
            }

            }
            else
            {
                flag=0;
            }

        }
        if(flag!=0)
            i++;
    }
    str[i]='\0';
}
//------------------------------------------------------------------------------------------------------------------------------------


int DisplayMenu(char menu_item[][32],int msize)
{

    const int n=msize;


    int kpsd[n],basey=wherey(),selected=1,i=0,basex=wherex();//position=basex;
    kpsd[0]=1;
    for(i=1;i<n;i++)
    kpsd[i]=0;

    while(1!=0)
    {
        i=0;
       int position=basey;
        color(78);
        gotoxy(wherex(),wherey());
        cout<<"Use "<<(char)24<<" & "<<(char)25<<" key to move up and down in the menu";
        gotoxy(basex,++position);
        for(i=0;i<n;i++)
        {

            if(kpsd[i]==1)
            {
                color(23);
                gotoxy(basex,++position);
                cout<<menu_item[i];
                gotoxy(basex,++position);
                color(02);
            }
            else
            {
                color(02);
                gotoxy(basex,++position);
                cout<<menu_item[i];
                gotoxy(basex,++position);
            }
        }

         char ch=getch();

        if(ch==80) //down
        {
            selected+=1;

            if(selected>n) {selected=1;}

            gotoxy(basex,basey);
            int x=selected-1;
            kpsd[x]=1;
            for(i=0;i<n;i++)
            {
               if(i!=x)
               kpsd[i]=0;
            }
        }

        else if(ch==72) //up
        {
            selected-=1;
            if(selected<=0) selected=n;

            gotoxy(basex,basey);

            int x=selected-1;
            kpsd[x]=1;
            for(i=0;i<n;i++)
            {
               if(i!=x)
               kpsd[i]=0;
            }
        }

        else if(ch==13)
        {
            for(i=0;i<n;i++)
            {
                if(kpsd[i]!=0)
                break;
            }
            i+=1;
            return i;
        }
        else
        gotoxy(basex,basey);
    }
    return i;
}
/*******************************************************************************************************************/

