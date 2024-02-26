#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

void gotoxy(int x,int y);
void hidecursor();
void map();
void soldier();
void enemy();
void fire();

int random;
int threshold = 3;
int skor = 5;
int MapWidth = 50;
int MapHeight = 10;
int sx = 3;
int sy = 5;
int enemyx = 49;
int enemyy;
int bullety;
int bulletx = 4;
int IsBulletFire;

void main(){
	enemyy = rand()%8+2;
	hidecursor();
	map();
	while(1){
		enemy();
		soldier();
		fire();
		if(enemyy==bullety&&enemyx==bulletx||sx==enemyx&&sy==enemyy){
			skor++;
    	    enemyx = 49;
    	    enemyy = rand()%8+2;
		}
		
		gotoxy(13,13);
		printf("Skor : %d",skor);
		if(skor<0){
			gotoxy(13,13);
			printf("Kale dustu");
			break;
		}
		if(skor>10){
			gotoxy(13,13);
			printf("Kazandýn dusman dustu");
			break;
		}
	}
	getch();
}
void hidecursor(){
	CONSOLE_CURSOR_INFO cursor_info={1,0}; 
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);	
}
void gotoxy(int x, int y)
{
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void map(){
		int i,j;
    gotoxy(1,1);
    for (i = 0; i < MapHeight; i++) {
    for (j = 0; j < MapWidth; j++) {
    if (i == 0 || i == MapHeight - 1 || j == 0 || j == MapWidth - 1) {
    printf("%c",220);
    }
    else
	printf(" ");
    }
    printf("\n");
    }
}
void soldier(){
	if(_kbhit()){
		char mc = getch();
		gotoxy(sx,sy);
		printf(" ");
		switch(mc){
			case 72: if(sy>2)sy--;
		break;
		    case 80: if(sy< 9)sy++;
		break;
		    case ' ': if(IsBulletFire==0){ bullety = sy; bulletx++; IsBulletFire++; }
				break;
		break;
		    default:
		break;
		}
		gotoxy(sx,sy);
		printf("S");
	}
}
void enemy(){
	enum {SECS_TO_SLEEP = 0, NSEC_TO_SLEEP = 90000000};
    struct timespec surec, istenen = {SECS_TO_SLEEP, NSEC_TO_SLEEP};
    gotoxy(enemyx,enemyy);
    printf(" ");
    enemyx--;
    	random=rand()%6;
    if(random<threshold&&enemyy<MapHeight-1){
    	enemyy++;
	}
    if(random>threshold&&enemyy>MapHeight-8){
    	enemyy--;
	}
    gotoxy(enemyx,enemyy);
    printf("e");
    nanosleep(&istenen,&surec);
    if(enemyx==2){
    	skor--;
    	gotoxy(enemyx,enemyy);
    	printf(" ");
    	enemyx = 49;
    	enemyy = rand()%8+2;
	}
}
void fire(){
	    if (bulletx > 4) {
        gotoxy(bulletx, bullety);
        printf(" "); 
        bulletx++;
        gotoxy(bulletx, bullety);
        printf("-");
        if (bulletx > MapWidth-2) {
        gotoxy(bulletx, bullety);
        printf(" ");
        bulletx = 4;
        IsBulletFire--;
        }
    }
}
