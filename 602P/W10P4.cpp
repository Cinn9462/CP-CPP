// TODO : FINISH

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
    ll B = N * (ll) sqrt(Q);
    v<ll> nums(N); For(i, N) cin >> nums[i];
    v<ll> ordered;
    v<v<p<ll, ll>>> queries(N / B + 1); ll l, r;
    For(i, Q) {
        cin >> l >> r;
        queries[l / B].pb({l, r});
        ordered.pb(l * 1e6 + r);
    }
    for(v<p<ll, ll>> block : queries) {
        sort(all(block), [&](p<ll, ll> p1, p<ll, ll> p2) {return p1.S < p1.F;});
    }
    ll ans = 0; map<ll, ll> lookup; v<ll> freq(1e6); l = 0; r = 0;
    for(v<p<ll, ll>> block: queries) {
        for (auto& [L, R] : block) {
            while(r < R) {
                ans -= freq[nums[r + 1]] * freq[nums[r + 1]] * nums[r + 1];
                ans += (freq[nums[r + 1]] + 1) * (freq[nums[r + 1]] + 1) * nums[r + 1];
                freq[nums[r + 1]]++;
                r++;
            }
            while(l != L) {
                if (l < L) {
                    ans -= freq[nums[r + 1]] * freq[nums[r + 1]] * nums[r + 1];
                    ans += (freq[nums[r + 1]] - 1) * (freq[nums[r + 1]] - 1) * nums[r + 1];
                    freq[nums[r + 1]]--;
                    l++;
                }
                else if (l > L) {
                    ans -= freq[nums[r - 1]] * freq[nums[r - 1]] * nums[r - 1];
                    ans += (freq[nums[r - 1]] - 1) * (freq[nums[r - 1]] - 1) * r;
                    freq[nums[r + 1]]--;
                    l--;
                }
            }
        }
    }
}