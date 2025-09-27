#define ll long long
#define pb push_back 
#define len(x) (ll)x.size()
#define Qsort(x) sort(x.begin(), x.end())
#define fileread(file) ifstream fin; fin.open((string)file + ".in"); ofstream fout; fout.open((string)file + ".out")
#define NL "\n"
#define INF 1000000000000000000
#define inf 1000000001
#define VTS(v) ([](auto&& ___c){ cout << "["; for (auto ____i = begin(___c); ____i != end(___c); ++____i) cout << (____i != begin(___c) ? ", " : "") << *____i; cout << "]\n"; })(v) // only for 1D arrays
#define MP(x, y) make_pair(x, y)

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    fileread("balancing");

    // Input
    ll N; fin >> N;
    vector<pair<ll, ll>> points;
    set<ll> unique_x, unique_y;

    for (ll i = 0; i < N; i++) {
        ll x, y; fin >> x >> y;
        unique_x.insert(x);
        unique_y.insert(y);
        points.pb(MP(x, y));
    }

    vector<ll> above, below;
    ll min_points = INF;

    for (ll y : unique_y) {
        // Sort points into points above and below the y line
        above.clear(); below.clear();
        for (auto &point : points) {
            if (point.second > y - 1) {
                above.pb(point.first);
            }
            else {
                below.pb(point.first);
            }
        }

        Qsort(above); Qsort(below);

        // Iterate through x points

        ll above_index = 0, below_index = 0;

        for (ll x : unique_x) {
            while (above_index < len(above) && above[above_index] < x - 1) {
                above_index++;
            }
            
            while (below_index < len(below) && below[below_index] < x - 1) {
                below_index++;
            }

            min_points = min(max({above_index, below_index, len(above) - above_index, len(below) - below_index}), min_points);       
        }
    }
    fout << min_points << NL;
}