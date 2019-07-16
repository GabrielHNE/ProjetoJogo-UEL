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

int main(int argc, char** argv){
	
	for(i=0;i<=51;i++){
		for(j=0;j<101;j++){
			gotoxy(100,3);
			
		}
	}
	return 0;
}




