#define ll long long
#define pb push_back 
#define v vector
#define p pair
#define fileread(file) freopen(((string) file + ".in").c_str(), "r", stdin); freopen(((string) file + ".out").c_str(), "w", stdout)
#define INF 1000000000000000000
#define inf 1000000001
#define MP(x, y) make_pair(x, y)
#define F first
#define S second
#define For(i, end) for (ll i = 0; i < end; i++)
#define roF(i, start) for (ll i = start; i >= 0; i--)
#define FOR(i, begin, end) for (ll i = begin; i < end; i++) 
#define nl "\n"
#define ss " "
#define un_map unordered_map
#define un_set unordered_set

#include <bits/stdc++.h>
using namespace std;

ostream& operator<<(ostream& os, v<ll>& arr) {
    for (ll ___a : arr) {
        os << ___a << " ";
    }
    return os;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    ll N, W; cin >> N >> W;
    v<ll> weights(N + 1), values(N + 1);

    For(i, N) {
        cin >> weights[i + 1] >> values[i + 1];
    }

    v<ll> dp(W + 1, 0); // each value is max value achievable at that weight after n items

    FOR(i, 1, N + 1) { // i is the ith object is able to be added

        roF(j, W) { // j is the weight observed
            if (j - weights[i] >= 0) {
                dp[j] = max(dp[j - weights[i]] + values[i], dp[j]);
            }
        }
    }

    cout << *max_element(dp.begin(), dp.end());
}