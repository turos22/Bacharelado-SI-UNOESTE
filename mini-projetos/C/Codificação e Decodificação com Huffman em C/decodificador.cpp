#include <stdio.h>
#include <string.h>
#include <conio2.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>

#include "registros.h"
#include "tree.h"

struct abb
{
	struct abb *esq, *dir;
	int simbolo;	
};
typedef struct abb abb;

abb *CriaNoABB(int simbolo)
{
	abb *novo = (abb*)malloc(sizeof(abb));
	novo -> esq = novo->dir = NULL;
	novo -> simbolo = simbolo;
	return novo;
}

void insereAbb(abb **raiz, abb*novo, char codigo[50], int iterador)
{
	
	if (*raiz == NULL && codigo[iterador] == '\0')
		*raiz = novo;
	else
	{
		if (*raiz == NULL)
			*raiz = CriaNoABB(0);
		if(codigo[iterador] == '1') //direita
			insereAbb(&(*raiz) -> dir, novo, codigo, iterador+1);
		else
			insereAbb(&(*raiz) -> esq, novo, codigo, iterador+1);
	}
}

void CriarABB(abb **raiz)
{
	FILE *arq = fopen("tabela.dat", "rb");
	abb *novo;
	dbi reg;
	if (arq != NULL)
	{
		fread(&reg, sizeof(dbi), 1, arq);
		while(!feof(arq))
		{
			novo = CriaNoABB(reg.simbolo);
			insereAbb(&*raiz, novo, reg.codigo, 0);
			fread(&reg, sizeof(dbi), 1, arq);    
				
		}
		fclose(arq);
	}
}

void BuscarSimbolo(abb *raiz, char codigoprocurado[50], int *simbolo)
{
	int i=0;
	while (raiz != NULL && codigoprocurado[i] != '\0')
	{
		if (codigoprocurado[i] == '0')
			raiz = raiz -> esq;
		else
			raiz = raiz -> dir;
		i++;		
	}
	
	if (raiz != NULL) //mesmo se achar zero nao tem problema! Eh feito um IF
		*simbolo = raiz -> simbolo;
	else
		*simbolo = 0;
}
//ini e fim virao como numero de registros Ftell(arq)/sizeof()
void BuscarPalavra(FILE *arq, int simbolo, char palavra[50], int ini, int fim)
{
	int meio;
	dbi reg;
	if (ini <= fim)
	{
		meio = (ini + fim)/2;
		fseek(arq, meio*sizeof(dbi), SEEK_SET);
		fread(&reg, sizeof(dbi), 1, arq);
		if(reg.simbolo == simbolo)
			strcpy(palavra, reg.palavra);
		else
			if (simbolo> reg.simbolo)
				BuscarPalavra(arq, simbolo, palavra, meio+1,fim);
			else
				BuscarPalavra(arq, simbolo, palavra, ini, meio-1);
	}
	else
		strcpy(palavra, "");
	
}

int obterBit(struct bits bi, int posicao) {
	int retorno=0;
    switch(posicao) {
        case 0: retorno = bi.b0; break;
        case 1: retorno = bi.b1; break;
        case 2: retorno = bi.b2; break;
        case 3: retorno = bi.b3; break;
        case 4: retorno = bi.b4; break;
        case 5: retorno = bi.b5; break;
        case 6: retorno = bi.b6; break;
        case 7: retorno = bi.b7; break;
    }
    return retorno;
}

void decodificarTexto() {
    FILE *arqBin = fopen("codificar.dat", "rb");
    FILE *arqTab = fopen("tabela.dat", "rb");
    byte byte;
    char codigoAcumulado[50],simboloEncontrado[50];
    int lenStr, i, bit, simbolo_arvore, fim_arqTab;

    abb *raiz=NULL;
    fseek(arqTab, 0, SEEK_END);
    fim_arqTab = ftell(arqTab)/sizeof(dbi);
    	
    CriarABB(&raiz);
    if (arqBin != NULL && raiz != NULL) {
    	strcpy(codigoAcumulado, "");
	    printf("\n--- Texto Decodificado ---\n");
	    fread(&byte.num, sizeof(unsigned char), 1, arqBin);
	    while (!feof(arqBin)) {
	        
	        for (i = 0; i < 8; i++) {
	            bit = obterBit(byte.bi, i);
	            lenStr = strlen(codigoAcumulado);
	            codigoAcumulado[lenStr] = bit + '0';
	            codigoAcumulado[lenStr + 1] = '\0';
	
				BuscarSimbolo(raiz, codigoAcumulado, &simbolo_arvore);
	            if (simbolo_arvore != 0) {
	            	BuscarPalavra(arqTab, simbolo_arvore, simboloEncontrado, 0, fim_arqTab);
	                printf("%s", simboloEncontrado);
	                strcpy(codigoAcumulado, "");
	            }
	        }
	        fread(&byte.num, sizeof(unsigned char), 1, arqBin);
	    }
	    printf("\n---------------------------\n");
	
	    fclose(arqBin);
	    fclose(arqTab);
    }
}

int main (){
	decodificarTexto();
	getch();
	return 0;
}
