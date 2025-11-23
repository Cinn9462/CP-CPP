// https://usaco.org/index.php?page=viewproblem2&cpid=1063

#define ll long long
#define pb push_back 
#define len(x) (int)x.size()
#define fileread(file) ifstream fin; fin.open((string)file + ".in"); ofstream fout; fout.open((string)file + ".out")
#define NL "\n"
#define INF 1000000000000000000
#define inf 1000000001
#define MP(x, y) make_pair(x, y)
#define F first
#define S second

#include <bits/stdc++.h>
using namespace std;


int rsum(int x1, int y1, int x2, int y2, array<array<int, 3000>, 3000> &grid) {
    int rx, ry, rxy;
    rx = x1 > 0 ? grid[x1 - 1][y2] : 0;
    ry = y1 > 0 ? grid[x2][y1 - 1]: 0;
    rxy = x1 > 0 && y1 > 0 ? grid[x1 - 1][y1 - 1] : 0;

    return grid[x2][y2] - rx - ry + rxy;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int N; cin>> N;
    int x, y;
    vector<pair<int, int>> points;
    for (int i = 0; i < N; i++) {
        cin >> x >> y;
        points.pb(MP(x, y));
    }

    sort(points.begin(), points.end());
    for (int i = 0; i < N; i++) {
        points[i].F = i + 1;
    }
    sort(points.begin(), points.end(), [](auto &p1, auto &p2) {return p1.S < p2.S;});
    for (int i = 0; i < N; i++) {
        points[i].S = i + 1;
    }

    array<array<int, 3000>, 3000> prefix_array;

    for (int i = 0; i < 3000; i++) {
        for (int j = 0; j < 3000; j++) {
            prefix_array[i][j] = 0;
        }
    }
    
    for (auto [x1, y1]: points) {
        prefix_array[x1][y1]++;
    }

    int rx, ry, rxy;
    for (int i = 0; i < 3000; i++) {
        for(int j = 0; j < 3000; j++) {
            rx = i > 0 ? prefix_array[i-1][j] : 0;
            ry = j > 0 ? prefix_array[i][j-1]: 0;
            rxy = i > 0 && j > 0 ? prefix_array[i-1][j-1] : 0;

            prefix_array[i][j] += rx + ry - rxy;
        }
    }

    // for (int i = 0; i < 3000; i++) {
    //     for (int j = 0; j < 3000; j++) {
    //         cout << prefix_array[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    ll res = N + 1;
    int left, right;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            // cout << points[i].F << "." << points[i].S << " " << points[j].F << "." << points[j].S << endl;
            // cout << rsum(0, min(points[i].S, points[j].S), min(points[i].F, points[j].F) - 1, max(points[i].S, points[j].S), prefix_array) << endl;
            // cout << rsum(max(points[i].F, points[j].F) + 1, min(points[i].S, points[j].S), 2999, max(points[i].S, points[j].S), prefix_array) << endl;


            left = rsum(0, min(points[i].S, points[j].S), min(points[i].F, points[j].F) - 1, max(points[i].S, points[j].S), prefix_array);
            right = rsum(max(points[i].F, points[j].F) + 1, min(points[i].S, points[j].S), 2999, max(points[i].S, points[j].S), prefix_array);
            res += left + right + left * right + 1;
        }
    }
    cout << res << endl;
}