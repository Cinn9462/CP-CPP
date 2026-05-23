#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pb push_back 
#define v vector
#define p pair
#define F first
#define S second
#define For(i, end) for (ll i = 0; i < end; i++)
#define roF(i, begin) for (ll i = begin; i >= 0; i--)
#define FOR(i, begin, end) for (ll i = begin; i < end; i++) 
#define ROF(i, begin, end) for (ll i = begin; i > end; i--)
#define nl "\n"
#define ss " "
#define all(x) x.begin(), x.end()
#define popcount(x) __builtin_popcountll(x)
#define fileread(file) ifstream fin; fin.open((string)file + ".in"); ofstream fout; fout.open((string)file + ".out")

ostream& operator<<(ostream& os, v<ll>& arr) {
    for (ll ___a : arr) {
        os << ___a << " ";
    }
    return os;
}

struct Friend {
    ll P, C, X;
    Friend(ll p, ll c, ll x) : P(p), C(c), X(x) {}
    Friend() : P(0), C(0), X(0) {}
};

bool xsort(Friend f1, Friend f2) {
    return f1.X < f2.X;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll N, C, X; cin >> N >> C >> X; // c = moonies, x = ice creams
    v<Friend> nums(N);
    For(i, N) cin >> nums[i].P >> nums[i].C >> nums[i].X;
    sort(all(nums), xsort);

    v<ll> dp(C + X + 1, -1);
    dp[0] = 0;

    for (Friend c : nums) {
        roF(i, C + X - c.C) {
            if (dp[i] == -1) continue;
            // spending all moonies
            if (i >= X) dp[i + c.C] = max(dp[i + c.C], dp[i] + c.P);
            // spending all ice creams
            else if (X - i >= c.C * c.X) dp[i + c.C * c.X] = max(dp[i + c.C * c.X], dp[i] + c.P);
            // spending a hybrid amount
            else dp[X + (c.C - ((X - i) / c.X))] = max(dp[X + (c.C - ((X - i) / c.X))], dp[i] + c.P);
        }
    }

    cout << *max_element(all(dp)) << nl;
}