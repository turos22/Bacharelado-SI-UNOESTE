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
    while(num != 1){
        if (num % 2 == 0){
            cout << num << " ";
            num /= 2;
        }
        else{
            cout << num << " ";
            num = (num * 3) + 1;
        }
    }
    cout << 1 << " ";

    return 0;
}