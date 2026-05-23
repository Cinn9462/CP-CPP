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

    ll N, type; cin >> N >> type;
    v<ll> parent(N);
    v<v<ll>> children(N);
    v<ll> growth(N);
    For(i, N - 1) {
        cin >> parent[i + 1] >> growth[i + 1];
        parent[i + 1]--;
        children[parent[i + 1]].pb(i + 1);
    }
    
    v<ll> size(N, 1);
    v<ll> depth(N, 1);
    v<ll> rate(growth);
    v<ll> dp_0(N); 
    v<ll> dp_1(N);

    roF(i, N - 1) {
        
        sort(all(children[i]), [&](ll &a, ll &b) {return rate[a] * size[b] > rate[b] * size[a];});
        ll time_0 = 0;
        ll max_depth = 0;

        for (ll c : children[i]) {
            max_depth = max(max_depth, depth[c]);
            size[i] += size[c];
            rate[i] += rate[c];

            dp_0[i] += dp_0[c];
            dp_0[i] += (time_0 + 1) * rate[c];
            time_0 += 2 * size[c];
        }

        if (!children[i].empty()) {
            dp_1[i] = LLONG_MAX;
            ll running_rate = rate[i] - growth[i];
            ll time_1 = 0;

            for (ll c : children[i]) {
                running_rate -= rate[c];
                if (depth[c] == max_depth) {

                    // current state - cost of previous state - cost of previous states behind pushed back + add after waiting for all + max internal rate
                    dp_1[i] = min(dp_0[i] - dp_0[c] - 2 * size[c] * running_rate + (time_0 - time_1 - 2*size[c]) * rate[c] + dp_1[c], dp_1[i]);
                }
                time_1 += 2 * size[c];
            }

            depth[i] += max_depth;
        }
    }

    if (type == 0) cout << 2 * (N - 1) << ss << dp_0[0] << nl;
    if (type == 1) cout << 2 * (N - 1) - depth[0] + 1 << ss << dp_1[0] << nl;
}