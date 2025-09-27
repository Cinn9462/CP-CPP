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

    ifstream fin ("triangles.in");
    ofstream fout ("triangles.out");

    // ll N; cin >> N;
    ll N; fin >> N;
    vector<pair<ll, ll>> points; ll x; ll y;
    for (ll i = 0; i < N; i++) {
        // cin >> x >> y;
        fin >> x >> y;
        points.pb(MP(x, y));
    }

    ll max_size = 0;

    for (ll i = 0; i < N; i++) {
        for (ll j = 0; j < N; j++) {
            for (ll k = 0; k < N; k++) {
                if (points[i].first == points[j].first && points[i].second == points[k].second) {
                    max_size = max(abs((points[j].second - points[i].second) * (points[k].first - points[i].first)), max_size);
                }
            }
        }
    }

    // cout << max_size << NL;
    fout << max_size << NL;
}