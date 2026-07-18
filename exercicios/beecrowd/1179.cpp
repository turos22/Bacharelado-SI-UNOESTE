#include <stdio.h>
#define TF 5
 
int main() {
 
    /**
     * Escreva a sua solução aqui
     * Code your solution here
     * Escriba su solución aquí
     */
 	int vetP[TF], vetI[TF], i, ent, par, imp, j, teste;
 	
 	par = 0;
 	imp = 0;
 	for (i = 0; i < 15; i++)
 	{
 		scanf("%d", &ent);
 		teste = ent %2;
 		if (ent % 2 == 1 || ent % 2 == -1)
 		{
 			if (imp < TF -1)
 			{
 				vetI[imp] = ent;
 				imp++;
 			}
 			else
 			{
 				vetI[imp] = ent;
 				imp++;
 				for (j = 0; j < imp; j++)
 					printf("impar[%d] = %d\n", j, vetI[j]);
 				imp = 0;
 			}
 		}
 		else
 		{
 			if (par < TF -1)
 			{
 				vetP[par] = ent;
 				par++;
 			}
 			else
 			{
 				vetP[par] = ent;
 				par++;
 				for (j = 0; j < par; j++)
 					printf("par[%d] = %d\n", j, vetP[j]);
 				par = 0;
 			}	
 		}
 	}
 	
	if (imp > 0) 	
		for(i = 0; i < imp; i++)
			printf("impar[%d] = %d\n", i, vetI[i]);
	
	if (par > 0) 	
		for(i = 0; i < par; i++)
			printf("par[%d] = %d\n", i, vetP[i]);
		
    return 0;
}
