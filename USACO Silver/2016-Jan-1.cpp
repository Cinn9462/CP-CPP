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

bool simulate(v<ll> &bales, ll &num_cows, ll &power) {
    ll cows_used = 1;
    ll last_bale = bales[0];
    for(ll &bale : bales) {
        // cout << "Used cows: " << cows_used << " " << " Last bale bombed: " << last_bale << " Checking: " << bale << endl;
        if (bale > last_bale + power * 2) {
            cows_used++;
            last_bale = bale;
        }
    }

    // cout << "Total used cows: " << cows_used << endl;

    return cows_used <= num_cows;
}

int main() {
    fileread("angry");
    ll num_bales, num_cows;
    fin >> num_bales >> num_cows;
    
    v<ll> bales;
    ll _b;
    For(i, num_bales) {
        fin >> _b;
        bales.pb(_b);
    }
    
    sort(bales.begin(), bales.end());

    // Binary search over possible power
    ll left, right, mid;
    left = 0; right = (ll) pow(10, 9);

    while (left != right) {
        
        // cout << left << " " << right << endl;

        mid = (left + right - 1) / 2;

        if (simulate(bales, num_cows, mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    fout << left;
}