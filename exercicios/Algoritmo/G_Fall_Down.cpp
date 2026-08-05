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

void solve(int n, int m, vector<string>& strs) {
    for (int j = 0; j < m; j++) {
        int ultima_livre = n - 1;
        for (int i = n - 1; i >= 0; i--) {
            if (strs[i][j] == 'o') {
                ultima_livre = i - 1;
            } 
            else if (strs[i][j] == '*') {
                strs[i][j] = '.';
                strs[ultima_livre][j] = '*';
                ultima_livre--;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        cout << strs[i] << '\n';
    }
}
int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t;
    cin >> t;
    while(t--){
        int n,m;
        cin >> n >> m;
        vector <string> strs;
        for (int i= 0; i<n; i++)
        {
            string s;
            cin >> s;
            strs.push_back(s);
        }
        solve(n, m, strs);
        cout << '\n';
    }

    return 0;
}