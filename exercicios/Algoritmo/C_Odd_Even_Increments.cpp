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
        int len;
        cin >> len;
        vector <int> v;
        int x, aux = 0;
        while(aux < len){            
            cin >> num;
            v.push_back(num);        
            aux++;
        }

        int consegue=1;
        int par=-1, imp=-1;
        for(int i=0; i < v.size(); i++)
        {
            if (i%2==0)//par
            {
                if (par==-1)
                    par = v[i]%2==0? 0 : 1; //todos os indices pares deverao 0 (par) ou 1 (impar)
                if (par==0 && v[i]%2==1)
                {
                    consegue=0;
                    break;
                }
                else if (par==1 && v[i]%2==0)
                {
                    consegue=0;
                    break;
                }
            }
            else
            {
                if (imp==-1)
                    imp = v[i]%2==0? 0 : 1; //todos os indices impares deverao 0 (par) ou 1 (impar)
                if (imp==0 && v[i]%2==1)
                {
                    consegue=0;
                    break;
                }
                else if (imp==1 && v[i]%2==0)
                {
                    consegue=0;
                    break;
                }
            }
        }
        if (consegue)
            cout << "YES\n";
        else
            cout << "NO\n";
    }

    return 0;
}