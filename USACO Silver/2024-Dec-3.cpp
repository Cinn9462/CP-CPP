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

struct PairHash {
    size_t operator()(const pair<ll,ll>& p) const {
        return hash<ll>()(p.F) ^ (hash<ll>()(p.S) << 1);
    }
};

struct Build {
    ll x, y;
    string type;

    Build(ll _x, ll _y, string t) : x(_x), y(_y), type(t) {}
};


ll grid_size, num_builds;
v<v<ll>> grid;
v<v<bool>> good;
ll curr_good = 0;

v<ll> dx = {0, 0, 1, -1};
v<ll> dy = {1, -1, 0, 0};
v<string> d = {"R", "L", "D", "U"};

int dir(string dir) {
    For(i, 4) {
        if (dir == d[i]) {
            return i;
        }
    }
    return -1;
}

bool in(ll x, ll y) {
    return x >= 0 && x < grid_size && y >= 0 && y < grid_size;
}

bool become_good(ll x, ll y) {
    if ((grid[x][y] != -1) && (!in(x + dx[grid[x][y]], y + dy[grid[x][y]]) || good[x + dx[grid[x][y]]][y + dy[grid[x][y]]])) {
        return true;
    }

    if (grid[x][y] == -1) {
        bool status = false;
        For(i, 4) {
            status = status || !in(x + dx[i], y + dy[i]) || good[x + dx[i]][y + dy[i]];
        }

        return status;
    }
    
    return false;
}

void printgood() {
    for (v<bool> r : good) {
        for (bool i : r) {
            cout << i << ss;
        }
        cout << nl;
    }  
}

void dfs(ll x, ll y) {
        // cout << "Looking at " << x << ss << y << nl; 

        // printgood();

        if (good[x][y]) {
            // cout << x << ss << y << " exited without adding to curr_good" << nl;
            return;
        }

        if (become_good(x, y)) {
            good[x][y] = true;
            curr_good++;
            For(i, 4) {
                if (in(x + dx[i], y + dy[i])) {
                    dfs(x + dx[i], y + dy[i]);
                }
            }
        }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    cin >> grid_size >> num_builds;

    v<Build> builds;
    ll _x, _y;
    string _t;

    For(i, num_builds) {
        cin >> _x >> _y >> _t;
        builds.pb(Build(_x - 1, _y - 1, _t));
    }

    grid.assign(grid_size, v<ll>(grid_size, -1));
    good.assign(grid_size, v<bool>(grid_size, false));

    for (Build b : builds) {
        grid[b.x][b.y] = dir(b.type);
    }

    v<ll> all_goods;
    
    For(i, grid_size) {
        For(j, grid_size) {
            // cout << "Beginning at " << i << ss << j << nl;
            dfs(i, j);
        }
    }

    all_goods.pb(curr_good);

    for(ll i = num_builds - 1; i >= 0; i--) {
        grid[builds[i].x][builds[i].y] = -1;
        dfs(builds[i].x, builds[i].y);
        all_goods.pb(curr_good);
    }

    for(ll i = num_builds - 1; i >= 0; i--) {
        cout << grid_size * grid_size - all_goods[i] << nl;
    }
}