#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define v vector
#define pb push_back
#define all(x) x.begin(), x.end()
#define For(i, a) for(ll i = 0; i < a; i++)
#define FOR(i, a, b) for(ll i = a; i < b; i++)
#define roF(i, a) for(ll i = a; i >= 0; i--)
#define ROF(i, a, b) for(ll i = a; i >= b; i--)
#define ss " "
#define nl "\n"

struct Rect {
    ll x, y, penalty;
};

struct Line{
    ll m, b; // m is -xj, b is dp[j]
    ll inter_top, inter_bottom;
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll N; cin >> N;
    v<Rect> rects;
    For(i, N) {
        Rect r; cin >> r.x >> r.y >> r.penalty;
        rects.pb(r);
    }
    sort(all(rects), [&](Rect& r1, Rect& r2){return r1.x < r2.x;});
    v<ll> dp(N);
    deque<Line> hull;
    Line start; start.m = 0; start.b = 0; start.inter_top = LLONG_MAX, start.inter_bottom = 1;
    hull.pb(start);
    For(i, N) {
        // cout << "Query " << i << nl;
        // cout << "Hull:" << nl;
        // for (Line l : hull) cout << l.m << ss << l.b << ss <<((double)l.inter_top / l.inter_bottom) << nl;
        Rect r = rects[i];
        while (hull.size() >= 2 && (__int128) hull[1].inter_top > r.y * hull[1].inter_bottom) {
            hull.pop_front();
        }
        // cout << "Hull:" << nl;
        // for (Line l : hull) cout << l.m << ss << l.b << ss <<((double)l.inter_top / l.inter_bottom) << nl;
        dp[i] = r.x * r.y - r.penalty + hull[0].m * r.y + hull[0].b;
        Line next; next.m = -r.x; next.b = dp[i];
        while (hull.size() >= 2 && next.b > hull.back().b && (__int128) (next.b - hull.back().b) * (hull[hull.size() - 2].m - hull.back().m) >= (__int128) (hull.back().b - hull[hull.size() - 2].b) * (hull.back().m - next.m)) {
            hull.pop_back();
        }
        if (next.b > hull.back().b) {
            next.inter_top = next.b - hull.back().b;
            next.inter_bottom = hull.back().m - next.m;
            hull.pb(next);
        }
    }

    cout << *max_element(all(dp)) << nl;
    // for (ll i : dp) cout << i << ss;
    // cout << nl;
}