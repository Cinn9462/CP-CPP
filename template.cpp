#define ll long long
#define pb push_back 
#define v vector
#define p pair
#define fileread(file) freopen(((string) file + ".in").c_str(), "r", stdin); freopen(((string) file + ".out").c_str(), "w", stdout)
#define INF 1000000000000000000
#define inf 1000000001
#define MP(x, y) make_pair(x, y)
#define F first
#define S second
#define For(i, end) for (ll i = 0; i < end; i++)
#define roF(i, start) for (ll i = start; i >= 0; i--)
#define FOR(i, begin, end) for (ll i = begin; i < end; i++) 
#define nl "\n"
#define ss " "
#define un_map unordered_map
#define un_set unordered_set

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
    size_t operator()(const p<ll, ll>& p) const {
        uint64_t x = p.first, y = p.second;
        x += 0x9e3779b97f4a7c15;
        y += 0x9e3779b97f4a7c15;

        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        y = (y ^ (y >> 30)) * 0xbf58476d1ce4e5b9;

        x ^= (x >> 27);
        y ^= (y >> 27);

        return x ^ (y << 1);
    }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    
}