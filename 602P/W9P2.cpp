#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define v vector
#define pb push_back
#define all(x) x.begin(), x.end()
#define For(i, a) for(ll i = 0; i < a; i++)
#define FOR(i, a, b) for(ll i = a; i < b; i++)
#define roF(i, a) for(ll i = a; i >= 0; i--)
#define ROF(i, a, b) for(ll i = a; i >= b; i--)
#define ss " "
#define nl "\n"

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll N; cin >> N; v<ll> nums(N); map<ll, ll> pos; For(i, N) {
        cin >> nums[i]; pos[nums[i]] = i;
    }

    v<ll> pow2 = {1};
    For(i, 60) {
        pow2.pb(pow2.back() * 2);
    }

    v<ll> b = nums;
    roF(bit, 60) {
        For(i, N) {
            if ((nums[i] >> bit) & 1) {
                ll f = b[pos[nums[i] - pow2[bit]]];
                b[pos[nums[i] - pow2[bit]]] = b[i];
                b[i] = f;
            }
        }
        // cout << bit << nl;
        // for(ll n : b) {
        //     cout << n << ss;
        // }
        // cout << nl;
        // for (auto&[a, b] : pos) {
        //     cout << a << ":" << b << ss;
        // }
        // cout << nl;
    }
    for(ll n : b) {
        cout << n << nl;
    }
}