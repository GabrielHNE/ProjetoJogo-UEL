#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h> 		//contem time(), que retorna o tempo atual em ms
#include <windows.h>	//contem funcoes necessarias para a funcao gotoxy;


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

void pontuacao(int Ox,int Oy,int *score,int mapa[][30]);
void delay(unsigned int milliseconds);
void gotoxy(int x, int y);
void mapaDraw(int mapa[][30]);
void printMapa(int map[][30],int i,int j);
					
	void printPac(int Nx, int Ny, int Ox, int Oy,int *score,int mapa[][30]);
	int verMovX(char* tecla,char* keepMove,int x, int y,int mapa[][30]);
	int verMovY(char* tecla,char* keepMove, int y, int x,int mapa[][30]);	

int main(int argc, char** argv){
	
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
						{0,0,0,0,5,1,5,5,1,8,6,6,6,0,0,0,0,6,6,6,7,1,5,5,1,5,0,0,0,0},
						{0,0,0,0,5,1,5,5,1,5,0,0,0,0,0,0,0,0,0,0,5,1,5,5,1,5,0,0,0,0},
						{0,0,0,0,5,1,5,5,1,5,0,0,0,0,0,0,0,0,0,0,5,1,5,5,1,5,0,0,0,0},
						{0,0,0,0,5,1,5,5,1,5,0,0,0,0,0,0,0,0,0,0,5,1,5,5,1,5,0,0,0,0},
						{6,6,6,6,9,1,4,9,1,5,0,0,0,0,0,0,0,0,0,0,5,1,4,9,1,4,6,6,6,6},
						{1,1,1,1,1,1,1,1,1,5,0,0,0,0,0,0,0,0,0,0,5,1,1,1,1,1,1,1,1,1},
						{6,6,6,6,7,1,8,7,1,5,0,0,0,0,0,0,0,0,0,0,5,1,8,7,1,8,6,6,6,6},
						{0,0,0,0,5,1,5,5,1,4,6,6,6,6,6,6,6,6,6,6,9,1,5,5,1,5,0,0,0,0},
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
						
	int gameOver=0;
	int i, x, y;
	int score=0; 
	char tecla = 's', oldTecla='d', keepMove; 
	Pacman pacman;
	
	system("MODE con cols=150 lines=30");   //define o tamanho da tela !!! para centralizar faz (150 - (largura do mapa))/2;
	delay(3000);
	mapaDraw(mapa);
	pacman.posX = 74; 						//distancia da parede (largura)
	pacman.posY	= 23; 						//altura
	gotoxy(pacman.posX,pacman.posY);		// coloca o pacman na posicao inicial
	pacman.oldX = 1;
	pacman.oldY = 1;
	
	while(!gameOver){
		if(pacman.oldX != pacman.posX ){
			pacman.oldX = pacman.posX;
		}
		if(pacman.oldY != pacman.posY)	{
			pacman.oldY = pacman.posY;
		}

		pacman.posY = verMovY(&tecla,&keepMove, pacman.posY, pacman.oldX,mapa);
		pacman.posX = verMovX(&tecla,&keepMove, pacman.posX,pacman.oldY,mapa);
		printPac(pacman.posX, pacman.posY, pacman.oldX, pacman.oldY,&score,mapa);
		if(kbhit()){
			keepMove = tecla;
			tecla = getch();
			if(oldTecla != tecla){			//nao deixa bugar
				oldTecla = tecla;
				pacman.oldX = pacman.posX;
				pacman.oldY = pacman.posY;
				pacman.posY = verMovY(&tecla, &keepMove, pacman.posY, pacman.oldX,mapa);
				pacman.posX = verMovX(&tecla, &keepMove, pacman.posX,pacman.oldY,mapa);
			}
			printPac(pacman.posX, pacman.posY, pacman.oldX, pacman.oldY,&score,mapa);
		}

		delay(200);
	}
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
void mapaDraw(int mapa[][30]){
	int i,j;
	for(i=0;i<30;i++){
		for(j=0;j<30;j++){
			printMapa(mapa,i,j);
		}
	}
}
void printMapa(int mapa[][30],int i, int j){
		
	switch(mapa[i][j]){
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
void printPac(int Nx, int Ny, int Ox, int Oy,int *score,int mapa[][30]){
	if(Nx!=Ox || Ny!=Oy)
	{
	gotoxy(Nx,Ny);
	printf("%c", personagem);
	gotoxy(0,0);
	pontuacao(Ox,Oy,score,mapa);
	gotoxy(Ox,Oy);
	printf(" ", personagem);
	mapa[Oy][Ox-60]=0;
	gotoxy(0,0);
	}
}
int verMovX(char* tecla, char* keepMove, int x,int y,int mapa[][30]){
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
int verMovY(char* tecla, char* keepMove, int y, int x,int mapa[][30]){
	
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

void pontuacao(int Ox,int Oy,int *score,int mapa[][30]){
	int digit;
	gotoxy(35,3);
	printf(" _________");
	gotoxy(35,4);
	printf("|  SCORE  | ");
	if(mapa[Oy][Ox-60]==1){
		(*score)++;
	}
	gotoxy(35,5);
	printf("|   ""%d",(*score));
	gotoxy(45,5);
	printf("|");
	gotoxy(35,6);
	printf("|_________|");
	gotoxy(0,0);
}	
