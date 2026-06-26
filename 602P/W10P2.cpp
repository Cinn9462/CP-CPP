#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define v vector
#define pb push_back
#define all(x) x.begin(), x.end()
#define For(i, a) for(ll i = 0; i < a; i++)
#define FOR(i, a, b) for(ll i = a; i < b; i++)
#define roF(i, a) for(ll i = a; i >= 0; i--)
#define ROF(i, a, b) for(l i = a; i >= b; i--)
#define ss " "
#define nl "\n"

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll N, M, Q; cin >> N >> M >> Q;
    v<bool> online(N);
    v<unordered_map<ll>> friends(N);
    ll B = (ll) sqrt(max(max(N, M), Q));

    ll count_online; cin >> count_online;
    For(i, count_online) {
        ll x; cin >> x;
        online[x - 1] = true;
    }

    v<ll> light(N);
    v<unordered_set> heavy(N);
    // initialize heavy and light

    v<unordered_set> friends(N); ll f1, f2;
    For(i, M) {
        cin >> f1 >> f2;
        friends[f1 - 1].insert(f2 - 1);
        friends[f2 - 1].insert(f1 - 1);
    }

}