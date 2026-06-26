#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define v vector
#define p pair
#define F first
#define S second
#define pb push_back
#define all(x) x.begin(), x.end()
#define For(i, a) for(ll i = 0; i < a; i++)
#define FOR(i, a, b) for(ll i = a;i < b; i++)
#define roF(i, a) for(ll i = a; i >= 0; i--)
#define ROF(i, a, b) for(ll i = a; i >= b; i--)
#define ss " "
#define nl "\n"

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    ll N, M; cin >> N >> M;
    v<v<p<ll, ll>>> adj(N);
    ll n1, n2, t; // b = 1 is one directional, b = 0 is bidirectional
    For(i, M) {
        cin >> n1 >> n2 >> t;
        adj[n1 - 1].pb({n2 - 1, 1});
        adj[n2 - 1].pb({n1 - 1, (t ? -1 : 1)});
    }

    v<ll> bi(N); // 0 is unvisited, 1, 2 for markers
    bool flag = false;
    auto dfs = [&](auto&& dfs, ll u) -> void {
        for(auto&[c, t] : adj[u]) {
            if (bi[c] == 0) {
                bi[c] = (bi[u] == 1 ? 2 : 1);
                dfs(dfs, c);
            }
            else if (bi[c] == 1 && bi[u] == 1) flag = true;
            else if (bi[c] == 2 && bi[u] == 2) flag = true;
        } 
    };

    bi[0] = 1;
    dfs(dfs, 0);
    if (flag) {
        cout << "NO" << nl;  
        return 0;
    }

    v<v<ll>> dist(N, v<ll>(N, LLONG_MAX)); // bellman-ford
    For(i, N) {
        for(auto& [c, t] : adj[i]) {
            dist[i][c] = t;
        }
        dist[i][i] = 0;
    }

    For(k, N) {
        For(i, N) {
            For(j, N) {
                if (dist[i][k] < LLONG_MAX && dist[k][j] < LLONG_MAX) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    ll best = 0;
    ll best_root = 0;

    For(i, N) {
        if(dist[i][i] < 0) {
            cout << "NO";
            return 0;
        }
        if ((*max_element(all(dist[i]))) - (*min_element(all(dist[i]))) > best) {
            best = (*max_element(all(dist[i]))) - (*min_element(all(dist[i])));
            best_root = i;
        }
    }

    cout << "YES" << nl;
    cout << best << nl;
    for(ll i : dist[best_root]) cout << i + 2000 << ss;
}