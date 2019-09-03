#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h> 		//contem time(), que retorna o tempo atual em ms
#include <windows.h>	//contem funcoes necessarias para a funcao gotoxy;
#include <math.h>

typedef struct{
    int score;
    char name;

} Lista;

int main(){
    char name[5], a, aux;
    int pontuacao, i;
    int cmpPoint[10];

    Lista lista[10][5];
    FILE *record;

    if((record = fopen("record.txt","a")) == NULL){
        printf("arquivo corrompido ou apagado!\n");
        return 1;
    }

    // printf("forneca o seu nome e score: ");
    // scanf("%s %d", name, &pontuacao);

    // fprintf(record,"%s %d\n", name, pontuacao);


    while(a != '@'){
        fscanf(record,"%c", &a);
        printf("%c", a);
        if(a =='#'){
            fscanf(record,"#%d", &cmpPoint[i]);
        }
        printf("entrou pelo menos!");
    }

    for(i=0;i<10;i++){
        printf("%d ", cmpPoint[i]);
    }

    fclose(record);
    getch();
    return 0;
}