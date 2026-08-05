#include <iostream>
#include <string>

using namespace std;

void solve() {
    int len;
    string entrada;
    cin >> len >> entrada;

    for (int i = 0; i < len; i++) {
        if (entrada[i] == 'W') continue;

        // Se chegou aqui, encontramos o começo de um bloco (um 'B' ou 'R')
        bool tem_b = false;
        bool tem_r = false;
        int j = i;

        while (j < len && entrada[j] != 'W') {
            if (entrada[j] == 'B') tem_b = true;
            if (entrada[j] == 'R') tem_r = true;
            j++;
        }

        if (!tem_b || !tem_r) {
            cout << "NO\n";
            return; 
        }

        i = j - 1; 
    }
    cout << "YES\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}