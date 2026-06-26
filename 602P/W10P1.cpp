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
    ll N, Q; cin >> N >> Q;
    ll sz = (ll) (sqrt(N * log(N))); // size of each block
    v<v<ll>> blocks((N + sz - 1) / sz);
    v<ll> nums(N);

    For(i, N) {
        cin >> nums[i];
        blocks[i / sz].pb(nums[i]);
    }
    for(v<ll>& b : blocks) sort(all(b));
    while(Q--) {
        // for(v<ll>& b : blocks) {for(ll e : b) cout << e << ss; cout << nl;} 

        string t; cin >> t;
        if (t == "M") {
            ll idx, v; cin >> idx >> v;
            idx--;
            blocks[idx / sz].erase(find(all(blocks[idx / sz]), nums[idx]));
            blocks[idx / sz].insert(lower_bound(all(blocks[idx / sz]), v), v);
            nums[idx] = v;
        }
        else {
            ll start, end, x; cin >> start >> end >> x;
            ll ans = 0;
            start--; end--;
            // cout << "Binary search over [" << start / sz + 1 << ", " << end / sz - 1 << "]" << nl;
            FOR(i, start / sz + 1, end / sz) {
                ans += upper_bound(all(blocks[i]), x) - blocks[i].begin();
            }
            // cout << ans << nl;
            // cout << "Manual search over " << start / sz << " staring from " << start % sz << nl;
            FOR(i, start, min(end + 1, (start / sz + 1) * sz)) {
                if (nums[i] <= x) ans++;
            }
            // cout << ans << nl;
            // cout << "Manual search over " << end / sz << " ending at " <<  end % sz << nl;
            if (start / sz != end / sz) {
                FOR(i, (end / sz) * sz, end + 1) {
                    if (nums[i] <= x) ans++;
                }
            }

            cout << ans << nl;
        }
    }
}