#define ll long long
#define pb push_back 
#define len(x) (ll)x.size()
#define fileread(file) ifstream fin; fin.open((string)file + ".in"); ofstream fout; fout.open((string)file + ".out")
#define INF 1000000000000000000
#define inf 1000000001
#define MP(x, y) make_pair(x, y)
#define fileread(file) ifstream fin; fin.open((string)file + ".in"); ofstream fout; fout.open((string)file + ".out")

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    fileread("hps");

    ll N; fin >> N; 

    vector<string> moves;
    string s;
    for (ll i = 0; i < N; i++) {
        fin >> s;
        moves.pb(s);
    }

    vector<ll> rock_p = {0};
    vector<ll> paper_p = {0};
    vector<ll> scissor_p = {0};

    ll win;

    for (ll i = 0; i < N; i++) {
        win = (moves[i] == "S") ? 1 : 0;
        rock_p.pb(rock_p[i] + win);
    }

    for (ll i = 0; i < N; i++) {
        win = (moves[i] == "H") ? 1 : 0;
        paper_p.pb(paper_p[i] + win);
    }

    for (ll i = 0; i < N; i++) {
        win = (moves[i] == "P") ? 1 : 0;
        scissor_p.pb(scissor_p[i] + win);
    }

    // for (auto i : rock_p) {
    //     cout << i << endl;
    // }
    // cout << endl;
    // for (auto i : paper_p) {
    //     cout << i << endl;
    // }
    // cout <<endl;
    // for (auto i : scissor_p) {
    //     cout << i << endl;
    // }
    // cout << endl;


    ll max_sum = 0;
    for (int i = 0; i < N; i++) {
        max_sum = max(max_sum, 
            max(max(rock_p[i], scissor_p[i]), paper_p[i]) + 
            max(max(rock_p[N] - rock_p[i], scissor_p[N] - scissor_p[i]), paper_p[N] - paper_p[i])
        );

        // cout << i << " " << max(max(rock_p[i], scissor_p[i]), paper_p[i]) << " " << max(max(rock_p[N] - rock_p[i], scissor_p[N] - scissor_p[i]), paper_p[N] - paper_p[i]) << endl;
    }
    fout << max_sum << endl;
    // cout << max_sum << endl;
}