#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define v vector
#define pb push_back
#define all(x) x.begin(), x.end()
#define For(i, a) for(ll i = 0; i < a; i++)
#define FOR(i, a, b) for (ll i = a; i < b; i++)
#define ROF(i, a, b) for(ll i = a; i >= b; i--)
#define ss " "
#define nl "\n"
#define fileread(file) ifstream fin; fin.open((string)file + ".in"); ofstream fout; fout.open((string)file + ".out")

ll N, K, M;

bool simulate(ll x) {
    ll milk = N;
    ll day = 0;
    ll y = N / x;
    while (y > M && day < K) {
        y = milk / x;
        ll d_day = (milk - y * x) / y + 1;
        // cout << "Day " << day << ": y = " << y << nl;
        // cout << "Days until change: " << d_day << nl;
        milk -= min(K - day, d_day) * y;
        day = min(day + d_day, K);
    }
    return (milk - M * (K - day) <= 0); // when reaching M, M milk is donated until kth day
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    fileread("loan");
    fin >> N >> K >> M;
    ll l = 1, r = N + 5;
    while(l != r) {
        ll mid = (l + r) / 2 + 1;
        if (simulate(mid)) l = mid;
        else r = mid - 1;
    }
    
    fout << l << nl;
}