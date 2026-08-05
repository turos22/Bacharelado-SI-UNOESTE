#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define lli long long int

const int MAXN = 1e6 + 5; // N pode ir ate 10^6 segundo a imagem!

vector<lli> vet;
lli st_min[4 * MAXN];
lli st_max[4 * MAXN];

void build(int p, int l, int r) {
    if (l == r) {
        st_min[p] = vet[l];
        st_max[p] = vet[l];
        return;
    }
    int mid = (l + r) / 2;
    build(2 * p, l, mid);
    build(2 * p + 1, mid + 1, r);
    st_min[p] = min(st_min[2 * p], st_min[2 * p + 1]);
    st_max[p] = max(st_max[2 * p], st_max[2 * p + 1]);
}

void update(int p, int l, int r, int pos, lli val) {
    if (l == r) {
        vet[pos] = val;
        st_min[p] = val;
        st_max[p] = val;
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid)
        update(2 * p, l, mid, pos, val);
    else
        update(2 * p + 1, mid + 1, r, pos, val);

    st_min[p] = min(st_min[2 * p], st_min[2 * p + 1]);
    st_max[p] = max(st_max[2 * p], st_max[2 * p + 1]);
}

lli query_min(int p, int l, int r, int ql, int qr) {
    if (qr < l || r < ql) return 2e18; // Infinito positivo
    if (ql <= l && r <= qr) return st_min[p];
    int mid = (l + r) / 2;
    return min(query_min(2 * p, l, mid, ql, qr), query_min(2 * p + 1, mid + 1, r, ql, qr));
}

lli query_max(int p, int l, int r, int ql, int qr) {
    if (qr < l || r < ql) return -2e18; // Infinito negativo
    if (ql <= l && r <= qr) return st_max[p];
    int mid = (l + r) / 2;
    return max(query_max(2 * p, l, mid, ql, qr), query_max(2 * p + 1, mid + 1, r, ql, qr));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vet.resize(n);
    for (int i = 0; i < n; i++) cin >> vet[i];

    build(1, 0, n - 1);

    int m;
    cin >> m;
    while (m--) {
        int q, l, r;
        cin >> q >> l >> r;
        if (q == 1) {
            lli menor = query_min(1, 0, n - 1, l - 1, r - 1);
            lli maior = query_max(1, 0, n - 1, l - 1, r - 1);

            if (menor == maior) {
                cout << "draw\n";
            } else {
                cout << "wins\n"; // MDC sempre sera menor que MMC se houverem elementos diferentes
            }
        } else {
            update(1, 0, n - 1, l - 1, r);
        }
    }

    return 0;
}