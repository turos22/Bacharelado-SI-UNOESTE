#include <stdio.h>
#include <string.h>
#include <stdlib.h>
# define TF 1000
 
int main() {
 
    /**
     * Escreva a sua solução aqui
     * Code your solution here
     * Escriba su solución aquí
     */
 	int e, d;
 	
 	scanf("%d %d", &e, &d);
 	
 	if (e > d)
 		printf("Eu odeio a professora!\n");
 	else
	  if ((d - e) >= 3)
	  		printf("Muito bem! Apresenta antes do Natal!\n");
	  else
	  	{
	  		printf("Parece o trabalho do meu filho!\n");
	  		if ((e + 2) >= 24)
	  			printf("Fail! Entao eh nataaaaal!\n");
	  		else
	  			printf("TCC Apresentado!\n");
	  	}
 		
 
    return 0;
}
