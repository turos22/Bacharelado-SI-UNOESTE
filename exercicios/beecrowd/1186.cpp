#include <stdio.h>
#define TF 12
 
int main() {
 
    /**
     * Escreva a sua solução aqui
     * Code your solution here
     * Escriba su solución aquí
     */
     
    int i, col, j ;
    float m[TF][TF], ent, soma;
    char oper;
    
    scanf("%c %d", &oper, &col);
    
    for (i = 0; i < TF; i++)
    {
    	for(j = 0; j < TF; j++)
    	{
    		scanf("%f", &ent);
    		m[i][j] = ent;
    	}
    }
    
    soma = 0;
	for (i = 0; i < TF; i++)   
	{
		for (j = 0; j < i; j++)
		{
			soma = soma + m[i][TF - (j+1)];
		}
	}
    if (oper == 'S' || oper == 's')
    	printf("%.1f\n", soma);
    else
    	if(oper == 'M' || oper == 'm')
			printf("%.1f\n", soma/66);
    return 0;
}
