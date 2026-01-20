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

    ll T;
    cin >> T;
    For (_t, T) {
        ll M, K;
        cin >> M >> K;
        
        ll n_k = K;
        v<ll> min_sum;
        For (i, 5) {
            if (n_k & 1) {
                min_sum.pb((1LL << (1LL << i)) - 1);
            }
            n_k >>= 1;
        }

        ll remainder = M - accumulate(min_sum.begin(), min_sum.end(), 0LL);

        if (remainder == 1) {
            if (min_sum[0] == 1) {
                min_sum[0] = 2;
            }
            else {
                cout << -1 << nl;
                continue;
            }
        }
        else if (remainder % 2 == 0 && remainder >= 0){
            min_sum.pb(remainder / 2);
            min_sum.pb(remainder / 2);
        }
        else if (remainder % 2 == 1 && remainder >= 3) {
            min_sum.pb(1);
            min_sum.pb(2);
            min_sum.pb((remainder - 3) / 2);
            min_sum.pb((remainder - 3) / 2);
        }

        else {
            cout << -1 << nl;
            continue;
        }

        cout << min_sum.size() << nl << min_sum[0];

        if (min_sum.size() > 1) {
            f0r(i, 1, min_sum.size()) {
                cout << ss << min_sum[i];
            }
        }

        cout << nl;
    }
}