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
    vector<int> v;
    //v.push_back();
    //v.size();
    //v[i]
    //vector<int> x(5,0) >> vetor de tamanho 5 com todos elementos preenchidos com 0
    cin >> t;
    while(t--){        
        int len;
        cin >> len;
        vector <int> v(len);
        int x, aux = 0;
        while(aux < len){            
            cin >> num;
            v[aux] = num;          
            aux++;
        }

        sort(v.begin(), v.end());

        int alvo, qtd = 0;
        for(int i=0; i<len && qtd<3; i++)
        {
            if (alvo != v[i])
            {
                alvo = v[i];
                qtd = 1;                                
            }
            else
                qtd++;                
        }

        if (qtd == 3)
            cout << alvo << "\n";
        else
            cout << -1  << "\n";        
    }

    return 0;
}