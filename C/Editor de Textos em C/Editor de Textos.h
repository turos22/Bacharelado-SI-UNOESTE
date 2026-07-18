struct TpDigitos
{
	char letra;
	struct TpDigitos *ant, *prox;
};
typedef struct TpDigitos Digitos;

struct TpLinha 
{
	struct TpLinha *top, *botton;
	int nro;
	Digitos *inicioL, *fimL;
};
typedef struct TpLinha Linha;

struct no {
	char letra;
	char terminal;
	struct no *prim;
	struct no *prox;
};
typedef struct no ListaGen;

ListaGen *Tail(ListaGen *L)
{
	return L -> prox;
}

ListaGen *Cons(char letra, ListaGen *cabeca, ListaGen *prox, int terminal)
{
	ListaGen *novo = (ListaGen*) malloc(sizeof(ListaGen));

    novo->letra = letra;
    novo->prim = cabeca;
    novo->prox = prox;
    if (terminal == 1)
    	novo -> terminal = 'T';
    else
    	novo -> terminal = 'F';

    return novo;
}

void novalinhabranco(Linha**linhaalvo, Linha *botton)
{
	Linha *aux, *nova;
	nova = (Linha*)malloc(sizeof(Linha));
	nova -> nro = 0;
	nova -> inicioL = (Digitos *)malloc(sizeof(Digitos));
	nova -> inicioL -> ant = NULL;
	nova -> inicioL -> prox = NULL;
	nova -> inicioL -> letra = 0;
	nova -> fimL = nova -> inicioL;
	nova -> top = *linhaalvo;
	nova -> botton = botton;	
	
	if (*linhaalvo == NULL)
		*linhaalvo = nova;
	else	
		(*linhaalvo) -> botton = nova;
	
	if (botton != NULL)
		botton -> top = nova;
}

void NovaLetra(Digitos**novoc, char c)
{
	*novoc = (Digitos*)malloc(sizeof(Digitos));
	(*novoc) -> letra = c;
	(*novoc) -> ant = 	(*novoc) -> prox = NULL;
}


int finallinha(Linha *linha)
{
	Digitos *aux;
	int contador=0;
	aux = linha -> inicioL;
	while (aux -> letra != 0)
	{
		aux = aux ->prox;
		contador++;
	}
	return contador+1;
}

int Maxlinhas(Linha *inicio)
{
	int contador=0; 
	if (inicio != NULL)
	{
		contador++;
		while (inicio -> botton!=NULL)
		{
			inicio = inicio -> botton;
			contador++;
		}
	}
	
	return contador;
}

void MoverCursor(int *x, int *y, Linha**linha_num, Digitos**pos, int qtd, char tipo)
{
	int contador, i;
	Digitos *procura_pos;
	
	switch(tipo)
	{
		case 'c':
			{
				if ((*linha_num) -> top != NULL)
				{
					for (contador = 0; contador  < qtd && (*linha_num) -> top != NULL; contador++)
						*linha_num = (*linha_num) -> top;
					procura_pos = (*linha_num)  -> inicioL;
				    for (i =0; (i<*y-1 && procura_pos -> letra != 0) ;i++)
				    	procura_pos = procura_pos -> prox;
				    *pos = procura_pos;
				    *y = i+1;
				    *x = *x -qtd;
				}
				
			}
			break;
		
		case 'b':
				{
					if ((*linha_num) -> botton != NULL)
					{
						for (contador = 0; contador  < qtd && (*linha_num) -> botton != NULL; contador++)
							*linha_num = (*linha_num) -> botton;	
						procura_pos = (*linha_num)  -> inicioL;
					    for (i =0; (i<*y-1 && procura_pos -> letra != 0) ;i++)
					    	procura_pos = procura_pos -> prox;
					    *pos = procura_pos;
					    *y = i+1;
					    *x = *x + qtd;
					}
				}
			break;
		
		case 'e':
				for (contador = 0; contador  < qtd && *y != 1; contador++)
				{
					*y = *y - 1;
					*pos = (*pos) -> ant;	
				}
			break;
			
		case 'd':
			for (contador = 0; contador  < qtd && *y != finallinha(*linha_num); contador++)
				{
					*y = *y + 1;
					*pos = (*pos) -> prox;	
				}
			break;
	}
}

