#define ll long long
#define pb push_back 
#define len(x) (ll)x.size()
#define fileread(file) ifstream fin; fin.open((string)file + ".in"); ofstream fout; fout.open((string)file + ".out")
#define NL "\n"


#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    fileread("measurement");

    ll N; fin >> N;

    array<array<ll, 3>, 100> days = {};
    ll index, amt; string name;
    
    for (ll i = 0; i < N; i++) {
        fin >> index >> name >> amt;
        if (name == "Bessie") {
            days[index - 1][0] = amt;
        }
        else if (name == "Elsie") {
            days[index - 1][1] = amt;
        }
        else if (name == "Mildred") {
            days[index - 1][2] = amt;
        }
        
    }

    array<ll, 3> cows = {7, 7, 7};
    ll top = 0; // top is a binary state
    ll res = 0;

    for (auto& change : days) {
        cows[0] += change[0]; cows[1] += change[1]; cows[2] += change[2];

        if (cows[0] > cows[1] && cows[0] > cows[2] && top != 4) {
            top = 4;
            res++;
        }
        else if (cows[1] > cows[0] && cows[1] > cows[2] && top != 2) {
            top = 2;
            res++;
        }
        else if (cows[2] > cows[0] && cows[2] > cows[1] && top != 1) {
            top = 1;
            res++;
        }
        else if (cows[0] == cows[1] && cows[0] > cows[2] && top != 6) {
            top = 6;
            res++;
        }
        else if (cows[0] == cows[2] && cows[0] > cows[1] && top != 5) {
            top = 5;
            res++;
        }
        else if (cows[1] == cows[2] && cows[1] > cows[0] && top != 3) {
            top = 3;
            res++;
        }
        else if (cows[0] == cows[1] && cows[0] == cows[2] && top != 0) {
            top = 0;
            res++;
        }
    }
    fout << res << NL;
}