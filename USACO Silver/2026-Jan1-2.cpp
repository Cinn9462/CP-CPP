// TODO: Finish debugging

#define ll long long
#define pb push_back 
#define v vector
#define p pair
#define F first
#define S second
#define For(i, end) for (ll i = 0; i < end; i++)
#define nl "\n"
#define ss " "
#define un_map unordered_map
#define un_set unordered_set

#include <bits/stdc++.h>
using namespace std;

ostream& operator<<(ostream& os, pair<ll, ll>& p) {
    return os << "[" << p.F << " " << p.S << "]";
}
ostream& operator<<(ostream& os, v<ll>& arr) {
    for (ll ___a : arr) {
        os << ___a << " ";
    }
    return os;
}

struct PairHash {
    size_t operator()(const pair<ll,ll>& p) const {
        return hash<ll>()(p.F) ^ (hash<ll>()(p.S) << 1);
    }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    ll num_rods, num_restrictions;
    cin >> num_rods >> num_restrictions;

    v<ll> rod_lb(num_rods), rod_ub(num_rods);
    For(i, num_rods) cin >> rod_lb[i];
    For(i, num_rods) cin >> rod_ub[i];

    v<v<p<ll, ll>>> adj(num_rods); // p.F is head, p.S is weight
    ll x, y, z;
    For(i, num_restrictions) {
        cin >> x >> y >> z; x--; y--;
        adj[x].pb({y, z});
        adj[y].pb({x, z});
    }

    v<bool> visited(num_rods, false);
    v<ll> limit_lb(num_rods, LLONG_MIN);
    v<ll> limit_ub(num_rods, LLONG_MAX);
    bool impossible = false;
    ll total = 0;

    For(n, num_rods) { // i is the current rod checked
        auto dfs = [&](auto self, ll i, ll coeff, ll offset) -> void { // coeff is -1 or 1, starts at -1
            
            ll start = min(offset - coeff * rod_lb[i], offset - coeff * rod_ub[i]);
            ll end = max(offset - coeff * rod_lb[i], offset - coeff * rod_ub[i]);

            limit_lb[i] = max(limit_lb[i], start);
            limit_ub[i] = min(limit_ub[i], end);
            
            if (limit_lb[i] > limit_ub[i]) {
                impossible = true;
                cout << "IMPOSSIBLE AT DESTINATION: " << i + 1  << ". Rods are of value " << limit_lb[i] << " and " << limit_ub[i] << "." << nl;
            }

            if (!visited[i]) {
                visited[i] = true;
                for( auto [j, w] : adj[i]) {
                    self(self, j, -1 * coeff, offset - coeff * w);
                }
            }
        };

        if (!visited[n]) dfs(dfs, n, 1, 0);

    }

    cout << impossible << nl << limit_lb << nl << limit_ub;
}