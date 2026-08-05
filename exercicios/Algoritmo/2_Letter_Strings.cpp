#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
using namespace std;

#define lli long long int
#define mk_p make_pair
#define fir first
#define sec second

void solve() {
    int n;
    cin >> n;

    lli cnt1[11] = {0};
    lli cnt2[11] = {0};
    lli cnt_full[11][11] = {0};

    lli soma = 0;

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;

        int c1 = s[0] - 'a'; // Converte 'a'..'k' para 0..10
        int c2 = s[1] - 'a';

        // Quantas strings já lidas diferem em APENAS 1 caractere desta?
        lli pares_validos = cnt1[c1] + cnt2[c2] - (2 * cnt_full[c1][c2]);

        soma += pares_validos;

        // Atualiza as contagens para as próximas strings
        cnt1[c1]++;
        cnt2[c2]++;
        cnt_full[c1][c2]++;
    }

    cout << soma << "\n";
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