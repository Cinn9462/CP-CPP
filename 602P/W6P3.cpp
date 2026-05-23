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
    ll N, MOD; cin >> N >> MOD; v<v<ll>> adj(N); ll e1, e2; For(i, N - 1) {cin >> e1 >> e2; e1--; e2--; adj[e1].pb(e2); adj[e2].pb(e1);}

    v<ll> root(N, 1);
    v<ll> ans(N);

    auto dfs = [&](auto&& self, ll u, ll p) -> void {
        for(int c : adj[u]) {
            if (c != p) {
                self(self, c, u);
                root[u] *= (root[c] + 1);
                root[u] %= MOD;
            }
        }
    };

    auto dfs2 = [&](auto&& self, ll u, ll p, ll val) -> void {

        ans[u] = (root[u] * val) % MOD;

        v<ll> prefix(adj[u].size() + 1, 1);
        v<ll> suffix(adj[u].size() + 1, 1);

        For(i, adj[u].size()) {
            ll c = adj[u][i];
            prefix[i + 1] = prefix[i];
            if (c != p) {
                prefix[i + 1] *= (root[c] + 1);
                prefix[i + 1] %= MOD;
            }
        }
        roF(i, adj[u].size() - 1) {
            ll c = adj[u][i];
            suffix[i] = suffix[i + 1];
            if (c != p) {
                suffix[i] *= (root[c] + 1);
                suffix[i] %= MOD;
            }
        }

        For(i, adj[u].size()) {
            ll c = adj[u][i];
            if (c != p) {
                self(self, c, u, ((((val * prefix[i]) % MOD) * suffix[i + 1]) % MOD + 1));
            }
        }
    };

    dfs(dfs, 0, -1);
    dfs2(dfs2, 0, -1, 1);
    For(i, N) cout << ans[i] << nl;
}