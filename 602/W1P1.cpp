#include <bits/stdc++.h>
using namespace std;
// #pragma GCC optimize("O3")

#define ll long long
#define v vector
#define pb push_back
#define For(i, a) for(ll i = 0; i < a; i++)
#define FOR(i, a, b) for(ll i = a; i < b; i++)
#define INF 1e18
#define ss " "
#define nl "\n"

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    ll T; cin >> T;
    while (T--) {
        ll N, a, b; cin >> N >> a >> b;
        string s; cin >> s;

        ll fixedOnes = 0;
        For(i, N) if (s[i] == '1') fixedOnes++;
        ll target = fixedOnes + b;

        v<ll> lastOne(N, -1), lastZero(N, -1);
        For(i, N) {
            if (i != 0) {
                lastOne[i] = lastOne[i - 1];
                lastZero[i] = lastZero[i - 1];
            }
            if (s[i] == '1') lastOne[i] = i;
            if (s[i] == '0') lastZero[i] = i;
        }

        auto check = [&](ll L) -> bool {
            v<ll> dp0min(N + 1, INF), dp1min(N + 1, INF);
            deque<ll> d0, d1;
            dp0min[0] = dp1min[0] = 0;
            d0.pb(0); d1.pb(0);

            FOR(i, 1, N + 1) {
                ll low0 = max(i - L, lastOne[i - 1] + 1);
                ll low1 = max(i - L, lastZero[i - 1] + 1);
                while(!d0.empty() && d0.front() < low0) d0.pop_front();
                while(!d1.empty() && d1.front() < low1) d1.pop_front();

                if (s[i - 1] == '1') {
                    dp1min[i] = d1.empty() ? INF : i + (dp0min[d1.front()] - d1.front());
                    dp0min[i] = INF;
                }
                if (s[i - 1] == '0') {
                    dp1min[i] = INF;
                    dp0min[i] = d0.empty() ? INF : dp1min[d0.front()];
                }
                if(s[i - 1] == '?') {
                    dp1min[i] = d1.empty() ? INF : i + (dp0min[d1.front()] - d1.front());
                    dp0min[i] = d0.empty() ? INF : dp1min[d0.front()];
                }

                if (dp1min[i] != INF) {
                    while(!d0.empty() && dp1min[d0.back()] >= dp1min[i]) d0.pop_back();
                    d0.pb(i);
                }
                if (dp0min[i] != INF) {
                    while (!d1.empty() && (dp0min[d1.back()] - d1.back()) >= dp0min[i] - i) d1.pop_back();
                    d1.pb(i);
                }
            }

        v<ll> dp0max(N + 1, -INF), dp1max(N + 1, -INF);
        d0.clear(); d1.clear();
        dp0max[0] = dp1max[0] = 0;
        d0.pb(0); d1.pb(0);

        FOR(i, 1, N + 1) {
            ll low0 = max(i - L, lastOne[i - 1] + 1);
            ll low1 = max(i - L, lastZero[i - 1] + 1);
            while(!d0.empty() && d0.front() < low0) d0.pop_front();
            while(!d1.empty() && d1.front() < low1) d1.pop_front();

            if (s[i - 1] == '1') {
                dp1max[i] = d1.empty() ? -INF : i + (dp0max[d1.front()] - d1.front());
                dp0max[i] = -INF;
            }
            if (s[i - 1] == '0') {
                dp1max[i] = -INF;
                dp0max[i] = d0.empty() ? -INF : dp1max[d0.front()];
            }
            if(s[i - 1] == '?') {
                dp1max[i] = d1.empty() ? -INF : i + (dp0max[d1.front()] - d1.front());
                dp0max[i] = d0.empty() ? -INF : dp1max[d0.front()];
            }

            if (dp1max[i] != -INF) {
                while(!d0.empty() && dp1max[d0.back()] <= dp1max[i]) d0.pop_back();
                d0.pb(i);
            }
            if (dp0max[i] != -INF) {
                while (!d1.empty() && (dp0max[d1.back()] - d1.back()) <= dp0max[i] - i) d1.pop_back();
                d1.pb(i);
            }
        }

        return min(dp0min[N], dp1min[N]) <= target && target <= max(dp0max[N], dp1max[N]);
    };

        ll left = 1, right = N;
        while (left < right) {
            ll mid = (left + right) / 2;
            if (check(mid)) right = mid;
            else left = mid + 1;
        }

        v<ll> p0min(N + 1, -1), p1min(N + 1, -1);
        v<ll> dp0min(N + 1, INF), dp1min(N + 1, INF);
        deque<ll> d0, d1;
        dp0min[0] = dp1min[0] = 0;
        d0.pb(0); d1.pb(0);

        FOR(i, 1, N + 1) {
            ll low0 = max(i - left, lastOne[i - 1] + 1);
            ll low1 = max(i - left, lastZero[i - 1] + 1);
            while(!d0.empty() && d0.front() < low0) d0.pop_front();
            while(!d1.empty() && d1.front() < low1) d1.pop_front();

            if (s[i - 1] == '1') {
                dp1min[i] = d1.empty() ? INF : i + (dp0min[d1.front()] - d1.front());
                p1min[i] = d1.empty() ? -1 : d1.front();
                dp0min[i] = INF;
            }
            if (s[i - 1] == '0') {
                dp1min[i] = INF;
                dp0min[i] = d0.empty() ? INF : dp1min[d0.front()];
                p0min[i] = d0.empty() ? -1 : d0.front();
            }
            if(s[i - 1] == '?') {
                dp1min[i] = d1.empty() ? INF : i + (dp0min[d1.front()] - d1.front());
                dp0min[i] = d0.empty() ? INF : dp1min[d0.front()];
                p0min[i] = d0.empty() ? -1 : d0.front();
                p1min[i] = d1.empty() ? -1 : d1.front();
            }

            if (dp1min[i] != INF) {
                while(!d0.empty() && dp1min[d0.back()] >= dp1min[i]) d0.pop_back();
                d0.pb(i);
            }
            if (dp0min[i] != INF) {
                while (!d1.empty() && (dp0min[d1.back()] - d1.back()) >= dp0min[i] - i) d1.pop_back();
                d1.pb(i);
            }
        }

        v<ll> p0max(N + 1, -1), p1max(N + 1, -1);
        v<ll> dp0max(N + 1, -INF), dp1max(N + 1, -INF);
        d0.clear(); d1.clear();
        dp0max[0] = dp1max[0] = 0;
        d0.pb(0); d1.pb(0);

        FOR(i, 1, N + 1) {
            ll low0 = max(i - left, lastOne[i - 1] + 1);
            ll low1 = max(i - left, lastZero[i - 1] + 1);
            while(!d0.empty() && d0.front() < low0) d0.pop_front();
            while(!d1.empty() && d1.front() < low1) d1.pop_front();

            if (s[i - 1] == '1') {
                dp1max[i] = d1.empty() ? -INF : i + (dp0max[d1.front()] - d1.front());
                p1max[i] = d1.empty() ? -1 : d1.front();
                dp0max[i] = -INF;
            }
            if (s[i - 1] == '0') {
                dp1max[i] = -INF;
                dp0max[i] = d0.empty() ? -INF : dp1max[d0.front()];
                p0max[i] = d0.empty() ? -1 : d0.front();
            }
            if(s[i - 1] == '?') {
                dp1max[i] = d1.empty() ? -INF : i + (dp0max[d1.front()] - d1.front());
                dp0max[i] = d0.empty() ? -INF : dp1max[d0.front()];
                p0max[i] = d0.empty() ? -1 : d0.front();
                p1max[i] = d1.empty() ? -1 : d1.front();
            }

            if (dp1max[i] != -INF) {
                while(!d0.empty() && dp1max[d0.back()] <= dp1max[i]) d0.pop_back();
                d0.pb(i);
            }
            if (dp0max[i] != -INF) {
                while (!d1.empty() && (dp0max[d1.back()] - d1.back()) <= dp0max[i] - i) d1.pop_back();
                d1.pb(i);
            }
        }

        ll stateMin = dp1min[N] < dp0min[N], stateMax = dp1max[N] > dp0max[N];

        string minSeq(N, '0'); ll i = N;
        while(i > 0) {
            if (stateMin == 1) {
                FOR(j, p1min[i], i) minSeq[j] = '1';
            }
            i = (stateMin == 0) ? p0min[i] : p1min[i];
            stateMin = !stateMin;
        }
        string maxSeq(N, '0'); i = N;
        while(i > 0) {
            if (stateMax == 1) {
                FOR(j, p1max[i], i) maxSeq[j] = '1';
            }
            i = (stateMax == 0) ? p0max[i] : p1max[i];
            stateMax = !stateMax;
        }

        v<ll> pMin(N + 1, 0), pMax(N + 1, 0);
        For(i, N) {
            pMin[i + 1] = pMin[i] + (minSeq[i] == '1');
            pMax[i + 1] = pMax[i] + (maxSeq[i] == '1');
        }

        string ans;
        For(i, N + 1) {
            if (pMin[i] + pMax[N] - pMax[i] == target && (i == 0 || minSeq[i - 1] != maxSeq[i])) {
                ans = minSeq.substr(0, i) + maxSeq.substr(i);
                break;
            }
        }
        cout << left << nl << ans << nl;
    }
}