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

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    ll Q; cin >> Q;
    For(i, Q) {
        ll N; cin >> N;
        v<ll> a(N);
        v<ll> b(N);
        For(i, N) cin >> a[i];
        For(i, N) cin >> b[i];
        sort(all(a));
        sort(all(b), greater<>());
        ll sum = 0;
        For(i, N) sum += a[i] * b[i];
        cout << "Case #" << i + 1 << ": " << sum << nl;
    }
        
}