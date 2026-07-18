#include <stdio.h>
#include <conio2.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "tadFILAHosp.h"

char menu(void)
{
	clrscr();
	printf("TRABALHO FILA HOSPITAL\n\n");
	printf("[A] Iniciar Atendimentos!\n");

	printf("[ESC] TERMINAR PROGRAMA\n");
	
	return toupper(getche());
}

void filaHosp(void){

	
	tpFilaP fila;
	inicializar(fila);
	int sort, tempo=0, cont=0, tempoAtend =0;
	float tempoMedio=0;
	FILE *ptr = fopen("Pacientes.txt", "r");
	tpElemento paciente;
	
	
	sort = 6;
	if(ptr == NULL){
		printf("\nErro de abertura de arquivo!!\n");
	}
	else{
		fscanf(ptr, "%[^;];%d;%d\n",&paciente.nome, &paciente.id, &paciente.prior);
		paciente.tempo = tempo;
		PUSH(fila,paciente);
		do{
			clrscr();
			exibirFila(fila, tempo, sort, tempoAtend);
		//	Sleep(1000);
			if(tempo%3==0 && tempo!=0 && !feof(ptr)){
				if(!verifFilaCheia(fila.qtde)){
					fscanf(ptr, "%[^;];%d;%d\n",&paciente.nome, &paciente.id, &paciente.prior);
					paciente.tempo = tempo;
					PUSH(fila,paciente);
				}
			}
			clrscr();
			exibirFila(fila, tempo, sort, tempoAtend);
			Sleep(200);
			if(!verifFilaVazia(fila.qtde) && tempoAtend%sort==0 && tempoAtend!=0){
				POP(fila);
				Stickman(fila.elem[0]);
				if(!verifFilaVazia(fila.qtde))
					tempoMedio+=tempo-fila.elem[fila.inicio].tempo;
				sort = rand()%4+3;
				cont++;
				tempoAtend = 0;
			}
			clrscr();
		
			exibirFila(fila, tempo, sort, tempoAtend);
			Sleep(200);
			tempo++;
			tempoAtend++;
		}while(!kbhit() && cont!=100);
		
		system("cls");
		printf("Total de pacientes atendidos: %d\n", cont);
		printf("Tempo medio para ser atendido: %.2f\n", tempoMedio/cont);
		getch();
		fclose(ptr);
	}
}



int main(void)
{
	
	Sleep(2000);
	textcolor(4);
	Moldura_Inicio(56, 16, 93, 23);
	gotoxy(70,18);
	Sleep(1000);
	printf("FEITO POR:");
	Sleep(1000);
	gotoxy(62,19);
	printf("Arthur Shirasaki Orosco");
	Sleep(1000);
	gotoxy(58,20);
	printf("Guilherme Augusto Viani Guimaraes");
	Sleep(1000);
	gotoxy(61,21);
	printf("Lucca Turra De Oliveira Senra");
	Sleep(4000);
	textcolor(7);
	
	
	char opcao;
	srand(time(NULL));	
	system("cls");
	do
	{
		opcao = menu();
		switch(opcao)
		{
			case 'A':	
				filaHosp();
				getch();
				break;
		}
			
	}while (opcao!=27);
	return 0 ;
}
