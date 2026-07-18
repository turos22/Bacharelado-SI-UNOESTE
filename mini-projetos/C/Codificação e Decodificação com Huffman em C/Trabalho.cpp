#include <stdio.h>
#include <string.h>
#include <conio2.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>

#include "registros.h"
#include "tree.h"


int main()
{
	Reg *lista=NULL, *aux;
	tree *huffman;
	InserirRegistros(&lista);
	aux = lista;
	huffman = Huffman(lista);
	printf("\n\n\n\n");
	exibetree(huffman);
	percorreSalva(huffman, lista);
	gravarArqBinario(lista);
	ExibirTabelaRegistros(lista);
	char palavra[100] = "Viver eh amar";
	codificarTexto(palavra);
	getch();
	return 0;
}
