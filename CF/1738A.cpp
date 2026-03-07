#define ll long long
#define pb push_back 
#define v vector
#define p pair
#define fileread(file) freopen(((string) file + ".in").c_str(), "r", stdin); freopen(((string) file + ".out").c_str(), "w", stdout)
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

#include <bits/stdc++.h>
using namespace std;

int main () {
    ll T;
    cin >> T;
    while (T--) {
        ll num_skills;
        cin >> num_skills;
        
        v<ll> type(num_skills), t1, t0;
        
        for (ll i = 0; i < num_skills; i++) {
            cin >> type[i];
        }
        
        ll p;
        for (ll i = 0; i < num_skills; i++) {
            cin >> p;
            if (type[i] == 1) {
                t1.push_back(p);
            }

            if (type[i] == 0) {
                t0.push_back(p);
            }
        }

        sort(t1.begin(), t1.end());
        sort(t0.begin(), t0.end());

        ll sum_0 = 0;
        ll sum_1 = 0;

        if (t0.size() > 0) { // sacrifice 0 first
            ll zero_index = (ll) t0.size() - 1;
            ll one_index = (ll) t1.size() - 1;
            ll count = 0;

            while(zero_index >= 0 && one_index >= 0) {
                if (count % 2 == 0) {
                    sum_0 += 2 * t0[zero_index--];
                    count++;
                }
                
                else {
                    sum_0 += 2 * t1[one_index--];
                    count++;
                }
            }

            if (zero_index != -1) {
                For (i, zero_index + 1) {
                    sum_0 += t0[i];
                }
            }

            else {
                For(i, one_index + 1) {
                    sum_0 += t1[i];
                }
            }
        }

        if (t1.size() > 0) { // sacrifice 1 first
            ll zero_index = (ll) t0.size() - 1;
            ll one_index = (ll) t1.size() - 1;
            ll count = 0;

            while(zero_index >= 0 && one_index >= 0) {
                if (count % 2 == 1) {
                    sum_1 += 2 * t0[zero_index--];
                    count++;
                }
                
                else {
                    sum_1 += 2 * t1[one_index--];
                    count++;
                }
            }

            if (zero_index != -1) {
                For (i, zero_index + 1) {
                    sum_1 += t0[i];
                }
            }

            else {
                For(i, one_index + 1) {
                    sum_1 += t1[i];
                }
            }
        }


        cout << max(sum_0, sum_1) << nl;
    }
}  