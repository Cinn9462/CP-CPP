#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pb push_back 
#define v vector
#define p pair
#define F first
#define S second
#define For(i, end) for (ll i = 0; i < end; i++)
#define roF(i, start) for (ll i = start; i >= 0; i--)
#define FOR(i, begin, end) for (ll i = begin; i < end; i++) 
#define nl "\n"
#define ss " "
#define all(x) x.begin(), x.end()

ostream& operator<<(ostream& os, v<ll>& arr) {
    for (ll ___a : arr) {
        os << ___a << " ";
    }
    return os;
}

bool PairComp(p<ll, ll> p1, p<ll, ll> p2) {
    return p1.S < p2.S;
}


int main () {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);

    ll N; cin >> N;
    v<ll> colors(N);
    For(i, N) cin >> colors[i];

    v<ll> arr(colors); sort(arr.begin(), arr.end());
    arr.resize(unique(arr.begin(), arr.end()) - arr.begin());
    For (i, N) colors[i] = lower_bound(all(arr), colors[i]) - arr.begin();

    v<v<ll>> adj(N);
    ll x, y;
    For(i, N - 1) {
        cin >> x >> y;
        adj[x - 1].pb(y - 1);
        adj[y - 1].pb(x - 1);
    }

    v<p<ll, ll>> eu(N);
    v<ll> euToNode(N); // maps eu index -> original node
    unordered_set<ll> visited;
    ll timer = 0;
    auto dfs = [&](auto&& self, ll curr) -> void {
        visited.insert(curr);
        eu[curr].F = timer;
        euToNode[timer] = curr;
        for (ll n : adj[curr]) { 
            if (visited.count(n) == 0) {
                timer++;
                self(self, n);
            }
        }
        eu[curr].S = timer;
    };

    dfs(dfs, 0);
    sort(all(eu), PairComp);

    v<ll> segtree(4*N);

    auto sum = [&](auto&& self, ll qleft, ll qright, ll left, ll right, ll index) -> ll {
        
        if (qright < left || qleft > right) return 0;

        if (qleft <= left && qright >= right) return segtree[index];

        return self(self, qleft, qright, left, (left + right) / 2, 2*index) + self(self, qleft, qright, (left + right) / 2 + 1, right, 2*index + 1);
    };

    auto update = [&](auto&& self, ll left, ll right, ll index, ll value, ll qindex) -> void {
        segtree[index] += value;

        if (left != right) {
            if (qindex <= (left + right) / 2) {
                self(self, left, (left + right) / 2, 2*index, value, qindex);
            }
            
            else {
                self(self, (left + right) / 2 + 1, right, 2*index + 1, value, qindex);
            }
        }
    };

    v<ll> ans(N);
    v<ll> seen(N, -1); // maps colors -> current eu tour index
    ll p = 0; // euler tour index
    
    For (i, eu.size()) {
        ll start = eu[i].F;
        ll end = eu[i].S;
        while (end >= p) {
            if (seen[colors[euToNode[p]]] == -1) {
                update(update, 0, N - 1, 1, 1, p);
                seen[colors[euToNode[p]]] = p;
            }
            else {
                update(update, 0, N - 1, 1, -1, seen[colors[euToNode[p]]]);
                update(update, 0, N - 1, 1, 1, p);
                seen[colors[euToNode[p]]] = p;
            }
            p++;
        }

        ans[euToNode[start]] = sum(sum, start, end, 0, N - 1, 1);
    }

    cout << ans << nl;
}