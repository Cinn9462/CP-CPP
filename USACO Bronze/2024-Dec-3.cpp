#define ll long long
#define pb push_back 
#define len(x) (ll)x.size()
#define fileread(file) ifstream fin; fin.open((string)file + ".in"); ofstream fout; fout.open((string)file + ".out")
#define INF 1000000000000000000
#define inf 1000000001
#define MP(x, y) make_pair(x, y)


#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    ll N; ll min_freq; cin >> N >> min_freq;
    string str; cin >> str;

    vector<string> letters = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
    map<string, int> occur; // {moo, frq}
    map<string, set<int>> used; // {moo, indexes used}
    vector<string> res;

    for (int i = 0; i < N - 2; i++) {
        if (str[i] != str[i + 1] && str[i + 1] == str[i + 2]) {
            occur[string(1, str[i]) + string(1, str[i+1]) + string(1, str[i+2])]++;
            used[string(1, str[i]) + string(1, str[i+1]) + string(1, str[i+2])].insert(i);
            used[string(1, str[i]) + string(1, str[i+1]) + string(1, str[i+2])].insert(i + 1);
            used[string(1, str[i]) + string(1, str[i+1]) + string(1, str[i+2])].insert(i + 2);
        }
    }

    vector<string> remove;
    for (auto &pair : occur) {
        if (pair.second >= min_freq) {
            res.pb(pair.first);

            remove.pb(pair.first);
        }
    }

    for (string &s : remove) {
        occur.erase(s);
    }

    for (int i = 0; i < len(str) - 2; i++) {
        
        if (str[i] != str[i + 2] 
            && used[string(1, str[i]) + string(1, str[i+2]) + string(1, str[i+2])].count(i) == 0
            && used[string(1, str[i]) + string(1, str[i+2]) + string(1, str[i+2])].count(i + 1) == 0
            && used[string(1, str[i]) + string(1, str[i+2]) + string(1, str[i+2])].count(i + 2) == 0
            && occur[string(1, str[i]) + string(1, str[i+2]) + string(1, str[i+2])] >= min_freq - 1) {

            res.pb(string(1, str[i]) + string(1, str[i+2]) + string(1, str[i+2]));
            occur.erase(string(1, str[i]) + string(1, str[i+2]) + string(1, str[i+2]));
        }

        if (str[i] != str[i + 1] 
            && used[string(1, str[i]) + string(1, str[i+1]) + string(1, str[i+1])].count(i) == 0
            && used[string(1, str[i]) + string(1, str[i+1]) + string(1, str[i+1])].count(i + 1) == 0
            && used[string(1, str[i]) + string(1, str[i+1]) + string(1, str[i+1])].count(i + 2) == 0
            && occur[string(1, str[i]) + string(1, str[i+1]) + string(1, str[i+1])] >= min_freq - 1) {

            res.pb(string(1, str[i]) + string(1, str[i+1]) + string(1, str[i+1]));
            occur.erase(string(1, str[i]) + string(1, str[i+1]) + string(1, str[i+1]));
        }


        if (str[i + 1] == str[i + 2]) {
            for (string &l : letters) {
                if (used[l + str[i + 2] + str[i + 2]].count(i) == 0
                    && used[l + str[i + 2] + str[i + 2]].count(i + 1) == 0
                    && used[l + str[i + 2] + str[i + 2]].count(i + 2) == 0
                    && l != string(1, str[i + 2])
                    && occur[l + str[i + 1] + str[i + 2]] >= min_freq - 1) {

                res.pb(l + str[i + 2] + str[i + 2]);
                occur.erase(l + str[i + 2] + str[i + 2]);
                }
            } 
        }
    }

    cout << len(res) << endl;
    sort(res.begin(), res.end());
    for (string &r : res) {
        cout << r << endl;
    }
}