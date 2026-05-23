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

    ll N, r; cin >> N >> r;
    v<p<ll, ll>> pos_projects;
    v<p<ll, ll>> neg_projects;

    For(i, N) {
        p<ll, ll> p; // req, change
        cin >> p.F >> p.S;
        if (p.S >= 0) pos_projects.pb(p);
        else neg_projects.pb(p);
    }

    sort(all(pos_projects), [&](p<ll, ll> &a, p<ll, ll> &b){return a.F < b.F;});
    sort(all(neg_projects), [&](p<ll, ll> &a, p<ll, ll> &b){return a.F + a.S > b.F + b.S;});

    v<ll> dp(6e4 + 1, -1);
    dp[r] = 0;
    
    For(i, pos_projects.size()) {
        roF(j, 6e4) {
            if (dp[j] != -1 && j >= pos_projects[i].F && dp[j] + 1 > dp[j + pos_projects[i].S]) {
                dp[j + pos_projects[i].S] = dp[j] + 1;
            }
        }
    }

    For(i, neg_projects.size()) {
        For(j, 6e4 + 1) {
            if (dp[j] != -1 && j >= neg_projects[i].F && j + neg_projects[i].S >= 0 && dp[j] + 1 > dp[j + neg_projects[i].S]) {
                dp[j + neg_projects[i].S] = dp[j] + 1;
            }
        }
    }

    cout << *max_element(all(dp)) << nl;
}