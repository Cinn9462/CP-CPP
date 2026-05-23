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

struct Piece {
    ll low, net, length;
    Piece(ll l, ll n, ll le) : low(l), net(n), length(le) {}
    Piece() : low(0), net(0), length(0) {}
};

bool pos_comp(Piece p1, Piece p2) {
    return p1.low < p2.low;
}

bool neg_comp(Piece p1, Piece p2) {
    return p1.net + p1.low > p2.net + p2.low;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll N; cin >> N;
    v<Piece> neg;
    v<Piece> pos;
    string s;
    For(i, N) {
        cin >> s;
        ll count = 0;
        Piece p = Piece();

        For(j, s.size()) {
            count += (s[j] == '(') ? 1 : -1;
            p.low = max(p.low, -count);
        }

        p.net = count;
        p.length = s.size();
        
        if (p.net < 0) neg.pb(p);
        else pos.pb(p);
    }

    sort(all(pos), pos_comp);
    sort(all(neg), neg_comp); 

    // valid indices are only positive, only up to 300*300
    v<ll> dp(300*300+1, -1);
    dp[0] = 0;

    for (Piece p : pos) roF(i, 300*300) if (dp[i] != -1 && i - p.low >= 0) dp[i + p.net] = max(dp[i] + p.length, dp[i + p.net]);
    for (Piece p : neg) For(i, 300*300+1) if (dp[i] != -1 && i - p.low >= 0) dp[i + p.net] = max(dp[i] + p.length, dp[i + p.net]);

    cout << dp[0] << nl;
}