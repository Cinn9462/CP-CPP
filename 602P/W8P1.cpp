#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define v vector
#define pb push_back
#define p pair
#define F first
#define S second
#define all(x) x.begin(), x.end()
#define ss " "
#define nl "\n"
#define For(i, a) for(ll i = 0; i < a; i++)
#define FOR(i, a, b) for(ll i = a; i < b; i++)
#define roF(i, a) for(ll i = a; i >= 0; i--)
#define ROF(i, a, b) for(ll i = a; i >= b; i--)

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll N; cin >> N;
    v<ll> b(N); For(i, N) cin >> b[i];
    v<p<ll, ll>> q;
    q.pb({b[0], 0});
    ll best = 0;
    FOR(i, 1, N) {
        ll start = i;
        while(!q.empty() && q.back().F > b[i]) {
            p<ll, ll> curr = {q.back().F, q.back().S};
            q.pop_back();
            best = max(best, (i - curr.S) * curr.F);
            start = curr.S;
        }
        q.pb({b[i], start});
    } 

    while(!q.empty()) {
        best = max(best, (N - q.back().S) * q.back().F);
        q.pop_back();
    }

    cout << best << nl;
}