#include <iostream>
#include <vector>

using namespace std;

#define lli long long int

void solve() {
    int n;
    lli k;
    cin >> n >> k;
    vector<int> zeros(31, 0);

    for (int i = 0; i < n; i++) {
        lli x;
        cin >> x;
        for (int j = 30; j >= 0; j--) {
            if (!((x >> j) & 1)) {
                zeros[j]++;
            }
        }
    }

    lli ans = 0;

    for (int j = 30; j >= 0; j--) {
        if (k >= zeros[j]) {
            k -= zeros[j];
            ans |= (1LL << j);
        }
    }

    cout << ans << "\n";
}

int main() {
    // ESSENCIAIS para evitar TLE por I/O:
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}