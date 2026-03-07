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
#define f0r(i, begin, end) for (ll i = begin; i < end; i++) 
#define nl "\n"
#define ss " "
#define un_map unordered_map
#define un_set unordered_set

#include <bits/stdc++.h>
using namespace std;

ostream& operator<<(ostream& os, pair<ll, ll>& p) {
    return os << "[" << p.F << " " << p.S << "]";
}
ostream& operator<<(ostream& os, v<ll>& arr) {
    for (ll ___a : arr) {
        os << ___a << " ";
    }
    return os;
}
ostream& operator<<(ostream& os, deque<ll>& arr) {
    for (ll ___a : arr) {
        os << ___a << " ";
    }
    return os;
}
struct PairHash {
    size_t operator()(const pair<ll,ll>& p) const {
        return hash<ll>()(p.F) ^ (hash<ll>()(p.S) << 1);
    }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll N; cin >> N;
    v<v<ll>> cost(N, {0, 0, 0});

    For (i, N) {
        cin >> cost[i][0] >> cost[i][1] >> cost[i][2];
    }

    v<v<ll>> dp(N, {0, 0, 0});
    dp[0] = {cost[0][0], cost[0][1], cost[0][2]};

    f0r(i, 1, N ) {
        dp[i][0] = cost[i][0] + max(dp[i - 1][1], dp[i - 1][2]);
        dp[i][1] = cost[i][1] + max(dp[i - 1][0], dp[i - 1][2]);
        dp[i][2] = cost[i][2] + max(dp[i - 1][0], dp[i - 1][1]);
    }

    cout << max(max(dp[N - 1][0], dp[N - 1][1]), dp[N - 1][2]);
}