#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(NULL);

    long long qtdIng, qtdPedi, tmp, quant;
    vector<long long> ingredientes;
    stack<long long> mdc;
    cin >> qtdIng >> qtdPedi;


    cin >> tmp;
    ingredientes.push_back(tmp);
    mdc.push(tmp);

    for (long long i = 1; i < qtdIng; i++)
    {
        cin >> tmp;
        ingredientes.push_back(tmp);
        mdc.push(gcd(mdc.top(), tmp));
    }
    
    for (long long i = 0; i < qtdPedi; i++)
    {
        cin >> tmp >> quant;

        if(tmp == 1){//novo ingrediente
            ingredientes.push_back(quant);
            mdc.push(gcd(ingredientes.back(), mdc.top()));
        }else if(tmp == 2){//remoção
            while(quant--){
                ingredientes.pop_back();
                mdc.pop();
            }
        }else{//pedido
            
            if(mdc.top()%quant == 0)
                cout << "SIM\n";
            else
                cout << "NAO\n";
        }
    }
    

    return 0;
}