#include<iostream>
#include<conio.h>
#include<dos.h>
#include <windows.h>
#include <time.h>

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int enemyY[3];
int enemyX[3];
int enemyFlag[3];
int carty=0;
char car[4][4] = { ' ','�','�',' ',
'�','�','�','�',
' ','�','�',' ',
'�','�','�','�' };

char car2[4][4] = { ' ','-','-',' ',
'-','-','-','-',
' ','-','-',' ',
'-','-','-','-' };

char car3[4][4] = { '�','�','�','�',
' ','�','�',' ',
' ','�','�',' ',
' ','�','�',' '};

int carPos = WIN_WIDTH/2;
int score = 0;

void gotoxy(int x, int y)
{
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}
void setcursor(bool visible, DWORD size)
{
    if(size == 0)
        size = 20;
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console,&lpCursor);
}
void drawBorder()
{
    for(int i=0; i<SCREEN_HEIGHT; i++)
    {
        for(int j=0; j<17; j++)
        {
            gotoxy(0+j,i); cout<<"�";
            gotoxy(WIN_WIDTH-j,i); cout<<"�";
        }
    }
    for(int i=0; i<SCREEN_HEIGHT; i++)
    {
        gotoxy(SCREEN_WIDTH,i); cout<<"�";
    }
}

void genEnemy(int ind)
{
    enemyX[ind] = 17 + rand()%(33);
}

void drawEnemy(int ind)
{
    if( enemyFlag[ind] == true )
    {
        gotoxy(enemyX[ind], enemyY[ind]);   cout<<"****";
        gotoxy(enemyX[ind], enemyY[ind]+1); cout<<" ** ";
        gotoxy(enemyX[ind], enemyY[ind]+2); cout<<"****";
        gotoxy(enemyX[ind], enemyY[ind]+3); cout<<" ** ";
    }
}

void eraseEnemy(int ind)
{
    if( enemyFlag[ind] == true )
    {
        gotoxy(enemyX[ind], enemyY[ind]); cout<<"    ";
        gotoxy(enemyX[ind], enemyY[ind]+1); cout<<"    ";
        gotoxy(enemyX[ind], enemyY[ind]+2); cout<<"    ";
        gotoxy(enemyX[ind], enemyY[ind]+3); cout<<"    ";
    }
}

void resetEnemy(int ind, int dlevel)
{
    eraseEnemy(ind);
    enemyY[ind] = dlevel;
    genEnemy(ind);
}

void drawCar()
{
    if (carty==1)
    {
        for(int i=0; i<4; i++)
        {
            for(int j=0; j<4; j++)
            {
                gotoxy(j+carPos, i+22); cout<<car[i][j];
            }
        }
    }
    else if (carty==2)
    {
        for(int i=0; i<4; i++)
        {
            for(int j=0; j<4; j++)
            {
                gotoxy(j+carPos, i+22); cout<<car2[i][j];
            }
        }
    }
    else if (carty==3)
    {
        for(int i=0; i<4; i++)
        {
            for(int j=0; j<4; j++)
            {
                gotoxy(j+carPos, i+22); cout<<car3[i][j];
            }
        }
    }
}

void eraseCar()
{
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            gotoxy(j+carPos, i+22); cout<<" ";
        }
    }
}

int collision()
{
    if( enemyY[0]+4 >= 23 )
    {
        if( enemyX[0] + 4 - carPos >= 0 && enemyX[0] + 4 - carPos < 9  )
        {
            return 1;
        }
    }
    return 0;
}

void gameover()
{
    system("cls");
    cout<<endl;
    cout<<"\t\t--------------------------"<<endl;
    cout<<"\t\t-------- Game Over -------"<<endl;
    cout<<"\t\t--------------------------"<<endl<<endl;
    cout<<"\t\tPress any key to go back to menu.";
    getch();
}

void updateScore()
{
    gotoxy(WIN_WIDTH + 7, 5);cout<<"Score: "<<score<<endl;
}

void instructions()
{
    system("cls");
    cout<<"Instructions";
    cout<<"\n----------------";
    cout<<"\n Avoid Cars by moving left or right. ";
    cout<<"\n\n Press 'a' to move left";
    cout<<"\n Press 'd' to move right";
    cout<<"\n Press 'escape' to exit";
    cout<<"\n\nPress any key to go back to menu";
    getch();
}

