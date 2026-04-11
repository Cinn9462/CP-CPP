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

// Solution: Memoization
int main() {
    ll num_nodes, num_edges; cin >> num_nodes >> num_edges;
    v<v<ll>> adj(num_nodes);
    ll n, m; // n -> m
    For (i, num_edges) {
        cin >> n >> m;
        adj[--n].pb(--m);
    }

    v<ll> dp(num_nodes, -1);

    auto dfs = [&](auto& self, ll i) -> ll {
        if (dp[i] != -1) return dp[i];
        else if (adj[i].size() == 0) {
            dp[i] = 0;
            return dp[i];
        }
        else {
            for (ll j : adj[i]) {
                dp[i] = max(dp[i], self(self, j) + 1);
            }
            return dp[i];
        }
    };

    ll max = 0;
    For (i, num_nodes) {
        dp[i] = dfs(dfs, i);
    }
    cout << *max_element(dp.begin(), dp.end()) << nl;
}

// Solution: Topological sort

// int main() {
//     ll num_nodes, num_edges; cin >> num_nodes >> num_edges;
//     v<v<ll>> adj(num_nodes);
//     v<ll> degree(num_nodes, 0);
//     ll n, m; // n -> m
//     For (i, num_edges) {
//         cin >> n >> m;
//         adj[--n].pb(--m);
//         degree[m]++;
//     }

//     v<ll> sorted; // topological sort
//     auto dfs = [&](auto& self, ll i) -> void {
//         if (degree[i] == 0) {
//             degree[i]--;
//             sorted.pb(i);
//             for (ll j : adj[i]) {
//                 degree[j]--;
//                 self(self, j);
//             }
//         }
//         return;
//     };

//     For (i, num_nodes) {
//         dfs(dfs, i);
//     }
//     reverse(sorted.begin(), sorted.end());

//     v<ll> path(num_nodes, 0);
//     for (ll i : sorted) {
//         for (ll j : adj[i]) {
//             path[i] = max(path[i], path[j] + 1);
//         }
//     }
//     cout << *max_element(path.begin(), path.end()) << nl;
// }