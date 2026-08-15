/*
Patterns of pref(n) where pref(n) = 1 ^ 2 ^ 3 ... ^ n - 1
4x + 0 mod 4 = 0
4x + 1 mod 4 = 4x + 0
4x + 2 mod 4 = 1
4x + 3 mod 4 = 4x + 3
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define v vector
#define pb push_back
#define all(x) x.begin(), x.end()
#define For(i, a) for(ll i = 0; i < a; i++)
#define FOR(i, a, b) for(ll i = a; i < b; i++)
#define ss " "
#define nl "\n"
#define MOD 998244353

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll L, R, target; cin >> L >> R >> target;

    // returns number of pairs (i, j) where pref(i) xor pref(j) = target given 0 <= i < l, 0 <= j < r
    auto solve = [&](ll l, ll r) -> ll {
        // i, j represent end bit patterns
        v<ll> end = {0, 0, 1, 3};
        ll ans = 0;
        For(i, 4) {
            For(j, 4) {
                ll count_i = (l + 3 - i) / 4;
                ll count_j = (r + 3 - j) / 4;
                if (end[i] > l || end[j] > r || count_i == 0 || count_j == 0) continue;

                if (i % 2 == 0) {
                    if (j % 2 == 0) { // both are constant
                        if ((end[i] ^ end[j]) == target) ans += ((count_i % MOD) * (count_j % MOD)) % MOD;
                    }
                    else { // i is constant, j is linear
                        if ((end[i] ^ end[j]) == target % 4 && target / 4 < count_j) ans += (count_i) % MOD;
                    }
                }
                else {
                    if (j % 2 == 0) { // i is linear, j is constant
                        if ((end[i] ^ end[j]) == target % 4 && target / 4 < count_i) ans += (count_j) % MOD;
                    }
                    else { // both are linear
                        if ((end[i] ^ end[j]) == target % 4) {
                            ll dp[61][2][2]; memset(dp, -1, sizeof(dp));
                            auto dfs = [&](auto&& dfs, ll pos, bool topL, bool topR) -> ll {
                                if (pos < 0) return (topL || topR) ? 0 : 1;
                                if (dp[pos][topL][topR] != -1) return dp[pos][topL][topR];
                                dp[pos][topL][topR] = 0;
                                ll maxL = topL ? (count_i >> pos) & 1 : 1;
                                ll maxR = topR ? (count_j >> pos) & 1 : 1;
                                For(lb, maxL + 1) {
                                    if ((((target >> (pos + 2)) & 1) ^ lb) > maxR) continue;
                                    dp[pos][topL][topR] += dfs(dfs, pos - 1, topL && (maxL == lb), topR && (maxR == ((target >> (pos + 2)) & 1) ^ lb));
                                    dp[pos][topL][topR] %= MOD;
                                }

                                return dp[pos][topL][topR] %= MOD;
                            };

                            ans += dfs(dfs, 60, true, true);
                        }
                    }
                }
                ans %= MOD;
            }
        }
        return ans;
    };
    ll total = (solve(L, L) + solve(R + 2, R + 2)) % MOD - (2 * solve(L, R + 2)) % MOD + MOD;
    total %= MOD;
    if (target == 0) total -= (R - L + 2) % MOD;
    total = (total + MOD ) % MOD;
    total *= (MOD + 1) / 2;
    total %= MOD;
    cout << total << nl;
}