void moverparabaixo(Linha**linha)
{
	if ((*linha) -> botton != NULL)
		moverparabaixo(&(*linha) -> botton);
	else
		novalinhabranco(linha, NULL);
	(*linha) -> botton -> inicioL = (*linha) -> inicioL;
	(*linha) -> botton -> nro = (*linha) -> nro;
}

ListaGen *InserirOrd(ListaGen **L, char letra, int terminal)
{
    ListaGen *aux, *ant, *retorno;
	if (*L == NULL)
	{
		*L = Cons(letra, NULL, NULL, terminal);
		retorno = *L;
	}
	else
	{
		if ((*L)->letra > letra)
		{
			*L = Cons(letra, NULL, *L, terminal);
			retorno = *L;
		}
		else
		{
			if ((*L)->letra == letra)
				retorno = *L;
			else
			{
				ant = *L;
				aux =Tail(ant);
				while(aux != NULL && aux->letra < letra)
				{
					ant = aux;
					aux = Tail(aux);
				}
				
				if (aux != NULL && aux -> letra == letra)
					retorno  = aux;
				else
				{
					ant -> prox = Cons(letra, NULL, aux,terminal);
					retorno = Tail(ant);
				}	
			}	
		}
	}
}


void InserirPalavraLGen(ListaGen **L, char palavra[100])
{
	int i;
	ListaGen *aux =NULL;
	for (i = 0; i<strlen(palavra);i++)
	{
		if (aux == NULL)
		{
			if (i == strlen(palavra) -1)
				aux = InserirOrd(L, palavra[i], 1);
			else
				aux = InserirOrd(L, palavra[i], 0);	
		}
		else
		{
			if (i == strlen(palavra) -1)
				aux = InserirOrd(&(aux -> prim) , palavra[i], 1);
			else
				aux = InserirOrd(&(aux -> prim), palavra[i], 0);	
		}
		
	}
}

void InsereLGen(Digitos *pos, ListaGen **L)
{
	char palavra[100];
	Digitos *aux;
	int i=0;
	aux = pos;
	if (aux != NULL)
	{
		aux = aux -> ant;
		while(aux -> ant != NULL && aux -> letra != ' ')
			aux = aux -> ant;
		
		if (aux -> letra == ' ')
			aux = aux->prox;
		
		if (aux != NULL)
		{
			while(aux != NULL && aux->letra != ' ')
			{
				palavra[i] = aux->letra;
				aux = aux -> prox;
				i++;
			}
			palavra[i] = '\0';
			
			if (i >1)
				InserirPalavraLGen(L, palavra);
		}
		
	}
}

void BuscarSug(ListaGen *L, char prefixo[100], char sug[100]) {
    ListaGen *atual = L;
    static char sugestao[100]; 
    int i = 0, sair=0, entrou=0;
    strcpy(sugestao, "");

    while (prefixo[i] != '\0' && sair == 0) {
        while (atual != NULL && atual->letra != prefixo[i]) {
            atual = atual->prox;
        }

        if (atual == NULL)
		   sair =1;
		else
		{
			sugestao[i] = atual->letra;
	        atual = atual->prim;
	        i++;	
		}	
   
    }

    while (atual != NULL && sair == 0) {
    	entrou = 1;
        sugestao[i] = atual->letra;
        
        if (atual->terminal == 'T') {
            sugestao[i + 1] = '\0';
            sair = 1;
        }
        
        atual = atual->prim; 
        i++;
    }

	if (entrou == 1)
		strcpy(sug, sugestao);
	else
    	strcpy(sug, "");
}

void BuscaSugestao(Digitos *pos, ListaGen *L, char sugestao[100])
{
	char prefixo[100];
	Digitos *aux =pos;
	int i=0;
	if (aux!=NULL)
	{
		if (aux -> letra == 0)
			aux = aux->ant;
			
		while(aux != NULL && aux -> letra != ' ')
			aux = aux -> ant;
			
		if (aux != NULL)
		{
			aux = aux->prox;
		
			while(aux != NULL && aux!=pos)
			{
				prefixo[i] = aux->letra;
				aux = aux -> prox;
				i++;
			}
			prefixo[i] = '\0';
			if (i>1)
			  BuscarSug(L, prefixo, sugestao);
		}
			
	}
}

