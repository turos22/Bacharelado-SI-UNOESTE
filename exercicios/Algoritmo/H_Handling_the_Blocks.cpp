#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Block {
    int num;
    int color;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, K;
    if (!(cin >> N >> K)) return 0;

    vector<Block> blocks(N);
    vector<int> original_colors(N);

    for (int i = 0; i < N; ++i) {
        cin >> blocks[i].num >> blocks[i].color;
        original_colors[i] = blocks[i].color;
    }

    sort(blocks.begin(), blocks.end(), [](const Block& a, const Block& b) {
        return a.num < b.num;
    });

    for (int i = 0; i < N; ++i) {
        if (blocks[i].color != original_colors[i]) {
            cout << "N\n";
            return 0;
        }
    }

    cout << "Y\n";
    return 0;
}