#define ll long long
#define pb push_back 
#define len(x) (ll)x.size()
#define fileread(file) ifstream fin; fin.open((string)file + ".in"); ofstream fout; fout.open((string)file + ".out")
#define NL "\n"
#define INF 1000000000000000000
#define inf 1000000001
#define MP(x, y) make_pair(x, y)
#define fileread(file) ifstream fin; fin.open((string)file + ".in"); ofstream fout; fout.open((string)file + ".out")

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    fileread("div7");

    ll N; fin >> N; 

    ll id;
    vector<ll> ids;
    for (ll i = 0; i < N; i++) {
        fin >> id; 
        ids.pb(id % 7);
    }

    vector<ll> prefix_array; prefix_array.pb(ids[0]);
    for (ll i = 1; i < N; i++) {
        prefix_array.pb((prefix_array[i - 1] + ids[i]) % 7);
    }

    map<ll, ll> m;
    m[0] = -1;
    ll max_dist = 0;
    for (ll i = 0; i < N; i++) {
        if (m.find(prefix_array[i]) == m.end()) {
            m[prefix_array[i]] = i;
        }
        else {
            max_dist = max(max_dist, i - m.at(prefix_array[i]));
        }
    }
    fout << max_dist << NL;
}