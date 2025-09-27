#define ll long long
#define pb push_back 
#define len(x) (ll)x.size()
#define Qsort(x) sort(x.begin(), x.end())
#define fileread(file) ifstream fin; fin.open((string)file + ".in"); ofstream fout; fout.open((string)file + ".out")
#define NL "\n"
#define INF 1000000000000000000
#define inf 1000000001
#define VTS(v) ([](auto&& ___c){ cout << "["; for (auto ____i = begin(___c); ____i != end(___c); ++____i) cout << (____i != begin(___c) ? ", " : "") << *____i; cout << "]\n"; })(v) // only for 1D arrays
#define MP(x, y) make_pair(x, y)


#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    ifstream fin ("cownomics.in"); 
    ofstream fout ("cownomics.out");

    ll N, M; fin >> N >> M;
    vector<string> genomes; string input;
    for (ll i = 0; i < 2 * N; i++) {
        // cin >> input; genomes.pb(input);
        fin >> input; genomes.pb(input);
    }

    ll count = 0;
    unordered_set<string> unique;

    for (ll i = 0; i < M; i++) {
        for (ll j = i + 1; j < M; j++) {
            for (ll k = j + 1; k < M; k++) {
                bool uniq = true;
                unique.clear();

                for (ll x = 0; x < N; x++) {
                    unique.insert(string() + genomes[x][i] + genomes[x][j] + genomes[x][k]);
                }
                for (ll x = N; x < 2 * N; x++) {
                    if (unique.count((string() + genomes[x][i] + genomes[x][j] + genomes[x][k])) > 0) {
                        uniq = false;
                    }
                }

                if (uniq) {
                    count++;
                }
            }
        }
    }

    // cout << count << NL;
    fout << count << NL;
}