#include<stdio.h>

int main (){
	int Num, n, m, h, aux;
	scanf("%d", &Num);
	int i=0;
	while(i<Num){
		scanf("%d%d%d", &n, &m, &h);
		int vet[n];
		int vetaux[n];
		
		for(int x=0; x<n;x++)
		{
			scanf("%d", &vet[x]);
			vetaux[x] = vet[x];
		}

		int c, b;
		for (aux =0;aux<m;aux++){
			scanf("%d%d", &b, &c);
			vet[b-1] = vet[b-1] + c;
			if (vet[b-1] > h)//ultrapassou
			{
				for(int x=0; x<n;x++)
					vet[x] = vetaux[x];
			}
		}
		for(aux=0; aux<n;aux++)	
			printf("%d ", vet[aux]);		
		i++;	
	}
}
