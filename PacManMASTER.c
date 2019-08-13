#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h> 		//contem time(), que retorna o tempo atual em ms
#include <windows.h>	//contem funcoes necessarias para a funcao gotoxy;
#include <math.h>

typedef struct Ghost{
	int posX;
	int	posY;
	int oldX;
	int oldY;
	int Life;	//boolean
	char charact;
}Ghost;
typedef struct Pacman{
	int posX;
	int	posY;
	int oldX;
	int oldY;
	int Life;
	char charact;
}Pacman;

void inicio();	
void showLetreiro();
void animacao();
void inf();		

void screenPoint();
void pontuacao(int Ox,int Oy,int *score,int mapa[][30]);
void auxPrintPac(int Ox, int Oy, int mapa[][30], char perso);
void delay(unsigned int milliseconds);
void gotoxy(int x, int y);
void mapaDraw(int mapa[][30]);
void printMapa(int map[][30],int i,int j);					
void printPac(int Nx, int Ny, int Ox, int Oy, char charc, int mapa[][30]);
int verMovX(char* tecla,char* keepMove,int x, int y,int mapa[][30]);
int verMovY(char* tecla,char* keepMove, int y, int x,int mapa[][30]);
int calculadist(int PMx, int PMy, int GHx, int GHy);
void movGhost(Ghost* ghost, Pacman* pacman, int mapa[][30]);	

