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

bool PairComp(p<ll, ll>& p1, p<ll, ll>& p2) {
    return p1.F > p2.F;
}

int main () {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);

    ll N; cin >> N;
    v<ll> score(N);
    For (i, N) cin >> score[i];

    v<ll> arr(score); sort(arr.begin(), arr.end());
    arr.resize(unique(arr.begin(), arr.end()) - arr.begin());
    
    v<p<ll, ll>> order(N);
    For (i, N) order[i] = {lower_bound(all(arr), score[i]) - arr.begin(), i};
    sort(all(order), PairComp);

    v<v<ll>> adj(N);
    ll from;
    For (i, N - 1) {
        cin >> from;
        adj[from - 1].pb(i + 1);
    }

    v<ll> start(N), end(N);
    ll timer = 0;
    auto dfs = [&](auto&& self, ll curr) -> void {
        start[curr] = timer;
        for (ll n : adj[curr]) {
            timer++;
            self(self, n);
        }
        end[curr] = timer;
    };

    dfs(dfs, 0);

    v<ll> segtree(4*N);

    auto sum = [&](auto&& self, ll qleft, ll qright, ll left, ll right, ll index) -> ll {
        
        if (qright < left || qleft > right) return 0;

        if (qleft <= left && qright >= right) return segtree[index];

        return self(self, qleft, qright, left, (left + right) / 2, 2*index) + self(self, qleft, qright, (left + right) / 2 + 1, right, 2*index + 1);
    };

    auto update = [&](auto&& self, ll left, ll right, ll index, ll qindex) -> void {
        segtree[index]++;

        if (left != right) {
            if (qindex <= (left + right) / 2) {
                self(self, left, (left + right) / 2, 2*index, qindex);
            }
            
            else {
                self(self, (left + right) / 2 + 1, right, 2*index + 1, qindex);
            }
        }
    };

    v<ll> ans(N);

    for (auto [prof, n] : order) {
        // cout << "Rod number: " << n  << " Sum: " << sum(sum, start[n], end[n], 0, N - 1, 1) << " Added to: " << start[n] << nl;
        ans[n] = sum(sum, start[n], end[n], 0, N - 1, 1);
        update(update, 0, N - 1, 1, start[n]);
    }

    for (ll n : ans) {
        cout << n << nl;
    }
}