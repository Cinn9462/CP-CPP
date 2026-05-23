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

ostream& operator<<(ostream& os, v<ll>& arr) {
    for (ll ___a : arr) {
        os << ___a << " ";
    }
    return os;
}
    
int main () {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);
    ll N, M; cin >> N >> M; // vertices, edges
    
    v<ll> adj(N);
    for (ll i = 0; i < M; i++) {
        ll x, y; cin >> x >> y;
        adj[x] |= (1LL << y);
        adj[y] |= (1LL << x);
    }

    ll mid = N / 2;

    v<ll> dp(1LL << mid);

    for(ll bitmask = 0; bitmask < (1LL << mid); bitmask++) {
        ll adjmask = 0; // tracks all neighbors
        for(ll i = 0; i < mid; i++) {
            if ((bitmask >> i) & 1LL) adjmask |= adj[i];
        }

        if ((bitmask & (adjmask & ((1LL << mid) - 1LL))) == 0) { // is a independent set
            dp[bitmask] = bitmask;
        }

        for(ll i = 0; i < mid; i++) {
            if ((bitmask >> i) & 1LL) dp[bitmask] = (popcount(dp[bitmask]) > popcount(dp[bitmask ^ (1LL << i)])) ? dp[bitmask] : dp[bitmask ^ (1LL << i)];
        }
    }

    ll max_bm = 0;

    // for (ll i : dp) {
    //     cout << i << ss;
    // }
    // cout << nl;  

    for(ll bitmask = 0; bitmask < (1LL << (N - mid)); bitmask++) {
        ll adjmask = 0; // tracks all neighbors
        for(ll i = 0; i < (N - mid); i++) {
            if ((bitmask >> i) & 1LL) adjmask |= adj[i + mid];
        }

        if ((bitmask & (adjmask >> mid)) == 0) {

            // for(ll i = 0; i < N; i++) {
            //     cout << ((adjmask >> i) & 1LL);
            // }
            // cout << nl;

            adjmask = ~adjmask;
            adjmask &= ((1LL << mid) - 1LL);
            // cout << bitmask << ss << adjmask << nl;
            max_bm = (popcount(max_bm) > popcount(bitmask << mid | dp[adjmask])) ? max_bm : bitmask << mid | dp[adjmask];
        }
    }

    cout << popcount(max_bm) << nl;
    for(ll i = 0; i < N; i++) {
        if ((max_bm >> i) & 1LL) cout << i << ss;
    }
}