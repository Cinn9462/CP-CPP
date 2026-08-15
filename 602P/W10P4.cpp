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
    ll B = N / (ll) sqrt(Q) + 1;
    v<ll> nums(N); For(i, N) cin >> nums[i];
    v<ll> ordered;
    v<v<p<ll, ll>>> queries(N / B + 1); ll l, r;
    For(i, Q) {
        cin >> l >> r;
        l--; r--;
        queries[l / B].pb({l, r});
        ordered.pb(l * (ll) 1e6 + r);
    }
    for(v<p<ll, ll>>& block : queries) {
        sort(all(block), [](p<ll, ll>& p1, p<ll, ll>& p2) {return p1.S < p2.S;});
    }
    map<ll, ll> lookup; v<ll> freq(1e6);
    for(v<p<ll, ll>>& block: queries) {
        ll ans = 0; l = 0; r = -1; For(i, 1e6) freq[i] = 0;
        for (auto& [L, R] : block) {
            // cout << L << ss << R << ss << "g" << nl;
            while(r < R) {
                ans -= freq[nums[r + 1]] * freq[nums[r + 1]] * nums[r + 1];
                ans += (freq[nums[r + 1]] + 1) * (freq[nums[r + 1]] + 1) * nums[r + 1];
                freq[nums[r + 1]]++;
                r++;
                // cout << l << ss << r << ss << ans << nl;
            }
            while(l != L) {
                if (l < L) {
                    ans -= freq[nums[l]] * freq[nums[l]] * nums[l];
                    ans += (freq[nums[l]] - 1) * (freq[nums[l]] - 1) * nums[l];
                    freq[nums[l]]--;
                    l++;
                    // cout << l << ss << r << ss << ans << nl;
                }
                else if (l > L) {
                    ans -= freq[nums[l - 1]] * freq[nums[l - 1]] * nums[l - 1];
                    ans += (freq[nums[l - 1]] + 1) * (freq[nums[l - 1]] + 1) * nums[l - 1];
                    freq[nums[l - 1]]++;
                    l--;
                    // cout << l << ss << r << ss << ans << nl;
                }
            }
            lookup[L * 1e6 + R] = ans;
        }
    }

    for(ll e : ordered) {
        cout << lookup[e] << nl;
    }
}