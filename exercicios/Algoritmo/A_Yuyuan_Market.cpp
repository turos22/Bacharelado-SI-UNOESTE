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
    int a, b;
    bool operator<(const P& other) const {
        if(this->a != other.a) return this->a < other.a;
        return this->b > other.b;
    }
    ll cost() const {return this->b-this->a;}
};

int n, a[2*maxN];
std::vector<P> pairs;
int main() {
    scanf("%d", &n);
    for(int i = 0; i < 2*n; i++) scanf("%d", a+i);
    pairs.assign(n+1, {INF,INF});
    for(int i = 0; i < 2*n; i++) {
        if(pairs[a[i]].a == INF) pairs[a[i]].a = i;
        else pairs[a[i]].b = i;
    }
    
    std::sort(pairs.begin(), pairs.end(), [&](P a, P b){if(a.b != b.b) return a.b < b.b; return a.cost() < b.cost();});

    int r = pairs[0].b, q = 1;
    ll c = pairs[0].cost();
    for(int i = 1; i < n; i++) {
        if(pairs[i].a > r) {
            r = pairs[i].b;
            q++;
            c += pairs[i].cost();
        }
    }

    printf("%d %lld\n", q, c);
    return 0;
}