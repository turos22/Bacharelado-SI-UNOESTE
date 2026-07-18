#include <stdio.h>
#include <conio2.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <math.h>
#include <time.h> 

#include "trabalhoED.h"

int main()
{
	int tempo=0 , cont_tempo=0, tempo_atual=0 , n_salas;
	Paciente *Fila = NULL;
	Paciente *ex;
	char ch;
	int novo, remover, salas_disponiveis ,i;
	DescritorMaster D;
	Descritor *aux_d;
	Medico *medicos, *aux_busca, aux_excluido;
	FILE *pont = fopen("Pacientes.txt","r");
	//contador de pacientes atendidos por triagem
	int verde=0, amarelo=0, vermelho=0;
	int t_verde=0, t_amarelo=0, t_vermelho=0;
	TpSalasExcluidas S[100]; 
	int TL=0, excluiu=0;
	
	srand(time(NULL));
	//Inicializar(Verde);
//	Inicializar(Amarelo);
//	Inicializar(Vermelho);
	InicializarDescMaster(D);
	if(pont == NULL)
	{
		printf("arquivo nao encontrado!");
	}else{
		system("cls");
		MolduraPadrao(50,15,125,25);
		gotoxy(52,17);
		printf("Determine o numero de medicos disponiveis para atendimento (max 6)");
		gotoxy(52,18);
		scanf("%d",&n_salas);
		while(n_salas<=0 || n_salas >6)
		{
			system("cls");
			MolduraPadrao(50,15,125,25);
			gotoxy(52,17);
			printf("Numero MAXIMO de salas utilizaveis eh 6");
			gotoxy(52,18);
			printf("Determine o numero de medicos disponiveis para atendimento (max 6)");
			gotoxy(52,19);
			scanf("%d",&n_salas);	
		}
		medicos = Nova_Sala(n_salas);
		Altera_status_sala(1, medicos, n_salas, 1, n_salas);
		salas_disponiveis = n_salas;
		fflush(stdin);
		
		
		ch = NULL;	
		do{
			//Sleep(1000);
			if(cont_tempo - tempo_atual == tempo && !feof(pont))//significa que chegou outro paciente.
			{
				//Fila = OrdemPrioritaria(Fila,D,pont);
				ex = NovoPaciente(pont);
				ex->tempo_fila = cont_tempo;
				if (ex->prio == 1)
					D.inicio = OrdemPrioritaria(ex, D.inicio);
				else if(ex->prio == 2)
					D.inicio->prox_desc = OrdemPrioritaria(ex, D.inicio->prox_desc);
				else
				{
					aux_d = D.inicio->prox_desc;
					aux_d->prox_desc = OrdemPrioritaria(ex, aux_d->prox_desc);					
				}
				
				tempo = rand() % 5 + 1;//sorteia quando chega o proximo paciente.
				tempo_atual = cont_tempo;
			}
		
			Exibir(D,medicos,vermelho,amarelo,verde,t_vermelho,t_amarelo,t_verde,cont_tempo);
			//Legendas(vermelho,amarelo,verde,t_vermelho,t_amarelo,t_verde);
			
			//Atendimento e contadores
			//loop de buscar entre salas
			//ver as disponiveis, se disponivel preencher com paciente
			//se nao, adicionar 1 no tempo
			// se sem paciente e nao disponivel
			
			
			//farei a lógica de forma sequencial, porem para logica aleatoria
			//seria necessario percorrer a lista de medicos para saber os disponiveis
			//e para os pacientes sortea-los entre esses aleatorios para poder fazer de forma randomica
			
			aux_busca = medicos;
			while(aux_busca != NULL)
			{
				aux_excluido.prox = NULL;
				excluiu = 0;
				if (aux_busca->atual != NULL && aux_busca->Status == 1)
				{
					if (aux_busca->atual->Tempo == aux_busca->Tempo_Estimado+1) //tempo estimado eh o tempo daql pac em atendimento
					{
						//troca paciente
						
						//etapa 1 - contadores
						if (aux_busca->atual->prio == 1) //vermelho
						{
							vermelho++;
							aux_busca->vermelho_atend++;
						}
						else if (aux_busca->atual->prio == 2){//amarelo
							  amarelo++;
							  aux_busca->amarelo_atend++;
							}
						else{
							verde++;
							aux_busca->verde_atend++; //verde
						}
						
						//etapa 2 - novo pac
						if (ExistePacienteFila(D))
						{
							if (D.inicio->inicio!=NULL){ //vermelho maior prioridade
								
								aux_busca->atual = RetornaProxPac(D.inicio);
								t_vermelho += cont_tempo - aux_busca->atual->tempo_fila;
							}
							else if(D.inicio->prox_desc->inicio!=NULL){ //amarelo
								
								aux_busca->atual = RetornaProxPac(D.inicio->prox_desc);
								t_amarelo += cont_tempo - aux_busca->atual->tempo_fila;
							}
							else 
							{
								aux_d = D.inicio->prox_desc;
								if(aux_d->prox_desc->inicio!=NULL){ //verde
									
									aux_busca->atual = RetornaProxPac(aux_d->prox_desc);
									t_verde += cont_tempo - aux_busca->atual->tempo_fila;									
								}
							}
							aux_busca->Tempo_Estimado =0;
							
						}
						else
							aux_busca->atual = NULL;	
					}
					else
						aux_busca->Tempo_Estimado++;
				}
				else if(aux_busca->atual != NULL){ //saiu la de cima porque o status eh 0
						if (aux_busca->atual->Tempo == aux_busca->Tempo_Estimado+1)
						{
							if (aux_busca->atual->prio == 1) //vermelho
								{
									vermelho++;
									aux_busca->vermelho_atend++;
								}
								else if (aux_busca->atual->prio == 2){//amarelo
									  amarelo++;
									  aux_busca->amarelo_atend++;
									}
								else{
									verde++;
									aux_busca->verde_atend++; //verde
								}
							
							aux_busca->atual = NULL;
							aux_busca->Tempo_Estimado=0;
							aux_excluido.prox = aux_busca->prox;
							excluiu = 1;
							medicos = ExcluirFisico(medicos, S, TL, aux_busca);
						}
						else
							aux_busca->Tempo_Estimado++;
					}
					else if(aux_busca->Status == 1) //sala vazia com status 1
					{
						//nesse caso paciente eh nulo, verificar status para adicionar ou nao
					    if (ExistePacienteFila(D))
						{
							if (D.inicio->inicio!=NULL){	 //vermelho maior prioridade
								
								aux_busca->atual = RetornaProxPac(D.inicio);
								t_vermelho += cont_tempo - aux_busca->atual->tempo_fila;
							}
							else if(D.inicio->prox_desc->inicio!=NULL){ //amarelo
								
								aux_busca->atual = RetornaProxPac(D.inicio->prox_desc);
								t_amarelo += cont_tempo - aux_busca->atual->tempo_fila;
							}
							else 
							{
								aux_d = D.inicio->prox_desc;
								if(aux_d->prox_desc->inicio!=NULL){ //verde
									
									aux_busca->atual = RetornaProxPac(aux_d->prox_desc);
									t_verde += cont_tempo - aux_busca->atual->tempo_fila;
								}
							}
							aux_busca->Tempo_Estimado =0;
							
						}
						//nao tem else pois esta sem paciente e com status == 0
					}
			
				if (excluiu == 1)
				{
					if(aux_excluido.prox == NULL)
						aux_busca = NULL; //JA ESTAREI NO NULO por ser o ultimo 
					else 
						aux_busca = aux_excluido.prox;
				}
				else
					aux_busca = aux_busca->prox;
				
			}
				
			
			
			cont_tempo+=1;
			if(kbhit())
			{
				system("cls");
				textcolor(7);
				ch =getch();
				MolduraPadrao(50,15,125,25);
				if (ch == 'n')
				{
					gotoxy(52,17);
					printf("Digite quantas salas deseja adicionar (%d ja em uso): ", salas_disponiveis);
					gotoxy(52,18);
					scanf("%d", &novo);
					while(salas_disponiveis+novo >6)
					{
						system("cls");
						MolduraPadrao(50,15,125,25);
						gotoxy(52,17);
						printf("Numero MAXIMO de salas utilizaveis eh 6");
						gotoxy(52,18);
						printf("Digite quantas salas deseja adicionar (%d ja em uso): ", salas_disponiveis);
						gotoxy(52,19);
						scanf("%d",&novo);	
					}
					Altera_status_sala(1, medicos, novo,0,salas_disponiveis);
					salas_disponiveis += novo;
					
				}
				else if (ch == 'r')
				{
					gotoxy(52,17);
					printf("Digite quantas salas deseja remover(%d ja em uso): ", salas_disponiveis);
					gotoxy(52,18);
					scanf("%d", &remover);
					while(salas_disponiveis-remover<=0)
					{
						system("cls");
						MolduraPadrao(50,15,125,25);
						gotoxy(52,17);
						printf("Numero MINIMO de salas utilizaveis eh 1");
						gotoxy(52,18);
						printf("Digite quantas salas deseja remover(%d ja em uso): ", salas_disponiveis);
						gotoxy(52,19);
						scanf("%d",&remover);	
					}
					Altera_status_sala(0, medicos, remover,0,salas_disponiveis);
					salas_disponiveis -= remover;
					//para remover basta definir o status como indisponivel e tenha cliente em atendimento
				}
			}
			Exibir(D,medicos,vermelho,amarelo,verde,t_vermelho,t_amarelo,t_verde,cont_tempo);
			//Legendas(vermelho,amarelo,verde,t_vermelho,t_amarelo,t_verde);
		}while(ch != 27);
		
		fclose(pont);
		gotoxy(1,30);
		clrscr();
		for(i = 0; i<TL;i++)
			printf("\nSala %d - %d atendimentos", S[i].num_sala, S[i].qtd_atend);
		
	}
	
	return 0;
}
