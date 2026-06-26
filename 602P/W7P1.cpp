#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define v vector
#define p pair
#define F first
#define S second
#define all(x) x.begin(), x.end()
#define pb push_back
#define ss " "
#define nl "\n"
#define For(i, a) for(ll i = 0; i < a; i++)
#define FOR(i, a, b) for(ll i = a; i < b; i++)
#define roF(i, a) for(ll i = a; i <= 0; i--)
#define ROF(i, a, b) for(ll i= a; i <= b; i--)

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll N; cin >> N; 
    
    v<ll> nums(N);
    v<v<ll>> connected(60);
    For(i, N) {
        cin >> nums[i];
        ll bit = 0;
        ll parse = nums[i];
        while(parse > 0) {
            if (parse & 1) connected[bit].pb(i);
            bit++;
            parse /= 2;
        }
    }

    for (v<ll> path : connected) {
        if (path.size() >= 3) {
            cout << 3;
            return 0;
        }
    }

    v<set<ll>> adj(N);
    for(v<ll> c : connected) {
        for(ll x : c) {
            for(ll y : c) {
                if (x != y) adj[x].insert(y);
            }
        }
    }
    ll cycle = LLONG_MAX;
    
    For(i, N) {
        deque<v<ll>> q;
        map<ll, ll> visited; // node -> depth found
        q.pb({0, i, -1});
        visited[i] = 0;
        while(!q.empty()) {
            ll d = q.front()[0];
            ll u = q.front()[1];
            ll p = q.front()[2];
            q.pop_front();

            for(ll c : adj[u]) {
                if (c != p && visited.count(c) != 0) {
                    // cout << u << ss << p << nl << d << ss << visited[c] << nl;
                    cycle = min(cycle, d + visited[c]);
                }
                else if (c != p && visited.count(c) == 0) {
                    q.pb({d + 1, c, u});
                    visited[c] = d + 1;
                }
            }
        }
    }

    cout << (cycle == LLONG_MAX ? -1 : cycle + 1) << nl;
}