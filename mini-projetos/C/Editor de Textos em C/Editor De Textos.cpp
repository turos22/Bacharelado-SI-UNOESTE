#include <stdio.h>
#include <string.h>
#include <conio2.h>
#include <conio.h>
#include <stdlib.h>
#include "Editor de Textos.h"

#define FDOIS 60
#define FTRES 61
#define FQUATRO 62
#define FCINCO 63
#define FDEZ 68
#define SETA_CIMA 72
#define SETA_BAIXO 80
#define SETA_ESQUERDA 75
#define SETA_DIREITA 77
#define HOME 71
#define END 79
#define INSERT 82
#define DELETE 83
#define PGUP 73
#define PGDW 81
#define MaxLinha 79
#define MaxLinhasPagina 21
#define COLOR_BOLD  "\e[1m"
#define COLOR_OFF   "\e[m"


int main ()
{
	int i, c, overwrite, linha_num, pos_num, qtd_linha_ant, x, y;
	int primeira_linha=0, rec_esq=0, rec_dir=0, sair=0;
	Linha *inicio=NULL, *aux_linha= NULL, *linha_ant, *exibir_a_partirde, *aux_exibicao;
	Digitos *pos_digito, *procura_pos=NULL, *pos_autocomplete;
	ListaGen *L;
	L = NULL;
	char sugestao[100];
	strcpy(sugestao, "");
	overwrite = linha_num = pos_num = 0;
	novalinhabranco(&inicio, NULL);
	x = Maxlinhas(inicio)+2;	
	aux_linha = inicio;
	y = finallinha(aux_linha);
	pos_digito =aux_linha -> inicioL;
	gotoxy(y,x);
	inserir('a', &aux_linha, &pos_digito, overwrite, NULL, sugestao);
	removerChar(&aux_linha, &pos_digito, 1, &x, &y);
	y++;
	visualizarlista(inicio,1, x,y,overwrite, "");
	exibir_a_partirde = inicio;
	textcolor(LIGHTGRAY);
	c = _getch();
	    while (c != 27 && sair == 0) {  
	    	int c_prox;
			switch(c)
			{
				case 0:
				case 224:
				c_prox = getch();
				switch(c_prox)
				{
					case SETA_CIMA:
							MoverCursor(&x,&y, &aux_linha, &pos_digito, 1, 'c');
						
						break;
					
					case SETA_BAIXO:
							MoverCursor(&x,&y, &aux_linha, &pos_digito, 1, 'b');
						
						break;
					case SETA_ESQUERDA:						
							MoverCursor(&x,&y, &aux_linha, &pos_digito, 1, 'e');
						
		                break;
		
		            case SETA_DIREITA:
						MoverCursor(&x,&y, &aux_linha, &pos_digito, 1, 'd');
		                break;
		
		            case HOME:
		            	MoverCursor(&x, &y, &aux_linha, &pos_digito, 79, 'e');
		                break;
		
		            case END:
		            	MoverCursor(&x, &y, &aux_linha, &pos_digito, 79, 'd');
		                break;
		
		            case INSERT:
		            	if (overwrite == 0)
		            		overwrite = 1;
		            	else
		            		overwrite = 0;
		                break;
		
		            case DELETE:
		            	removerChar(&aux_linha, &pos_digito, 0,  &x, &y);
		                break;
		
		            case PGUP:
						MoverCursor(&x,&y, &aux_linha, &pos_digito, 21, 'c'); 
		                break;
		
		            case PGDW: 
		                MoverCursor(&x,&y, &aux_linha, &pos_digito, 21, 'b');
		                break;
		                
		            case FDOIS: Abrir(inicio, primeira_linha, rec_esq, rec_dir);
		            	break;
		            	
		            case FTRES:Salvararqtexto(inicio);
		            	break;
		            	
		            case FQUATRO:sair=1;
		            	break;
						    
		            case FCINCO:SalvarConfig(&primeira_linha, &rec_esq, &rec_dir);
		            	break;
		            
		                
		            case FDEZ:inserir('§', &aux_linha, &pos_digito, overwrite, &L, sugestao);
		            	break;
				}
				break;
				
				case 8:
					removerChar(&aux_linha, &pos_digito, 1, &x, &y);
				break; 
				
				case 9: //tab
					{
						if(pos_digito != NULL)
						{							
							while (pos_digito != NULL && pos_digito -> ant != NULL && pos_digito -> ant -> letra != ' ')
								removerChar(&aux_linha, &pos_digito, 1, &x, &y);
							
							for (i=0; i<strlen(sugestao); i++)
							{
								linha_ant = aux_linha;
								inserir(sugestao[i], &aux_linha, &pos_digito, overwrite, &L, sugestao);
								if (linha_ant != aux_linha)
								{
									x++;
									if (pos_digito -> letra != 0)
									{
										procura_pos = aux_linha -> inicioL;
										y = 1;
										while (procura_pos -> letra != NULL && procura_pos != pos_digito)
											{
												y++;
												procura_pos = procura_pos -> prox;	
											}
										
									}
									else
										y = finallinha(aux_linha);							
									
								}
								else
									y++;
							}
							
						}
							
							
					}
					break;
				
				case 13:
					{
						//enter
						//aux_linha = inicio;
					//	while(aux_linha -> botton != NULL)
//							aux_linha = aux_linha -> botton;
						novalinhabranco(&aux_linha, aux_linha->botton); 
						aux_linha = aux_linha -> botton;
						x++;
						y = finallinha(aux_linha);
						pos_digito =aux_linha -> inicioL;
					}
					break;
				
				default:
					//qualquer outro caractere
					{
						linha_ant = aux_linha;
						inserir(c, &aux_linha, &pos_digito, overwrite, &L, sugestao);
						if (linha_ant != aux_linha)
						{
							x++;
							if (pos_digito -> letra != 0)
							{
								procura_pos = aux_linha -> inicioL;
								y = 1;
								while (procura_pos -> letra != NULL && procura_pos != pos_digito)
									{
										y++;
										procura_pos = procura_pos -> prox;	
									}
								
							}
							else
								y = finallinha(aux_linha);							
							
						}
						else
							y++;
						//if (aux_linha -> nro <= qtd_linha_ant) //se diminuiu e palavra onde estava o cursor era do final da linha
//						{
//							if (pos_digito -> letra == NULL)
//							{
//								pos_digito = aux_linha -> botton -> inicioL;
//								for (i = 0; i <qtd_linha_ant - aux_linha->nro; i++)
//									pos_digito = pos_digito -> prox;
//								
//								y = qtd_linha_ant - aux_linha->nro+1; //mais um para mover o cursor uma casa a frente da palavra nova escrita
//								aux_linha = aux_linha -> botton;
//								x = x++;	
//							}
//							else
//							{
//								//se diminuiu quer dizer q alguem desceu
//								pos_digito = pos_digito -> prox;
//							}
//						}		
//						else 
//							y++;
							
						//if (overwrite == 1 && pos_digito -> letra != NULL) 
//							pos_digito = pos_digito -> prox;
					}
					break;
			}
			if (sair == 0)
			{
				qtd_linha_ant = x-3;
				if (qtd_linha_ant/21 > 0)
				{
					aux_exibicao = exibir_a_partirde;
					for (i = 0; i < 21*(qtd_linha_ant/21) && aux_exibicao->botton != NULL; i++)
						aux_exibicao = aux_exibicao -> botton;
					exibir_a_partirde = aux_exibicao;
					x = 3;
				}
				else
				{
					if (qtd_linha_ant < 0)
					{
						aux_exibicao = exibir_a_partirde;
						for ( ;x < 3; x++)
							aux_exibicao = aux_exibicao -> top;
						exibir_a_partirde = aux_exibicao;
					}
				}
				if (pos_digito != NULL)
					if (pos_digito-> ant != NULL)
					{
						if (pos_digito -> ant -> letra != ' ' || pos_digito->ant->letra != 21)
							BuscaSugestao(pos_digito, L, sugestao);
					}
				
	    		visualizarlista(exibir_a_partirde,1, x,y,overwrite, sugestao);
	    		gotoxy(y,x);
	    		c = getch();	
			}			
   	    }
    DestruirEstrutura(&inicio);
    ImprimirTrie(L);
} 
