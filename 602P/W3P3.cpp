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

ll p3[40];

void pow3() {
    p3[0] = 1;
    FOR(i, 1, 40) {
        p3[i] = p3[i - 1] * 3L;
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    // position, x carry, y carry, comp
    ll dp[40][2][2][3];
    pow3();

    ll Q; cin >> Q;
    while(Q--) {
        ll d, x, y; cin >> d >> x >> y;
        memset(dp, 0, sizeof(dp));
        dp[0][0][0][1] = 1;

        For(i, 39) {
            ll xdigit = x / p3[i] % 3;
            ll ydigit = y / p3[i] % 3;
            ll ddigit = d / p3[i] % 3;
            For(xcarry, 2) {
                For(ycarry, 2) {
                    For(comp, 3) {
                        For(k, 3) {
                            ll next_xdigit = (xdigit + xcarry + k) % 3;
                            ll next_ydigit = (ydigit + ycarry + k) % 3;
                            ll next_xcarry = (xdigit + xcarry + k) / 3;
                            ll next_ycarry = (ydigit + ycarry + k) / 3;
                            ll next_comp = comp;
                            if (k < ddigit) next_comp = 0;
                            if (k > ddigit) next_comp = 2;
                            if (next_xdigit % 2 == next_ydigit % 2) {
                                dp[i + 1][next_xcarry][next_ycarry][next_comp] += dp[i][xcarry][ycarry][comp];
                            }
                        }
                    }
                }
            }
        }

        cout << dp[39][0][0][1] + dp[39][0][0][0] << nl;
    }    
}