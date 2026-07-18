#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define TF 100
 
int main() {
 
    /**
     * Escreva a sua solução aqui
     * Code your solution here
     * Escriba su solución aquí
     */
 	
 	
 	int deslg[TF], ultimo_num, proximo_num, Num, d, m, operacoes, i, j, cont, n_achou, pos;
 	
 	scanf("%d", &Num);
 	while (Num != 0)
 		{	
 			m = 0;
 			while (m < 300 && ultimo_num != 13)
 			{
 				m +=1;
 				for(i = 0; i < Num; i++)
 					deslg[i] = 0;
 				d = 0;
 				ultimo_num = 0;
 				proximo_num = 1;
 				ultimo_num = proximo_num;
 				operacoes = Num-1;
 				while(operacoes != 0)
 				{	
					deslg[d] = ultimo_num;
					d += 1;
					cont = m;
					while(cont != 0)
						{	
							n_achou = 0;
							while (n_achou == 0)
							  {
							  	if (proximo_num + 1 > Num)
							  		proximo_num = 1;
							  	else
							  		proximo_num +=1;
							  	pos = 0;
							  	for (j = 0; j < Num && deslg[j] != proximo_num; j++)
							  		pos++;
							  	if (pos == Num)	
							  		{
							  			cont = cont -1;
							  			n_achou = 1;	
							  		}	
							  }		
						}
					ultimo_num = proximo_num;
					operacoes = operacoes - 1;	
 				}
 				
 			}
 			printf("%d\n", m);
 			ultimo_num = 0;
 			scanf("%d", &Num);		
 		}
 	
 	
 	
 	
    return 0;
}
