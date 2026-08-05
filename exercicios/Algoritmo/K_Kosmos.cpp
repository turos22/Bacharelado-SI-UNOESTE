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

constexpr int mtxM = 2;
void multiply(ll F[mtxM][mtxM], ll M[mtxM][mtxM]) {
    ll R[mtxM][mtxM] = {0};
    for (int i = 0; i < mtxM; ++i)
        for (int j = 0; j < mtxM; ++j)
            for (int k = 0; k < mtxM; ++k)
                R[i][j] = (R[i][j] + F[i][k] * M[k][j])%(MOD-1);

    for (int i = 0; i < mtxM; ++i)
        for (int j = 0; j < mtxM; ++j)
            F[i][j] = R[i][j];
}

void mtxexp(ll F[mtxM][mtxM], ll n) {
    if (n == 0 || n == 1) return;
    ll M[mtxM][mtxM], R[mtxM][mtxM] = { {1,0}, {0,1} };
    
    for (int i = 0; i < mtxM; ++i)
        for (int j = 0; j < mtxM; ++j)
            M[i][j] = F[i][j];

    while(n) {
        if (n&1) multiply(R, M);
        multiply(M, M);
        n >>= 1;
    }

    for(int i = 0; i < mtxM; i++)
        for(int j = 0; j < mtxM; j++)
            F[i][j] = R[i][j];
}

ll fib(ll n) {
    if (n == 0) return 0;
    ll F[mtxM][mtxM] = { { 1, 1 }, { 1, 0 } };
    mtxexp(F, n - 1);
 
    return F[0][0]%(MOD-1);
}

int t, q, k, m;
ll n;
int main() {
    scanf("%lld", &n);
    ll f = fib(n);
    printf("%lld\n", binpow(2, f));
    return 0;
}