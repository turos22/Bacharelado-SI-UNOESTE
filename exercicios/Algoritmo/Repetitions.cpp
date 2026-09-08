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

    string s;
    cin >> s;
    char c = s[0];
    int count = 1;
    int maior = 0;
    for (lli i = 1; i < s.length(); i++){
        if (s[i] == c){
            count++;
        } else {
            //cout << c << count;
            if (count > maior){
                maior = count;
            }
            c = s[i];
            count = 1;
        }
    }
    if (count > maior){
        maior = count;
    }

    cout << maior << endl;

    return 0;
}