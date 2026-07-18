
struct tree
{
	struct tree *dir;
	struct tree *esq;
	int freq, simbolo;
};
typedef struct tree tree;

struct lista_tree
{
	tree *info;
	struct lista_tree *prox;
};
typedef struct lista_tree ltree;

ltree *CriaArvFloresta(tree *arv)
{
	ltree *lt = (ltree*)malloc(sizeof(ltree));
	lt -> info = arv;
	lt -> prox = NULL;
	return lt;
}

tree *CriaArvore(tree *e, tree *d, int simbolo, int frequencia)
{
	tree *ar = (tree*)malloc(sizeof(tree));
	ar -> esq = e;
	ar -> dir = d;
	ar -> simbolo = simbolo;
	ar -> freq = frequencia;
	return ar;
}

void InserirFloresta(ltree **lista, tree *arv)
{
	ltree *novo = CriaArvFloresta(arv), *atual, *ant;
	if (*lista == NULL)
		*lista = novo;
	else
	{
		if((*lista) -> info -> freq < arv->freq)
		{
			novo -> prox = *lista;
			*lista = novo;
		}
		else
		{
			ant = *lista;
			atual = ant -> prox;
			while(atual!=NULL && atual -> info -> freq > arv->freq)
			{
				ant = atual;
				atual = atual -> prox;
			}
			novo -> prox = atual;
			ant -> prox = novo;
		}
	}
}

tree *removefinal(ltree **lista)
{
	ltree *aux, *ant;
	tree *retorno;
	if (*lista != NULL)
	{
		ant = NULL;
		aux = *lista;
		while(aux -> prox != NULL)
		{
			ant = aux;
			aux = aux -> prox;
		}
		retorno = aux->info;
		aux -> info = NULL;
		
		if (ant == NULL)
			*lista = NULL;
		else
			ant -> prox = NULL;
		free(aux);
		return retorno;
	}
	return NULL;
}

tree *Huffman(Reg *registros)
{
	ltree *lista=NULL;
	tree *esq, *dir, *retorno;
	while(registros != NULL)
	{
		InserirFloresta(&lista, CriaArvore(NULL, NULL, registros -> simbolo, registros -> frequencia));
		registros = registros -> prox;
	}	
	while(lista -> prox != NULL)
	{
		dir = removefinal(&lista);
		esq = removefinal(&lista);
		InserirFloresta(&lista, CriaArvore(esq,dir, 0, dir->freq + esq->freq));
	}
	retorno = lista -> info;
	lista -> info = NULL;
	free(lista);
	return retorno;
}

void exibetree(tree *tree)
{
	static int n = -1;
	int i;
	if (tree != NULL)
	{
		n++;
		exibetree(tree -> dir);
		for (i=0; i<5*n;i++)
			printf(" ");
		printf("(%d, %d)\n", tree -> simbolo, tree->freq);
		exibetree(tree->esq);
		n--;
	}
}

void salvarRegistro(int simbolo, Reg *registros, char codigo[50])
{
    Reg *aux = registros;
    while (aux != NULL && aux->simbolo != simbolo)
        aux = aux->prox;
    if (aux != NULL)
      strcpy(aux->codigo, codigo);
}

void percorreSalva(tree *tree, Reg *registros)
{
    static char codigo[50]; 
    static int t = -1;
    
    if (tree != NULL)
    {
        if (tree->esq == NULL && tree->dir == NULL)
        {
            codigo[t + 1] = '\0';
            salvarRegistro(tree->simbolo, registros, codigo);
        }
        else
        {
            t++;
            codigo[t] = '0';
            percorreSalva(tree->esq, registros); 
            codigo[t] = '1';
            percorreSalva(tree->dir, registros); 
            t--;
        }
    }
}

