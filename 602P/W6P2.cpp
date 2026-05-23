#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define v vector
#define pb push_back
#define all(x) x.begin(), x.end()
#define p pair
#define F first
#define S second
#define For(i, a) for(ll i = 0; i < a; i++)
#define FOR(i, a, b) for(ll i = a; i < b; i++)
#define roF(i, a) for(ll i = a; i >= 0; i--)
#define ROF(i, a, b) for(ll i = a; i >= b; i--)
#define ss " "
#define nl "\n"

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    ll N; cin>> N; v<ll> a(N); For(i, N) cin >> a[i]; v<v<ll>> adj_list(N); ll e1, e2; For(i, N - 1) {cin >> e1 >> e2; e1--; e2--; adj_list[e1].pb(e2); adj_list[e2].pb(e1);}

    v<ll> suma(N);
    ll start = 0;
    auto dfs = [&](auto&& self, ll u, ll p, ll d) -> ll {
        ll curr_sum = a[u];
        start += d * a[u];
        for(ll c : adj_list[u]) {
            if (c == p) continue;
            curr_sum += self(self, c, u, d + 1);
        }
        return suma[u] = curr_sum;
    };

    dfs(dfs, 0, -1, 0);

    ll max_v = start;
    auto dfs2 = [&](auto&& self, ll u, ll p, ll v) -> void {
        max_v = max(max_v, v);
        for(ll c: adj_list[u]) {
            if (c == p) continue;
            self(self, c, u, v - 2 * suma[c] + suma[0]);
        }
    };

    dfs2(dfs2, 0, -1, start);

    cout << max_v << nl;
}