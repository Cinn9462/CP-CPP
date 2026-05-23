#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define v vector
#define pb push_back
#define all(x) x.begin(), x.end()
#define p pair
#define F first
#define S second
#define For(i, a) for(ll i = 0; i < a; i++)
#define FOR(i, a, b) for(ll i = a; i < b; i++)
#define roF(i, a) for(ll i = a; i >= 0; i--)
#define ROF(i, a, b) for(ll i = a; i >= b; i--)
#define ss " "
#define nl "\n"
#define MOD 998244353

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll N, M, K; cin >> N >> M >> K;
    
    v<v<ll>> dp(K + 1, v<ll>(K + 1));
    dp[1][1] = N;
    FOR(i, 2, K + 1) {
        FOR(j, 1, i + 1) {
            dp[i][j] = (dp[i - 1][j] * j + dp[i - 1][j - 1] * (N - j + 1)) % MOD;
        }
    }

    v<ll> mp = {1}; // mp[i] = m^i
    For(i, K + 1) {
        mp.pb((mp.back() * M) % MOD);
    }

    auto mpow = [](ll start, ll i) -> ll {
        v<ll> mbp = {start};
        For(i, 50) {
            mbp.pb((mbp.back() * mbp.back()) % MOD);
        }

        ll ans = 1;
        ll count = 0;
        while(i != 0) {
            if (i % 2 == 1) ans *= mbp[count];
            ans %= MOD;
            i /= 2;
            count++;
        }

        return ans;
    };
    
    ll sum = 0;
    For(i, K + 1) {
        sum += (mpow(mp[i], MOD - 2) * dp[K][i]);
        sum %= MOD;
    }

    cout << sum << nl;
}