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
struct Interval { // Length of interval = end - start, end is exclusive
    ll start, end;
};

int main() {
    fileread("herding");

    ll N; fin >> N;
    
    v<ll> cows;
    
    ll c;
    For(i, N) {
        fin >> c;
        cows.pb(c);
    }

    sort(cows.begin(), cows.end());

    // Maximum 
    ll max_move;
    if (cows[1] - cows[0] <= cows[N - 1] - cows[N - 2]) {
        max_move = cows[N - 1] - cows[1] - N + 2;
    }
    else {
        max_move = cows[N - 2] - cows[0] - N + 2;
    }

    // Minimum via two pointers - find the largest chunk with lenght N with cows already populated
    ll min_move = pow(2, 32);
    For(left, N) {
        ll right = left;
        while (right < N && cows[right] - cows[left] < N) {
            right++;
        }
        if (!((left == 0 || right == N) && cows[right - 1] - cows[left] == N - 2)) {
            min_move = min(min_move, N - (right - left));
        }
    }
    fout << min_move << endl;
    fout << max_move << endl;
}