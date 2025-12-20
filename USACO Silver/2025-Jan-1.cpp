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
    ios::sync_with_stdio(0); cin.tie(0);

    ll num_cows; 
    cin >> num_cows;

    v<ll> position;
    
    ll _p;
    For (i, num_cows) {
        cin >> _p; 
        position.pb(_p);
    }


    v<ll> ideal;

    For (i, num_cows) {
        cin >> _p;
        ideal.pb(_p);
    }

    unordered_map<ll, v<ll>> edge;

    For(i, num_cows) {
        
        if (edge.count(ideal[i]) == 0) {
            v<ll> new_edge = {min(i + 1, num_cows - i)};
            edge.insert(MP(ideal[i], new_edge));
        }

        else {
            edge.at(ideal[i]).pb(min(i + 1, num_cows - i));
        }
    }

    unordered_map<ll, v<ll>> prefix;

    for (auto &[species, edge_pos] : edge) {
        sort(edge_pos.begin(), edge_pos.end());
        // cout << species << "-" << edge_pos << endl;

        v<ll> new_prefix = {0};
        for (ll &pos : edge_pos) {
            new_prefix.pb(new_prefix.back() + pos);
        }

        prefix.insert(MP(species, new_prefix));
    }


    // Iterate by cow
    ll ans = 0;

    For (i, num_cows) { // i denotes position, position[i] denotes species

        // cout << "Current cow at "  << i << " with species " << position[i] << endl;

        if (edge.count(position[i]) == 0) {
            continue;
        }

        if (position[i] == ideal[i]) {
            ans += ((i - 1) * i)/2;
            ans += (num_cows - i) * (num_cows - i + 1) / 2;
        }

        

        ll curr_dist = min(i + 1, num_cows - i);

        // cout << "Current distance to edge: " << curr_dist << endl; 

        ll index = upper_bound(edge.at(position[i]).begin(), edge.at(position[i]).end(), curr_dist) - edge.at(position[i]).begin();

        // cout << edge.at(position[i]) << endl;
        // cout << index << endl;

        ans += prefix.at(position[i])[index];
        ans += curr_dist * (edge.at(position[i]).size() - index);

        // cout << "Total countributions: " << ans << endl;
    }

    cout << ans << endl;
}