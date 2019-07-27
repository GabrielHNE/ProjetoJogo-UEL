#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h> 		//contem time(), que retorna o tempo atual em ms
#include <windows.h>	//contem funcoes necessarias para a funcao gotoxy;

#define WIDTH 150
#define WEIGTH 100

int mapa[30][30] =     {{8,6,6,6,6,6,6,6,6,6,6,6,6,6,7,8,6,6,6,6,6,6,6,6,6,6,6,6,6,7},
						{5,1,1,1,1,1,1,1,1,1,1,1,1,1,5,5,1,1,1,1,1,1,1,1,1,1,1,1,1,5},
						{5,1,8,6,7,1,8,6,6,6,6,6,7,1,5,5,1,8,6,6,6,6,6,7,1,8,6,7,1,5},
						{5,1,5,0,5,1,5,0,0,0,0,0,5,1,5,5,1,5,0,0,0,0,0,5,1,5,0,5,1,5},
						{5,1,4,6,9,1,4,6,6,6,6,6,9,1,4,9,1,4,6,6,6,6,6,9,1,4,6,9,1,5},
						{5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5},
						{5,1,8,6,7,1,8,7,1,6,6,6,6,6,7,8,6,6,6,6,6,1,8,7,1,8,6,7,1,5},
						{5,1,4,6,9,1,5,5,1,1,1,1,1,1,5,5,1,1,1,1,1,1,5,5,1,4,6,9,1,5},
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
	int oldX;
	int oldY;
	int Life;
}Pacman;

void delay(unsigned int milliseconds);			//funcao que permite criar delays para debugging
void gotoxy(int x, int y);						//funcao q coloca o curso na posicao desejada
void inicio();									//coloca letreiros e pede para iniciar o jogo
void showLetreiro();							//Letreiro chamado por inicio
void animacao();								//animacao chamado por inicio
void inf();										//controles e regras
void mapaDraw(int mapa[30][30]);								//Possui o mapa e chama a funcao printMapa
void printMapa(int map[30][30],int i, int j);	//Funcao chamada por mapaDraw() para printar os pontos do mapa
void movingPacman();							//incompleta, mas devera incluir as funções identadas;						
	void printPac(int x, int y);
	int verMovX(char* tecla, char* keepMove, int x, int y);
	int verMovY(char* tecla, char* keepMove, int y, int x);
		
