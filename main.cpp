#include <iostream>
#include<conio.h>
#include<string.h>
#include "extra_function.h"
#include<fstream>
#define WIDTH 165
#define HEIGHT 40
struct coordinate
{
    int x,y;
    int color;
    char block;
    coordinate *next,*previous;
    coordinate(char ch='.',int inkc=10)
    {
    	x=y=-1;
    	color=inkc;
    	block=ch;
    	next=previous=NULL;
	}

	coordinate(coordinate &c)
	{
	    x=c.x;
	    y=c.y;
	    color=c.color;
	    next=c.next;
	    previous=c.previous;
	}
	~coordinate(){}
};

int fabs(int n)      //returns magnitude
{
    if(n<0)
    return n * (-1);
    else
    return n;
}
int sign(int n)       //return sign direction
{
	if(n<0)
	return -1;
	else
	return 1;
}

unsigned int totalwindows=0;
class PAINT
{
    private:
    coordinate *START;
    coordinate *LAST;
    unsigned char pen;
    char FILENAME[128],chart[MAX_PATH][MAX_PATH];
    unsigned int windowno;
    unsigned int inkcolor,bgcolor,edited;
    void redundant();
    void constrain(int &a,int &b);
    string exepath()
    {
        char buffer[MAX_PATH];
        GetModuleFileName(NULL,buffer,MAX_PATH);
        string::size_type pos=string(buffer).find_last_of("\\/");
        return string(buffer).substr(0,pos);
    }
    void window(char wname[],int x=0,int y=0,int width=WIDTH,int height=HEIGHT)
    {
    gotoxy(x,y);
    cout<<(char)219;
    gotoxy(x+width,y+0);
    cout<<(char)219;
    for(int i=1;i<width;i++)
    {
        gotoxy(i+x,0+y);
        cout<<(char)223;
        gotoxy(i+x,height+y);
        cout<<(char)220;
    }
    for(int i=1;i<=height;i++)
    {
        gotoxy(0+x,i+y);
        cout<<(char)221;
        gotoxy(width+x,i+y);
        cout<<(char)222;
    }
    gotoxy(0+x,height+y);
    cout<<(char)219;
    gotoxy(width+x,height+y);
    cout<<(char)219;

    gotoxy(((x+WIDTH)/2) - strlen(wname)/2 - 10,y);
    puts(wname);
    }

