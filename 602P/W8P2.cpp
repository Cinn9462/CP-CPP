#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define v vector
#define pb push_back
#define all(x) x.begin(), x.end()
#define p pair
#define F first
#define S second
#define For(i, a) for(ll i = 0; i < a; i++)
#define FOR(i, a, b) for(ll i = a; i < b; i++)
#define roF(i, a) for(ll i = a; i >= 0; i--)
#define ROF(i, a, b) for(ll i = a; i >= b; i--)
#define ss " "
#define nl "\n"

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll N, M; cin >> N >> M;
    v<v<ll>> adj(N);
    ll v1, v2;
    For(i, M) {
        cin >> v1 >> v2;
        adj[v1 - 1].pb(v2 - 1);
        adj[v2 - 1].pb(v1 - 1);
    }

    map<ll, ll> cnt; // sz -> count
    set<ll> global_v;
    
    auto dfs = [&](auto&& dfs, ll u, set<ll>& v) -> void {
        for (ll c : adj[u]) {
            if (v.count(c) == 0) {
                global_v.insert(c);
                v.insert(c);
                dfs(dfs, c, v);
            }
        }
    };

    For(i, N) {
        if (global_v.count(i) == 0) {
            set<ll> curr_v;
            curr_v.insert(i);
            dfs(dfs, i, curr_v);
            cnt[curr_v.size()]++;
        }
    }
    
    v<ll> dp_new(N + 1, -1);
    dp_new[0] = 0;
    v<ll> dp_old;
    deque<ll> mono; // store indexes
    for (auto& [n, c] : cnt) {
        dp_old = dp_new;
        For(r, n) {
            mono = {};
            for(ll i = r; i <= N; i += n) {
                // remove old elements
                while(!mono.empty() && (mono.front() < i - c * n)) mono.pop_front();
                if (dp_new[i] == -1 && mono.empty()) continue;
                // eval current dp space
                if (dp_new[i] == -1 && !mono.empty()) dp_new[i] = (i - mono.front()) / n + dp_old[mono.front()];
                else if (!mono.empty()) dp_new[i] = min((i - mono.front()) / n + dp_old[mono.front()], dp_old[i]);
                // consider current space for mono
                if (dp_old[i] != -1) {
                    while(!mono.empty() && ((i - mono.back()) / n) + dp_old[mono.back()] >  dp_new[i]) mono.pop_back();
                    mono.pb(i);
                }
            }
        }

        // for (ll i : dp_new) {
        //     cout << i << ss;
        // }
        // cout << nl;
    }

    v<ll> targets;
    auto dfs2 = [&](auto&& dfs2, ll n) {
        if (n > N) return;
        targets.pb(n);
        dfs2(dfs2, n*10 + 4);
        dfs2(dfs2, n*10 + 7);
    };
    dfs2(dfs2, 4);
    dfs2(dfs2, 7);

    ll ans = LLONG_MAX;
    for(ll t : targets) {
        if (t <= N && dp_new[t] != -1) ans = min(ans, dp_new[t]);
    }
    cout << ((ans == LLONG_MAX) ? -1 : ans - 1) << nl;
}