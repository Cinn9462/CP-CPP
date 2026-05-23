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
#define popcount(x) __builtin_popcountll(x)

ostream& operator<<(ostream& os, pair<ll, ll>& p) {
    return os << "[" << p.F << " " << p.S << "]";
}
ostream& operator<<(ostream& os, v<ll>& arr) {
    for (ll ___a : arr) {
        os << ___a << " ";
    }
    return os;
}

struct PairHash {
    size_t operator()(const p<ll, ll>& p) const {
        return p.F * 239 + p.S;
    }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    ll N; cin >> N;
    v<ll> nums(N);
    For(i, N) cin >> nums[i];

    v<v<ll>> dp(N, v<ll>(N, -1)); // [i, j] is inclusive interval
    For(sz, N) { // size of interval
        For(i, N - sz) {
            if (sz == 0) {
                dp[i][i] = 0LL;
                continue;
            }

            ll min_size = LLONG_MAX;
            ll total = accumulate(nums.begin() + i, nums.begin() + i + sz + 1, 0LL);
            For(k, sz) {
                min_size = min(dp[i][i + k] + dp[i + k + 1][i + sz], min_size);
            }
            dp[i][i + sz] = total + ((min_size == LLONG_MAX) ? 0LL : min_size);
        }
    }
    
    cout << dp[0][N - 1] << nl;
}