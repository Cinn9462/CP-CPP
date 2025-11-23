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



bool simulate(v<ll> &times, ll &stage_size, ll &max_time) {
    priority_queue<ll, v<ll>, greater<ll>> stage; 
    for (ll &time : times) {
        if (stage.size() < stage_size) {
            stage.push(time);
        }
        else { // stage.size == stage_size, pop and push
            ll out = stage.top();
            stage.pop();
            stage.push(time + out);
        }
    }

    while(stage.size() != 1) { // Empty out pq
        stage.pop();
    }

    return stage.top() <= max_time;

}

int main() {
    fileread("cowdance");
    ll num_cows, max_time;
    fin >> num_cows >> max_time;
    
    v<ll> times;
    ll _t;
    For(i, num_cows) {
        fin >> _t;
        times.pb(_t);
    }
    
    // Binary search over possible stage sizes
    ll left, right, mid;
    left = 1; right = (ll) pow(10, 6);

    while (left != right) {

        mid = (left + right - 1) / 2;

        if (simulate(times, mid, max_time)) { // If mid runs within t_max, lower right search to mid
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    fout << left;
}