int main(int argc, char** argv){
	
	int mapa[30][30] = { {4,9,9,9,9,9,9,9,9,9,9,9,9,9,5,4,9,9,9,9,9,9,9,9,9,9,9,9,9,5},
						{8,1,1,1,1,1,1,1,1,1,1,1,1,1,8,8,1,1,1,1,1,1,1,1,1,1,1,1,1,8},
						{8,1,4,9,5,1,4,9,9,9,9,9,5,1,8,8,1,4,9,9,9,9,9,5,1,4,9,5,1,8},
						{8,1,8,0,8,1,8,0,0,0,0,0,8,1,8,8,1,8,0,0,0,0,0,8,1,8,0,8,1,8},
						{8,1,6,9,7,1,6,9,9,9,9,9,7,1,6,7,1,6,9,9,9,9,9,7,1,6,9,7,1,8},
						{8,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,8},
						{8,1,4,9,5,1,4,5,1,9,9,9,9,9,5,4,9,9,9,9,9,1,4,5,1,4,9,5,1,8},
						{8,1,6,9,7,1,8,8,1,1,1,1,1,1,8,8,1,1,1,1,1,1,8,8,1,6,9,7,1,8},
						{8,1,1,1,1,1,8,8,9,9,9,9,9,1,6,7,1,9,9,9,9,9,5,8,1,1,1,1,1,8},
						{6,9,9,9,5,1,8,8,1,1,1,1,1,1,1,1,1,1,1,1,1,1,8,8,1,8,9,9,9,9},
						{0,0,0,0,8,1,8,8,1,4,9,9,9,0,0,0,0,9,9,9,5,1,8,8,1,8,0,0,0,0},
						{0,0,0,0,8,1,8,8,1,8,0,0,0,0,0,0,0,0,0,0,8,1,8,8,1,8,0,0,0,0},
						{0,0,0,0,8,1,8,8,1,8,0,0,0,0,0,0,0,0,0,0,8,1,8,8,1,8,0,0,0,0},
						{0,0,0,0,8,1,8,8,1,8,0,0,0,0,0,0,0,0,0,0,8,1,8,8,1,8,0,0,0,0},
						{9,9,9,9,7,1,6,7,1,8,0,0,0,0,0,0,0,0,0,0,8,1,6,7,1,6,9,9,9,9},
						{1,1,1,1,1,1,1,1,1,8,0,0,0,0,0,0,0,0,0,0,8,1,1,1,1,1,1,1,1,1},
						{9,9,9,9,5,1,4,5,1,8,0,0,0,0,0,0,0,0,0,0,8,1,4,5,1,4,9,9,9,9},
						{0,0,0,0,8,1,8,8,1,6,9,9,9,9,9,9,9,9,9,9,7,1,8,8,1,8,0,0,0,0},
						{0,0,0,0,8,1,8,8,1,1,1,1,1,1,1,1,1,1,1,1,1,1,8,8,1,8,0,0,0,0},
						{0,0,0,0,8,1,8,8,1,4,9,9,9,9,9,9,9,9,9,9,5,1,8,8,1,8,0,0,0,0},
						{4,9,9,9,7,1,6,7,1,6,9,9,9,9,5,4,9,9,9,9,7,1,6,7,1,6,9,9,9,5},
						{8,1,1,1,1,1,1,1,1,1,1,1,1,1,8,8,1,1,1,1,1,1,1,1,1,1,1,1,1,8},
						{8,1,9,9,5,1,9,9,9,9,9,9,9,1,6,7,1,9,9,9,9,9,9,9,1,4,9,9,1,8},
						{8,1,1,1,8,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,8,1,1,1,8},
						{8,9,9,1,8,1,4,5,1,9,9,9,9,9,5,4,9,9,9,9,9,1,4,5,1,8,1,9,9,8},
						{8,1,1,1,1,1,8,8,1,1,1,1,1,1,8,8,1,1,1,1,1,1,8,8,1,1,1,1,1,8},
						{8,1,4,9,9,9,7,6,9,9,9,9,5,1,8,8,1,4,9,9,9,9,7,6,9,9,9,5,1,8},
						{8,1,6,9,9,9,9,9,9,9,9,9,7,1,6,7,1,6,9,9,9,9,9,9,9,9,9,7,1,8},
						{8,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,8},						
						{6,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,7}};
						
	int gameOver=0;
	int i, x, y;
	int score = 0; 
	char tecla = 's', oldTecla='d', keepMove; 

	system("MODE con cols=150 lines=30"); //define o tamanho da tela !!! para centralizar faz (150 - (largura do mapa))/2;
	inicio();
	inf();
	delay(5000);
	system("cls");  
	delay(1000);
	mapaDraw(mapa);
	screenPoint();

	//configurando o pacman
	Pacman pm;
	pm.charact = 'c';
	pm.posX = 74; 						//distancia da parede (largura)
	pm.posY	= 23; 						//altura
	gotoxy(pm.posX,pm.posY);		// coloca o pacman na posicao inicial
	//ghost
	Ghost ghost;
	ghost.charact = 'w';
	ghost.posX = 74;
    ghost.posY = 13;
    gotoxy(ghost.posX, ghost.posY);
    gotoxy(0,0);

	while(!gameOver)
	{
		if(kbhit()){
			keepMove = tecla;
			tecla = getch();
		}

		if(pm.oldX != pm.posX ){
			pm.oldX = pm.posX;
		}
		if(pm.oldY != pm.posY)    {
			pm.oldY = pm.posY;
		}

		if(ghost.oldX != ghost.posX)
		{
			ghost.oldX = ghost.posX;
		}
		if(ghost.oldY != ghost.posY)
		{
			ghost.oldY = ghost.posY;
		}

		pm.posY = verMovY(&tecla, &keepMove, pm.posY, pm.oldX, mapa);
		pm.posX = verMovX(&tecla, &keepMove, pm.posX, pm.oldY, mapa);
		movGhost(&ghost, &pm, mapa);
		pontuacao(pm.oldX, pm.oldY, &score, mapa);

		printPac(pm.posX, pm.posY, pm.oldX, pm.oldY, pm.charact, mapa);
		printPac(ghost.posX, ghost.posY, ghost.oldX, ghost.oldY, ghost.charact, mapa);

		if(pm.posX==ghost.posX && pm.posY==ghost.posY){
        	gameOver=1;
		}

		delay(200);
	}
	return 0;
}
void inicio(){
	int start;
	showLetreiro();
	delay(2000);
	animacao();
	system("cls");
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
		case 0:{
			//vazio
			gotoxy(60+j,i);
			printf(" ");
			break;
		}
		case 1:{
			//printa pontos
			gotoxy(60+j,i);
			printf("*");
			break;
		}
		case 4:{
			//canto superio esquerdo
			gotoxy(60+j,i);
			printf("%c", 201);
			break;
		}
		case 5:{
			//canto superior direito
			gotoxy(60+j,i);
			printf("%c", 187);
			break;
		}
		case 6:{
			//inferior direito
			gotoxy(60+j,i);
			printf("%c", 200);
			break;
		}
		case 7:{
			//inferio esquerdo
			gotoxy(60+j,i);
			printf("%c", 188);
			break;
		}
		case 8:{
			//vertical			
			gotoxy(60+j,i);
			printf("%c", 186);
			break;
		}
		case 9:{
			//horizontal
			gotoxy(60+j,i);
			printf("%c", 205);
			break;
		}
	}
}
void printPac(int Nx, int Ny, int Ox, int Oy, char charc, int mapa[][30]){
	if(Nx!=Ox || Ny!=Oy)
	{
	gotoxy(Nx,Ny);
	printf("%c", charc);
	gotoxy(0,0);
	auxPrintPac(Ox, Oy, mapa, charc);	
	}
}
void auxPrintPac(int Ox, int Oy, int mapa[][30], char perso){
	if(perso == 'w'){	
		printMapa(mapa, Oy, (Ox-60));	
		gotoxy(0,0);		
	} else{
		gotoxy(Ox,Oy);
		printf(" ");
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
void screenPoint(){
	gotoxy(35,3);
	printf(" _________");
	gotoxy(35,4);
	printf("|  SCORE  | ");
	gotoxy(45,5);
	printf("|");
	gotoxy(35,6);
	printf("|_________|");
	gotoxy(0,0);
}
void pontuacao(int Ox, int Oy, int *score, int mapa[][30]){
	if(mapa[Oy][Ox-60]==1){
		(*score)++;
		mapa[Oy][Ox-60] = 0;
	}
	gotoxy(35,5);
	printf("|   ""%d",(*score));
}
int calculadist(int PMx, int PMy, int GHx, int GHy){
	return sqrt(pow(GHx-PMx,2) + pow(GHy-PMy,2));
}
void movGhost(Ghost* ghost, Pacman* pacman, int mapa[][30]){
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
    else if((mapa[(*ghost).posY][((*ghost).posX-59)] == 1 || mapa[(*ghost).posY][((*ghost).posX - 59)] == 0) && (calculadist(((*ghost).posX +1),(*ghost).posY,(*pacman).posX,(*pacman).posY) < dist_menor))
  	{
      GHx_menor = ((*ghost).posX) + 1;
      GHy_menor = (*ghost).posY;
  	}
  	else if((mapa[(*ghost).posY-1][((*ghost).posX - 60)] == 1 || mapa[(*ghost).posY-1][((*ghost).posX-60)] == 0) && (calculadist((*ghost).posX ,((*ghost).posY-1),(*pacman).posX,(*pacman).posY) < dist_menor))
  	{
      GHx_menor = (*ghost).posX ;
      GHy_menor = ((*ghost).posY - 1);
  	}
  	else if((mapa[(*ghost).posY + 1][((*ghost).posX-60)] == 1 || mapa[(*ghost).posY + 1][((*ghost).posX-60)] == 0) && (calculadist((*ghost).posX ,((*ghost).posY+1),(*pacman).posX,(*pacman).posY) < dist_menor))
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
