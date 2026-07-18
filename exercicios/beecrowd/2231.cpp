#include <stdio.h>
#define TF 10000
 
int main() {
 
    /**
     * Escreva a sua solução aqui
     * Code your solution here
     * Escriba su solución aquí
     */
     
    int i, TL,  N, M, vet[TF], media_maior, media_menor, pos_media, i_controle = 0, media, z, soma;
    
    scanf("%d%d", &N, &M);
    while(N > 0 && M > 0)
    {
    	i = 0;
    	TL = 0;
    	for(i = 0; i < N; i++)
    	{
    		scanf("%d", &vet[i]);
    		TL++;
    	}
    	
			
		pos_media = M -1;
	  	for(i = 0; i < TL && i <= TL - M; i++)
    	{
    		soma = 0;
    		for (z = i; z <= i + pos_media; z++)
    			soma = soma + vet[z]; 
    		
			media = soma/M;
			
			if (i == 0)
			{
				media_maior = media;
				media_menor = media;	
			}
			else
			{
				if (media_maior < media)
					media_maior = media;
			    if (media_menor > media)
					media_menor = media;	
			}
			
    	}
    	
    	printf("Teste %d\n", i_controle + 1);
    	printf("%d %d\n\n", media_menor, media_maior);
    	
    	i_controle++;
    	
    	scanf("%d%d", &N, &M);
    	
    }
 
    return 0;
}
