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

ll grid_size, num_builds;

struct Build {
    ll x, y;
    string type;

    Build(ll _x, ll _y, string t) : x(_x), y(_y), type(t) {}
}

v<ll> dx = {0, 0, 1, -1};
v<ll> dy = {1, -1, 0, 0};
v<string> d = {"U", "D", "L", "R"};

int dir(string dir) {
    For(i, 4) {
        if (dir == d[i]) {
            return i;
        }
    }
    return -1
}

bool in(x, y) {
    return x >= 0 && x < grid_size && y >= 0 && y < grid_size;
}

v<v<int>> grid;
v<v<bool> good;
ll curr_good; 

void dfs(v<v<string>> &grid, ll x, ll y) {

}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    cin >> grid_size >> num_builds

    v<Build> builds;
    ll _x, _y;
    string _t;

    For(i, num_builds) {
        cin >> _x >> _y >> _t
        builds.pb(Build(_x - 1, _y - 1, _t))
    }

    grid.assign(grid_size, v<int>(grid_size, -1))
    good.assign(grid_size, v<bool>(grid_size, false))

    for (Build b : builds) {
        grid[b.x][b.y] = dir(b.type);
    }
}