void LinhaCheia(Linha**linha_num,Digitos**pos)
{
	Linha *linha_abaixo;
	Digitos *aux, *sentinela;
	int tamanho=0;	
	aux = (*linha_num) -> fimL;
	aux = aux -> ant;
	while (aux -> letra != ' ' && aux -> ant != NULL)
	{
		aux = aux -> ant;
		tamanho++;
	}
	
	if (aux -> prox -> letra == 0)
	{
		//espaco em branco vazio no final da linhna, dar free nele
		(*linha_num) -> fimL -> ant = aux -> ant;
		(*linha_num) -> fimL -> ant -> prox = (*linha_num) -> fimL;
		if (*pos == aux)
			*pos = (*linha_num) -> fimL;
		free(aux);
		(*linha_num) -> nro--;
	}	
	else
	{
		if ((*linha_num) -> botton == NULL)
			novalinhabranco(linha_num, NULL);
		else
			moverparabaixo(&(*linha_num) -> botton);
		
		linha_abaixo = (*linha_num) -> botton;
		linha_abaixo -> inicioL = (Digitos *)malloc(sizeof(Digitos));
		linha_abaixo -> inicioL -> ant = NULL;
		linha_abaixo -> inicioL -> prox = NULL;
		linha_abaixo -> inicioL -> letra = 0;
		linha_abaixo -> nro = 0;
		
		//vai apontar para o (*linha_num) -> fimL da linha de baixo
		linha_abaixo -> inicioL -> ant = (*linha_num) -> fimL -> ant;
	    (*linha_num) -> fimL -> ant -> prox = linha_abaixo -> inicioL;
		//palavra maior que 79 char
		if (aux -> ant == NULL)
		{
			linha_abaixo -> inicioL = (*linha_num) -> fimL -> ant;
			(*linha_num) -> fimL -> ant = (*linha_num) -> fimL -> ant -> ant;
			(*linha_num) -> fimL -> ant -> prox = (*linha_num) -> fimL;
			(*linha_num) -> nro--;
			linha_abaixo -> nro++;
		}
		else
		{
			aux = aux -> prox;
			(*linha_num) -> fimL -> ant = aux -> ant;
			aux -> ant -> prox = (*linha_num) -> fimL;
			linha_abaixo -> inicioL = aux;
			(*linha_num) -> nro -= tamanho;
			linha_abaixo -> nro += tamanho; 
		}
		
		linha_abaixo -> inicioL -> ant = NULL;
		
		if ((*pos) -> letra == 0)
		{
			(*linha_num) = linha_abaixo;
			aux = linha_abaixo -> inicioL;
			while (aux -> letra !=0)
				aux = aux -> prox;
			*pos = aux;
		}
		else
		{
			if (*pos == linha_abaixo -> inicioL) //estava antes da palavra que caiu
				*pos = (*linha_num) -> fimL;
			else
			{
				aux = linha_abaixo -> inicioL;
				while (aux -> letra != 0 && *pos != aux)
					aux = aux -> prox;
				if (*pos == aux) //estava no meio da palavra que caiu
					(*linha_num) = linha_abaixo;		
				
			}	
		}
	}

}

