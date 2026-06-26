#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define v vector
#define all(x) x.begin(), x.end()
#define pb push_back
#define For(i, a) for(ll i = 0; i < a; i++)
#define FOR(i, a, b) for(ll i = a; i < b; i++)
#define roF(i, a) for(ll i = a; i >= 0; i--)
#define ROF(i, a, b) for(ll i = a; i >= b; i--)
#define ss " "
#define nl "\n"

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll T; cin >> T;
    while(T--) {
        ll N; cin >> N;
        v<ll> a(N); v<ll> b(N);
        For(i, N) cin >> a[i]; For(i, N) cin >> b[i];
        v<v<v<ll>>> part;
        v<v<v<ll>>> new_part = {{a, b}};
        roF(bit, 30) {
            // identify if current bit can be used to partition
            bool flag = true;
            for(v<v<ll>> sect : new_part) {
                v<ll> count = {0, 0, 0, 0}; // a0, a1, b0, b1
                for(ll i : sect[0]) {
                    if ((i >> bit) & 1) count[0]++;
                    else count[1]++;
                }
                for(ll i : sect[1]) {
                    if ((i >> bit) & 1) count[2]++;
                    else count[3]++;
                }
                flag &= (count[0] == count[3]) && (count[1] == count[2]);
            }
            // if partition can occur
            if (flag) {
                part = new_part;
                new_part = {};
                for(v<v<ll>> sect : part) { // partitions into [a0, b1], [a1, b0]
                    v<v<ll>> n0 = {{}, {}};
                    v<v<ll>> n1 = {{}, {}};
                    for(ll i : sect[0]) { // a
                        if ((i >> bit) & 1) { // a1
                            n1[0].pb(i);
                        }
                        else { // a0
                            n0[0].pb(i);
                        }
                    }
                    for(ll i : sect[1]) { // b
                        if ((i >> bit) & 1) { // b1
                            n0[1].pb(i);
                        }
                        else { // b0
                            n1[1].pb(i);
                        }
                    }

                    if (n0[0].size() > 0 && n0[1].size() > 0) new_part.pb(n0);
                    if (n1[0].size() > 0 && n1[1].size() > 0) new_part.pb(n1);
                }
            }
        }
        ll ans = LLONG_MAX;
        for (v<v<ll>> sect : new_part) {
            For(i, sect[0].size()) {
                ans &= sect[0][i] ^ sect[1][i];
            }
        }
        cout << ans << nl;
    }
}