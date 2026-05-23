#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define v vector
#define pb push_back
#define p pair
#define F first
#define S second
#define ss " "
#define nl "\n"
#define For(i, a) for(ll i = 0; i < a; i++)
#define FOR(i, a, b) for(ll i = a; i < b; i++)
#define roF(i, a) for(ll i = a; i >= 0; i--)
#define ROF(i, a, b) for(ll i = a; i >= b; i--)
#define all(x) x.begin(), x.end()

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll N; cin >> N;
    v<v<ll>> adj(N);
    ll _i, _j;
    For(i, N - 1) {
        cin >> _i >> _j;
        adj[_i - 1].pb(_j - 1);
        adj[_j - 1].pb(_i - 1);
    }
    
    long double x = 1;
    auto dfs = [&](auto&& self, ll node, ll depth, ll parent) -> void {
        for (ll n : adj[node]) {
            if (n != parent) {
                x += 1.0 / depth;
                self(self, n, depth + 1, node);
            }
        }
    };
    dfs(dfs, 0, 2, 0);
    cout << fixed << setprecision(20) << x << nl;
}