#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
using namespace std;

#define lli long long int
#define mk_p make_pair
#define fir first
#define sec second

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t, num;
    cin >> t;
    while(t--){
       vector <int> v;
       cin >> num;
       for(int i=0; i<num; i++){
           int aux;
           cin >> aux;
           v.push_back(aux);
       }

       int p1 = 0;
       int p2 = num-1;
       int peso_doces1 = 0;
       int peso_doces2 = 0;
       int maior_doces_juntos=0;
       while(p1 < p2){
        //Se for igual, eu ando ambos
        //se for diferente, eu ando APENAS o menor
        if (peso_doces1 == 0 &&peso_doces1 == peso_doces2){ //primeira vez no laco
            peso_doces1 = v[p1];
            peso_doces2 = v[p2];    
        }
        if (peso_doces1 > peso_doces2)
        {
            p2--;
            peso_doces2 += v[p2];
        }
        else
            if(peso_doces1 < peso_doces2){
                p1++;
                peso_doces1 += v[p1];
            }
            else{
                maior_doces_juntos = p1+1 + (num-p2);
                p1++; p2--;
                peso_doces1 += v[p1];
                peso_doces2 += v[p2];
            } 
       }
       cout << maior_doces_juntos << '\n';
    }
}