    public:
    PAINT *next;
    int getedited()
    {
        return edited;
    }
    void dispalyinfo(int twindow)
    {
        int basex=wherex(),basey=wherey();
        gotoxy(135,HEIGHT+2);
        cout<<"BRUSH : "<<(char)pen;
        gotoxy(135,HEIGHT+5);
        color(inkcolor);
        cout<<"Color : "<<(char)219;
        gotoxy(135,HEIGHT+7);
        cout<<"Total windows:"<<windowno<<"/"<<twindow;
        gotoxy(basex,basey);
    }
    void drawwindows(int twindow)
    {
         system("color 07");
         window(FILENAME,0,0,WIDTH-15,HEIGHT);
         window("\0",0,HEIGHT+1,WIDTH-15,HEIGHT-33);
         window("\0",WIDTH-14,0,WIDTH-148,HEIGHT+8);
         gotoxy(WIDTH-11,0);cout<<"|WINDOW NO:"<<windowno<<"|";
         window("\0",134,HEIGHT+1,16,7);
         dispalyinfo(twindow);
         gotoxy(WIDTH/2,HEIGHT/2);
    }
    void choosebrush()
    {
        int n,x=wherex(),y=wherey();
        gotoxy(WIDTH-12,2);
        for(int i=0;i<13;i++)
        cout<<" ";
        gotoxy(WIDTH-13,2);
        cout<<"Brush no:";
        cin>>n;
        pen=(char)n;
            system("cls");
            drawwindows(windowno);
            refresh(START);
            gotoxy(x,y);
    }
    void setcolor()
{
    int x1=wherex(),y1=wherey();
     gotoxy(WIDTH-13,2);
      char ch=right;
      int basex,x,y,basey;
      basex=x=wherex();
      basey=y=wherey();
      for(int i=1;i<=8;i++)
      {
          color(i);
          cout<<(char)219<<" ";
      }
     gotoxy(x,y+=2);
     while(ch!=13)
      {
          gotoxy(basex,y);
         for(int j=0;j<15;j++)
          cout<<" ";
          gotoxy(x,y);
          cout<<(char)24;
         ch=getch();
         if(ch==right)
          {
            if((x-basex)>=14)
             {
                  x=basex;
             }
             else
              {
                  x+=2;
              }
              gotoxy(x,y);
             cout<<(char)24;
          }
         else if(ch==left)
          {
              if((x-basex)<=0)
              {
                  x=basex+14;
            }
              else
             {
                  x-=2;
              }
              gotoxy(x,y);
              cout<<(char)24;
         }
      }
     inkcolor= (x-basex)/2 +1;
     system("cls");
     drawwindows(windowno);
      refresh(START);
      gotoxy(x1,y1);
}
    int getwindowno(){return windowno;}
    coordinate *getstart()
    {
        return START;
    }
    coordinate *getlast()
    {
        return LAST;
    }
    char getpen()
    {
        return pen;
    }
    char *getfilename()
    {
        return FILENAME;
    }
    int getinkcolor()
    {
        return inkcolor;
    }
    int getbgcolor()
    {
        return bgcolor;
    }
    int setwindowno(unsigned int n)
    {
        windowno=n;
    }
    PAINT(int wno=1,char wname[]="UNTITLED.C_art",int opening=false)
    {
        next=NULL;
        START=LAST=NULL;
        pen='.';
        inkcolor=10;
        bgcolor=0;
        edited=false;
        strcpy(FILENAME,wname);
        windowno=wno;
        drawwindows(windowno);
        if(opening==false)
        open(wname,opening);
        else
        drawwindows(windowno);
    }
    PAINT(PAINT *p)
    {
        next=p->next;
        START=p->getstart();
        LAST=p->getlast();
        pen=p->getpen();
        inkcolor=p->getinkcolor();
        bgcolor=p->getbgcolor();
        strcpy(FILENAME,p->getfilename());
    }
    PAINT(PAINT &p)
    {
        next=p.next;
         START=p.getstart();
         LAST=p.getlast();
         pen=getpen();
        inkcolor=getinkcolor();
        bgcolor=getbgcolor();
        strcpy(FILENAME,p.getfilename());
    }
    ~PAINT()
    {
        coordinate *ptr=START;
        while(ptr!=NULL)
        {
            coordinate *temp=ptr;
            ptr=ptr->next;
            delete temp;
        }
        next=NULL;
        //cout<<"PAINT "<<(int)this<<" DESTROYED";
    }
    void refresh(coordinate *ptr)
    {
        int x=wherex(),y=wherey();
        while(ptr!=NULL)
        {
            gotoxy(ptr->x,ptr->y);
            color(ptr->color);
            cout<<ptr->block;
            ptr=ptr->next;
        }
        gotoxy(x,y);
    }
    coordinate *insert(coordinate *point=NULL)
    {
        redundant();
    coordinate *temp=new coordinate,*ptr;
    if (temp==NULL){return NULL;}

    if(point==NULL)        //initiallize from screen
	{
		temp->x=wherex();
    	temp->y=wherey();
    	temp->color=inkcolor;
    	temp->block=pen;
	}
	else                   //initiallize from given point
	{
		temp->x=point->x;
		temp->y=point->y;
		temp->color=point->color;
		temp->block=point->block;
	}
    if(START==NULL)
    {
        START=LAST=temp;
        START->previous=NULL;
        LAST->next=NULL;
    }
    else
    {
        LAST->next=temp;
        ptr=LAST;
        LAST=temp;
        LAST->previous=ptr;
        LAST->next=NULL;
    }
    edited=true;
	return LAST;
}
    void Delete(coordinate *point=NULL)
    {
	redundant();
    coordinate *ptr;
    int x1,y1;
	if(point==NULL)
	{
        x1=wherex();
        y1=wherey();
	}
	else
	{
		x1=point->x;
		y1=point->y;
	}

	coordinate *temp=NULL;
                temp=START;
	while(temp!=NULL)
	{

		if(temp->x==x1  && temp->y==y1)
			break;

		temp=temp->next;
	}

	if(temp!=NULL)
	{

		ptr=temp;
		if(START==LAST)
		{
			START=LAST=temp=NULL;
			gotoxy(ptr->x,ptr->y);
			cout<<" ";
			gotoxy(ptr->x,ptr->y);
			delete ptr;
		}
		else if(temp==START)
		{
			START=temp->next;
			START->previous=NULL;
			gotoxy(ptr->x,ptr->y);
			cout<<" ";
			gotoxy(ptr->x,ptr->y);
			delete ptr;
		}

		else if(temp==LAST)
		{
			LAST=temp->previous;
			LAST->next=NULL;
			gotoxy(ptr->x,ptr->y);
			cout<<" ";
			gotoxy(ptr->x,ptr->y);
			delete ptr;
		}

		else
		{
		    gotoxy(temp->x,temp->y);
		    cout<<" ";
		    gotoxy(temp->x,temp->y);
			temp=temp->previous;
			temp->next=ptr->next;
			temp=ptr->next;
			temp->previous=ptr->previous;
		}

	}
	edited=true;
	}
    coordinate *line(int x1,int y1,int x2,int y2)
    {
	int dx=x2-x1;
	int dy=y2-y1;
	coordinate temp(pen,inkcolor),linebeg;
	linebeg.x=x1;
	linebeg.y=y1;
	if(fabs(dy)>fabs(dx))
	{
		for(int y=y1;y!=y2;y+=sign(dy))
		{
			int x=x1+(y-y1)*dx/dy;
			temp.x = x;
			temp.y = y;
			insert(&temp);
		}
	}
	else
	{
	    int prevY=0;
		for(int x=x1;x!=x2;x+=sign(dx))
		{
		    if(dy==0)
		    {
			temp.x=x;
			temp.y=y1;
			insert(&temp);
            }
            else
            {
			int y=y1+(x-x1)*dy/dx;
			if(prevY==y)
			continue;

			temp.x=x;
			temp.y=y;
			insert(&temp);
			prevY=y;
			}
		}
	}
	temp.x=x2;
	temp.y=y2;
    insert(&temp);
    return &linebeg;
    }
    char move()
    {
    char ch='\0';
    int x=-1,y=-1;
    while(1)
    {
        x=wherex();
        y=wherey();
        constrain(x,y);
        ch=getch();
        if(ch==up)
            gotoxy(x,--y);
        else if(ch==down)
            gotoxy(x,++y);
        else if(ch==right)
            gotoxy(++x,y);
        else if(ch==left)
            gotoxy(--x,y);
        else if(ch=='.' or ch=='l' or ch=='c' or ch==13
                or ch=='d' or ch=='e' or ch=='s' or ch=='o'
                or ch=='b' or ch=='r' or ch=='n' or (ch>=48 and ch<=57)
                or ch=='u' or ch=='p' or ch==' ')
        break;
    }
    return ch;
    }
    void drawline();
    int Displaymenu(char menu_item[][MAX_PATH],int msize);
    char *fileexp()
    {
    int i=0,j;
    char path[MAX_PATH],cmd[MAX_PATH+128];
    for(i=0;i<MAX_PATH;i++)
    chart[i][0]=0;
    strcpy(path,"\"");
    strcat(path,exepath().c_str());
    strcat(path,"\\C_PAINT-art");
    strcpy(cmd,"cd ");
    strcat(cmd,path);
    strcat(cmd,"\"");
    int check=system(cmd);
    if(check==1)
    {
        strcpy(cmd,"mkdir ");
        strcat(cmd,path);
        strcat(cmd,"\"");
        system(cmd);
    }
    strcpy(cmd,"dir /b ");
    strcat(path,"\"");
    strcat(cmd,path);
    strcat(cmd," >");
    strcat(path,"\\tmp.dat\"");
    strcat(cmd,path);
    system(cmd);
    for(j=strlen(path)-2;path[j]!='\"' && j>=0;j--);
        while(path[j]!=0)
       {
         path[j]=path[j+1];
            j++;
       }
    fstream file;
    for(j=0;j<strlen(path);j++)
    {
        if(path[j]=='\"')
        {
            for(int l=j;l<=strlen(path)-1;l++)
            path[l]=path[l+1];
        }
    }
    file.open(path,ios::in);
    if(!file){cout<<"ERROR! Not able to read directory"; return NULL;}
j=0;
while(!file.eof())
{
    file.getline(chart[j],MAX_PATH,'\n');
     if(strcmp(chart[j],"tmp.bat")==0)
     {
         j--;
     }

     j++;

     if(j==MAX_PATH)break;
}
    j--;
    gotoxy(WIDTH-14,0);
   return chart[Displaymenu(chart,j)];
}
int save()
    {

        int basex=wherex(),basey=wherey();
        char filepath[MAX_PATH];
        strcpy(filepath,exepath().c_str());
        strcat(filepath,"\\C_PAINT-art\\");
        gotoxy(1,HEIGHT+3);
        cout<<"Enter file name:";cin.getline(FILENAME,128,'\n');
        strcat(filepath,FILENAME);
        int check=system("cd C_PAINT-art");
        if(check!=0)
        system("md C_PAINT-art");
        strcat(filepath,".C_art");strcat(FILENAME,".C_art");
        cout<<filepath;
        fstream file;file.open(filepath,ios::out|ios::binary);
        gotoxy(1,HEIGHT+3);
        if(!file){cerr<<"Unable to create file! Please check your file permision";return -1;}
        coordinate *temp=START;
        edited=false;
        while(temp!=NULL)
        {
            file.write((char*)temp,sizeof(coordinate));
            temp=temp->next;
        }
        system("cls");
        drawwindows(windowno);
        refresh(START);
        gotoxy(1,HEIGHT+3);
        cout<<FILENAME<<" Saved...Successfully";
        file.close();
        gotoxy(basex,basey);
        return 0;
    }
    int open(char *name=NULL,int display=true)
    {
        fstream file;
        coordinate temp;char *str=NULL;
        char filepath[MAX_PATH];

        if(display==true and name==NULL)
        {
            strcpy(filepath,exepath().c_str());
            strcat(filepath,"\\C_PAINT-art");
            if(system("cd C_PAINT-art")!=0)
            {
                gotoxy(1,HEIGHT+2);
                cerr<<"Error! Directory \"C_PAINT-art\" not found.";
                return -1;
            }
            str=fileexp();
            strcpy(FILENAME,str);
            strcat(filepath,"\\");
            strcat(filepath,FILENAME);
            file.open(filepath,ios::in|ios::binary);
        }
         else
        {
            file.open(FILENAME,ios::in|ios::binary);
        }
        if(!file){cerr<<"Cannot read the directory"; return -1;}
        START=LAST=NULL;
        while(file)
        {
            file.read((char *)&temp,sizeof(coordinate));
            insert(&temp);
        }
        system("cls");
        drawwindows(windowno);
        refresh(START);
        gotoxy(LAST->x,LAST->y);
        return 0;
    }
void freehanddrawing()
{
    edited=true;
    char ch;int x=wherex(),y=wherey();
     insert(NULL);
     refresh(START);
    while(1)
    {
        ch=getch();
        switch(ch)
        {
          case up:
          gotoxy(x,--y);constrain(x,y);
          break;
          case down:
          gotoxy(x,++y);constrain(x,y);
          break;
          case right:
          gotoxy(++x,y);constrain(x,y);
          break;
          case left:
          gotoxy(--x,y);constrain(x,y);
          break;
          case 13:
          return;
        };
        redundant();insert(NULL);
        refresh(LAST);
    }
}
void freehanderasing()
{
    edited=true;
    char ch;int x=wherex(),y=wherey();
     Delete();
     //refresh(START);
    while(1)
    {
        ch=getch();
        switch(ch)
        {
          case up:
          gotoxy(x,--y);constrain(x,y);
          break;
          case down:
          gotoxy(x,++y);constrain(x,y);
          break;
          case right:
          gotoxy(++x,y);constrain(x,y);
          break;
          case left:
          gotoxy(--x,y);constrain(x,y);
          break;
          case 13:
          return;
        };
        redundant();Delete();
    }
}
};
int PAINT::Displaymenu(char menu_item[][MAX_PATH],int msize)
{
    const int n=msize;
    int kpsd[n],basey=wherey(),selected=1,i=0,basex=wherex();
    kpsd[0]=1;
    for(i=1;i<n;i++)
    kpsd[i]=0;
    while(1)
    {
        i=0;
       int position=basey;
        color(78);
        gotoxy(wherex(),wherey());
        gotoxy(basex,++position);
        for(i=0;i<msize;i++)
        {

            if(kpsd[i]==1)
            {
                color(23);
                gotoxy(basex,++position);
                cout.write(menu_item[i],11);if(strlen(menu_item[i])>11)cout<<"...";
                gotoxy(basex,++position);
                color(02);
            }
            else
            {
                color(02);
                gotoxy(basex,++position);
                cout.write(menu_item[i],11);
                if(strlen(menu_item[i])>11)cout<<"...";
                gotoxy(basex,++position);
            }
        }
         char ch=getch();
        if(ch==down) //down
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
        else if(ch==up) //up
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
            return i;
        }
        else
        gotoxy(basex,basey);
    }
    return i;
}
void PAINT::constrain(int &a,int &b)   //checks limits
{
	if(a>=WIDTH-17)
	a=WIDTH-17;
	else if(a<=1)
	 a=2;

	if(b>=HEIGHT-2)
	b=HEIGHT-2;
	else if(b<=2)
	b=2;
}
void PAINT::redundant()               // duplicacy remover
{
	coordinate *val,*temp,*ptr;
	temp=ptr=LAST;
	while(temp!=NULL)
	{
		ptr=temp;
		while(ptr!=NULL)
		{
			if((temp->x==ptr->x && temp->y==ptr->y) && ptr!=temp)
			{
				val=ptr;
				if(val==START)
				{
				 START=START->next;
				 START->previous=NULL;
				 ptr=START->previous;
				 delete val;
				 break;
				}
				else
				{
				ptr=ptr->next;
				ptr->previous=val->previous;
				ptr=val->previous;
				ptr->next=val->next;
				ptr=val->next;
				delete val;
				}
			}
			ptr=ptr->previous;
		}
		temp=temp->previous;
	}
}

