#define ll long long
#define pb push_back 
#define v vector
#define fileread(file) ifstream fin; fin.open((string)file + ".in"); ofstream fout; fout.open((string)file + ".out")
#define INF 1000000000000000000
#define inf 1000000001
#define MP(x, y) make_pair(x, y)
#define F first
#define S second
#define For(i, end) for (ll i = 0; i < end; i++)
#define f0r(i, begin, end) for (ll i = begin; i < end; i++) 

#include <bits/stdc++.h>
using namespace std;
struct Interval { // Length of interval = end - start, end is exclusive
    ll start, end;
};

int main() {
    ll T; cin >> T;
    For(_i, T) {
        ll N; cin >> N;
        v<ll> cakes; ll cake;
        For(i, N) {
            cin >> cake;
            cakes.pb(cake);
        }

        ll left = 0;
        ll right = accumulate(cakes.end() - (N / 2) + 1, cakes.end(), 0LL);
        ll max_cake = left + right;

        For(i, N / 2 - 1) {
            left += cakes[i];
            right -= cakes[N/2 + 1 + i];
            max_cake = max(max_cake, (left + right));
        }

        cout << accumulate(cakes.begin(), cakes.end(), 0LL) - max_cake << " " << max_cake << endl;
    }
}