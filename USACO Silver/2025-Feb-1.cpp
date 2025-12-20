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

    ll t; cin >> t;
    For(_i, t) {

        ll N;
        cin >> N;
        
        map<ll, v<ll>, greater<ll>> nums;
        ll _n;

        For(i, N) {
            cin >> _n;
            if (nums.count(_n) == 0) {
                nums[_n] = {(ll) i};
            }

            else {
                nums[_n].pb(i);
            }
        }

        v<ll> ideal = {};
        ll last_index = -1;
        ll last_last_index = -1;

        bool operation = true;

        for (auto &[num, indices] : nums) {
            if (indices.size() == 1) {
                // cout << num << " " << last_index << " " << last_last_index << endl;

                if (indices[0] > last_index) {
                    ideal.pb(num);
                    last_last_index = last_index;
                    last_index = indices[0];
                    
                }

                else if (operation && indices[0] > last_last_index) {
                    operation = false;
                    ideal.pb(num);
                    last_index = indices[0];
                    // last last index no longer matters since operation is completed
                }
            }

            else { // duplicate numbers
                sort(indices.begin(), indices.end());

                for (ll i : indices) {
                    if (operation && i > last_last_index && i < last_index) {
                        operation = false;
                        ideal.pb(num);
                        last_index = i;
                    }

                    else if (i > last_index) {
                        ideal.pb(num);
                        last_last_index = last_index;
                        last_index = i;            
                    }
                }
            }
        }

        For(i, (ll) (ideal.size()) - 1) {
            cout << ideal[i] << " ";
        }
        cout << ideal.back() << endl;
    }
}
