#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3")

#define ll long long
#define v vector
#define pb push_back
#define all(x) x.begin(), x.end()
#define For(i, a) for(ll i = 0; i < a; i++)
#define FOR(i, a, b) for(ll i = a; i < b; i++)
#define roF(i, a) for (ll i = a; i >= 0; i--)
#define ROF(i, a, b) for(ll i = a; i >= b; i--)
#define p pair
#define F first
#define S second
#define ss " "
#define nl "\n"

struct Edge {
    ll v1, v2, id;
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll N, M; cin >> N >> M;

    v<ll> parent(N);
    For(i, N) parent[i] = i;
    v<ll> size(N, 1);

    auto find = [&](auto&& find, ll v1) -> ll {
        if (v1 == parent[v1]) return v1;
        return parent[v1] = find(find, parent[v1]);
    };

    auto merge = [&](ll v1, ll v2) -> void {
        ll p_u = find(find, v1);
        ll p_v = find(find, v2);
        if (p_u != p_v) {
            if (size[p_u] > size[p_v]) {
                parent[p_v] = p_u;
                size[p_u] += size[p_v];
            }
            else {
                parent[p_u] = p_v;
                size[p_v] += size[p_u];
            }
        } 
    };
    
    map<ll, v<Edge>> edges;
    v<ll> poss(M, false);
    For(i, M) {
        ll v1, v2, w; cin >> v1 >> v2 >> w; Edge e; e.v1 = --v1; e.v2 = --v2; e.id = i; edges[w].pb(e);
    }

    ll chosen = 0;
    for(auto& [w, edge_list] : edges) {
        if (chosen >= N - 1) break;
        for (Edge e : edge_list) {
            if (find(find, e.v1) != find(find, e.v2)) {
                poss[e.id] = true;
            }
        }
        for (Edge e : edge_list) {
            if (find(find, e.v1) != find(find, e.v2)) {
                merge(e.v1, e.v2);
                chosen++;
            }
        }
    }
    For(i, M) cout << (poss[i] ? "YES" : "NO") << nl;
}