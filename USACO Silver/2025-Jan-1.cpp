#define ll long long
#define pb push_back 
#define v vector
#define fileread(file) ifstream fin; fin.open((string)file + ".in"); ofstream fout; fout.open((string)file + ".out")
#define MP(x, y) make_pair(x, y)
#define F first
#define S second
#define For(i, end) for (ll i = 0; i < end; i++)
#define f0r(i, begin, end) for (ll i = begin; i < end; i++) 

#include <bits/stdc++.h>
using namespace std;

ostream& operator<<(ostream& os, pair<ll, ll>& p) {
    return os << p.F << " " << p.S;
}
ostream& operator<<(ostream& os, v<ll>& arr) {
    for (ll ___a : arr) {
        os << ___a << " ";
    }
    return os;
}

int main() {
    ll num_cows; 
    cin >> num_cows; // same as # species

    vector<ll> position;
    
    ll _p;
    For (i, num_cows) {
        cin >> _p; 
        position.pb(_p - 1);
    }

    vector<vector<ll>> ideal; // ideal[species] = [locations]
    ideal.resize(num_cows);

    For (i, num_cows) {
        cin >> _p;
        ideal[_p - 1].pb(i);
    }

    // for(vector<ll> arr : ideal) {
    //     cout << arr << endl;
    // } 

    vector<vector<ll>> edge; // edge[species] = [distance to edges]
    edge.resize(num_cows);
    For(i, num_cows) {
        for (ll pos : ideal[i]) {
            edge[i].pb(min(pos + 1, num_cows - pos));
        }

        sort(edge[i].begin(), edge[i].end());
    }

    // for(vector<ll> arr : edge) {
    //     cout << arr << endl;
    // } 

    vector<vector<ll>> prefix; // prefix[species] = [prefix array of edges squared]
    prefix.resize(num_cows);

    For(i, num_cows) {
        prefix[i].pb(0);
        for (ll pos : edge[i]) {
            prefix[i].pb(prefix[i].back() + pos);
        }
    }

    // for(vector<ll> arr : prefix) {
    //     cout << arr << endl;
    // }

    // Iterate by cow
    ll ans = 0;

    For (i, num_cows) { // i denotes position, position[i] denotes species

        if (count(ideal[position[i]].begin(), ideal[position[i]].end(), i) > 0) {
            ans += ((i + 1) * i)/2;
            ans += (num_cows - i - 1) * (num_cows - i) / 2;
            //  cout << ((i + 1) * i)/2 << " " << (num_cows - i - 1) * (num_cows - i) / 2 << endl;
        }


        ll curr_dist = min(i + 1, num_cows - i);
        ll index = upper_bound(edge[position[i]].begin(), edge[position[i]].end(), curr_dist) - edge[position[i]].begin();

        // cout << edge[position[i]] << endl;
        // cout << index << endl;


        ans += prefix[position[i]][index];
        ans += curr_dist * (ideal[position[i]].size() - index);

        // cout << "Total countributions: " << ans << endl;
    }

    cout << ans << endl;
}