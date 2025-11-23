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

struct Point{
    ll, x, y, f; // 0 = ?, 1 = U, 2 = D, 3 = L, 4 = R
    Point(ll _x, ll _y, ll _f) : x(_x), y(_y), f(_f) {}
};

int main() {
    ll grid_size, num_queries;

    vector<Point> points;
    ll _x, _y;
    char _f;
    For(i, num_queries) {
        cin >> _x >> _y >> _f;
        if (_f == "?") {
                        
        } else if (_f == "U") {
            
        } else if (_f == "D") {
            
        } else if (_f == "L") {
            
        } else if (_f == "R") {
            
        } 
    }
}