#define ll long long
#define pb push_back 
#define v vector
#define p pair
#define fileread(file) ifstream fin; fin.open((string)file + ".in"); ofstream fout; fout.open((string)file + ".out")
#define INF 1000000000000000000
#define inf 1000000001
#define MP(x, y) make_pair(x, y)
#define F first
#define S second
#define For(i, end) for (ll i = 0; i < end; i++)
#define f0r(i, begin, end) for (ll i = begin; i < end; i++) 
#define nl "\n"
#define ss " "

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

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    ll _t;
    cin >> _t;
    For (i, _t) {

        ll N, goal;
        cin >> N >> goal;

        v<ll> nums;
        unordered_map<ll, ll> count_nums; // tracks how many n's are in the nums array 
        ll num;

        For(i, N) {
            cin >> num;

            num %= goal;
            nums.pb(num);

            count_nums[num]++;
        }

        sort(nums.begin(), nums.end());

        // local max occurs when a number switches from increasing to decreasing after x = n
        // local min occurs when a number switches from decreasing to increasing after x = n

        // eval x, then eval switches

        map<ll, v<ll>> events;

        for(auto &[key, count] : count_nums) {

            events[key].pb(-count);

            ll distance = (key < goal / 2) ? (goal + 1) / 2 : - goal / 2;
            events[key + distance].pb(count);
        }

        ll curr_count = 0;
        ll curr_add = 0;
        ll curr_sub = 0;
        ll curr_x = 0;

        for(ll n: nums) {
            curr_count += min(n, goal - n);

            if (n < goal / 2) {
                curr_sub++;
            }
    
            else {
                curr_add++;
            }
        }

        ll min_count = curr_count;

        for(auto &[x, event] : events) {

            for (ll e : event) {
                if (goal % 2 == 1 && e > 0 && x != 0) {
                    curr_count -= e;
                }
            }

            if (x != 0) {
                curr_count += (x - curr_x) * (curr_add - curr_sub);
                min_count = min(min_count, curr_count);
                
            }
            
            for (ll e : event) {
                curr_add -= e;
                curr_sub += e;
            }

            curr_x = x;
        }

        cout << min_count << nl;
    }
}