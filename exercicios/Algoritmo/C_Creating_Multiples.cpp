#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
using namespace std;

#define lli long long int
#define ll long long
#define mk_p make_pair
#define fir first
#define sec second

#include <iostream>
#include <vector>
#include <string>


using namespace std;

ll binpow_mod(ll base, ll exp, ll mod) {
    base %= mod;
    ll result = 1;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ll b, l;
    cin >> b >> l;

    vector<ll> digitos(l); 
    ll mod = b + 1;

    ll resto = 0;
    for (ll i = 0; i < l; i++) {
        cin >> digitos[i];
        ll expoente = l - 1 - i;             
        ll pot = binpow_mod(b, expoente, mod); 
        resto = (resto + digitos[i] * pot) % mod;
    }
    resto %= mod;
    if (resto < 0) resto += mod;

    if (resto == 0) {
        cout << 0 << " " << 0 << "\n";
        return 0;
    }

    ll r  = resto;
    ll r2 = mod - resto;

    for (ll i = 0; i < l; i++) {
        ll expoente = l - 1 - i;
        ll delta = (expoente % 2 == 0) ? r : r2;

        if (delta >= 1 && delta <= digitos[i]) {
            cout << (i + 1) << " " << (digitos[i] - delta) << "\n";
            return 0;
        }
    }

    cout << -1 << " " << -1 << "\n";
    return 0;
}