#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h> 		//contem time(), que retorna o tempo atual em ms
#include <windows.h>	//contem funcoes necessarias para a funcao gotoxy;
#include <math.h>

int mapa[30][30] =     {{8,6,6,6,6,6,6,6,6,6,6,6,6,6,7,8,6,6,6,6,6,6,6,6,6,6,6,6,6,7},
						{5,1,1,1,1,1,1,1,1,1,1,1,1,1,5,5,1,1,1,1,1,1,1,1,1,1,1,1,1,5},
						{5,1,8,6,7,1,8,6,6,6,6,6,7,1,5,5,1,8,6,6,6,6,6,7,1,8,6,7,1,5},
						{5,1,5,0,5,1,5,0,0,0,0,0,5,1,5,5,1,5,0,0,0,0,0,5,1,5,0,5,1,5},
						{5,1,4,6,9,1,4,6,6,6,6,6,9,1,4,9,1,4,6,6,6,6,6,9,1,4,6,9,1,5},
						{5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5},
						{5,1,8,6,7,1,8,7,1,6,6,6,6,6,7,8,6,6,6,6,6,1,8,7,1,1,1,1,1,5},
						{5,1,4,6,9,1,5,5,1,1,1,1,1,1,5,5,1,1,1,1,1,1,5,5,1,1,1,1,1,5},
						{5,1,1,1,1,1,5,8,6,6,6,6,6,1,4,9,1,6,6,6,6,6,7,5,1,1,1,1,1,5},
						{4,6,6,6,7,1,5,5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5,5,1,8,6,6,6,9},
						{0,0,0,0,5,1,5,5,1,0,0,0,0,0,0,0,0,0,0,0,0,1,5,5,1,5,0,0,0,0},
						{0,0,0,0,5,1,5,5,1,0,0,0,0,0,0,0,0,0,0,0,0,1,5,5,1,5,0,0,0,0},
						{0,0,0,0,5,1,5,5,1,0,0,0,0,0,0,0,0,0,0,0,0,1,5,5,1,5,0,0,0,0},
						{0,0,0,0,5,1,5,5,1,0,0,0,0,0,0,0,0,0,0,0,0,1,5,5,1,5,0,0,0,0},
						{6,6,6,6,9,1,4,9,1,0,0,0,0,0,0,0,0,0,0,0,0,1,4,9,1,4,6,6,6,6},
						{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
						{6,6,6,6,7,1,8,7,1,0,0,0,0,0,0,0,0,0,0,0,0,1,8,7,1,8,6,6,6,6},
						{0,0,0,0,5,1,5,5,1,0,0,0,0,0,0,0,0,0,0,0,0,1,5,5,1,5,0,0,0,0},
						{0,0,0,0,5,1,5,5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5,5,1,5,0,0,0,0},
						{0,0,0,0,5,1,5,5,1,8,6,6,6,6,6,6,6,6,6,6,7,1,5,5,1,5,0,0,0,0},
						{8,6,6,6,9,1,4,9,1,4,6,6,6,6,7,8,6,6,6,6,9,1,4,9,1,4,6,6,6,7},
						{5,1,1,1,1,1,1,1,1,1,1,1,1,1,5,5,1,1,1,1,1,1,1,1,1,1,1,1,1,5},
						{5,1,6,6,7,1,6,6,6,6,6,6,6,1,4,9,1,6,6,6,6,6,6,6,1,8,6,6,1,5},
						{5,1,1,1,5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5,1,1,1,5},
						{5,6,6,1,5,1,8,7,1,6,6,6,6,6,7,8,6,6,6,6,6,1,8,7,1,5,1,6,6,5},
						{5,1,1,1,1,1,5,5,1,1,1,1,1,1,5,5,1,1,1,1,1,1,5,5,1,1,1,1,1,5},
						{5,1,8,6,6,6,9,4,6,6,6,6,7,1,5,5,1,8,6,6,6,6,9,4,6,6,6,7,1,5},
						{5,1,4,6,6,6,6,6,6,6,6,6,9,1,4,9,1,4,6,6,6,6,6,6,6,6,6,9,1,5},
						{5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5},						
						{4,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,9}};
char personagem = 'C';
typedef struct Ghost{
	int posX;
	int	posY;
	int oldX;
	int oldY;
	int Life;	//boolean
}Ghost;
typedef struct Pacman{
	int posX;
	int	posY;
	int oldX;
	int oldY;
	int Life;
}Pacman;

void delay(unsigned int milliseconds);
void gotoxy(int x, int y);
void mapaDraw();
void printMapa(int map[30][30],int i,int j);
int calculadist(int PMx, int PMy, int GHx, int GHy);
					
	void printPac(int Nx, int Ny, int Ox, int Oy, int c);
	int verMovX(char* tecla,char* keepMove,int x, int y);
	int verMovY(char* tecla,char* keepMove, int y, int x);
	void movGhost(Ghost* ghost, Pacman* pacman);	

int main(int argc, char** argv){
	int gameOver=0;
	int i=4, x, y; 
	char tecla = 's', oldTecla='d', keepMove, sair;
	Pacman pacman;
    Ghost  ghost;
	
	system("MODE con cols=150 lines=30");   //define o tamanho da tela !!! para centralizar faz (150 - (largura do mapa))/2;
	delay(3000);
	mapaDraw();
	pacman.posX = 73; 						//distancia da parede (largura)
	pacman.posY	= 3; 						//altura
	gotoxy(pacman.posX,pacman.posY);		// coloca o pacman na posicao inicial
    gotoxy(0,0);
	pacman.oldX = 1;
	pacman.oldY = 1;

    ghost.posX = 74;
    ghost.posY = 13;
    gotoxy(ghost.posX, ghost.posY);
    gotoxy(0,0);
	
	while(!gameOver){
		if(pacman.oldX != pacman.posX ){
			pacman.oldX = pacman.posX;
		}
		if(pacman.oldY != pacman.posY)	{
			pacman.oldY = pacman.posY;
		}
		if(ghost.oldX != ghost.posX)
		{
			ghost.oldX = ghost.posX;
		}
		if(ghost.oldY != ghost.posY)
		{
			ghost.oldY = ghost.posY;
		}
		
		if(kbhit()){
			keepMove = tecla;
			tecla = getch();
		}
		pacman.posY = verMovY(&tecla,&keepMove, pacman.posY, pacman.oldX);
		pacman.posX = verMovX(&tecla,&keepMove, pacman.posX,pacman.oldY);
        movGhost(&ghost, &pacman);
       
		printPac(pacman.posX, pacman.posY, pacman.oldX, pacman.oldY,1);
        printPac(ghost.posX, ghost.posY, ghost.oldX, ghost.oldY,0);
        
        if(pacman.posX==ghost.posX && pacman.posY==ghost.posY)
        {
        	gameOver=1;
		}

		delay(200);
	}
	
	system("cls");
	return 0;
}
void delay(unsigned int milliseconds){	//funcao que permite criar delays para debugging
    clock_t start = clock();
    while((clock() - start) * 1000 / CLOCKS_PER_SEC < milliseconds){}
}
void gotoxy(int x, int y){
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void mapaDraw(){
	int i,j;
	for(i=0;i<30;i++){
		for(j=0;j<30;j++){
			printMapa(mapa,i,j);
		}
	}
}
void printMapa(int map[30][30],int i, int j){
		
	switch(map[i][j]){
		case 1:{
			//printa pontos
			gotoxy(60+j,i);
			printf("*");
			break;
		}
		case 4:{
			//canto inferior esquerdo
			gotoxy(60+j,i);
			printf("%c", 200);
			break;
		}
		case 5:{
			//printa vertical
			gotoxy(60+j,i);
			printf("%c", 186);
			break;
		}
		case 6:{
			//printa horizontal
			gotoxy(60+j,i);
			printf("%c", 205);
			break;
		}
		case 7:{
			//canto superior direito
			gotoxy(60+j,i);
			printf("%c", 187);
			break;
		}
		case 8:{
			//canto superior esquerdo			
			gotoxy(60+j,i);
			printf("%c", 201);
			break;
		}
		case 9:{
			//canto inferior direito
			gotoxy(60+j,i);
			printf("%c", 188);
			break;
		}
		case -1:{
			gotoxy(60+j,i);
			printf("%c", 202);
			break;
		}
	}
}
void printPac(int Nx, int Ny, int Ox, int Oy, int c){
	if(c == 1)
	{
		if(Nx!=Ox || Ny!=Oy)
		{
		gotoxy(Nx,Ny);
		printf("%c", personagem);
		gotoxy(0,0);
		gotoxy(Ox,Oy);
		printf(" ");
		gotoxy(0,0);
		}
	} else{
		if(Nx!=Ox || Ny!=Oy)
		{
		gotoxy(Nx,Ny);
		printf("G");
		gotoxy(0,0);
		gotoxy(Ox,Oy);
		printf(" ");
		gotoxy(0,0);
		}	
	}
		
}
int verMovX(char* tecla, char* keepMove, int x,int y){
	switch(*tecla){
		case 'a':{
			if(mapa[y][x-61] == 1 || mapa[y][x-61] == 0){
				x--;
				*keepMove = *tecla;
				return x;
			} else{
				*tecla = *keepMove;
				return x;}
			break;
		}
		case 'd':{
			if(mapa[y][x-59] == 1 || mapa[y][x-59] == 0){
				x++;
				*keepMove = *tecla;				
				return x;
			} else {
				*tecla = *keepMove;
				return x;}
			break;
		}
		default:{
			return x;
			break;
		}
	}
}
int verMovY(char* tecla, char* keepMove, int y, int x){
	
	switch(*tecla){
		case 'w':{
			if(mapa[y-1][x-60] == 1 || mapa[y-1][x-60] == 0){
				y--;
				*keepMove = *tecla;
				return y;
			}else{
				*tecla = *keepMove;
				return y;}
			break;
		}
		case 's':{
			if(mapa[y+1][x-60] == 1 || mapa[y+1][x-60] == 0){
				y++;
				*keepMove = *tecla;				
				return y;
			}else{
				*tecla = *keepMove;
				return y;}
			break;
		}
		default:{
			return y;
			break;
		}
	}
}
int calculadist(int PMx, int PMy, int GHx, int GHy){
	return sqrt(pow(GHx-PMx,2) + pow(GHy-PMy,2));
}
void movGhost(Ghost* ghost, Pacman* pacman){
	int dist_menor;
  	int GHx_menor;
  	int GHy_menor;
  	dist_menor = calculadist((*ghost).posX,(*ghost).posY,(*pacman).posX,(*pacman).posY);
  	GHx_menor = (*ghost).posX ;
  	GHy_menor = (*ghost).posY;
  	
  	if((mapa[(*ghost).posY][(*ghost).posX  - 61] == 1 || mapa[(*ghost).posY][((*ghost).posX - 61)] == 0) && (calculadist(((*ghost).posX-1),(*ghost).posY,(*pacman).posX,(*pacman).posY) < dist_menor))
  	{
      GHx_menor = ((*ghost).posX - 1);
      GHy_menor = (*ghost).posY;
	}	
  	else if((mapa[(*ghost).posY][((*ghost).posX-59)] == 1 || mapa[(*ghost).posY][((*ghost).posX - 61)] == 0) && (calculadist(((*ghost).posX +1),(*ghost).posY,(*pacman).posX,(*pacman).posY) < dist_menor))
  	{
      GHx_menor = ((*ghost).posX) + 1;
      GHy_menor = (*ghost).posY;
  	}
  	else if((mapa[(*ghost).posY-1][((*ghost).posX - 60)] == 1 || mapa[(*ghost).posY][((*ghost).posX-60) - 1] == 0) && (calculadist((*ghost).posX ,((*ghost).posY-1),(*pacman).posX,(*pacman).posY) < dist_menor))
  	{
      GHx_menor = (*ghost).posX ;
      GHy_menor = ((*ghost).posY - 1);
  	}
  	else if((mapa[(*ghost).posY+1][((*ghost).posX-60)] == 1 || mapa[(*ghost).posY][((*ghost).posX-60) - 1] == 0) && (calculadist((*ghost).posX ,((*ghost).posY+1),(*pacman).posX,(*pacman).posY) < dist_menor))
  	{
      GHx_menor = (*ghost).posX ;
      GHy_menor = ((*ghost).posY + 1);
  	}
  	
    if((*ghost).posX  == GHx_menor && ((*ghost).posY == GHy_menor))
    {
        if( pow( ((*ghost).posX -1) - (*pacman).posX ,2) < pow( ((*ghost).posX - (*pacman).posX) ,2)  && (mapa[(*ghost).posY][(*ghost).posX -61] == 1 || mapa[(*ghost).posY][(*ghost).posX -61] == 0))
            GHx_menor = (*ghost).posX -1;
        else if( pow( ((*ghost).posX +1) - (*pacman).posX, 2) < pow( ((*ghost).posX - (*pacman).posX), 2) && (mapa[(*ghost).posY][(*ghost).posX -59] == 1 || mapa[(*ghost).posY][(*ghost).posX -59] == 0))
            GHx_menor = (*ghost).posX +1;

        if( pow( ((*ghost).posY-1) - (*pacman).posY ,2) < pow( ((*ghost).posY - (*pacman).posY) ,2) && (mapa[(*ghost).posY-1][(*ghost).posX-60] == 1 || mapa[(*ghost).posY-1][(*ghost).posX -60] == 0))
            GHy_menor = (*ghost).posY-1;
        else if( pow( ((*ghost).posY+1) - (*pacman).posY, 2) < pow( ((*ghost).posY - (*pacman).posY), 2) && (mapa[(*ghost).posY+1][(*ghost).posX-60] == 1 || mapa[(*ghost).posY+1][(*ghost).posX-60] == 0))
            GHy_menor = (*ghost).posY+1;
    } 
    

    (*ghost).posX  = GHx_menor;
    (*ghost).posY = GHy_menor;
	
}

void debug(Pacman* pac, Ghost* ghost, int i){
	gotoxy(4,i);
	printf("pac: %d, %d", (*pac).posX,(*pac).posY);
	gotoxy(4,i);
	printf("ghost: %d, %d", (*ghost).posX,(*ghost).posY);
}