void inserir(char c, Linha**linha_num, Digitos**pos, int overwrite, ListaGen **L, char *sugestao)
{
	Linha *nova, *linha_abaixo;
	Digitos *novo_digito, *aux, *troca;
	int cont_linha=0, cont_digito;
	
	if (overwrite == 1 && (*pos) -> letra != 0)
	{
		(*pos) -> letra = c;
		*pos = (*pos) -> prox;	
	}
	else
	{   NovaLetra(&novo_digito, c);
	    if (*pos == NULL)
	    {
	    	(*linha_num) -> inicioL -> ant = novo_digito;
			novo_digito -> prox = (*linha_num) -> inicioL;
			(*linha_num) -> inicioL = novo_digito;	
	    }
	    else
	    {
	    	if ((*pos) -> ant == NULL && overwrite==0)
			{	
				(*linha_num) -> inicioL -> ant = novo_digito;
				novo_digito -> prox = (*linha_num) -> inicioL;
				(*linha_num) -> inicioL = novo_digito;		
			}	
			else
			{
				novo_digito -> ant = (*pos) -> ant;
				novo_digito -> prox = *pos;
				(*pos) -> ant -> prox = novo_digito;
				(*pos) -> ant = novo_digito;
			}	
	    }
		(*linha_num) -> nro++;		
	}
	
	if ((*linha_num) -> nro > 79)
		LinhaCheia(linha_num, pos);
	if (c == ' ')
	{
		if (overwrite == 1)
			{
				if ((*pos) -> letra == 0)	
					InsereLGen((*pos) -> ant, L);			
				else
					InsereLGen(*pos, L);			
			}
		else
			InsereLGen(novo_digito, L);
	}
}

void RemoverFinalInicio(Linha *linha_num, int tipo)
{
	Digitos *aux, *fim_linha_alv, *sentinela_linha_acima;
	Linha *linha_alvo;
	int contador=0, i=0, tam_palavra;
	//delete
	if (tipo == 0)
		linha_alvo = linha_num -> botton;
	else
		linha_alvo = linha_num;
	
	if (linha_alvo -> nro > 0)
	{
		contador = linha_alvo -> top -> nro;
		sentinela_linha_acima = linha_alvo -> top -> fimL;
		
		aux = linha_alvo -> inicioL;
		while (aux -> letra != 0 && i < 79-contador)
		{
			aux = aux -> prox;
			i++;
		}
		fim_linha_alv = aux;
		
		//conecto o sentinela ao inicio da linha de baixo a partir daqui
		sentinela_linha_acima -> ant -> prox = linha_alvo -> inicioL;
		linha_alvo -> inicioL -> ant = sentinela_linha_acima -> ant;
		
		if (aux -> letra != 0)
		{
			//ha mais caracteres que o limite possivel
			//buscar o espacamento em branco antes de aux 
			tam_palavra = i;
			while (aux -> ant != NULL && aux -> letra != ' ')
			{
				aux = aux ->ant;
				i--;
			}	
				
			if(aux -> ant != NULL)
			{
				//achou espaco em branco
				sentinela_linha_acima -> ant = aux -> ant;
				aux -> ant -> prox = sentinela_linha_acima;
				aux -> prox -> ant = NULL;
				linha_alvo -> inicioL = aux->prox;
				free(aux);
				
				if (tipo == 0)
					linha_num -> nro += i;
				else
					linha_num -> top -> nro +=i;
			}
			else
			{
				//palavrona imensa
				fim_linha_alv = fim_linha_alv -> ant;
				fim_linha_alv -> prox -> ant = NULL;
				linha_alvo -> inicioL = fim_linha_alv -> prox;
				fim_linha_alv -> prox = sentinela_linha_acima;
				sentinela_linha_acima -> ant = fim_linha_alv;
				if (tipo == 0)
					linha_num -> nro += tam_palavra;
				else
					linha_num -> top -> nro +=tam_palavra;
			}
			
		}
		else
		{
			sentinela_linha_acima -> ant = aux -> ant;
			aux -> ant -> prox = sentinela_linha_acima;
			linha_alvo -> inicioL = aux;
			linha_alvo -> nro = 0;
			aux -> ant = NULL;
		    if (tipo == 0)
				linha_num -> nro += i;
			else
				linha_num -> top -> nro +=i;
			
		}	
	}
		
	
}

