// TODO: Finish debugging

#define ll long long
#define pb push_back 
#define v vector
#define p pair
#define fileread(file) freopen(((string) file + ".in").c_str(), "r", stdin); freopen(((string) file + ".out").c_str(), "w", stdout)
#define INF 1000000000000000000
#define inf 1000000001
#define MP(x, y) make_pair(x, y)
#define F first
#define S second
#define For(i, end) for (ll i = 0; i < end; i++)
#define f0r(i, begin, end) for (ll i = begin; i < end; i++) 
#define nl "\n"
#define ss " "
#define un_map unordered_map
#define un_set unordered_set

#include <bits/stdc++.h>
using namespace std;

ostream& operator<<(ostream& os, pair<ll, ll>& p) {
    return os << "[" << p.F << " " << p.S << "]";
}
ostream& operator<<(ostream& os, v<ll>& arr) {
    for (ll ___a : arr) {
        os << ___a << " ";
    }
    return os;
}

struct PairHash {
    size_t operator()(const pair<ll,ll>& p) const {
        return hash<ll>()(p.F) ^ (hash<ll>()(p.S) << 1);
    }
};

struct Node {
    v<ll> edges = {};
    v<ll> weights = {};
    v<ll> restrictionIDs = {};
    ll count = 0;
    ll l = 0;
    ll r = 0; 
};

bool flag = false;

void dfs(map<ll, p<ll, ll>>& queue, v<Node>& rods, un_set<ll>& visited, ll depth, ll rod_num, ll modifier, ll r_ID, bool same) {

    if (visited.count(r_ID) > 0 || rods[rod_num].count == 0) {
        return;
    }

    cout << "DFS: " << depth << ss << rod_num << ss << r_ID << nl;

    visited.insert(r_ID);
    
    ll r_modifier = (depth % 2 == 0) ? -1 : 1;


    ll start = min(modifier - r_modifier * rods[rod_num].l, modifier - r_modifier * rods[rod_num].r);
    ll end = max(modifier - r_modifier * rods[rod_num].l, modifier - r_modifier * rods[rod_num].r);

    if (same) {
        start = 
    }

    if (queue.count(rod_num) > 0) {
        ll new_start = max(queue[rod_num].F, start);
        ll new_end = min(queue[rod_num].S, end);

        cout << queue[rod_num] << ss << start << ss << end << nl;

        if (new_end < new_start) {
            flag = true;
            return;
        }

        queue[rod_num] = {new_start, new_end};
    }

    else if (depth > 0){
        queue.insert({rod_num, {start, end}});
        For(i, rods[rod_num].count) {
            if (rods[rod_num].edges[i] == rod_num && (rods[rod_num].weights[i] % 2 == 1)) {
                flag = true;
            }

            dfs(queue, rods, visited, depth + 1, rods[rod_num].edges[i], modifier - r_modifier * rods[rod_num].weights[i], rods[rod_num].restrictionIDs[i], rods[rod_num].edges[i] == rod_num);
        }
    }
    else {
        For(i, rods[rod_num].count) {
            dfs(queue, rods, visited, depth + 1, rods[rod_num].edges[i], modifier - r_modifier * rods[rod_num].weights[i], rods[rod_num].restrictionIDs[i], rods[rod_num].edges[i] == rod_num);
        }
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    ll num_rods, num_restrictions;
    cin >> num_rods >> num_restrictions;

    v<Node> rods(num_rods);
    For(i, num_rods) {
        cin >> rods[i].l;
    }

    For(i, num_rods) {
        cin >> rods[i].r;
    }

    ll x, y, z;
    For(i, num_restrictions) {
        cin >> x >> y >> z;
        x--; y--;
        rods[x].edges.pb(y);
        rods[x].weights.pb(z);
        rods[y].edges.pb(x);
        rods[y].weights.pb(z);
        rods[x].count++;
        rods[y].count++;
        rods[x].restrictionIDs.pb(i);
        rods[y].restrictionIDs.pb(i);
    }

    ll total_loss = 0;
    un_set<ll> visited;
    For(i, num_rods) {
        map<ll, p<ll, ll>> queue; // rod number to range it maps
        dfs(queue, rods, visited, 0, i, 0, -(i + 1), false);

        ll start = rods[i].l;
        ll end = rods[i].r;

        priority_queue<ll, v<ll>, greater<ll>> timeline;
        ll max_size = 0;

        v<p<ll, ll>> q;

        cout << "Queue: ";
        for (auto [key, range] : queue) {
            cout << range << ss;
            if (key == i) {
                ll new_start = max(start, range.F);
                ll new_end = min(end, range.S);

                if (new_start <= new_end) {
                    q.pb({new_start, new_end});
                }
            }

            else {
                q.pb(range);
            }
        }
        cout << nl;

        sort(q.begin(), q.end());

        for(auto [l, r] : q) {

            while(!timeline.empty() && timeline.top() < l) {
                timeline.pop();
            }

            timeline.push(r);
            max_size = max(max_size, (ll) timeline.size());
        }
        total_loss += (ll) queue.size() - max_size;

        if (flag) {
            cout << -1 << nl;
            // continue;
        }
    }

    cout << num_rods - total_loss << nl;
}