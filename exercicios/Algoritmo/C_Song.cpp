#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    // Otimização de I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;

    int n;
    cin >> n;

    vector<vector<bool>> valid(26, vector<bool>(26, false));

    for (int i = 0; i < n; i++) {
        char u, v;
        cin >> u >> v;
        valid[u - 'a'][v - 'a'] = true;
    }

    bool is_beautiful = true;

    for (size_t i = 0; i + 1 < s.length(); i++) {
        int u = s[i] - 'a';
        int v = s[i + 1] - 'a';

        if (!valid[u][v]) {
            is_beautiful = false;
            break; 
        }
    }

    if (is_beautiful) {
        cout << "SIM\n";
    } else {
        cout << "NAO\n";
    }

    return 0;
}