#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define v vector
#define pb push_back
#define all(x) x.begin(), x.end
#define p pair
#define F first
#define S second
#define ss " "
#define nl "\n"
#define For(i, a) for(ll i = 0; i < a; i++)
#define FOR(i, a, b) for(ll i = a; i < b; i++)
#define roF(i, a) for(ll i = a; i >= 0; i--)
#define ROF(i, a, b) for(ll i = a; i >= b; i--)
#define fileread(file) ifstream fin; fin.open((string)file + ".in"); ofstream fout; fout.open((string)file + ".out")


int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll T; cin >> T;
    while(T--) {
        ll N, M, W; cin >> N >> M >> W;
        v<v<p<ll, ll>>> adj(N);
        ll e1, e2, w;
        For(i, M) {
            cin >> e1 >> e2 >> w;
            e1--; e2--;
            adj[e1].pb({e2, w});
            adj[e2].pb({e1, w});
        }
        For(i, W) {
            cin >> e1 >> e2 >> w;
            e1--; e2--;
            adj[e1].pb({e2, -w});
        }

        v<ll> dist(N, LLONG_MAX);
        dist[0] = 0; // 0 is root
        For(i, M + W) {
            For(u, N) {
                for(auto& [c, w] : adj[u]) {
                    dist[c] = min(dist[c], (dist[u] == LLONG_MAX ? LLONG_MAX : dist[u] + w));
                }
            }
        }

        bool flag = true;
        For(u, N) {
            for(auto& [c, w] : adj[u]) {
                if (dist[c] > dist[u] + w) {
                    flag = false;
                }
            }
        }

        cout << (flag ? "NO" : "YES") << nl;
    }
}