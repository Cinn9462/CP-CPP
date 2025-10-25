// https://usaco.org/index.php?page=viewproblem2&cpid=1063

#define ll long long
#define pb push_back 
#define len(x) (ll)x.size()
#define fileread(file) ifstream fin; fin.open((string)file + ".in"); ofstream fout; fout.open((string)file + ".out")
#define NL "\n"
#define INF 1000000000000000000
#define inf 1000000001
#define MP(x, y) make_pair(x, y)
#define F first
#define S second


#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int N; cin>> N;
    ll x, y;
    vector<pair<ll, ll>> points;
    for (ll i = 0; i < N; i++) {
        cin >> x >> y;
        points.pb(MP(x, y));
    }

    sort(points.begin(), points.end());
    for (ll i = 0; i < N; i++) {
        points[i].first = i + 1;
    }
    sort(points.begin(), points.end(), [](auto &p1, auto &p2) {return p1.second < p2.second;});
    for (ll i = 0; i < N; i++) {
        points[i].second = i + 1;
    }

    array<array<int, 2500>, 2500> prefix_array; 
}