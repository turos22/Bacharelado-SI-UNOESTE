#include <bits/stdc++.h>
using namespace std;

#define lli long long int
#define mk_p make_pair
#define fir first
#define sec second

int main (){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t, num;
    cin >> t;
    while(t--){
        cin >> num;
        char saida;
        if (num <=1399)
            saida = '4';
        else if (num <= 1599)
            saida = '3';
        else if (num <= 1899)
            saida = '2';            
        else
            saida = '1';
        cout << "Division " << saida << "\n";
    }
    return 0;
}