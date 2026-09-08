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

    lli num;
    cin >> num;
    lli soma_tot = num*(num+1)/2;
    lli soma=0;
    while(num != 1){
        int n;
        cin >> n;
        soma += n;
        num--;
    }

    cout << soma_tot - soma << endl;


    return 0;
}