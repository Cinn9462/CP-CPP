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
#define popcount(x) __builtin_popcount(x)

ostream& operator<<(ostream& os, v<ll>& arr) {
    for (ll ___a : arr) {
        os << ___a << " ";
    }
    return os;
}

int main () {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);
    int N, M; cin >> N >> M; // vertices, edges
    
    v<ll> adj(N);
    for (int i = 0; i < M; i++) {
        int x, y; cin >> x >> y;
        adj[x] |= (1 << y);
        adj[y] |= (1 << x);
    }

    int mid = N / 2;

    v<int> dp(1 << mid);

    for(int bitmask = 0; bitmask < (1 << mid); bitmask++) {
        ll adjmask = 0; // tracks all neighbors
        for(int i = 0; i < mid; i++) {
            if ((bitmask >> i) & 1) adjmask |= adj[i];
        }

        if ((bitmask & (adjmask & ((1 << mid) - 1))) == 0) { // is a independent set
            dp[bitmask] = bitmask;
        }

        for(int i = 0; i < mid; i++) {
            if ((bitmask >> i) & 1) dp[bitmask] = (popcount(dp[bitmask]) > popcount(dp[bitmask ^ (1 << i)])) ? dp[bitmask] : dp[bitmask ^ (1 << i)];
        }
    }

    ll max_bm = 0;

    // for (int i : dp) {
    //     cout << i << ss;
    // }
    // cout << nl;  

    for(int bitmask = 0; bitmask < (1 << (N - mid)); bitmask++) {
        ll adjmask = 0; // tracks all neighbors
        for(int i = 0; i < (N - mid); i++) {
            if ((bitmask >> i) & 1) adjmask |= adj[i + mid];
        }

        if ((bitmask & (adjmask >> mid)) == 0) {

            // for(int i = 0; i < N; i++) {
            //     cout << ((adjmask >> i) & 1);
            // }
            // cout << nl;

            adjmask = ~adjmask;
            adjmask &= ((1 << mid) - 1);
            // cout << bitmask << ss << adjmask << nl;
            max_bm = (popcount(max_bm) > popcount(bitmask << mid | dp[adjmask])) ? max_bm : bitmask << mid | dp[adjmask];
        }
    }

    cout << popcount(max_bm) << nl;
    for(int i = 0; i < N; i++) {
        if ((max_bm >> i) & 1) cout << i << ss;
    }
}