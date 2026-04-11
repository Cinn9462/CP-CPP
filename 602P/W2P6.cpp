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

ostream& operator<<(ostream& os, v<ll>& arr) {
    for (ll ___a : arr) {
        os << ___a << " ";
    }
    return os;
}

struct PairHash {
    size_t operator()(const p<ll, ll>& p) const {
        return p.F * 479 + p.S;
    }
};

int main () {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);
    int N, xG, yG; cin >> N >> xG >> yG;
    
    v<int> x(N), y(N);
    for(int i = 0; i < N; i++) cin >> x[i] >> y[i];
    
    unordered_map<p<ll, ll>, unordered_map<int, ll>, PairHash> half; // cords -> directions used -> count
    int mid = N / 2;

    for(int bitmask = 0; bitmask < (1 << mid); bitmask++) {
        ll xi = 0; ll yi = 0;
        for(int i = 0; i < mid; i++) {
            xi += ((bitmask >> i) & 1) ? x[i] : 0;
            yi += ((bitmask >> i) & 1) ? y[i] : 0;
        }

        half[{xi, yi}][__builtin_popcount(bitmask)]++;
    }
    
    v<ll> ans(N + 1); // number of moves appended to ith index

    for(int bitmask = 0; bitmask < (1 << (N - mid)); bitmask++) {
        ll xi = xG; ll yi = yG;
        for(int i = 0; i < N - mid; i++) {
            xi -= ((bitmask >> i) & 1) ? x[i + mid] : 0;
            yi -= ((bitmask >> i) & 1) ? y[i + mid] : 0;
        }

        for(auto& [key, value] : half[{xi, yi}]) ans[__builtin_popcount(bitmask) + key] += value;
    }

    FOR(i, 1, N + 1) cout << ans[i] << nl;
}