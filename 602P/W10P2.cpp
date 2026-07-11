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
    ll B = (ll) sqrt(max(max(N, M), Q));
    ll count_online; cin >> count_online;
    For(i, count_online) {
        ll x; cin >> x;
        online[x - 1] = true;
    }

    v<ll> count_online_light(N);
    v<unordered_set<ll>> heavy(N);

    // initialize heavy and light
    v<unordered_set<ll>> friends(N);
    For(i, M) {
        ll f1, f2; cin >> f1 >> f2; f1--; f2--;
        friends[f1].insert(f2);
        friends[f2].insert(f1);

        if (friends[f1].size() < B && online[f1]) count_online_light[f2]++; // f1 was always light
        if (friends[f1].size() > B) heavy[f2].insert(f1); // f1 was always heavy
        if (friends[f1].size() == B) { // f1 just became heavy
            for (ll f : friends[f1]) {
                heavy[f].insert(f1);
                if (online[f1] && f != f2) count_online_light[f]--; // f2 not decremented since f2 wasn't incremented earlier
            }
        }
        if (friends[f2].size() < B && online[f2]) count_online_light[f1]++; // f2 was always light
        if (friends[f2].size() > B) heavy[f1].insert(f2); // f2 was always heavy
        if (friends[f2].size() == B) { // f2 just became heavy
            for (ll f : friends[f2]) {
                heavy[f].insert(f2);
                if (online[f2] && f != f1) count_online_light[f]--; // f2 not decremented since f2 wasn't incremented earlier
            }
        }
    }

    // Print friends
    // for(auto fset : friends) {
    //     for(auto f : fset) cout << f << ss; 
    //     cout << nl;
    // }
    // Prints heavy
    // for(auto fset : heavy) {
    //     for(auto f : fset) cout << f << ss; 
    //     cout << nl;
    // }
    // Print counts
    // for (auto c : count_online_light) cout << c << ss;
    // cout << nl;

    while (Q--) {
        string type; cin >> type;
        if (type == "O") {
            ll f; cin >> f; f--;
            online[f] = true;
            if (friends[f].size() < B) { // light
                for (ll f1 : friends[f]) {
                    count_online_light[f1]++;
                }
            }
        }
        if (type == "F") {
            ll f; cin >> f; f--;
            online[f] = false;
            if (friends[f].size() < B) { // light
                for (ll f1 : friends[f]) {
                    count_online_light[f1]--;
                }
            }

        }
        if (type == "A") {
            ll f1, f2; cin >> f1 >> f2; f1--; f2--;
            friends[f1].insert(f2);
            friends[f2].insert(f1);

            if (friends[f1].size() < B && online[f1]) count_online_light[f2]++; // f1 was always light
            if (friends[f1].size() > B) heavy[f2].insert(f1); // f1 was always heavy
            if (friends[f1].size() == B) { // f1 just became heavy
                for (ll f : friends[f1]) {
                    heavy[f].insert(f1);
                    if (online[f1] && f != f2) count_online_light[f]--; // f2 not decremented since f2 wasn't incremented earlier
                }
            }
            if (friends[f2].size() < B && online[f2]) count_online_light[f1]++; // f2 was always light
            if (friends[f2].size() > B) heavy[f1].insert(f2); // f2 was always heavy
            if (friends[f2].size() == B) { // f2 just became heavy
                for (ll f : friends[f2]) {
                    heavy[f].insert(f2);
                    if (online[f2] && f != f1) count_online_light[f]--; // f2 not decremented since f2 wasn't incremented earlier
                }
            }
        }
        if (type == "D") {
            ll f1, f2; cin >> f1 >> f2; f1--; f2--;
            friends[f1].erase(f2);
            friends[f2].erase(f1);

            if (friends[f1].size() < B - 1 && online[f1]) count_online_light[f2]--; // f1 was always light
            if (friends[f1].size() > B - 1) heavy[f2].erase(f1); // f1 was always heavy
            if (friends[f1].size() == B - 1) { // f1 just became light
                heavy[f2].erase(f1);
                for (ll f : friends[f1]) {
                    heavy[f].erase(f1);
                    if (online[f1]) count_online_light[f]++; // every other f is incremented since f1 is now light
                }
            }
            if (friends[f2].size() < B - 1 && online[f2]) count_online_light[f1]--; // f2 was always light
            if (friends[f2].size() > B - 1) heavy[f1].erase(f2); // f2 was always heavy
            if (friends[f2].size() == B - 1) { // f2 just became light
                heavy[f1].erase(f2);
                for (ll f : friends[f2]) {
                    heavy[f].erase(f2);
                    if (online[f2]) count_online_light[f]++; // every other f is incremented since f2 is now light
                }
            }
        }
        if (type == "C") {
            ll f; cin >> f; f--;
            ll count = count_online_light[f];
            for (ll f1 : heavy[f]) count += online[f1];
            cout << count << nl;
        }
    }
}