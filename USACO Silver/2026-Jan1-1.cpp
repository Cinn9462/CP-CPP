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

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    ll Q; cin >> Q;
    ll type, x, time;
    For(_t, Q) {
        cin >> type >> x >> time;

        if (type == 1) {

            if (time < 2 * x) {
                cout << x << nl;
                continue;
            }

            if (time < 3*x) {
                cout << 3*x - time - 1 << nl;
                continue;
            }

            ll back_time = 3*x;
            
            while (back_time <= time) {
                back_time += (back_time / 2) + 1;
            }
            cout << back_time - time - 1<< nl;
        }

        else if (type == 2) {
            if (x >= time / 2 + 1) {
                cout << x << nl;
                continue;
            }

            ll back_time = time + x + 1;

            while(back_time % 3 != 0 && back_time > 3) {
                back_time -= back_time / 3 + 1;
            }

            if (back_time % 3 == 0) {
                cout << back_time / 3 << nl;
                continue;
            }

            if (back_time < 3) {
                cout << 0 << nl;
                continue;
            }
        }
    }
}