int main(int argc, char** argv){
	int gameOver=0;
	int i;
	char tecla='a', keepMove;
	Pacman pacman;

	//define o tamanho da tela !!! para centralizar faz (150 - (largura do mapa))/2;
	system("MODE con cols=150 lines=100"); 
	inicio();
	inf();
	delay(5000);
	system("cls");
	//codigo do jogo em si
	mapaDraw(mapa);
	pacman.posX = 74; 						//distancia da parede (largura)
	pacman.posY	= 23; 						//altura
	gotoxy(pacman.posX,pacman.posY);		// coloca o pacman na posicao inicial
	
	while(!gameOver){
		//tentar transformar em funcao (movingPacman)
		pacman.posY = verMovY(&tecla, &keepMove, pacman.posY, pacman.posX);
		pacman.posX = verMovX(&tecla, &keepMove, pacman.posX,pacman.posY);
		if(kbhit()){
		    keepMove = tecla;
			tecla = getch();
			pacman.posY = verMovY(&tecla, &keepMove, pacman.posY, pacman.posX);
			pacman.posX = verMovX(&tecla, &keepMove, pacman.posX,pacman.posY);
		}
		delay(100);		
		printPac(pacman.posX,pacman.posY);
		delay(100);
	}
	return 0;
}
//funcao que permite criar delays para debugging e controle de movimento
void delay(unsigned int milliseconds){	
    clock_t start = clock();
    while((clock() - start) * 1000 / CLOCKS_PER_SEC < milliseconds){}
}
//funcao q coloca o curso na posi��o desejada
void gotoxy(int x, int y){
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void inicio(){
	int start;
	showLetreiro();
	delay(2000);
	animacao();
	system("cls");
}
void inf(){
	gotoxy(60,5);
	printf("Controles do jogo!");
	gotoxy(60,6);
	printf("W -> Cima");
	gotoxy(60,7);
	printf("S -> Baixo");
	gotoxy(60,8);
	printf("A -> Esquerda");
	gotoxy(60,9);
	printf("D -> Direita");
	gotoxy(60,10);
	printf("Regras!");
	gotoxy(60,11);
	printf("%c Para ganhar coma todos os pontos no menor tempo possivel", 175);
	gotoxy(60,12);
	printf("%cNao deixe os fantasmas te pegarem",175);
	gotoxy(60,13);
	printf("%c Voce so tem 3 vidas",175);
	gotoxy(60,14);
	printf("%cCerejas dao ponos extras (100pts)",175);
	gotoxy(83,15);
	printf("BOMMMM JOOOGO!");

}
void showLetreiro(){
	gotoxy(60,0);
	printf(" _____   _____               _   _   _____   _     _     \n");
    gotoxy(60,1);
	printf("|  _  | |  _  |   _____     | | | | |  _  | | \\   | |    \n");
   	gotoxy(60,2);	
	printf("| | | | | | | | /       \\   | | | | | | | | |  \\  | | \n");
    gotoxy(60,3);	
	printf("| | | | | | |  /      X  \\  | \\ / | | | | | |   \\ | | \n");
    gotoxy(60,4);	
	printf("| | | | | | | /           \\ |     | | | | | |    \\| | \n");
    gotoxy(60,5);	
	printf("| |_| | | |_||           /  | |v| | | |_| | | |\\    |\n");
    gotoxy(60,6);	
	printf("|  ___/ |    |         <    | | | | |     | | | \\   |\n");
    gotoxy(60,7);	
	printf("|  |    |  _ |           \\  | | | | |  _  | | |  \\  | \n");
    gotoxy(60,8);
    printf("|  |    | | | \\           / | | | | | | | | | |   | | \n");
    gotoxy(60,9);
    printf("|  |    | | | |\\         /  | | | | | | | | | |   | |\n");
    gotoxy(60,10);
    printf("|__|    |_| |_| \\ _____ /   |_| |_| |_| |_| |_|   |_|        \n");
}
void animacao(){
	char mStart;
	int i;
	gotoxy(74,11);
	printf("Pressione SPACE para comecar");
	
	for(i=0;i<31;i++){						//cria a caixa de animacao
		if(i==0){
			gotoxy(71,13);
			printf("|");
			gotoxy(104,13);
			printf("|");
		}
		gotoxy(71+i,12);
		printf("-");
		gotoxy(71+i,14);
		printf("-");
	}

	while(mStart!= 32){
		for(i=0;i<29;i++){
			if(kbhit()){					//sempre verifica se alguma tecla foi pressionada, caso sim verifica se foi SPACE e finaliza!
				mStart = getch();
			break;
		 	}								//faz a anima��o
			gotoxy(75+i,13);
			printf("C");
			gotoxy(0,0);
			delay(60);
			gotoxy(75+i,13);
			printf(" ");
			gotoxy(0,0);
			delay(100);
		}
		gotoxy(0,0);
	}
}
//Desenho do mapa e for que chama a funcao para printar o mapa na tela
void mapaDraw(int mapa[30][30]){
	int i,j;
	//desenho do mapa;	
	for(i=0;i<30;i++){
		for(j=0;j<30;j++){
			printMapa(mapa,i,j);
		}
	}
}
//funcao que printa todo o mapa na tela;
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
	gotoxy(0,0);
	delay(60);
	gotoxy(x,y);
	printf(" ");
	gotoxy(0,0);
}
int verMovX(char* tecla, char* keepMove, int x,int y){
	switch(*tecla){
		case 'a':{
			if(mapa[y][x-61] == 1 || mapa[y][x-61] == 0){
				x--;
				return x;
			} else {
				*tecla =*keepMove;
				return x;}
			break;}
		case 'd':{
			if(mapa[y][x-59] == 1 || mapa[y][x-59] == 0){
				x++;
				return x;
			} else {
				*tecla =*keepMove;
				return x;}
			break;}
		default:{
			return x;
			break;}
	}
}
int verMovY(char* tecla, char* keepMove,  int y, int x){
	
	switch(*tecla){
		case 'w':{
			if(mapa[y-1][x-60] == 1 || mapa[y-1][x-60] == 0){
				y--;
				return y;
			} else {
				*tecla =* keepMove;
				return y;}
			break;}
		case 's':{
			if(mapa[y+1][x-60] == 1 || mapa[y+1][x-60] == 0){
				y++;
				return y;
			} else {
				*tecla =* keepMove;
				return y;}
			break;}
		default:{
			return y;
			break;}
	}
}
//para terminar essa função devo aprender mais sobre ponteiros
void movingPacman(){
}
