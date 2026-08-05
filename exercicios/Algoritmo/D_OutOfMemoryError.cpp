#include<stdio.h>
#define TF 200005

int main()
{
    int t;
    scanf("%d", &t);
    while(t>0)
    {
        int n=0,m,h;
        scanf("%d%d%d", &n,&m,&h);
        int v1[TF], v2[TF], v3[TF];

        for (int x=0; x<n;x++)
        {
            scanf("%d", &v1[x]);
            v2[x] = v1[x];
            v3[x] = -1;
        }

        int ultimo_reset=0;
        for (int y=0; y<m;y++)
        {
            int b,c;
            scanf("%d%d", &b,&c);
            b--;
            if (ultimo_reset > v3[b]){
                v2[b] = v1[b]; //ele faz isso para o caso de outros elementos
                // que nao sao resetados automaticamente no reset
                //exemplo: [5,2,1]
                // caso o 2 estoure, ele deve permanecer 2
                // e o 5 deve voltar para com0o era antes
            }
            v3[b] = y;
            v2[b] += c;
            if (v2[b] > h){
                v2[b]=v1[b];
                ultimo_reset =y;
            }
        }
        for (int x=0; x<n; x++)
        {
            int val;
            if (ultimo_reset > v3[x]){ //caso o valor tenha mudado ANTES do reset
                printf("%d ", v1[x]);
            }
            else
                printf("%d ", v2[x]);
        }
        printf("\n");
        t--;
    }
    return 0;
}