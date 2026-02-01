#define ll long long
#define pb push_back 
#define v vector
#define p pair
#define fileread(file) freopen(((string) file + ".in").c_str(), "r", stdin); freopen(((string) file + ".out").c_str(), "w", stdout)
#define INF 1000000000000000000
#define inf 1000000001
#define MP(x, y) make_pair(x, y)
#define F first
#define S second
#define For(i, end) for (ll i = 0; i < end; i++)
#define f0r(i, begin, end) for (ll i = begin; i < end; i++) 
#define nl "\n"
#define ss " "
#define un_map unordered_map
#define un_set unordered_set

#include <bits/stdc++.h>
using namespace std;

ostream& operator<<(ostream& os, pair<ll, ll>& p) {
    return os << "[" << p.F << " " << p.S << "]";
}
ostream& operator<<(ostream& os, v<ll>& arr) {
    for (ll ___a : arr) {
        os << ___a << " ";
    }
    return os;
}

struct PairHash {
    size_t operator()(const pair<ll,ll>& p) const {
        return hash<ll>()(p.F) ^ (hash<ll>()(p.S) << 1);
    }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    ll t; cin >> t;
    For(_t, t) {
        ll length, window_size;
        string bits;
        cin >> length >> window_size >> bits;

        v<v<ll>> pairs;
        
        For(start, window_size) {
            v<ll> pair = {1, 0}; // {first index, !first index}
            ll curr = 0;
            ll i = start;
            while (i + window_size < length) {
                if (bits[i] != bits[i + 1]) {
                    curr++;
                }

                pair[curr % 2]++;
                i += window_size;
            }
            pairs.pb(pair);
        }

        // for (auto p : pairs) {
        //     cout << p[0] << ss << p[1] << nl;
        // }

        ll max_sum = 0;
        ll min_sum = 0;
        ll max_first_window = 0;
        ll min_first_window = 0;
        ll min_difference = LLONG_MAX;
        for(v<ll> p : pairs) {
            max_first_window += min_element(p.begin(), p.end()) - p.begin();
            min_first_window += max_element(p.begin(), p.end()) - p.begin();
            max_sum += max(p[0], p[1]);
            min_sum += min(p[0], p[1]);
            min_difference = min(min_difference, abs(p[0] - p[1]));
        }

        if (max_first_window % 2 != bits[0] - '0') {
            max_sum -= min_difference;
        }

        if (min_first_window % 2 != bits[0] - '0') {
            min_sum += min_difference;
        }

        cout << min_sum << ss << max_sum << nl;
    }
}