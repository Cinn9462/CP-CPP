#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define v vector
#define pb push_back
#define all(x) x.begin(), x.end()
#define For(i, a) for(ll i = 0; i < a; i++)
#define FOR(i, a, b) for(ll i = a; i < b; i++)
#define ss " "
#define nl "\n"

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll N; cin >> N; v<ll> h(N); For(i, N) cin >> h[i];
    v<set<ll>> visible(N);
    auto comp = [&](ll over, ll bk, ll cand) { // bk -> back of set, cand -> candidate
        return (h[cand] - h[over]) * (bk - over) >= (h[bk] - h[over]) * (cand - over);
    };

    // initial build
    For(i, N) {
        FOR(j, i + 1, N) {
            if (visible[i].empty()) visible[i].insert(j);
            else if (comp(i, *visible[i].rbegin(), j)) visible[i].insert(j);
        }
    }

    ll Q; cin >> Q;
    while(Q--) {
        ll x, inc; cin >> x >> inc;
        h[--x] += inc;

        // check if form new pairs/broke old pairs
        For(i, x) {
            auto it = visible[i].upper_bound(x);
            while(it != visible[i].end() && !comp(i, x, *it)) visible[i].erase(it++);
            if (visible[i].empty()) visible[i].insert(x);
            else if (comp(i, *--it, x)) visible[i].insert(x);
        }

        // rebuild x
        visible[x].clear();
        FOR(i, x + 1, N) {
            if (visible[x].empty()) visible[x].insert(i);
            else if (comp(x, *visible[x].rbegin(), i)) visible[x].insert(i);
        }

        // count visible
        ll ans = 0;
        For(i, N) {
            ans += visible[i].size();
        }
        cout << ans << nl;
    }
}