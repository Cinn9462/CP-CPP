#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pb push_back 
#define v vector
#define p pair
#define F first
#define S second
#define For(i, end) for (ll i = 0; i < end; i++)
#define roF(i, start) for (ll i = start; i >= 0; i--)
#define FOR(i, begin, end) for (ll i = begin; i < end; i++) 
#define nl "\n"
#define ss " "
#define all(x) x.begin(), x.end()

ostream& operator<<(ostream& os, v<ll>& arr) {
    for (ll ___a : arr) {
        os << ___a << " ";
    }
    return os;
}

int main () {
    ll X, Y, K;
    cin >> X >> Y >> K;
    
    v<v<ll>> grid(X, v<ll>(Y));
    For (i, X) For (j, Y) cin >> grid[i][j];

    v<unordered_map<ll, ll>> count(Y);
    ll mid = (X + Y) / 2 - 1;

    auto forward_dfs = [&](auto&& self, ll x, ll y, ll mod) {
        if (x >= X || y >= Y) return;
        else if (x + y == mid) count[y][mod ^ grid[x][y]]++;
        else {
            self(self, x + 1, y, mod ^ grid[x][y]);
            self(self, x, y + 1, mod ^ grid[x][y]);
        }
    };
    forward_dfs(forward_dfs, 0, 0, 0);
    
    ll ans = 0;
    auto backward_dfs = [&](auto&& self, ll x, ll y, ll mod) {
        if (x < 0 || y < 0) return;
        else if (x + y == mid) ans += count[y][mod ^ K];
        else {
            self(self, x - 1, y, mod ^ grid[x][y]);
            self(self, x, y - 1, mod ^ grid[x][y]);
        }
    };
    backward_dfs(backward_dfs, X - 1, Y - 1, 0);

    cout << ans << nl;
}