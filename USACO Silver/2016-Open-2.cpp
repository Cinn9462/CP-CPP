#define ll long long
#define pb push_back 
#define len(x) (int)x.size()
#define fileread(file) ifstream fin; fin.open((string)file + ".in"); ofstream fout; fout.open((string)file + ".out")
#define NL "\n"
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
    fileread("diamond");

    ll N, k;
    fin >> N >> k;

    vector<ll> size; ll s;
    For(i, N) {
        fin >> s;
        size.pb(s);
    }

    vector<Interval> interval;

    sort(size.begin(), size.end());

    For(left, N) {
        ll right = left;
        while (right < N && size[right] <= size[left] + k) {
            right++;
        }
        Interval inter = {left, right};
        interval.pb(inter);
    }
    
    ll max_size = 0;

    For(i, N) {
        // cout << interval[i].start << " " << interval[i].end << endl;
    }

    For(i, N) {
        f0r(j, i + 1, N) {
            if (interval[i].end > interval[j].start) {
                continue;
            }
            // cout << interval[i].start << " " << interval[i].end << " " << interval[j].start << " " << interval[j].end << endl;
            max_size = max(max_size, (interval[i].end - interval[i].start) + (interval[j].end - interval[j].start));
        }
    }

    if (interval.size() == 1) {
        max_size = interval[0].end - interval[0].start;
    }
    fout << max_size << endl;
}