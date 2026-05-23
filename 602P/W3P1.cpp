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
#define fileread(file) ifstream fin; fin.open((string)file + ".in"); ofstream fout; fout.open((string)file + ".out")

ostream& operator<<(ostream& os, v<ll>& arr) {
    for (ll ___a : arr) {
        os << ___a << " ";
    }
    return os;
}

struct Cow {
    ll w, s, e; // weight, start, end
    Cow(ll a, ll b, ll c) : w(a), s(b), e(c) {} 
    Cow() {}
};

bool CowComp(const Cow &c1, const Cow &c2) {
    return c1.w > c2.w;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    fileread("pieaters");    

    ll NCK, NCW; fin >> NCK >> NCW;
    v<Cow> cows(NCW);
    For(i, NCW) {
        fin >> cows[i].w >> cows[i].s >> cows[i].e;
        cows[i].s--; cows[i].e--;
    }

    v<v<v<ll>>> mx(NCK, v<v<ll>>(NCK, v<ll>(NCK, 0))); // left endpoint, right endpoint, selectd pie

    for(Cow c : cows) {
        FOR(i, c.s, c.e + 1) mx[c.s][c.e][i] = max(c.w, mx[c.s][c.e][i]);
    }

    FOR(sz, 1, NCK) {
        For(i, NCK - sz) {
            For(k, NCK) {
                mx[i][i + sz][k] = max(max(mx[i + 1][i + sz][k], mx[i][i + sz - 1][k]), mx[i][i + sz][k]);
            }
        }
    }

    v<v<ll>> dp(NCK, v<ll>(NCK, 0));

    For(sz, NCK) {
        For(i, NCK - sz) {
            ll max_size = LLONG_MIN;
            For(k, sz + 1) {
                max_size = max(max_size, ((k+i-1 >= 0) ? dp[i][k + i - 1] : 0) + ((k+i+1 < NCK) ? dp[k + i + 1][i + sz] : 0) + mx[i][i + sz][k + i]);
            }

            dp[i][i + sz] = max((max_size == LLONG_MIN) ? 0 : max_size, dp[i][i + sz]);
        }
    }

    fout << dp[0][NCK - 1] << nl;
}