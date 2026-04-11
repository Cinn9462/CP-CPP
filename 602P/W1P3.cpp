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
    ll T; cin >> T;
    while(T--) {
        ll N, Q; cin >> N >> Q;

        v<ll> segtree(4*N);
        v<ll> lazy(4*N, 0);

        auto update = [&](auto&& self, ll ql, ll qr, ll left, ll right, ll index, ll modifier) -> void { // call update only if update is new

            if (lazy[index]) {
                segtree[index] += lazy[index] * (right - left + 1);
                if (left != right) {
                    lazy[2 * index] += lazy[index];
                    lazy[2 * index + 1] += lazy[index];
                }
                lazy[index] = 0;
            }

            if (qr < left || ql > right) return; // query out of range
            
            if (ql <= left && qr >= right) { // query completely in range
                lazy[index] += modifier;

                if (lazy[index]) {
                    segtree[index] += lazy[index] * (right - left + 1);
                    if (left != right) {
                        lazy[2 * index] += lazy[index];
                        lazy[2 * index + 1] += lazy[index];
                    }
                    lazy[index] = 0;
                }

                return;
            }
            
            // query partially in range
            self(self, ql, qr, left, (left + right) / 2, 2*index, modifier);
            self(self, ql, qr, (left + right) / 2 + 1, right, 2*index + 1, modifier);

            segtree[index] = segtree[2*index] + segtree[2*index + 1]; // recompute after lazy updates propagate down 
        };

        auto sum = [&](auto&& self, ll ql, ll qr, ll left, ll right, ll index) -> ll {
            
            if (qr < left || ql > right) return 0; // query out of range

            if (lazy[index]) { // query needs propogation before summation
                segtree[index] += (right - left + 1) * lazy[index];
                if (left != right) {
                    lazy[2*index] += lazy[index];
                    lazy[2*index + 1] += lazy[index];
                }
                lazy[index] = 0;
            }

            if (ql <= left && qr >= right) return segtree[index];

            return self(self, ql, qr, left, (left + right) / 2, 2*index) + self(self, ql, qr, (left + right) / 2 + 1, right, 2*index + 1);
        };

        while (Q--) {
            ll t; cin >> t;
            if (t) {
                ll x, y; cin >> x >> y;
                cout << sum(sum, x - 1, y - 1, 0, N - 1, 1) << nl;
            }
            else {
                ll a, b, c; cin >> a >> b >> c;
                update(update, a - 1, b - 1, 0, N - 1, 1, c);
            }
        }
    }
}