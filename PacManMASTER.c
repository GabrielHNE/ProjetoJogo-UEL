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
	int kill;	//boolean
	char charact;
	char mov;
}Ghost;
typedef struct Pacman{
	int posX;
	int	posY;
	int oldX;
	int oldY;
	int Life;
	char charact;
}Pacman;

void delay(unsigned int milliseconds);
void gotoxy(int x, int y);

void inicio();	
void showLetreiro();
void animacao();
void inf();		
void screenPoint();

void start();
char screenFinal(int* score);
void win(int mapa[][30], Pacman *pm);
void pontuacao(int Ox,int Oy,int *score,int mapa[][30], Pacman* pm);
void auxPrintPac(int Ox, int Oy, int mapa[][30], char perso);

void mapaDraw(int mapa[][30]);
void printMapa(int map[][30],int i,int j);					
void printPac(int Nx, int Ny, int Ox, int Oy, char charc, int mapa[][30]);
void movPac( Pacman* pm, char* tecla, char* keepMove, int mapa[][30]);
int verMovX(char** tecla,char** keepMove,int x, int y,int mapa[][30]);
int verMovY(char** tecla,char** keepMove, int y, int x,int mapa[][30]);
int calculadist(int PMx, int PMy, int GHx, int GHy);
void movGhost(Ghost* ghost, Pacman* pacman, int mapa[][30]);	
void teleport(Pacman **pm);
void teleportGhost(Ghost** ghost);
void checaFim(Pacman* pm, Ghost* ghost, int* qtd_comeu, int* score);
void perseguePac(Ghost** ghost, Pacman** pacman, int mapa[][30]);
void fogePac(Ghost** ghost, Pacman** pacman, int mapa[][30]);

void timer(int tInicio, int tFim);

void movGhost2(Ghost* ghost, Pacman* pacman, int mapa[][30]);
void randomMov(Ghost** ghost, int mapa[][30]);

void copiaMapa(int mapaO[][30], int mapa[][30]);