void removerChar(Linha**linha_num, Digitos**pos, int tipo, int *x, int *y)
{
	Digitos *aux, *pos_anterior;
	Linha *linha_aux;
	int contador=0;
	//delete
	if (tipo == 0)
	{
		if ((*pos) -> letra != 0)
		{
			if ((*pos) -> ant == NULL)
				(*linha_num) -> inicioL = (*pos) -> prox;
			else
				(*pos) -> ant -> prox = (*pos) -> prox;	
			
			(*pos) -> prox -> ant = (*pos) -> ant;
			aux = *pos;
			*pos = (*pos) -> prox;
			free(aux);
			(*linha_num) -> nro--;
		}
		else
		{
			//subir a linha abaixo para cima	
			if ((*linha_num) -> botton != NULL && (*linha_num) -> nro < 79)
			{
				pos_anterior = (*pos)->ant;
				RemoverFinalInicio(*linha_num, tipo);
				*pos = pos_anterior->prox;
			}		
		}	
		
	}
	else
	{
		if ((*linha_num) -> nro != 0)
		{
			if ((*pos) -> ant != NULL && (*pos) -> ant != (*linha_num) -> inicioL)		
			{
				aux = (*pos) -> ant; 
				(*pos) -> ant -> ant -> prox = *pos;
				(*pos) -> ant = (*pos) -> ant -> ant;
				free(aux);
				*y = *y -1;
				(*linha_num) -> nro--;
			}
			else
			{
				if ((*pos) -> ant == (*linha_num) -> inicioL)
				{
					aux = (*pos) -> ant;
					(*linha_num) -> inicioL = *pos;
					(*pos) -> ant = NULL;
					free(aux);
					(*linha_num) -> nro--;
					*y = *y - 1;
					
				}
				else
				{
					if ((*linha_num) -> top != NULL && (*linha_num) -> top -> nro < 79)
					{
						*y = finallinha((*linha_num) ->top);
						*x = *x-1;
						RemoverFinalInicio(*linha_num, tipo);
						*linha_num =  (*linha_num) -> top;
						//*pos = (*pos) -> ant;
						
					}		
				}
			}
		}
		else
		{
			if ((*linha_num) -> top != NULL)
			{
				linha_aux = (*linha_num) -> botton;
				*linha_num = (*linha_num) -> top;
				*pos = (*linha_num) -> fimL;
				free((*linha_num) -> botton);
				if (linha_aux != NULL)
					linha_aux -> top = (*linha_num);
				(*linha_num) -> botton = linha_aux;	
				*y = finallinha(*linha_num);
				*x = *x-1;
			}
			
		}
		
	}
}

void Moldura(int x, int y, int entrada, char *sugestao)
{
	int i;
    char txt_ent[10];
    
    clrscr();
    textcolor(LIGHTGRAY);
    x -= 2;

    gotoxy(1, 1);
    printf(" F2-Abrir   F3-Salvar   F4-Sair   F5-Exibir");

    gotoxy(1, 2);
    for (i = 0; i < 80; i++) {
        printf("-");
    }


    gotoxy(1, 24);
    for (i = 0; i < 80; i++) {
        printf("-");
    }
    
    gotoxy(1, 25);
    if (entrada == 1){
    	printf(" COL=%d,  LIN=%d   %s   ||||   %s", y, x, "OVERWRITE", sugestao);
    }
    	
    else
	{
    	printf(" COL=%d,  LIN=%d   %s   ||||   %s", y, x, "INSERT", sugestao);
    }
    	

 

    gotoxy(1, 3);
}


void visualizarlista(Linha *linha, int linha_p, int x, int y, int ovewrite, char *sugestao)
{
	Linha *aux_linha;
	int cont, cor = 8;
	Digitos *aux;
	clrscr();
	linha_p = 3;
	Moldura(x,y,ovewrite, sugestao);
	textcolor(cor);
	cont = 1;
	if (linha != NULL)
	{
		aux_linha = linha;
		aux = linha -> inicioL;
		gotoxy(1,linha_p++);
		while (aux -> letra != 0)
		{

			if (aux -> letra == '§')
			{
				if (cor == 8)
					cor = 15;
				else
					cor = 8;
				textcolor(cor);
			}
			else
				printf("%c", aux->letra);
			//printf( "\e[m");
			aux = aux ->prox;
		}
		cont++;
		while (aux_linha -> botton != NULL && cont <=21)
		{   
		    gotoxy(1,linha_p++);
			aux_linha = aux_linha -> botton;
			aux = aux_linha -> inicioL;
			while (aux -> letra != 0)
			{
				if (aux -> letra == '§')
				{
					if (cor == 8)
						cor = 15;
					else
						cor = 8;
					textcolor(cor);
				}
				else
					printf("%c", aux->letra);
				aux = aux ->prox;
			}	
			cont++;
		}
	}		
}

