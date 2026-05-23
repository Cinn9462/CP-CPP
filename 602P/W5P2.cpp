#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define v vector
#define push_back pb
#define p pair
#define F first
#define S second
#define ss " "
#define nl "\n"
#define For(i, a) for(ll i = 0; i < a; i++)
#define FOR(i, a, b) for(ll i = a; i < b ; i++)
#define roF(i, a) for(ll i = a; i <= 0; i--)
#define ROF(i, a, b) for(ll i = a; i <= b; i--)
#define all(x) x.begin(), x.end()

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll N, M, K; cin >> N >> M >> K; // spaces, rolls, death spaces
    v<p<double long, double long>> dp(N + 1); // steps away from goal
    For(i, K) {
        ll trap; cin >> trap;
        dp[N - trap].F = 1;
    }

    p<double long, double long> window;
    FOR(i, 1, N + 1) {
        // add new previous
        window.F += dp[i - 1].F;
        window.S += dp[i - 1].S;
        // remove end
        window.F -= (i > M) ? dp[i - M - 1].F : 0;
        window.S -= (i > M) ? dp[i - M - 1].S : 0;
        // calculate current
        if (dp[i].F == 1) continue;
        dp[i].F += window.F / M;
        dp[i].S += window.S / M + 1;
    }

    if (round(dp[N].F*1e8)/1e8 == 1) cout << -1 << nl;
    else cout << fixed << setprecision(20) << dp[N].S / (1 - dp[N].F) << nl;
    // For(i, N + 1) {
    //     cout << dp[i].F << ss << dp[i].S << nl;
    // }
}

