struct registros
{
	int simbolo, frequencia;
	char palavra[50], codigo[50];
	struct registros *prox;
};
typedef struct registros Reg;

struct dadobinario
{
	int simbolo;
	char palavra[50], codigo[50];
};
typedef struct dadobinario dbi;

struct bits 
{
	unsigned char b7:1;
	unsigned char b6:1;
	unsigned char b5:1;
	unsigned char b4:1;
	unsigned char b3:1;
	unsigned char b2:1;
	unsigned char b1:1;
	unsigned char b0:1;
};

union byte
{
	struct bits bi;
	unsigned char num;
};
typedef union byte byte;




void Minusculo(char palavra[50])
{
	int i;
	for (i=0; i<strlen(palavra);i++)
	{
		if (palavra[i] >= 65 && palavra[i]<=90) 
			palavra[i] = tolower(palavra[i]);
	}
}

Reg *CriaNo(char palavra[50])
{
	Reg *novo = (Reg*)malloc(sizeof(Reg));
	novo -> simbolo = 0;
	novo -> frequencia = 1;
	strcpy(novo -> palavra, palavra);
	strcpy(novo -> codigo, "");
	novo -> prox = NULL;
}

void ValidaInsereReg(Reg **registros, char palavra[50])
{
    Reg *ant, *aux, *novo;
    Minusculo(palavra);
    
    if (*registros == NULL)
        *registros = CriaNo(palavra); 
    else
    {
        if (strcmp((*registros)->palavra, palavra) == 0)
            (*registros)->frequencia++;
        else
        {
            ant = *registros;
            aux = (*registros)->prox;
            while(aux != NULL && strcmp(aux->palavra, palavra) != 0)
            {
                ant = aux;
                aux = aux->prox;
            }
            if (aux != NULL)
                aux->frequencia++;
            else
            {
                novo = CriaNo(palavra);
                ant->prox = novo;    
            }
        }    
    }
}
void OrdenaFrequencia(Reg **registros)
{
	Reg *resultado=NULL, *seq_resultado;
	Reg *atual, *ant;
	Reg *maior, *ant_maior;
	int simbolo = 1;
	while(*registros != NULL)
	{
		ant = NULL;
		atual = *registros;
		
		maior = *registros;
		ant_maior = NULL;
		while(atual != NULL)
		{
			if (atual -> frequencia > maior ->frequencia)
			{
				maior = atual;
				ant_maior = ant;
			}
			ant = atual;
			atual = atual ->prox;
		}
		
		if (ant_maior == NULL)
			*registros = (*registros) ->prox;
		else
			ant_maior ->prox = maior ->prox;
		
		maior -> prox = NULL;
		maior -> simbolo = simbolo;
		if (resultado == NULL)
			resultado = maior;
		else
			seq_resultado->prox = maior;
		seq_resultado = maior;
		simbolo++;
	}
	
	*registros = resultado;
}

void InserirRegistros(Reg **registros)
{  
    char aux[50], caractere, char_especial[50];
    int i = 0;
    FILE *arq = fopen("Construir.txt", "r"); 
    
    if (arq != NULL)
    {
        caractere = fgetc(arq);
        while(!feof(arq))
        {
        	
            if (caractere == '\r') 
                caractere = fgetc(arq);
            else
            {
            	 if (caractere == ' ' || caractere == ',' || caractere == '.' || caractere == ';' || caractere == '\n')
	            {
	                if (i > 0) 
	                {
	                    aux[i] = '\0';
	                    ValidaInsereReg(&*registros, aux);
	                }
	                char_especial[0] = caractere;
	                char_especial[1] = '\0';
	                ValidaInsereReg(&*registros, char_especial);
	                
	                i = 0;
	                aux[0] = '\0'; 
	            }
	            else   
	               aux[i++] = caractere;
	               
	            
	            caractere = fgetc(arq);	
            }
        }
        if (i > 0) {
            aux[i] = '\0';
            ValidaInsereReg(registros, aux);
        }
        fclose(arq); 
    }
    
    OrdenaFrequencia(&*registros); 
}

void gravarArqBinario(Reg *registro)
{
	FILE *arq = fopen("tabela.dat", "wb");
	Reg *aux=registro;
	dbi reg;
	while(aux != NULL)
	{
		reg.simbolo = aux -> simbolo;
		strcpy(reg.palavra, aux->palavra);
		strcpy(reg.codigo, aux->codigo);
		fwrite(&reg, sizeof(dbi),1,arq);
		aux = aux -> prox;
	}
	fclose(arq);
}

