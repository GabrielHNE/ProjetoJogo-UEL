#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h> 		//contem time(), que retorna o tempo atual em ms
#include <windows.h>	//contem funções necessarias para a funcao gotoxy;

void delay(unsigned int milliseconds){	//funcao que permite criar delays para debugging
    clock_t start = clock();
    while((clock() - start) * 1000 / CLOCKS_PER_SEC < milliseconds){}
}

void gotoxy(int x, int y)				//função q coloca o curso na posição desejada
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void inicio();			//coloca letreiros e pede para iniciar o jogo
void showLetreiro();	//Letreiro chamado por inicio
void animacao();		//animação chamado por inicio

int main(int argc, char** argv){
	char start;
	
	inicio();
	//codigo do jogo
	printf("\ndeu certo!");

	return 0;
}

void inicio(){
	int start;
	showLetreiro();
	delay(2000);
	animacao();
}
void showLetreiro(){
	printf("                                                                                                   ");
	printf(" _____   _____               _   _   _____   _     _     \n");
    printf("                                                                                                   ");	
	printf("|  _  | |  _  |   _____     | | | | |  _  | | \\   | |    \n");
    printf("                                                                                                   ");	
	printf("| | | | | | | | /       \\   | | | | | | | | |  \\  | | \n");
    printf("                                                                                                   ");	
	printf("| | | | | | |  /      X  \\  | \\ / | | | | | |   \\ | | \n");
    printf("                                                                                                   ");	
	printf("| | | | | | | /           \\ |     | | | | | |    \\| | \n");
    printf("                                                                                                   ");	
	printf("| |_| | | |_||           /  | |v| | | |_| | | |\\    |\n");
    printf("                                                                                                   ");	
	printf("|  ___/ |    |         <    | | | | |     | | | \\   |\n");
    printf("                                                                                                   ");	
	printf("|  |    |  _ |           \\  | | | | |  _  | | |  \\  | \n");
    printf("                                                                                                   ");
    printf("|  |    | | | \\           / | | | | | | | | | |   | | \n");
    printf("                                                                                                   ");
    printf("|  |    | | | |\\         /  | | | | | | | | | |   | |\n");
    printf("                                                                                                   ");
    printf("|__|    |_| |_| \\ _____ /   |_| |_| |_| |_| |_|   |_|        \n");
}
void animacao(){
	char mStart;
	int i;
	printf("                                                                                                   ");
	printf("           Pressione SPACE para comecar\n");
	printf("                                                                                                   ");
	
	for(i=0;i<32;i++){						//cria a caixa de animação
		if(i==0){
			gotoxy(108,13);
			printf("|");
			gotoxy(139,13);
			printf("|");
		}
		gotoxy(108+i,12);
		printf("-");
		gotoxy(108+i,14);
		printf("-");
	}
	delay(1000);							//delay de 1 segundo para nao bugar a tela 
	while(mStart!= 32){
		for(i=0;i<29;i++){
			if(kbhit()){					//sempre verifica se alguma tecla foi pressionada, caso sim verifica se foi SPACE e finaliza!
				mStart = getch();
			break;
		 	}								//faz a animação
			gotoxy(100+i,13);
			printf("C");
			gotoxy(0,0);
			delay(100);
			gotoxy(100+i,13);
			printf(" ");
			gotoxy(0,0);
			delay(100);
		}
		gotoxy(0,0);
	}
}
