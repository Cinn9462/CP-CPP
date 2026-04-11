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
    ios::sync_with_stdio(0); cin.tie(0);

    ll N; cin >> N;
    v<ll> count(4, 0);
    ll idx;
    For(i, N) {
        cin >> idx;
        count[idx]++;
    }

    v<v<v<double>>> dp(301, v<v<double>>(301, v<double>(301, 0)));

    auto dfs = [&](auto& self, ll x, ll y, ll z) -> double {
        if (x < 0 || y < 0 || z < 0) {
            return 0;
        }

        if (x == 0 && y == 0 && z == 0) {
            return 0;
        }

        if (dp[x][y][z]) {
            return dp[x][y][z];
        }

        dp[x][y][z] = (double) (N + x * self(self, x - 1, y, z) + y * self(self, x + 1, y - 1, z) + z * self(self, x, y + 1, z - 1)) / (x + y + z);
        return dp[x][y][z];
    };

    cout << fixed << setprecision(10) << dfs(dfs, count[1], count[2], count[3]);
}