#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

const int MAXN = 100005;

vector<int> adj[MAXN];

int topico_do_no[MAXN];

int tempo_entrada[MAXN];
int tempo_saida[MAXN];

int timer = 0;

map<int, vector<int>> topico_para_tempos;

void dfs(int u, int p) {
    timer++;
    tempo_entrada[u] = timer;
    topico_para_tempos[topico_do_no[u]].push_back(timer);

    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
        }
    }

    tempo_saida[u] = timer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    for (int i = 1; i <= n; i++) {
        cin >> topico_do_no[i];
    }

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, 0);

    // Processamento das Q consultas
    while (q--) {
        int x, k;
        cin >> x >> k;

        int L = tempo_entrada[x];
        int R = tempo_saida[x];

        // CASO 1: O tópico K nem sequer existe na empresa toda
        if (topico_para_tempos.find(k) == topico_para_tempos.end()) {
            cout << 0 << "\n";
            continue;
        }

        const auto& lista_tempos = topico_para_tempos[k];
        auto it_inicio = lower_bound(lista_tempos.begin(), lista_tempos.end(), L);
        auto it_fim = upper_bound(lista_tempos.begin(), lista_tempos.end(), R);

        cout << (it_fim - it_inicio) << "\n";
    }

    return 0;
}