void SalvarConfig(int *pl, int *rec_esq, int *rec_dir)
{
	clrscr();
	printf("Digite o valor do espacamento da primeira linha: ");
	scanf("%d", &(*pl));
	printf("\nDigite o valor do recuo a esquerda: ");
	scanf("%d", &(*rec_esq));
	printf("\nDigite o valor do recuo a direita: ");
	scanf("%d", &(*rec_dir));
	printf("\n Configs Salvas!");
	getch();
}

void Abrir(Linha *linha, int pl, int rec_esq, int rec_dir) {
    Linha *aux_l = linha;
    Digitos *aux_d;
    int y = 3; 
    int x;
    int negrito = 0;
    int limite_direita = 78 - rec_dir; 
    int i;

    clrscr();
    textcolor(7);
    gotoxy(1, 1);
    for(i = 0; i < 80; i++) printf("|"); 

    for(i = 2; i <= 24; i++) {
        gotoxy(1, i);  printf("|");
        gotoxy(80, i); printf("|");
    }

    gotoxy(1, 25);
    for(i = 0; i < 80; i++) printf("-");

    x = 2 + rec_esq + pl; 
    gotoxy(x, y);

    while (aux_l != NULL) {
        aux_d = aux_l->inicioL;

        while (aux_d != aux_l->fimL && aux_d != NULL) {
            
            if (aux_d->letra == '§') {
                negrito = !negrito;
                textcolor(negrito ? 15 : 7);
            } 
            else {
                if (x < 80) {
                    printf("%c", aux_d->letra);
                    x++;
                }
                if (aux_d->letra == '.' || aux_d->letra == '!' || aux_d->letra == '?') {
                    y++; 
                    x = 2 + rec_esq + pl; 
                    if (y <= 24) gotoxy(x, y);
                }
                else if (x > limite_direita) {
                    y++; 
                    x = 2 + rec_esq; 
                    if (y <= 24) gotoxy(x, y);
                }
            }
            aux_d = aux_d->prox;

            if (y > 24) break;
        }
        if (y > 24) break;
        aux_l = aux_l->botton; 
    }

    textcolor(7);
    getch();
}

void DestruirEstrutura (Linha**inicio)
{
	Linha *aux_pesquisa, *aux_limpa;
	Digitos *aux_digito, *aux_busca;
	aux_pesquisa = *inicio;
	while (aux_pesquisa != NULL)
	{
		aux_digito = aux_pesquisa -> inicioL;
		while (aux_digito != 0)
		{
			aux_busca = aux_digito -> prox;
			free(aux_digito);
			aux_digito=aux_busca;
		}
		aux_limpa = aux_pesquisa -> botton;
		free(aux_pesquisa);
		aux_pesquisa = aux_limpa;
	}
	*inicio = NULL;
	free(*inicio);
}

void ExibirPalavras(ListaGen *no, char *palavra_atual, int indice) {
    if (no == NULL) {
        return;
    }

    palavra_atual[indice] = no->letra;
    if (no->terminal == 'T') {
        palavra_atual[indice + 1] = '\0'; 
        printf("%s\n", palavra_atual);
    }
    ExibirPalavras(no->prim, palavra_atual, indice + 1);
    ExibirPalavras(no->prox, palavra_atual, indice);
}

void ImprimirTrie(ListaGen *raiz) {
    char buffer[100]; 
    clrscr();
    ExibirPalavras(raiz, buffer, 0);
}

void Salvararqtexto(Linha *L) {
    FILE *arq = fopen("editor_de_texto.txt", "w");
    
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo para salvar!\n");
        return;
    }

    Linha *auxL = L; 
    Digitos *auxD;   

    while (auxL != NULL) {
        auxD = auxL->inicioL;
        while (auxD != NULL && auxD != auxL->fimL) {
            
            if (auxD->letra != 0) {
                fputc(auxD->letra, arq);
            }
            
            auxD = auxD->prox;
        }
        fputc('\n', arq);

        auxL = auxL->botton; 
    }

    fclose(arq);
    printf("Arquivo salvo com sucesso!\n");
}
