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
    ll H, W;
    cin >> H >> W;
    v<string> grid(H);
    For(i, H) {
        cin >> grid[i];
    }

    v<v<ll>> dp(H + 1, v<ll>(W + 1, 0));
    For (i, H) {
        For (j, W) {
            if (grid[i][j] == '.') dp[i + 1][j + 1] = (dp[i][j + 1] + dp[i + 1][j]) % (ll) (1e9 + 7);
            if (grid[i][j] == '#') dp[i + 1][j + 1] = 0;
            if (i == 0 && j == 0) dp[i + 1][j+ 1] = 1;
        }
    }
    
    // for (auto row : dp) {
    //     cout << row << nl;
    // }

    cout << dp[H][W] % (ll) (1e9 + 7) << nl;
}