void play(int dlevel)
{
    carPos = -1 + WIN_WIDTH/2;
    score = 0;
    enemyFlag[0] = 1;
    enemyFlag[1] = 0;
    enemyY[0] = enemyY[1] = dlevel;
    system("cls");
    drawBorder();
    updateScore();
    genEnemy(0);
    genEnemy(1);
    gotoxy(WIN_WIDTH + 7, 2);cout<<"Car Game";
    gotoxy(WIN_WIDTH + 6, 4);cout<<"----------";
    gotoxy(WIN_WIDTH + 6, 6);cout<<"----------";
    gotoxy(WIN_WIDTH + 7, 12);cout<<"Control ";
    gotoxy(WIN_WIDTH + 7, 13);cout<<"-------- ";
    gotoxy(WIN_WIDTH + 2, 14);cout<<" A Key - Left";
    gotoxy(WIN_WIDTH + 2, 15);cout<<" D Key - Right";
    gotoxy(18, 5);cout<<"Press any key to start";
    getch();
    gotoxy(18, 5);cout<<"                      ";
    while(1)
    {
        if(kbhit())
        {
            char ch = getch();
            if( ch=='a' || ch=='A' )
            {
                if( carPos > 18 )
                carPos -= 4;
            }
            if( ch=='d' || ch=='D' )
            {
                if( carPos < 50 )
                carPos += 4;
            }
            if(ch==27)
            {
                break;
            }
        }
        drawCar();
        drawEnemy(0);
        drawEnemy(1);
        if( collision() == 1  )
        {
            gameover();
            return;
        }
        Sleep(50);
        eraseCar();
        eraseEnemy(0);
        eraseEnemy(1);
        if( enemyY[0] == 10 )
            if( enemyFlag[1] == 0 )
            enemyFlag[1] = 1;
        if( enemyFlag[0] == 1 )
            enemyY[0] += 1;
        if( enemyFlag[1] == 1 )
            enemyY[1] += 1;
        if( enemyY[0] > SCREEN_HEIGHT-4 )
        {
            resetEnemy(0, dlevel);
            score++;
            updateScore();
        }
        if( enemyY[1] > SCREEN_HEIGHT-4 )
        {
            resetEnemy(1, dlevel);
            score++;
            updateScore();
        }
    }
}

int main()
{
    setcursor(0,0);
    srand( (unsigned)time(NULL));
    do
    {
        system("cls");
        gotoxy(10,5); cout<<" -------------------------- ";
        gotoxy(10,6); cout<<" |        Car Game        | ";
        gotoxy(10,7); cout<<" --------------------------";
        gotoxy(10,9); cout<<"1. Start Game";
        gotoxy(10,10); cout<<"2. Instructions";
        gotoxy(10,11); cout<<"3. Quit";
        gotoxy(10,13); cout<<"Select option: ";
        char op = getche();
        if( op=='1')
        {
            system("cls");
            gotoxy(10,5); cout<<" -------------------------- ";
            gotoxy(10,6); cout<<" |        Car Game        | ";
            gotoxy(10,7); cout<<" --------------------------";
            gotoxy(10,9); cout<<"Choose your difficulty Level:";
            gotoxy(10,11); cout<<"1. Easy";
            gotoxy(10,12); cout<<"2. Medium";
            gotoxy(10,13); cout<<"3. Hard";
            gotoxy(10,15); cout<<"Choose your Option:";
            char opl = getche();
            system("cls");
            gotoxy(10,5); cout<<" -------------------------- ";
            gotoxy(10,6); cout<<" |        Car Game        | ";
            gotoxy(10,7); cout<<" --------------------------";
            gotoxy(10,9); cout<<"Select your Car Type:";
            gotoxy(10,11); cout<<"1. Car Type 1";
            gotoxy(10,12); cout<<"2. Car Type 2";
            gotoxy(10,13); cout<<"3. Car Type 3";
            gotoxy(10,15); cout<<"Choose your Option:";
            char cty = getche();
            if (cty=='1')
                carty=1;
            else if (cty=='2')
                carty=2;
            else if (cty=='3')
                carty=3;
            if (opl=='1')
            {
                play(1);
            }
            else if (opl=='2')
                play(5);
            else if (opl=='3')
                play(10);
        }
        else if( op=='2') instructions();
        else if( op=='3') exit(0);
    }while(1);
return 0;
}