void PAINT::drawline()
{
    coordinate pointa,pointb;
	int count=0;edited=true;
		    char input;
			while(input!='\n')
			{
				input=move();
					if(input=='.')
					{
						++count;
						if(count==1)
						{
							pointa.x=wherex();
							pointa.y=wherey();
							cout<<'.';
							gotoxy(pointa.x,pointa.y);
							constrain(pointa.x,pointa.y);
						}
						else if(count==2)
						{
							pointb.x=wherex();
							pointb.y=wherey();
                            line(pointa.x,pointa.y,pointb.x,pointb.y);
							break;
						}
					}
			}
}
HANDLE wHnd,rHnd;
void window(char wname[]="C_PAINT")
 {
    SMALL_RECT windowSize = {0, 0,2*WIDTH - 1, 2*HEIGHT - 1};
  COORD bufferSize = {2*WIDTH,2* HEIGHT};
  COORD characterBufferSize = {2*WIDTH,2* HEIGHT};
  COORD characterPosition = {0, 0};
  SMALL_RECT consoleWriteArea = {0, 0,2* WIDTH - 1,2* HEIGHT - 1};
 wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
  rHnd = GetStdHandle(STD_INPUT_HANDLE);
  SetConsoleTitle(wname);
  SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
  SetConsoleScreenBufferSize(wHnd, bufferSize);
 }
