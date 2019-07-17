#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h> 		//contem time(), que retorna o tempo atual em ms
#include <windows.h>	//contem fun��es necessarias para a funcao gotoxy;

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
char personagem = 'C';

typedef struct Pacman{
	int posX;
	int	posY;
	int Life;
}Pacman;

void delay(unsigned int milliseconds);
void gotoxy(int x, int y);
void mapaDraw();
void printMapa(int map[30][30],int i,int j);
void movingPacman();	//incompleta, mas devera incluir as funções identadas;						
	void printPac(int x, int y);
	int verMovX(char tecla,int x, int y);
	int verMovY(char tecla, int y, int x);	

int main(int argc, char** argv){
	int gameOver=0;
	int i;
	char tecla;
	Pacman pacman;
	
	system("MODE con cols=150 lines=100");   //define o tamanho da tela !!! para centralizar faz (150 - (largura do mapa))/2;
	delay(3000);
	mapaDraw(mapa);
	pacman.posX = 74; 						//distancia da parede (largura)
	pacman.posY	= 23; 						//altura
	gotoxy(pacman.posX,pacman.posY);		// coloca o pacman na posicao inicial
	
	while(!gameOver){
		if(kbhit()){
			tecla = getch();
				pacman.posY = verMovY(tecla,pacman.posY, pacman.posX);
				pacman.posX = verMovX(tecla,pacman.posX,pacman.posY);
		}		
		printPac(pacman.posX,pacman.posY);
		delay(150);
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
void mapaDraw(int mapa[30][30]){
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
void printPac(int x, int y){	
	gotoxy(x,y);
	printf("%c",personagem);
	delay(80);
	gotoxy(x,y);
	printf(" ");
	gotoxy(0,0);
}
int verMovX(char tecla, int x,int y){
	switch(tecla){
		case 'a':{
			if(mapa[y][x-61] == 1 || mapa[y][x-61] == 0){
				x--;
				return x;
			}else{return x;
			}
			break;
		}
		case 'd':{
			if(mapa[y][x-59] == 1 || mapa[y][x-59] == 0){
				x++;
				return x;
			}else{return x;}
			break;
		}
		default:{
			return x;
			break;
		}
	}
}
int verMovY(char tecla, int y, int x){
	
	switch(tecla){
		case 'w':{
			if(mapa[y-1][x-60] == 1 || mapa[y-1][x-60] == 0){
				y--;
				return y;
			}else{return y;}
			break;
		}
		case 's':{
			if(mapa[y+1][x-60] == 1 || mapa[y+1][x-60] == 0){
				y++;
				return y;
			}else{return y;}
			break;
		}
		default:{
			return y;
			break;
		}

	}

}
//para terminar essa função devo aprender mais sobre ponteiros
void movingPacman(){
}
