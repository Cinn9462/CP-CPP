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

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    ll grid_size; cin >> grid_size;

    ll n;
    v<v<ll>> grid(grid_size, v<ll>(grid_size, 0));
    v<ll> freq(grid_size * 2 + 1);

    For(i, grid_size) {
        For(j, grid_size) {
            cin >> n;
            grid[i][j] = n;
            freq[n]++;
        }
    }

    if (grid_size == 1) {
        For(i, grid_size) {
            For(j, grid_size) {
                if (j != 0) {
                    cout << ss << grid[i][j];
                }
                else {
                    cout << grid[i][j];
                }
            }
            cout << nl;
            exit(0);
        }
    }

    v<ll> one_occur;
    For(i, (ll) freq.size()) {
        if (freq[i] == 1) {
            one_occur.pb(i);
        }
    }

    unordered_map<ll, ll> actual;

    bool chosen = true;
    ll x, y;
    ll row;
    For (i, grid_size) {
        For (j, grid_size) {
            if (freq[grid[i][j]] != grid_size && chosen) {
                chosen = false;
                x = i; y = j;
            }

            if (freq[grid[i][j]] == 1) {
                row = i;
            }
        }
    }

    bool small = find(grid[row].begin(), grid[row].end(), grid[x][y]) != grid[row].end();

    if (small) {
        For (i, grid_size) {
            actual[grid[row][i]] = freq[grid[row][i]] + 1;  
        }
    } else {
        For (i, grid_size) {
            actual[grid[row][i]] = 2 * grid_size + 1 - freq[grid[row][i]];
        }
    }

    For (i, grid_size) {
        For (j, grid_size) {
            if (actual.count(grid[i][j])) {
                grid[i][j] = actual[grid[i][j]];
            }
            else {
                grid[i][j] = small ? 2 * grid_size + 1 - freq[grid[i][j]] : freq[grid[i][j]] + 1;  
            }
        }
    }

    For(i, grid_size) {
        For(j, grid_size) {
            if (j != 0) {
                cout << ss << grid[i][j];
            }
            else {
                cout << grid[i][j];
            }
        }
        cout << nl;
    }
}