#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
const ll INF = 1e18;

vector<ll> saldo_por_nivel;
ll caminho(int N, int k, ll X) {
    vector<ll> result_nivel(N + 2, -INF);
    result_nivel[1] = 0;

    for (int i = 1; i <= N; i++) {
        if (result_nivel[i] == -INF) continue;

        int proximo_nivel_normal = min(N + 1, i + 1);
        result_nivel[proximo_nivel_normal] = max(
            result_nivel[proximo_nivel_normal], 
            result_nivel[i] + saldo_por_nivel[i - 1]
        );

        int proximo_nivel_salto = min(N + 1, i + k);
        result_nivel[proximo_nivel_salto] = max(
            result_nivel[proximo_nivel_salto], 
            result_nivel[i] - X
        );
    }

    return max(0LL, result_nivel[N + 1]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, k;
    ll X; 
    if (!(cin >> N >> k >> X)) return 0;

    int aux = N;
    while (N--) {
        ll monstro, energia;
        cin >> monstro >> energia;
        saldo_por_nivel.push_back(energia - monstro);
    }

    cout << caminho(aux, k, X) << '\n';

    return 0;
}