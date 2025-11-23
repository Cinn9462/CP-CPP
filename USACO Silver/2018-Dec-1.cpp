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

bool simulate(ll &time, ll &num_bus, ll &bus_cap, v<ll> &cows) {
    ll bus_used = 0;
    ll curr_bus_time = cows[0];
    ll curr_bus_cap = 0;
    for(ll &cow : cows) {
        if (curr_bus_cap == bus_cap) {
            // cout << 'c' << endl;
            curr_bus_cap = 0;
            curr_bus_time = cow;
            bus_used++;
        }
        else if (cow - curr_bus_time > time) {
            // cout << 't' << endl;
            curr_bus_cap = 0;
            curr_bus_time = cow;
            bus_used++;
        }
        curr_bus_cap++;
    }
    if (curr_bus_cap != 0) {
        bus_used++;
    }

    // cout << time << " " << bus_used << endl;

    return bus_used <= num_bus;
}

int main() {

    fileread("convention");

    ll num_cows, num_bus, bus_cap;
    fin >> num_cows >> num_bus >> bus_cap;
    
    v<ll> cows;
    ll _c;
    For(i, num_cows) {
        fin >> _c;
        cows.pb(_c);
    }
    
    sort(cows.begin(), cows.end());

    // Binary search over possible t
    ll left, right, mid;
    left = 0; right = (ll) pow(10, 9);

    while (left != right) {
        mid = (left + right + 1) / 2;

        if (simulate(mid, num_bus, bus_cap, cows)) {
            right = mid - 1;
        } else {
            left = mid;
        }
    }

    if (simulate(left, num_bus, bus_cap, cows)) {
        fout << left << endl;
    } else {
        fout << left + 1 << endl;
    }
}