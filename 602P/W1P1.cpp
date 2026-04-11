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

#include <bits/stdc++.h>
using namespace std;

ostream& operator<<(ostream& os, v<ll>& arr) {
    for (ll ___a : arr) {
        os << ___a << " ";
    }
    return os;
}

int main () {
    ll N, Q; cin >> N >> Q;
    v<ll> nums(N);
    For (i, N) cin >> nums[i];

    v<ll> segtree(4*N);
    auto build = [&](auto&& self, ll left, ll right, ll index) -> ll {
        if (left == right) {
            segtree[index] = nums[left];
            return nums[left];
        }

        segtree[index] = self(self, left, (left + right) / 2, 2*index) + self(self, (left + right) / 2 + 1, right, 2*index + 1);
        return segtree[index];
    };

    build(build, 0, N - 1, 1);

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

    while (Q--) {
        ll t, x, y; cin >> t >> x >> y;
        if (t) {
            cout << sum(sum, x, y - 1, 0, N - 1, 1) << nl;
        }
        else {
            update(update, 0, N - 1, 1, y, x);
        }
    }
}