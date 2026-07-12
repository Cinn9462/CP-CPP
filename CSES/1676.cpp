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

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll N, Q; cin >> N >> Q;
    v<ll> parent(N);
    For(i, N) parent[i] = i;
    v<ll> size(N, 1);
    ll largest = 1; ll comp = N;
    auto find = [&](auto&& find, ll u) -> ll {
        if (u == parent[u]) return u;
        // return parent[u] = find(find, parent[u]);
        return find(find, parent[u]);
    };
    auto merge = [&](ll u, ll v) -> void {
        ll p_u = find(find, u);
        ll p_v = find(find, v);
        if (p_u != p_v) {
            comp--;
            if (size[p_u] > size[p_v]) {
                parent[p_v] = p_u;
                size[p_u] += size[p_v];
                largest = max(largest, size[p_u]);
            }
            else {
                parent[p_u] = p_v;
                size[p_v] += size[p_u];
                largest = max(largest, size[p_v]);
            }
        } 
    };
    while(Q--) {
        ll u, v; cin >> u >> v;
        merge(--u, --v);
        cout << comp << ss << largest << nl;
    }
}