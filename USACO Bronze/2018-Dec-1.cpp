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
    fileread("mixmilk");

    ll c1, a1, c2, a2, c3, a3; fin >> c1 >> a1 >> c2 >> a2 >> c3 >> a3;
    f0r(i, 0, 100) {
        switch (i % 3) {
            case 0:
                if (a1 + a2 > c2) {
                    a1 -= c2 - a2; a2 = c2;
                }
                else {
                    a2 += a1; a1 = 0;
                }
                break;
            case 1:
                if (a2 + a3 > c3) {
                    a2 -= c3 - a3; a3 = c3;
                }
                else {
                    a3 += a2; a2 = 0;
                }
                break;
            case 2:
                if (a3 + a1 > c1) {
                    a3 -= c1 - a1; a1 = c1;
                }
                else {
                    a1 += a3; a3 = 0;
                }
                break;
        }
    }
    fout << a1 << NL << a2 << NL << a3 << NL;
}