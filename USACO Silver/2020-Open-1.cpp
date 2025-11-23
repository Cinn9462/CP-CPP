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
    for (ll a : arr) {
        os << a << " ";
    }
    return os;
}



bool simulate(v<pair<ll, ll>> &patches, ll cows, ll dist) {
    ll last_cow = patches[0].F;
    ll patch_index = 0;
    For(c, cows - 1) {

        // cout << "Testing patch: " << patch_index << " on cow " << c + 2 << endl;
        // cout << "Current position: " << last_cow << endl;

        if (patch_index == patches.size()) {
            return false;
        }

        if (last_cow + dist <= patches[patch_index].S) {
            last_cow += dist;
        } else {
            while (patch_index < patches.size() && patches[patch_index].S < last_cow + dist) {
                patch_index++;
            }
            last_cow = max(patches[patch_index].F, last_cow + dist);
        }
    }

    if (patch_index == patches.size()) {
        return false;
    }

    return true;
}

int main() {

    fileread("socdist");

    ll num_cows, num_patches;
    fin >> num_cows >> num_patches;
    
    v<pair<ll, ll>> patches;
    ll _x, _y;
    For(i, num_patches) {
        fin >> _x >> _y;
        patches.pb(MP(_x, _y));
    }

    sort(patches.begin(), patches.end(), [](pair<ll, ll> &a, pair<ll, ll> &b){return a.F < b.F;});

    auto max_patch = max_element(patches.begin(), patches.end(), [](pair<ll, ll> &a, pair<ll, ll> &b) {return max(a.F, a.S) < max(b.F, b.S);});
    auto min_patch = min_element(patches.begin(), patches.end(), [](pair<ll, ll> &a, pair<ll, ll> &b) {return min(a.F, a.S) < min(b.F, b.S);});

    // Binary search over D
    ll left, right, mid;
    left = 1; right = ((*max_patch).S - (*min_patch).F) / (num_cows - 1); // Largest possible distance is 

    while (left != right) {

        mid = (left + right + 1) / 2;

        // cout << "Left: " << left << " Right: " << right << " Testing: " << mid << endl;
        // if (simulate(patches, num_cows, mid)) {
        //     cout << "Distance was achievable" << endl;
        // } else {
        //     cout << "Distance was too close" << endl;
        // }

        if (simulate(patches, num_cows, mid)) {
            left = mid;
        } else {
            right = mid - 1;
        }
    }

    fout << left;
}