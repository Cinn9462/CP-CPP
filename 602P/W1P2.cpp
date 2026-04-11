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

struct Data {
    ll lm, rm, best, sum;

    Data(ll left, ll right, ll b, ll s) : lm(left), rm(right), best(b), sum(s) {} 
    Data() : lm(LLONG_MIN), rm(LLONG_MIN), best(LLONG_MIN), sum(LLONG_MIN) {}
};

Data combine(const Data& d1, const Data& d2) { // d1 < d2
    if (d1.sum == LLONG_MIN) {
        return d2;
    }

    if (d2.sum == LLONG_MIN) {
        return d1;
    }

    return Data(
        max(d1.lm, d1.sum + d2.lm),
        max(d2.rm, d1.rm + d2.sum),
        max(max(d1.best, d2.best), d1.rm + d2.lm),
        d1.sum + d2.sum
    );
};

int main () {
    ll N, Q; cin >> N;
    v<ll> nums(N);
    For (i, N) cin >> nums[i];

    v<Data> segtree(4*N);
    auto build = [&](auto&& self, ll left, ll right, ll index) -> void {
        if (left == right) {
            segtree[index] = Data(nums[left], nums[left], nums[left], nums[left]);
            return;
        }
        
        self(self, left, (left + right) / 2, 2*index);
        self(self, (left + right) / 2 + 1, right, 2*index + 1);
        segtree[index] = combine(segtree[2*index], segtree[2*index + 1]);
    };

    build(build, 0, N - 1, 1);

    auto sum = [&](auto&& self, ll qleft, ll qright, ll left, ll right, ll index) -> Data {
        
        if (qright < left || qleft > right) return Data();

        if (qleft <= left && qright >= right) return segtree[index];

        return combine(self(self, qleft, qright, left, (left + right) / 2, 2*index), self(self, qleft, qright, (left + right) / 2 + 1, right, 2*index + 1));
    };

    auto update = [&](auto&& self, ll left, ll right, ll index, ll value, ll qindex) -> void {
        if (left == right) {
            segtree[index] = Data(value, value, value, value);
            return;
        }
        
        if (qindex <= (left + right) / 2) {
            self(self, left, (left + right) / 2, 2*index, value, qindex);
        }
        
        else {
            self(self, (left + right) / 2 + 1, right, 2*index + 1, value, qindex);
        }

        segtree[index] = combine(segtree[2*index], segtree[2*index + 1]);
    };

    cin >> Q;

    while (Q--) {
        ll t, x, y; cin >> t >> x >> y;
        if (t) {
            cout << sum(sum, x - 1, y - 1, 0, N - 1, 1).best << nl;
        }
        else {

            assert (x >= 1); // x is index;
            update(update, 0, N - 1, 1, y, x - 1);
        }
    }
}