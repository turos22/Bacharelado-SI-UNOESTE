#include<stdio.h>
#define TF 200005
int BuscaBinaria(int vet[], int ini, int fim, int x){
    if(ini>fim)return-1;
    int meio = (ini+fim)/2;
    if (vet[meio]==x)return meio;
    if (vet[meio]>x)return BuscaBinaria(vet, ini, meio-1, x);
    return BuscaBinaria(vet, meio+1, fim, x);
}
int main (){
    int t; 
    scanf("%d", &t);
    while(t>0){
        int n,m,k;
        scanf("%d%d%d", &n, &m, &k);
        int a[TF], b[TF]; //a para robos e b para espinhos

        for (int x=0; x<n; x++){
            scanf("%d", &a[x]);
            int y=x;
            while(y>0 && a[y]<a[y-1]){
                int aux = a[y];
                a[y] = a[y-1];
                a[y-1] = aux;
                y--;
            }
        }

        for (int x=0; x<m; x++){
            scanf("%d", &b[x]);
            int y=x;
            while(y>0 && b[y]<b[y-1]){
                int aux = b[y];
                b[y] = b[y-1];
                b[y-1] = aux;
                y--;
            }
        }
        int rb_vivo = n;
        for (int x=0; x<k;x++){
            char mov;
            scanf(" %c", &mov);
            if (rb_vivo==0){printf("0 ");continue;}
            if (mov=='L'){
                for (int x=0; x<n; x++){
                    a[x]--;
                    if (BuscaBinaria(b, 0, m-1, a[x])>-1){
                        rb_vivo--;
                    }
                }
            }
            else if (mov=='R'){
                for (int x=0; x<n; x++){
                    a[x]++;
                    if (BuscaBinaria(b, 0, m-1, a[x])>-1){
                        rb_vivo--;
                    }
                }
            }
            printf("%d ", rb_vivo);
        }
        printf("\n");
    

        t--;
    }
}

