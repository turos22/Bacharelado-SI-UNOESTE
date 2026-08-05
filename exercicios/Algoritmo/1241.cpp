#include <stdio.h>
#include <string.h>
#define TF 1000
 
int main() {
 
    /**
     * Escreva a sua solução aqui
     * Code your solution here
     * Escriba su solución aquí
     */
	
	int i, j, k, ents, totalB, comecoA, dif;
	char A[TF], B[TF];
	
	scanf("%d", &ents);
	
	for (k = 0; k < ents; k++)
	{
		scanf("%s %s", &A, &B);
		totalB = strlen(B);
		if (strlen(A) == strlen(B))
			comecoA =0;
		else
			comecoA = strlen(A) - strlen(B);
		
		dif = 0;
		for (i = 0; i < totalB && dif == 0; i++)
		{
			if(A[comecoA] != B[i])
				 dif +=1;
			comecoA++;
		}
		
		if (i == totalB)
			printf("encaixa\n");
		else
			printf("nao encaixa\n");
			
		
	}

 
    return 0;
}