int main(int argc, char** argv){
	int mapa[30][30];
	int mapaO[30][30] = {
						{4,9,9,9,9,9,9,9,9,9,9,9,9,9,5,4,9,9,9,9,9,9,9,9,9,9,9,9,9,5},//0
						{8,1,1,1,1,1,1,1,1,1,1,1,1,1,8,8,1,1,1,1,1,1,1,1,1,1,1,1,1,8},//1
						{8,1,4,9,5,1,4,9,9,9,9,9,5,1,8,8,1,4,9,9,9,9,9,5,1,4,9,5,1,8},//2
						{8,2,8,0,8,1,8,0,0,0,0,0,8,1,8,8,1,8,0,0,0,0,0,8,1,8,0,8,2,8},//3
						{8,1,6,9,7,1,6,9,9,9,9,9,7,1,6,7,1,6,9,9,9,9,9,7,1,6,9,7,1,8},//4
						{8,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,8},//5
						{8,1,4,9,5,1,4,5,1,9,9,9,9,9,5,4,9,9,9,9,9,1,4,5,1,4,9,5,1,8},//6
						{8,1,6,9,7,1,8,8,1,1,1,1,1,1,8,8,1,1,1,1,1,1,8,8,1,6,9,7,1,8},//7
						{8,1,1,1,1,1,8,8,9,9,9,9,9,1,6,7,1,9,9,9,9,9,5,8,1,1,1,1,1,8},//8
						{6,9,9,9,5,1,8,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,8,1,8,9,9,9,9},//9
						{0,0,0,0,8,1,8,8,0,4,9,9,5,0,0,0,0,4,9,9,5,0,8,8,1,8,0,0,0,0},//10
						{0,0,0,0,8,1,8,8,0,8,0,0,8,0,0,0,0,8,0,0,8,0,8,8,1,8,0,0,0,0},//11
						{0,0,0,0,8,1,8,8,0,8,0,0,8,0,0,0,0,8,0,0,8,0,8,8,1,8,0,0,0,0},//12
						{0,0,0,0,8,1,8,8,0,8,0,0,8,0,0,0,0,8,0,0,8,0,8,8,1,8,0,0,0,0},//13
						{9,9,9,9,7,1,6,7,0,8,0,0,8,0,0,0,0,8,0,0,8,0,6,7,1,6,9,9,9,9},//14
						{3,1,1,1,1,1,0,0,0,8,0,0,6,9,9,9,9,7,0,0,8,0,0,0,1,1,1,1,1,3},//15
						{9,9,9,9,5,1,4,5,0,8,0,0,0,0,0,0,0,0,0,0,8,0,4,5,1,4,9,9,9,9},//16
						{0,0,0,0,8,1,8,8,0,6,9,9,9,9,9,9,9,9,9,9,7,0,8,8,1,8,0,0,0,0},//17
						{0,0,0,0,8,1,8,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,8,1,8,0,0,0,0},//18
						{0,0,0,0,8,1,8,8,0,4,9,9,9,9,9,9,9,9,9,9,5,0,8,8,1,8,0,0,0,0},//19
						{4,9,9,9,7,1,6,7,1,6,9,9,9,9,5,4,9,9,9,9,7,1,6,7,1,6,9,9,9,5},//20
						{8,1,1,1,1,1,1,1,1,1,1,1,1,1,8,8,1,1,1,1,1,1,1,1,1,1,1,1,1,8},//21
						{8,1,9,9,5,1,9,9,9,9,9,9,9,1,6,7,1,9,9,9,9,9,9,9,1,4,9,9,1,8},//22
						{8,2,1,1,8,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,8,1,1,2,8},//23
						{8,9,9,1,8,1,4,5,1,9,9,9,9,9,5,4,9,9,9,9,9,1,4,5,1,8,1,9,9,8},//24
						{8,1,1,1,1,1,8,8,1,1,1,1,1,1,8,8,1,1,1,1,1,1,8,8,1,1,1,1,1,8},//25
						{8,1,4,9,9,9,7,6,9,9,9,9,5,1,8,8,1,4,9,9,9,9,7,6,9,9,9,5,1,8},//26
						{8,1,6,9,9,9,9,9,9,9,9,9,7,1,6,7,1,6,9,9,9,9,9,9,9,9,9,7,1,8},//27
						{8,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,8},//28					
						{6,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,7}};//29
						
	int gameOver=0;
	int score = 0; 
	char tecla = 's', oldTecla='d', keepMove;
	int tInicio, tFim, tempoComer = 10000, qtd_comeu = 1, especial = 0;

	Pacman pm;
	Ghost ghost, ghost2, ghost3, ghost4;

	srand(time(0));
	system("MODE con cols=150 lines=30"); //define o tamanho da tela !!! para centralizar faz (150 - (largura do mapa))/2;
	inicio();
	inf();
	delay(5000);
	start(&pm, &ghost, &ghost2, &ghost3, &ghost4, mapa, mapaO);

	while(!gameOver){
		while(pm.Life >0){
			if(kbhit()){
				keepMove = tecla;
				tecla = getch();
			}
			
			if(!especial){
				movPac(&pm, &tecla, &keepMove, mapa);
				movGhost(&ghost, &pm, mapa);
				movGhost2(&ghost2, &pm, mapa);
				movGhost2(&ghost3, &pm, mapa);
				movGhost2(&ghost4, &pm, mapa);
			} else{
				movGhost(&ghost, &pm, mapa);
				movGhost2(&ghost2, &pm, mapa);
				movGhost2(&ghost3, &pm, mapa);
				movGhost2(&ghost4, &pm, mapa);
				movPac(&pm, &tecla, &keepMove, mapa);
			}

			if(mapa[pm.posY][pm.posX-60] == 2){
				especial = 1;
				tInicio = clock();
				//ghost
				ghost.charact = 'm';
				ghost.kill = 1;
				//ghost2
				ghost2.charact = 'm';
				ghost2.kill = 1;
				//ghost3
				ghost3.charact = 'm';
				ghost3.kill = 1;
				//ghost4
				ghost4.charact = 'm';
				ghost4.kill = 1;

			}

			checaFim(&pm,&ghost, &qtd_comeu, &score);
			checaFim(&pm,&ghost2, &qtd_comeu, &score);
			checaFim(&pm,&ghost3, &qtd_comeu, &score);
			checaFim(&pm,&ghost4, &qtd_comeu, &score);
			tFim = clock();

			if(especial){
				timer(tInicio, tFim);
			}

			if((tFim - tInicio)/(CLOCKS_PER_SEC/1000) >= tempoComer){
				especial = 0;
				//ghost
				ghost.kill = 0;
				ghost.charact = 'w';
				//ghost2
				ghost2.kill = 0;
				ghost2.charact = 'w';
				//ghost3
				ghost3.kill = 0;
				ghost3.charact = 'w';
				//ghost4
				ghost4.kill = 0;
				ghost4.charact = 'w';
				
				qtd_comeu = 1;
			} 

			pontuacao(pm.oldX, pm.oldY, &score, mapa, &pm);
			win(mapa,&pm);

			if(!especial){
				printPac(pm.posX, pm.posY, pm.oldX, pm.oldY, pm.charact, mapa);
				printPac(ghost.posX, ghost.posY, ghost.oldX, ghost.oldY, ghost.charact, mapa);
				printPac(ghost2.posX, ghost2.posY, ghost2.oldX, ghost2.oldY, ghost2.charact, mapa);
				printPac(ghost3.posX, ghost3.posY, ghost3.oldX, ghost3.oldY, ghost3.charact, mapa);
				printPac(ghost4.posX, ghost4.posY, ghost4.oldX, ghost4.oldY, ghost4.charact, mapa);
			} else{
				printPac(ghost.posX, ghost.posY, ghost.oldX, ghost.oldY, ghost.charact, mapa);
				printPac(ghost2.posX, ghost2.posY, ghost2.oldX, ghost2.oldY, ghost2.charact, mapa);
				printPac(ghost3.posX, ghost3.posY, ghost3.oldX, ghost3.oldY, ghost3.charact, mapa);
				printPac(ghost4.posX, ghost4.posY, ghost4.oldX, ghost4.oldY, ghost4.charact, mapa);
				printPac(pm.posX, pm.posY, pm.oldX, pm.oldY, pm.charact, mapa);
			}
			delay(200);
		}

		system("cls"); 

		if(screenFinal(&score) =='s'){
			start(&pm, &ghost, &ghost2, &ghost3, &ghost4, mapa, mapaO);
			//talvez salvar score em file
			score = 0;
		} else if(screenFinal(&score) == 'n'){
			gameOver = 1;
		}
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
			gotoxy(102,13);
			printf("|");
		}
		gotoxy(71+i,12);
		printf("-");
		gotoxy(71+i,14);
		printf("-");
	}

	while(mStart!= 32){
		for(i=0;i<27;i++){
			if(kbhit()){					//sempre verifica se alguma tecla foi pressionada, caso sim verifica se foi SPACE e finaliza!
				mStart = getch();
			break;
		 	}								//faz a animacao

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
	gotoxy(83,5);
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
	printf("%c Nao deixe os fantasmas te pegarem",175);
	gotoxy(60,13);
	printf("%c Voce so tem 3 vidas",175);
	gotoxy(60,14);
	printf("%c Cerejas dao ponos extras (100pts)",175);
	gotoxy(83,15);
	printf("BOMMMM JOOOGO!");

}
void start(Pacman* pm, Ghost* ghost,Ghost* ghost2, Ghost* ghost3, Ghost* ghost4, int mapa[][30], int mapaO[][30]){

	copiaMapa(mapaO, mapa);
	system("cls");  
	delay(1000);
	mapaDraw(mapa);
	screenPoint();

	
	//configurando o pacman
	(*pm).Life = 3;
	(*pm).charact = 'c';
	(*pm).posX = 74; 						//distancia da parede (largura)
	(*pm).posY	= 23; 						//altura
	gotoxy((*pm).posX,(*pm).posY);		// coloca o pacman na posicao inicial

	//ghost
	(*ghost).charact = 'w';
	(*ghost).kill = 0;
	(*ghost).posX = 74;
    (*ghost).posY = 13;
    gotoxy((*ghost).posX, (*ghost).posY);
    gotoxy(0,0);

	//ghost2
	(*ghost2).charact = 'w';
	(*ghost2).kill = 0;
	(*ghost2).posX = 74;
    (*ghost2).posY = 12;
	(*ghost2).mov  = 'w';
    gotoxy((*ghost2).posX, (*ghost2).posY);
    gotoxy(0,0);

	//ghost3
	(*ghost3).charact = 'w';
	(*ghost3).kill = 0;
	(*ghost3).posX = 74;
    (*ghost3).posY = 11;
	(*ghost3).mov  = 'w';
    gotoxy((*ghost3).posX, (*ghost3).posY);
    gotoxy(0,0);

	//ghost4
	(*ghost4).charact = 'w';
	(*ghost4).kill = 0;
	(*ghost4).posX = 74;
    (*ghost4).posY = 10;
	(*ghost4).mov  = 'w';
    gotoxy((*ghost4).posX, (*ghost4).posY);
    gotoxy(0,0);
}
char screenFinal(int* score){
	char f;

	gotoxy(70,10);
	//printa parte superior
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",201,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,187);
	gotoxy(70,11);
	printf("%c       SCORE:       %c",186,186);
	gotoxy(70,12);
	printf("%c                    %c",186,186);
	gotoxy(70,13);
	printf("%c                    %c",186,186);
	gotoxy(70,14);
	printf("%c   jogar novamente? %c",186,186);
	gotoxy(70,15);
	printf("%c                    %c",186,186);
	gotoxy(70,16);
	printf("%c                    %c",186,186);
	gotoxy(70,17);
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,188);

	gotoxy(80,12);
	printf("%d", *score);
	gotoxy(0,0);

	while(f != 's'|| f != 'n'){
		if(kbhit()){
			f = getch();
			if(f=='s')
				return f;
		} else if(f == 'n'){
				return f;
		}
	} 
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
		case 2:{
			gotoxy(60+j,i);
			printf("O");
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
	if(perso == 'w'|| perso == 'm'){	
		printMapa(mapa, Oy, (Ox-60));	
		gotoxy(0,0);		
	} else{
		gotoxy(Ox,Oy);
		printf(" ");
		gotoxy(0,0);
	}
}
void movPac(Pacman* pm, char* tecla, char* keepMove, int mapa[][30]){

	if((*pm).oldX != (*pm).posX ){
		(*pm).oldX = (*pm).posX;
	}
	if((*pm).oldY != (*pm).posY)    {
		(*pm).oldY = (*pm).posY;
	}

	(*pm).posX = verMovX(&tecla, &keepMove, (*pm).oldX, (*pm).oldY, mapa);
	(*pm).posY = verMovY(&tecla, &keepMove, (*pm).oldY, (*pm).oldX, mapa);

	teleport(&pm);
}
int verMovX(char** tecla, char** keepMove, int x,int y,int mapa[][30]){
	switch(**tecla){
		case 'a':{
			if(mapa[y][x-61] <=3){
				x--;
				**keepMove = **tecla;
				return x;
			} else{
				**tecla = **keepMove;
				return x;}
			break;
		}
		case 'd':{
			if(mapa[y][x-59] <=3){
				x++;
				**keepMove = **tecla;				
				return x;
			} else {
				**tecla = **keepMove;
				return x;}
			break;
		}
		default:{
			return x;
			break;
		}
	}
}
int verMovY(char** tecla, char** keepMove, int y, int x,int mapa[][30]){
	//pointeiro do pointeiro hehe
	switch(**tecla){
		case 'w':{
			if(mapa[y-1][x-60] <=3){
				y--;
				**keepMove = **tecla;
				return y;
			}else{
				**tecla = **keepMove;
				return y;}
			break;
		}
		case 's':{
			if(mapa[y+1][x-60]<=3){
				y++;
				**keepMove = **tecla;				
				return y;
			}else{
				**tecla = **keepMove;
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
 int i,j=0,x,y;
  
  for(i=0;i<3-j;i++){
	   if(i==0){
         x=35;
         y=3;
	    }
	   else if(i==1){
	   	 x=104;
	   	 y=3;
	    }
	   else if(i==2){
	   	 if(j==0){
	   	 x=35;
	   	 y=9;
		   }
	    }
	 gotoxy(x,y);
	 printf("%c%c%c%c%c%c%c%c%c%c%c",201,205,205,205,205,205,205,205,205,205,187);
	 gotoxy(x,y+1);
	 printf("%c",186);
	 if(i==0){
	 	gotoxy(x+3,y+1);
	    printf("SCORE");
	 }
	 else if(i==1){
	 	gotoxy(x+3,y+1);
	    printf("LIFES");
	 }
	 else if(i==2){
	 	gotoxy(x+3,y+1);
	    printf("TIMER");
	 }
	 gotoxy(x+10,y+1);
	 printf("%c",186);
	 gotoxy(x,y+2);
	 printf("%c",186);
	 gotoxy(x+10,y+2);
	 printf("%c",186);
	 gotoxy(x,y+3);
	 printf("%c%c%c%c%c%c%c%c%c%c%c",200,205,205,205,205,205,205,205,205,205,188);
	 gotoxy(0,0);
	}
}
void pontuacao(int Ox, int Oy, int *score, int mapa[][30], Pacman* pm){
	switch(mapa[Oy][Ox-60]){
		case 1:{
			(*score)++;
			mapa[Oy][Ox-60] = 0;
			break;
		}
		case 2:{
			(*score)+=10;
			mapa[Oy][Ox-60] = 0;
			break;
		}
	}
	gotoxy(37,5);
	printf("  %d",(*score));
	gotoxy(106,5);
	printf("  %d",(*pm).Life);
	gotoxy(0,0);
}
int calculadist(int PMx, int PMy, int GHx, int GHy){
	return sqrt(pow(GHx-PMx,2) + pow(GHy-PMy,2));
}
void movGhost(Ghost* ghost, Pacman* pacman, int mapa[][30]){

	if((*ghost).oldX != (*ghost).posX){
		(*ghost).oldX = (*ghost).posX;
	}
	if((*ghost).oldY != (*ghost).posY){
		(*ghost).oldY = (*ghost).posY;
	}
 
  	if((*ghost).kill == 0){
		if(rand()%100 < 70){
			perseguePac(&ghost, &pacman, mapa);
		} 
	} else{
		if(rand()%100 < 50){
			fogePac(&ghost, &pacman, mapa);
		} 
	}

	teleportGhost(&ghost);
}
void movGhost2(Ghost* ghost, Pacman* pacman, int mapa[][30]){

	int dist_menor = calculadist((*ghost).posX,(*ghost).posY,(*pacman).posX,(*pacman).posY);
	if((*ghost).oldX != (*ghost).posX){
		(*ghost).oldX = (*ghost).posX;
	}
	if((*ghost).oldY != (*ghost).posY){
		(*ghost).oldY = (*ghost).posY;
	}

	if(dist_menor < 6){

		if((*ghost).kill == 0){
		if(rand()%100 < 80){
			perseguePac(&ghost, &pacman, mapa);
		} 
	} else {
		if(rand()%100 < 80){
			fogePac(&ghost, &pacman, mapa);
			} 
		}
	} else {
		randomMov(&ghost, mapa);
	}
	
	teleportGhost(&ghost);
}
void teleport(Pacman **pm){
	if((**pm).posX == 60){
		(**pm).posX = 89; 
	} else if((**pm).posX == 89){
		(**pm).posX = 60;
	}	
}
void teleportGhost(Ghost** ghost){
	if((**ghost).posX == 60){
			(**ghost).posX = 89;
	} else if((**ghost).posX == 89){
		(**ghost).posX = 60;
	}
}
void checaFim(Pacman* pm, Ghost* ghost, int* qtd_comeu, int* score){

	if((*pm).posX == (*ghost).posX && (*pm).posY == (*ghost).posY){
		switch((*ghost).kill){
			case 0:{
				(*pm).Life --;
				(*pm).posX=74;
				(*pm).posY=23;
				delay(1000);
				break;
			}
			case 1:{
				//respawn no ghost
				(*ghost).posX = 74;
				(*ghost).posY = 13;
				(*ghost).kill = 0;
				(*ghost).charact = 'w';

				//showScreen
				gotoxy(75,33);
				printf("+%d", 100*(*qtd_comeu));
				delay(250);
				gotoxy(75,33);
				printf("              ");
				
				//logica
				(*score) +=100*(*qtd_comeu);
				(*qtd_comeu)++;
				break;
			}
		}
	}	
}
void perseguePac(Ghost** ghost, Pacman** pacman, int mapa[][30]){
	int GHx_menor = (**ghost).posX;
	int GHy_menor = (**ghost).posY;
	int dist_menor;

	dist_menor = calculadist((**ghost).posX,(**ghost).posY,(**pacman).posX,(**pacman).posY);

	if((mapa[(**ghost).posY][(**ghost).posX  - 61] <=3) && (calculadist(((**ghost).posX-1),(**ghost).posY,(**pacman).posX,(**pacman).posY) < dist_menor)){
		GHx_menor = ((**ghost).posX - 1);
		GHy_menor = (**ghost).posY;
		}	
		else if((mapa[(**ghost).posY][((**ghost).posX-59)] <= 3 ) && (calculadist(((**ghost).posX +1),(**ghost).posY,(**pacman).posX,(**pacman).posY) < dist_menor))
		{
		GHx_menor = ((**ghost).posX) + 1;
		GHy_menor = (**ghost).posY;
		}
		else if((mapa[(**ghost).posY-1][((**ghost).posX - 60)] <=3 ) && (calculadist((**ghost).posX ,((**ghost).posY-1),(**pacman).posX,(**pacman).posY) < dist_menor))
		{
		GHx_menor = (**ghost).posX ;
		GHy_menor = ((**ghost).posY - 1);
		}
		else if((mapa[(**ghost).posY + 1][((**ghost).posX-60)] <=3) && (calculadist((**ghost).posX ,((**ghost).posY+1),(**pacman).posX,(**pacman).posY) < dist_menor))
		{
		GHx_menor = (**ghost).posX ;
		GHy_menor = ((**ghost).posY + 1);
		}
	

	if((**ghost).posX  == GHx_menor && ((**ghost).posY == GHy_menor)){
		if( pow( ((**ghost).posX -1) - (**pacman).posX ,2) < pow( ((**ghost).posX - (**pacman).posX) ,2)  && (mapa[(**ghost).posY][(**ghost).posX -61] <=3))
			GHx_menor = (**ghost).posX -1;
		else if( pow( ((**ghost).posX +1) - (**pacman).posX, 2) < pow( ((**ghost).posX - (**pacman).posX), 2) && (mapa[(**ghost).posY][(**ghost).posX -59] <=3))
			GHx_menor = (**ghost).posX +1;

		if( pow( ((**ghost).posY-1) - (**pacman).posY ,2) < pow( ((**ghost).posY - (**pacman).posY) , 2) && (mapa[(**ghost).posY-1][(**ghost).posX-60] <=3))
			GHy_menor = (**ghost).posY-1;
		else if( pow( ((**ghost).posY+1) - (**pacman).posY, 2) < pow( ((**ghost).posY - (**pacman).posY), 2) && (mapa[(**ghost).posY+1][(**ghost).posX-60] <=3))
			GHy_menor = (**ghost).posY+1;
	}

	(**ghost).posX  = GHx_menor;
	(**ghost).posY  = GHy_menor;

}
void fogePac(Ghost** ghost, Pacman** pacman, int mapa[][30]){
	int GHx_menor = (**ghost).posX;
	int GHy_menor = (**ghost).posY;
	int dist_menor;

	dist_menor = calculadist((**ghost).posX,(**ghost).posY,(**pacman).posX,(**pacman).posY);

	if((mapa[(**ghost).posY][(**ghost).posX  - 61] <=3) && (calculadist(((**ghost).posX-1),(**ghost).posY,(**pacman).posX,(**pacman).posY) > dist_menor)){
		GHx_menor = ((**ghost).posX - 1);
		GHy_menor = (**ghost).posY;
		}	
		else if((mapa[(**ghost).posY][((**ghost).posX-59)] <= 3 ) && (calculadist(((**ghost).posX +1),(**ghost).posY,(**pacman).posX,(**pacman).posY) > dist_menor))
		{
		GHx_menor = ((**ghost).posX) + 1;
		GHy_menor = (**ghost).posY;
		}
		else if((mapa[(**ghost).posY-1][((**ghost).posX - 60)] <=3 ) && (calculadist((**ghost).posX ,((**ghost).posY-1),(**pacman).posX,(**pacman).posY) > dist_menor))
		{
		GHx_menor = (**ghost).posX ;
		GHy_menor = ((**ghost).posY - 1);
		}
		else if((mapa[(**ghost).posY + 1][((**ghost).posX-60)] <=3) && (calculadist((**ghost).posX ,((**ghost).posY+1),(**pacman).posX,(**pacman).posY) > dist_menor))
		{
		GHx_menor = (**ghost).posX ;
		GHy_menor = ((**ghost).posY + 1);
		}
	

	if((**ghost).posX  == GHx_menor && ((**ghost).posY == GHy_menor)){
		if( pow( ((**ghost).posX -1) - (**pacman).posX ,2) > pow( ((**ghost).posX - (**pacman).posX) ,2)  && (mapa[(**ghost).posY][(**ghost).posX -61] <=3))
			GHx_menor = (**ghost).posX -1;
		else if( pow( ((**ghost).posX +1) - (**pacman).posX, 2) > pow( ((**ghost).posX - (**pacman).posX), 2) && (mapa[(**ghost).posY][(**ghost).posX -59] <=3))
			GHx_menor = (**ghost).posX +1;

		if( pow( ((**ghost).posY-1) - (**pacman).posY ,2) > pow( ((**ghost).posY - (**pacman).posY) , 2) && (mapa[(**ghost).posY-1][(**ghost).posX-60] <=3))
			GHy_menor = (**ghost).posY-1;
		else if( pow( ((**ghost).posY+1) - (**pacman).posY, 2) > pow( ((**ghost).posY - (**pacman).posY), 2) && (mapa[(**ghost).posY+1][(**ghost).posX-60] <=3))
			GHy_menor = (**ghost).posY+1;
	}

	(**ghost).posX  = GHx_menor;
	(**ghost).posY  = GHy_menor;
}
void randomMov(Ghost** ghost, int mapa[][30]){
	
	switch((**ghost).mov){
		case 'w':{
			if(mapa[(**ghost).posY][(**ghost).posX  - 61] <=3){
				(**ghost).posX --;
			} else{
				if(rand()%100 < 40){
					(**ghost).mov = 'a';
					randomMov(ghost, mapa);
				}else if(rand()%100 < 80){
					(**ghost).mov = 'd';
					randomMov(ghost, mapa);
				}else{
					(**ghost).mov = 's';
					randomMov(ghost, mapa);
				}
			}
			break;
		}
		case 'a':{
			if(mapa[(**ghost).posY-1][(**ghost).posX  - 60] <=3){
				(**ghost).posY --;
			} else{
				if(rand()%100 < 40){
					(**ghost).mov = 'w';
					randomMov(ghost, mapa);
				}else if(rand()%100 < 80){
					(**ghost).mov = 's';
					randomMov(ghost, mapa);
				}else{
					(**ghost).mov = 'd';
					randomMov(ghost, mapa);
				}
			}
			break;
		}		
		case 's':{
			if(mapa[(**ghost).posY][(**ghost).posX  - 59] <=3){
				(**ghost).posX ++;
			} else{
				if(rand()%100 < 40){
					(**ghost).mov = 'a';
					randomMov(ghost, mapa);
				}else if(rand()%100 < 80){
					(**ghost).mov = 'd';
					randomMov(ghost, mapa);
				}else{
					(**ghost).mov = 'w';
					randomMov(ghost, mapa);
				}
			}
			break;
		}
		case 'd':{
			if(mapa[(**ghost).posY+1][(**ghost).posX  - 60] <=3){
				(**ghost).posY ++;
			} else{
				if(rand()%100 < 40){
					(**ghost).mov = 'w';
					randomMov(ghost, mapa);
				}else if(rand()%100 < 80){
					(**ghost).mov = 's';
					randomMov(ghost, mapa);
				}else{
					(**ghost).mov = 'a';
					randomMov(ghost, mapa);
				}
			}
			break;
		}
	}

} 
void timer(int tInicio, int tFim){

	int i =10 - (tFim - tInicio)/(CLOCKS_PER_SEC  );
	gotoxy(38,11);
	i != 0? printf(" %d ", 10 - (tFim - tInicio)/(CLOCKS_PER_SEC  )): printf("   ");
	gotoxy(0,0);

}  
void copiaMapa(int mapaO[30][30], int mapa[30][30]){
	int i,j;

	for(i=0;i<30;i++){
		for(j=0;j<30;j++){
			mapa[i][j]=mapaO[i][j];
		}
	}
}
void win(int mapa[][30], Pacman *pm){
	int i,j, soma=0;

	for(i=1;i<29;i++){
		for(j=1;j<29;j++){
			if(mapa[i][j] == 1 ||mapa[i][j] == 2){
				soma ++;
			}
		}
	}

	if(soma == 0){
		(*pm).Life = -1;		
	}
}