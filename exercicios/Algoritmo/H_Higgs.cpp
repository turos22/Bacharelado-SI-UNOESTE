#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

struct Aresta {
    int to;
    int h;
};

int N, M, K;
vector<vector<Aresta>> adj;

// Função que TESTA se um valor H é possível usando 0-1 BFS
bool checar(int H) {
    vector<int> subornos(N + 1, 1e9);
    deque<int> dq;

    subornos[1] = 0;
    dq.push_back(1);

    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();

        if (u == N) break;

        for (auto& edge : adj[u]) {
            int v = edge.to;
            int peso = (edge.h > H) ? 1 : 0; // Se h > H, precisa de 1 suborno

            if (subornos[u] + peso < subornos[v]) {
                subornos[v] = subornos[u] + peso;
                if (peso == 0) {
                    dq.push_front(v); // Peso 0 vai pra frente da fila
                } else {
                    dq.push_back(v);  // Peso 1 vai pro final da fila
                }
            }
        }
    }

    // Se o total de subornos para chegar em N for <= K, o valor H FUNCIONA!
    return subornos[N] <= K;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> N >> M >> K)) return 0;

    adj.resize(N + 1);
    int max_h = 0;

    for (int i = 0; i < M; i++) {
        int u, v, h;
        cin >> u >> v >> h;
        adj[u].push_back({v, h});
        adj[v].push_back({u, h});
        max_h = max(max_h, h);
    }

    // BUSCA BINÁRIA NA RESPOSTA (O "chute inteligente")
    int L = 0, R = max_h;
    int ans = max_h;

    while (L <= R) {
        int mid = L + (R - L) / 2;

        if (checar(mid)) {
            ans = mid;     // Deu certo! Guarda esse valor
            R = mid - 1;   // Mas tenta achar um Nível H ainda MENOR
        } else {
            L = mid + 1;   // Deu errado! Precisa de um Nível H MAIOR
        }
    }

    cout << ans << "\n";

    return 0;
}