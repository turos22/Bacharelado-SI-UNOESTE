#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
using namespace std;

#define lli long long int
#define mk_p make_pair
#define fir first
#define sec second

#include <iostream>
#include <vector>
#include <string>


using namespace std;

int main (){
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m, saida=-1;
    cin >> n >> m;
    for (int i = 0; i < n; i++){
        int num;
        cin >> num;
        if (saida == -1  && num >= m)
            saida = i+1;
    }

    cout << saida << endl;


    return 0;
}
