#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define v vector
#define pb push_back
#define p pair
#define F first
#define S second
#define For(i, a) for(ll i = 0; i < a; i++)
#define FOR(i, a, b) for(ll i = a; i < b; i++)
#define roF(i, a) for(ll i = a; i >= 0; i--)
#define ROF(i, a, b) for(ll i = a; i >= b; i--)
#define all(x) x.begin(), x.end()
#define ss " "
#define nl "\n"

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll N, x, y; cin >> N >> x >> y; // x is spanning tree time, y is graph time
    v<v<ll>> adj_list(N);
    ll e1, e2;
    For(i, N - 1) {
        cin >> e1 >> e2;
        e1--; e2--;
        adj_list[e1].pb(e2);
        adj_list[e2].pb(e1);
    }

    if (x >= y) { // prefer graph time over spanning tree time
        for(v<ll> l : adj_list) {
            if (l.size() == N - 1) {
                cout << (N - 2) * y + x << nl;
                return 0;
            } 
        }
        cout << (N - 1) * y << nl;
    }

    else { // prefer spanning tree time over graph time
        v<v<ll>> dp(N, v<ll>(2)); // 0 -> parent cut, 1 -> parent kept
        auto dfs = [&](auto&& self, ll node, ll parent) -> void {
            v<ll> best_c = {0, 0};
            ll subtree_sz = 0;
            for(ll c : adj_list[node]) {
                if (c == parent) continue;
                self(self, c, node);
                subtree_sz += dp[c][0];

                best_c.pb(dp[c][1] - dp[c][0]);
            }

            nth_element(best_c.begin(), best_c.begin() + 1, best_c.end()); // sort index 0 and 1

            dp[node][0] = 1 + subtree_sz + best_c[0] + best_c[1];
            dp[node][1] = subtree_sz + best_c[0];
        };

        dfs(dfs, 0, -1);
        cout << (dp[0][0] - 1) * y + (N - dp[0][0]) * x << nl;
    }
}