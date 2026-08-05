#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define lli long long int

const int MAXN = 1e5 + 5;
const lli INF = 2e18; 

vector<lli> vet;
lli st[4 * MAXN];

// Mudei o retorno para lli
lli build(int p, int l, int r) {
    if (l == r) return st[p] = vet[l];
    int mid = (l + r) / 2;
    return st[p] = max(build(2 * p, l, mid), build(2 * p + 1, mid + 1, r));
}

// Mudei o retorno para lli
lli query(int p, int i, int j, int l, int r) {
    if (j < l || r < i)
        return -INF;

    if (i >= l && j <= r)
        return st[p];

    int mid = (i + j) / 2;
    return max(query(p * 2, i, mid, l, r), query(p * 2 + 1, mid + 1, j, l, r));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vet.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> vet[i];
    }
    build(1, 0, n - 1);

    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << query(1, 0, n - 1, l - 1, r - 1) << '\n';
    }

    return 0;
}