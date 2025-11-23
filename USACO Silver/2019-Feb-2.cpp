#define ll long long
#define pb push_back 
#define len(x) (ll)x.size()
#define fileread(file) ifstream fin; fin.open((string)file + ".in"); ofstream fout; fout.open((string)file + ".out")
#define INF 1000000000000000000
#define inf 1000000001
#define MP(x, y) make_pair(x, y)


#include <bits/stdc++.h>
using namespace std;

struct Point {
    ll x, y;
};

struct Rect {
    ll startX, startY, endX, endY;
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    fileread("paintbarn");

    ll nPoints; ll value; fin >> nPoints >> value;
    vector<Rect> rectangles;
    ll x1, x2, y1, y2;
    Rect newRect;

    for (ll i = 0; i < nPoints; i++) {
        fin >> x1 >> y1 >> x2 >> y2;
        newRect = {x1, y1, x2, y2};
        rectangles.pb(newRect);
    }

    array<array<ll, 1002>, 1002> grid;

    for (int i = 0; i < 1002; i++) {
        for (int j = 0; j < 1002; j++) {
            grid[i][j] = 0;
        }
    }

    for (Rect &r : rectangles) {
        grid[r.startX][r.startY]++;
        grid[r.endX][r.endY]++;
        grid[r.startX][r.endY]--;
        grid[r.endX][r.startY]--;
    }

    ll rx, ry, rxy;
    for (int i = 0; i < 1002; i++) {
        for (int j = 0; j < 1002; j++) {
            rx = i > 0 ? grid[i-1][j] : 0;
            ry = j > 0 ? grid[i][j-1]: 0;
            rxy = i > 0 && j > 0 ? grid[i-1][j-1] : 0;

            grid[i][j] += rx + ry - rxy;
        }
    }

    ll res = 0;
    for (int i = 0; i < 1002; i++) {
        for (int j = 0; j < 1002; j++) {
            if (grid[i][j] == value) {
                res++;
            }
        }
    }
    fout << res << endl;
}