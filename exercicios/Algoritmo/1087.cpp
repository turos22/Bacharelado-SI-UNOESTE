#include <stdio.h>
# define TF 20
 
int main() {
 
    /**
     * Escreva a sua solução aqui
     * Code your solution here
     * Escriba su solución aquí
     */
 
 
  int x1, x2, y1, y2, i, dx, dy, j, achou;
 
  scanf ("%d%d%d%d", &x1,&y1,&x2,&y2);
  while (x1 != 0 && x2 != 0 && y1 != 0 && y2 != 0)
 {
	 dx = x1 - x2;
	 dy = y1 - y2;
	 
	 if (dx < 0)
	 	dx = -dx;
	if (dy < 0)
		dy = -dy;
	//verificação das diagonais
	
	
	if (x1 == x2 && y1 == y2)
		printf("0\n");
	else
		if (x1 == x2 || y1 == y2)
			printf("1\n");
		else
			if (dx == dy)
				printf("1\n");
			else
				printf("2\n");
		
	scanf("%d%d%d%d", &x1,&y1,&x2,&y2);
 }

 return 0;

