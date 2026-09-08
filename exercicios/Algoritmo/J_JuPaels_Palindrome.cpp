#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    string s;
    cin >> s;

    // Guarda a PRIMEIRA vez que cada máscara apareceu.
    // Chave: máscara de bits (int), Valor: índice onde apareceu
    unordered_map<int, int> primeira_posicao;

    int mask = 0;
    int maior_tamanho = 0;

    primeira_posicao[0] = -1;

    for (int i = 0; i < n; i++) {
        mask ^= (1 << (s[i] - 'a'));

        if (primeira_posicao.count(mask)) {
            maior_tamanho = max(maior_tamanho, i - primeira_posicao[mask]);
        } else {
            primeira_posicao[mask] = i;
        }

        for (int k = 0; k < 26; k++) {
            int mask_com_1_diferente = mask ^ (1 << k);
            if (primeira_posicao.count(mask_com_1_diferente)) {
                maior_tamanho = max(maior_tamanho, i - primeira_posicao[mask_com_1_diferente]);
            }
        }
    }

    cout << maior_tamanho << "\n";

    return 0;
}