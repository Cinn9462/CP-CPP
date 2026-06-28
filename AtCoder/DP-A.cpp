#define ll long long
#define pb push_back 
#define v vector
#define For(i, end) for (ll i = 0; i < end; i++)
#define nl "\n"
#define ss " "

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll N; cin >> N;

    v<ll> cost(N);
    For(i, N) {
        cin >> cost[i];
    }

    v<ll> dp(N, LLONG_MAX);
    dp[0] = 0;

    For(i, N ) {
        if (i + 1 < N) {
            dp[i + 1] = min(dp[i + 1], dp[i] + abs(cost[i] - cost[i + 1]));
        }
        if (i + 2 < N) {
            dp[i + 2] = min(dp[i + 2], dp[i] + abs(cost[i] - cost[i + 2]));
        }
    }
    cout << dp[N - 1];
}