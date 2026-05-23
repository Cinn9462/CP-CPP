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

    ll N, S; cin >> N >> S;
    v<v<ll>> apps(N, v<ll>(3, 0));
    For(i, N) {
        cin >> apps[i][0] >> apps[i][1];
        apps[i][2] = i;
    }

    v<v<ll>> sorted_apps(apps);

    sort(all(sorted_apps), [&](v<ll> &a, v<ll> &b){return a[1] - a[0] < b[1]  - b[0];});

    v<ll> dp(S + 1, -1);
    v<v<bool>> taken(N, v<bool>(S + 1));

    dp[0] = 0;

    For(i, N) {
        ll download = sorted_apps[i][0];
        ll disk = sorted_apps[i][1];
        roF(j, S) {
            if (dp[j] != -1 && j + max(download, disk) <= S && dp[j] + 1 > dp[j + disk]) {
                dp[j + disk] = dp[j] + 1;
                taken[i][j + disk] = true;
            }
        }
    }

    ll largest = *max_element(all(dp));
    v<ll> ans;

    For(i, S + 1) {
        if (dp[i] == largest) {
            ll curr = i; // Find correct weight
            roF(j, N - 1) {
                if(taken[j][curr]) {
                    ans.pb(sorted_apps[j][2]);
                    curr -= sorted_apps[j][1]; // subtract disk
                }
            }
            break;
        }
    }

    cout << ans.size() << nl;
    roF(i, ans.size() - 1) cout << ans[i] + 1 << ss;
}