#define ll long long
#define pb push_back 
#define v vector
#define p pair
#define fileread(file) freopen(((string) file + ".in").c_str(), "r", stdin); freopen(((string) file + ".out").c_str(), "w", stdout)
#define INF 1000000000000000000
#define inf 1000000001
#define MP(x, y) make_pair(x, y)
#define F first
#define S second
#define For(i, end) for (ll i = 0; i < end; i++)
#define roF(i, start) for (ll i = start; i >= 0; i--)
#define FOR(i, begin, end) for (ll i = begin; i < end; i++) 
#define nl "\n"
#define ss " "
#define un_map unordered_map
#define un_set unordered_set

#include <bits/stdc++.h>
using namespace std;

ostream& operator<<(ostream& os, v<ll>& arr) {
    for (ll ___a : arr) {
        os << ___a << " ";
    }
    return os;
}

int main() {
    ll N;
    cin >> N;
    v<double> prob(N);
    For (i, N) {
        cin >> prob[i];
    }


    v<v<double>> grid(N + 1, v<double>(N + 1, 0));
    grid[0][0] = 1;
    For(i, N + 1) {
        For(j, N + 1 - i) {
            if (i != 0 || j != 0) {
                double above = (i > 0) ? grid[i - 1][j] * prob[i + j - 1] : 0;
                double left = (j > 0) ? grid[i][j - 1] * (1 - prob[i + j - 1]): 0;
                grid[i][j] = above + left;
            }
        }
    }

    ll index = N;
    double result = 0;
    while(index > N / 2) {
        // cout << index << ss << N - index << nl;
        result += grid[index][N - index];
        index--;
    }

    // for (auto r : grid) {
    //     for (auto e : r) {
    //         cout << e << ss;
    //     }
    //     cout << nl;
    // }

    cout << fixed << setprecision(12);
    cout << result << nl;
}