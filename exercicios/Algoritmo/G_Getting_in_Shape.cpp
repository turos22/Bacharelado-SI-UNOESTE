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

ll fib(ll n) {
    if (n <= 1) return 1;
    return fib(n - 1) + fib(n - 2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    cin >> n;
    
    printf("\n%ll", fib(n));

    return 0;
}