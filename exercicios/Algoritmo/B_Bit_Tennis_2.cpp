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
constexpr int maxN = 3e5+4, maxLOG = 20, INF = 1e9+2, MOD = 998244353;
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
    ll a, b;
    bool operator<(const P& other) const {
        if(this->a != other.a) return this->a < other.a;
        return this->b > other.b;
    }
};

int t, q, k, m, n, x;
int main() {
    scanf("%d%d", &n, &x);
    // 2, 2, 1, 1
    // 1
    // 1, 1
    // 2
    // 1 1 2
    //int nim[maxN];
    int cnt[2] = {};
    for(int i = 0; i < n; i++) {
        scanf("%d", &k);
        int bc = __builtin_popcount(k);
        cnt[bc&1]++;
        //dbg(bc);
    }
    bool jw = (((cnt[1]&1) == (cnt[0]&1) && (cnt[0] > 0)) || (cnt[1]&1)) && cnt[1] > 0;
    puts(jw ? "Julia":"Giovana");
    return 0;
}