Reg *LerTabela()
{
	FILE *arq = fopen("tabela.dat", "rb");
	Reg *lista=NULL, *novo, *registro_atual;
	dbi reg;
	if (arq != NULL)
	{
		fread(&reg, sizeof(dbi), 1, arq);
		while(!feof(arq))
		{
			novo = (Reg*)malloc(sizeof(Reg));
			novo -> simbolo = reg.simbolo;
			strcpy(novo -> palavra, reg.palavra);
			strcpy(novo -> codigo, reg.codigo);
			novo->prox = NULL;
			if (lista ==NULL)
				lista = novo;
			else
				registro_atual->prox = novo;
		    registro_atual = novo;
			fread(&reg, sizeof(dbi), 1, arq);    
				
		}
		fclose(arq);
	}
	return lista;
}

void definirBit(struct bits *bi, int posicao, int valor) {
    switch(posicao) {
        case 0: bi->b0 = valor; 
        case 1: bi->b1 = valor; 
        case 2: bi->b2 = valor; 
        case 3: bi->b3 = valor; 
        case 4: bi->b4 = valor; 
        case 5: bi->b5 = valor; 
        case 6: bi->b6 = valor; 
        case 7: bi->b7 = valor; 
    }
}

void processarCodigo(char cod[50], FILE *arq, byte *b, int *cont) {
	int i, bit;
    for (i = 0; cod[i] != '\0'; i++) {
        bit = cod[i] - '0';
        definirBit(&b->bi, *cont, bit);
        (*cont)++;
        if (*cont == 8) {
            fwrite(&b->num, sizeof(unsigned char), 1, arq);
            b->bi.b0 = 0;
            b->bi.b1 = 0;
            b->bi.b2 = 0;
            b->bi.b3 = 0;
            b->bi.b4 = 0;
            b->bi.b5 = 0;
            b->bi.b6 = 0;
            b->bi.b7 = 0;
            *cont = 0;
        }
    }
}

void BuscarCodigo(Reg *registro, char palavra[50], char codigo[50])
{
	Reg *aux;
	aux = registro;
	Minusculo(palavra);
	while(aux != NULL && strcmp(aux->palavra, palavra)!=0)
		aux = aux -> prox;
	if (aux != NULL)
		strcpy(codigo, aux->codigo);
	else
		strcpy(codigo, "");
}

void codificarTexto(char texto[100])
{
	FILE *arq = fopen("codificar.dat", "wb");
	Reg *lista = LerTabela(), *limpa, *limpa_aux;
	byte byte;
	int contagem = 0, bit, i=0, idFrase=0;;
	char aux[50], char_especial[2], codPalavra[50];
	byte.num = 0;
	if(lista != NULL)
	{
		
	    
	    while (texto[idFrase] != '\0') {
	        char caractere = texto[idFrase];
	
	        if (caractere == ' ' || caractere == ',' || caractere == '.' || caractere == ';' || caractere == '\n') {
	            
	            if (i > 0) {
	                aux[i] = '\0';
	                BuscarCodigo(lista, aux, codPalavra);
	                if (strcmp(codPalavra, "") != 0) 
				    	processarCodigo(codPalavra, arq, &byte, &contagem);
	                 else 
	                    printf("[?]");
	                i = 0;
	            }
	
	            char_especial[0] = caractere;
	            char_especial[1] = '\0';
	            BuscarCodigo(lista, char_especial,codPalavra);
	            if (strcmp(codPalavra, "")) 
	            	processarCodigo(codPalavra, arq, &byte, &contagem);
	
	        } else 	            
	             aux[i++] = caractere;
	        idFrase++;
	    }
	
	    if (i > 0) {
	         aux[i] = '\0';
	         BuscarCodigo(lista, aux, codPalavra);
             if (strcmp(codPalavra, "")) 
	         	processarCodigo(codPalavra, arq, &byte, &contagem);
	    }
	    if (contagem > 0) {
	        fwrite(&byte.num, sizeof(unsigned char), 1, arq);
	    }
	
	  fclose(arq);
	  limpa = lista;
	  while(limpa != NULL)
	  {
	  	limpa_aux = limpa;
	  	limpa = limpa->prox;
	  	free(limpa_aux);
	  }
	}
}

void ExibirTabelaRegistros(Reg *registros)
{
    Reg *atual = registros;
    int simboloId = 0;

    printf("===================================================================\n");
    printf("| %-7s | %-15s | %-12s | %-20s |\n", "Simbolo", "Palavra", "Frequencia", "Codigo de Huffman");
    printf("===================================================================\n");

    while (atual != NULL)
    {
        char palavraVisivel[50];
        if (strcmp(atual->palavra, " ") == 0) {
            strcpy(palavraVisivel, "[Espaco]");
        } else if (strcmp(atual->palavra, "\n") == 0) {
            strcpy(palavraVisivel, "[Nova Linha]");
        } else {
            strcpy(palavraVisivel, atual->palavra);
        }

     
        char codigoHuffman[50];
        strcpy(codigoHuffman, "");
        printf("| %-7d | %-15s | %-12d | %-20s |\n", 
               atual -> simbolo, 
               palavraVisivel, 
               atual->frequencia, 
               atual -> codigo);

        simboloId++;
        atual = atual->prox;
    }
    printf("===================================================================\n");
}
