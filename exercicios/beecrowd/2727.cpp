#include <stdio.h>
#include <string.h>
#define TF 37
 
int main() {
 
    /**
     * Escreva a sua solução aqui
     * Code your solution here
     * Escriba su solución aquí
     */
 
 	char t[TF];
 	int i, ent, espacos, total_pontos, j;
 	
 	while (scanf("%d", &ent) != EOF)
 	{	getchar();
 		for (i = 0; i < ent; i++)
 			{
 				gets(t);
 				espacos = 0;
 				total_pontos = 0;
				for(j = 0; j < strlen(t); j++)
					if (t[j] == ' ')
						{
							espacos++;
							if (total_pontos == 0)
								total_pontos = j;
						}
				if (total_pontos == 0)
					total_pontos = strlen(t);
				
				printf("%c\n", 96 + total_pontos + espacos * 3);
								
 			}
 	}
 	
 
     return 0;
}
