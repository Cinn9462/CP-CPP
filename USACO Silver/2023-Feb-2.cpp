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

struct Location {
    ll x, y, time;
    Location(ll _x, ll _y, ll _t) : x(_x), y(_y), time(_t) {}
    
};

bool operator< (const Location &x, const Location &y) {
    return x.time < y.time;
}

bool check(Location &event, Location &cow) { // true if cow cannot reach location
    ll dt = event.time - cow.time;
    ll dx = event.x - cow.x;
    ll dy = event.y - cow.y;
    return dt * dt < dx * dx + dy * dy;
}

int main() {
    ll num_events, num_cows; 
    cin >> num_events >> num_cows;

    ll _x, _y, _t;
    v<Location> events;
    v<Location> cows;

    For(i, num_events) {
        cin >> _x >> _y >> _t;
        events.pb(Location(_x, _y, _t));
    }
    For(i, num_cows) {
        cin >> _x >> _y >> _t;
        cows.pb(Location(_x, _y, _t));
    }
    
    sort(events.begin(), events.end());

    ll innocent = 0;

    for(Location &cow : cows) {
        ll index_above = (ll) (upper_bound(events.begin(), events.end(), cow) - events.begin());
        ll index_below = max(index_above - 1, (ll) 0);
        index_above = min(index_above, num_events - 1);

        // cout <<  index_below << " " << index_above << endl;
        // cout << check(events[index_below], cow) << " " << check(events[index_above], cow) << endl;
        if (check(events[index_below], cow) || check(events[index_above], cow)) {
            innocent++;
        }
    }
    cout << innocent << endl;
}