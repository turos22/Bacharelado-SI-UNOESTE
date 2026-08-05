#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
#include <queue>
#include <algorithm>
#include <map>
#include <array>
#include <set>
#include <string.h>
#include <bitset>
#include <numeric>
#include <unordered_set>
#include <random>
#include <chrono>

using ll = long long;
using pll = std::pair<ll,ll>;
using pii = std::pair<int,int>;
constexpr int maxN = 1e5+4, maxLOG = 20, INF = 1e9+2, MOD = 998244353;
constexpr ll LLINF = 1e18;
constexpr double PI = 3.14159265358979323846;
constexpr double DEG2RAD = PI/180.0;

using i128 = ll;

#define f_io() \
    std::ios::sync_with_stdio(0);
 
#ifndef ONLINE_JUDGE
#define DEBUG_H
#include "Debug.h"
#else
    #define dbgf(fmt, x)
    #define p_vi(v)
    #define dbgvi(v)
    #define dbgmi(mtx, rows)
    #define p_v(v)
    #define dbgv(v)
    #define dbgm(m)
    #define dbg(...)
    #define dbg2(...)
    #define dbgbin(n)
#endif

int msb(ll x) {
    for(int i = 63; i >= 0; i--)
        if(x&(1LL<<i)) return i;
}

ll binpow(ll base, ll exp) {
    ll res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return res;
}

ll modinv(ll x) { // Fernat's Little Theorem
    return binpow(x, MOD - 2)%MOD;
}

constexpr ll inv2 = (MOD+1)>>1;

struct P {
    ll a, b;
    bool operator<(const P& other) const {
        if(this->a != other.a) return this->a < other.a;
        return this->b > other.b;
    }
};

int t, q, k, m, n;
std::vector<int> adj[maxN];
int main() {
    scanf("%d%d", &n, &m);
    
    int a, b;
    for(int i = 0; i < m; i++) {
        scanf("%d%d", &a, &b);
        if(a == b) { puts("IMPOSSIVEL"); return 0; }
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    int c[maxN] = {};
    memset(c, -1, sizeof(c));
    std::set<int> bag[2];
    auto bfs = [&](int start) -> bool {
        std::queue<int> q;
        q.push(start);
        c[start] = 0;
        while(!q.empty()) {
            int node = q.front();
            q.pop();
            //dbg(node);
            for(int e : adj[node]) {
                //printf("%d => %d\n", node, e);
                //if(c[e] == c[node]) continue;
                if(c[e] != -1) continue;
                //else if(c[e] != -1 && c[e] != c[node]) return false;
                q.push(e);
                c[e] = !c[node];
            }
        }
        return true;
    };

    for(int i = 1; i <= n; i++)
        if(c[i] == -1)
            if(!bfs(i)) { puts("IMPOSSIVEL"); return 0; }
    
    for(int i = 1; i <= n; i++) bag[c[i]].insert(i);

    for(int i : bag[1])
        for(int e : adj[i]) if(bag[1].find(e) != bag[1].end()) { puts("IMPOSSIVEL"); return 0; }

    for(int i : bag[0]) if(bag[1].find(i) != bag[1].end()) { puts("IMPOSSIVEL"); return 0; }
    
    for(int i : bag[0])
        for(int e : adj[i]) if(bag[0].find(e) != bag[0].end()) { puts("IMPOSSIVEL"); return 0; }

    puts("POSSIVEL");
    printf("%lld %lld\n", bag[0].size(), bag[1].size());
    for(int i : bag[0]) printf("%d ", i); putchar('\n');
    for(int i : bag[1]) printf("%d ", i);

    return 0;
}