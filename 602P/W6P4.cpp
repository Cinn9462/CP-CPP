#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define v vector
#define pb push_back
#define p pair
#define F first
#define S second
#define all(x) x.begin(), x.end()
#define ss " "
#define nl "\n"
#define For(i, a) for(ll i = 0; i < a; i++)
#define FOR(i, a, b) for(ll i = a; i < b; i++)
#define roF(i, a) for(ll i = a; i >= 0; i--)
#define ROF(i, a, b) for(ll i = a; i >= b; i--)

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll N; cin >> N; v<v<p<ll, ll>>> adj_list(N);
    ll e1, e2, t;
    For(i, N - 1) {
        cin >> e1 >> e2 >> t;
        e1--; e2--;
        adj_list[e1].pb({e2, t});
        adj_list[e2].pb({e1, t});
    }
    v<p<ll, ll>> ans(N);
    v<p<ll, ll>> paths(N); // F -> 0-path, S -> 1-path
    auto dfs = [&](auto&& dfs, ll u, ll p) -> void { 
        for (auto& [c, type] : adj_list[u]) {
            if(c != p) {
                dfs(dfs, c, u);
                if (type == 0) paths[u].F += paths[c].F + paths[c].S + 1; // if 0-path, can include both 0-edge and 1-edge
                if (type == 1) paths[u].S += paths[c].S + 1; // if 1-path, cannot have 0-edge before
            }
        }
    };

    dfs(dfs, 0, -1);

    ans[0] = paths[0];
    auto dfs2 = [&](auto&& dfs2, ll u, ll p) -> void {
        for(auto& [c, type] : adj_list[u]) {
            if (c != p) {
                if (type == 0) {
                    ans[c].F = ans[u].F - paths[c].S + ans[u].S;
                    ans[c].S = paths[c].S;
                    dfs2(dfs2, c, u);
                }
                if (type == 1) {
                    ans[c].F = paths[c].F;
                    ans[c].S = ans[u].S;
                    dfs2(dfs2, c, u);
                }
            }
        }
    };

    dfs2(dfs2, 0, -1);

    ll r = 0;

    // for(p<ll, ll> node : ans) {
    //     cout << node.F << ss << node.S << nl;
    // }

    for(p<ll, ll> node : ans) {
        r += node.F + node.S;
    }
    cout << r << nl;
}