#include <bits/stdc++.h>
using namespace std;
#define lli long long

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    lli n, m, k;
    cin >> n >> m >> k;

    lli N = n + k;
    vector<vector<pair<lli,lli>>> adj(N + 1); 

    for (lli i = 0; i < m; i++){
        lli u, v, c;
        cin >> u >> v >> c;
        adj[u].push_back({v, c});
        adj[v].push_back({u, c});
    }

    for (lli cidade = 1; cidade <= n; cidade++){
        lli qtd;
        cin >> qtd;
        for (lli y = 0; y < qtd; y++){
            lli tipo, custo;
            cin >> tipo >> custo;
            lli noTipo = n + tipo;
            adj[cidade].push_back({noTipo, custo}); // pagar pra "entrar" no canal do tipo
            adj[noTipo].push_back({cidade, 0});      // sair de graça em qualquer cidade com esse tipo
        }
    }

    vector<lli> dist(N + 1, LLONG_MAX);
    priority_queue<pair<lli,lli>, vector<pair<lli,lli>>, greater<>> pq;
    dist[1] = 0;
    pq.push({0, 1});

    while (!pq.empty()){
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue; 
        for (auto &[v, w] : adj[u]){
            if (dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    cout << dist[n] << "\n";
    return 0;
}