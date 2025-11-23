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

struct Restriction { // extra = trees that can be cut down in the given range
    ll start, end, extra;
};

bool start_comp(Restriction a, Restriction b) {
    return a.start < b.start;
}
struct extra_comp {
    bool operator() (Restriction a, Restriction b) {
        return a.extra > b.extra;
    }
};

int main() {
    ll T; cin >> T;
    For(_i, T) {

        // Input
        ll num_trees, num_restrictions; cin >> num_trees >> num_restrictions;
        
        v<ll> trees; ll tr;
        For(i, num_trees) {
            cin >> tr; trees.pb(tr);
        }

        sort(trees.begin(), trees.end());

        v<Restriction> restrictions; Restriction restr; ll s, e, r, t;
        For(i, num_restrictions) {
            cin >> s >> e >> r;
            t = distance(lower_bound(trees.begin(), trees.end(), s), upper_bound(trees.begin(), trees.end(), e));
            restr = {s, e, t - r};
            restrictions.pb(restr);
        }

        sort(restrictions.begin(), restrictions.end(), start_comp);

        // Timeline with heap
        priority_queue<Restriction, v<Restriction>, extra_comp> active_restrictions;
        ll restriction_index = 0; // index of last added restriction
        ll cut_trees = 0;

        for (ll tree : trees) {
            // Deque old restrictions after last tree but before current tree
            while (!active_restrictions.empty() && active_restrictions.top().end < tree) {
                active_restrictions.pop();
            }

            // Enque all new restrictions
            while (restriction_index < num_restrictions && restrictions[restriction_index].start <= tree) {
                
                // Add count when putting into active restrictions
                // Allows for tracking of how many trees were cut while the restriction was in place
                restrictions[restriction_index].extra += cut_trees;
                
                active_restrictions.push(restrictions[restriction_index]);
                restriction_index++;
            }

            // Determine if current tree can be cut
            if (active_restrictions.empty()) { // No active restrictions
                cut_trees++;
                // cout << "Cut tree at : " << tree << endl;
            }

            else if (cut_trees < active_restrictions.top().extra) { // Cut if limit is not reached
                cut_trees++;
                // cout << "Cut tree at : " << tree << endl;
            }

            // Deque all old restrictions
            while (!active_restrictions.empty() && active_restrictions.top().end <= tree) {
                active_restrictions.pop();
            }
        }
        cout << cut_trees << endl;  
    }
}