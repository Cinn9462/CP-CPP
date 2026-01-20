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

v<v<bool>> visited(200, v<bool>(200, false));
v<v<ll>> visited_depth(200, v<ll>(200, -1));
ll max_x, max_y, operations, goal;

void dfs(ll depth, ll x, ll y) {
    if (visited_depth[x][y] == -1) {
        visited_depth[x][y] = depth;
    }

    if (visited_depth[x][y] > depth) {
        visited_depth[x][y] = depth;
    }

    else if (visited_depth[x][y] > operations || visited[x][y]) {
        return;
    }

    visited[x][y] = true;

    dfs(depth + 1, max_x, y);
    dfs(depth + 1, x, max_y);
    dfs(depth + 1, min(x + y, max_x), max(0LL, y - (min(x + y, max_x) - x)));
    dfs(depth + 1, max(0LL, y - (min(y + x, max_y) - x)), min(y + x, max_y));
    dfs(depth + 1, x, 0);
    dfs(depth + 1, 0, y);
}

int main() {
    fileread("pails");
    fin >> max_x >> max_y >> operations >> goal;
    // cin >> max_x >> max_y >> operations >> goal;
    ll minimum = LLONG_MAX;
    dfs(0, 0, 0);
    For(i, 200) {
        For (j, 200) {
            if (visited[i][j]) {
                minimum = min(minimum, abs(goal - (i + j)));
            }
        }
    }

    fout << minimum;
    // cout << minimum;
}