PAINT *p,*START=NULL,*LAST=NULL;  //GOLOBAL OBJECTS

PAINT *insertpaint(int wno,char *name=NULL,int opened=false)
{
    PAINT *temp;
    if(name==NULL)
     temp=new PAINT(wno,"UNTITLED",true);
    else
     temp=new PAINT(wno,name,opened);
    if(START==NULL)
    {
        START=LAST=temp;
        START->next=NULL;
        LAST->next=NULL;
    }
    else
    {
        LAST->next=temp;
        LAST=temp;
        LAST->next=NULL;
    }
    return LAST;
}
PAINT *deletepaint(PAINT *p)
{
    if(START==NULL)
    return NULL;
    else
    {
        PAINT *temp=p,*previous=START;
        if(p==START)
        {
            START=p=START->next;
            START->setwindowno(1);
            delete temp;
            return START;
        }
        else
        {
            while(previous->next!=temp )
            {
                previous=previous->next;
            }
            if(previous!=NULL)
            {
                previous->next=temp->next;
                PAINT *forward=previous->next;
                forward->setwindowno(forward->getwindowno()-1);
                delete temp;
                return previous;
            }
        }
    }
}
int main(int argc, char** argv=NULL)
{
    window();
    system("cls");
    system("color 07");
    int wno=0;
    char input=0;
    if(argv!=NULL)
    p=insertpaint(++wno,argv[1],false);
    else
    p=insertpaint(++wno);
    while(1)
    {
        if(p==NULL){cerr<<"System out of memory!!! Program exiting";totalwindows=1;return -1;}
        input=p->move();
        if(input=='.')
        p->insert(NULL);
        else if(input=='p')
        p->freehanddrawing();
        else if(input=='c')
        p->Delete(NULL);
        else if(input=='l')
        p->drawline();
        else if(input=='s')
         {
             if(p->save()==-1)
            {
                cout<<"Unable to save!!! Try again else (e)xit";
            }
         }
        else if(input=='o')
            p->open();
        else if(input=='b')
        p->choosebrush();
        else if(input=='r')
        {p->setcolor();}
        else if(input=='n')
        {
            system("cls");
            p=insertpaint(++wno);
            totalwindows+=1;
            p->drawwindows(p->getwindowno());
            p->refresh(p->getstart());
        }
        else if(input==' ')
        {
            p->freehanderasing();
        }
        else if(input>=48 and input<=57)
        {
            PAINT *ptr=START;
            while(ptr!=NULL)
            {
                if(ptr->getwindowno()==input-48)
                {
                    system("cls");
                    ptr->drawwindows(ptr->getwindowno());
                    ptr->dispalyinfo(wno);
                    ptr->refresh(ptr->getstart());
                    p=ptr;
                    break;
                }
                else
                ptr=ptr->next;
            }
        }
        else if(input=='e')
        {
            char ch;
            if(p->getedited()==true )
            {
                gotoxy(1,HEIGHT+2);
                int check;
                cout<<"'"<<p->getfilename()<<"'"<<" NOT SAVED, Do you Want to save it?(Y/N):";
                ch=getche();
                if(ch=='Y' or ch=='y')
                {
                    p->save();
                    p=deletepaint(p);
                    if(p==NULL)
                    return 0;
                    else
                    {
                        system("cls");
                        p->drawwindows(p->getwindowno());
                        p->dispalyinfo(--wno);
                        p->refresh(p->getstart());
                    }
                }

            else if(ch=='N' or ch=='n')
            {
                p=deletepaint(p);
                    if(p==NULL)
                    return 0;
                    else
                    {
                        system("cls");
                        p->drawwindows(p->getwindowno());
                        p->dispalyinfo(--wno);
                        p->refresh(p->getstart());
                    }
            }
            }
        }
        if(p==NULL)break;
        p->refresh(p->getstart());
        }
    return 0;
}
