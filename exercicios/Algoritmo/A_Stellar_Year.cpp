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

    vector<int> estrelas;
    int n, x;
    cin >> n >> x;
    while(n--){
        int num;
        cin >> num;
        estrelas.push_back(num);
    }

    int total = 0;
    vector <int> saidas;
    for(int i =0; i<estrelas.size();i++){
        if (x % estrelas[i] == 0 ){
            total++;
            saidas.push_back(i+1);
        }        
    }


    cout << total << '\n';
    for (int y=0; y< saidas.size(); y++){
        cout << saidas[y] << ' ';
    }

    return 0;
}
