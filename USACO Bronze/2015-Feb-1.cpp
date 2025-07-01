#define ll long long
#define V vector
#define pb push_back 
#define len(x) (ll)x.size()
#define f0r(i, begin, end) for (ll i = begin; i < end; i ++) 
#define fileread(file) ifstream fin; fin.open((string)file + ".in"); ofstream fout; fout.open((string)file + ".out")
#define NL "\n"

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    fileread("censor");
    
    string text, censor, res; fin >> text >> censor;
    
    for (char c : text) {
        res += c;
        if (len(res) >= len(censor) && res.substr(len(res) - len(censor)) == censor) {
            res = res.substr(0, len(res) - len(censor));
        }
    }
    fout << res << NL;
}