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

int main () {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);

    ll N; cin >> N;
    v<unordered_set<ll>> nums(N);
    For (i, N) cin >> nums[i];

    v<v<ll>> segtree(4*N);
    auto build = [&](auto&& self, ll left, ll right, ll index) -> void {
        if (left == right) {
            segtree[index] = {nums[left]};
            return; 
        }
        self(self, left, (left + right) / 2, 2 * index);
        self(self, (left + right) / 2 + 1, right, 2 * index + 1);
        merge(segtree[2*index].begin(), segtree[2*index].end(), segtree[2*index+1].begin(), segtree[2*index+1].end(), back_inserter(segtree[index]));
    };

    build(build, 0, N - 1, 1);

    auto query = [&](auto&& self, ll qleft, ll qright, ll left, ll right, ll index, ll target) -> ll {
        
        if (qright < left || qleft > right) return 0;

        if (qleft <= left && qright >= right) return segtree[index].size() - (upper_bound(segtree[index].begin(), segtree[index].end(), target) - segtree[index].begin());

        return self(self, qleft, qright, left, (left + right) / 2, 2*index, target) + self(self, qleft, qright, (left + right) / 2 + 1, right, 2*index + 1, target);
    };

    ll Q; cin >> Q;
    while (Q--) {
        ll l, r, t;
        cin >> l >> r >> t;
        cout << query(query, l - 1, r - 1, 0, N - 1, 1, t) << nl;
    }
}