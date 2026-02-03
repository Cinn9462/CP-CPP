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

#include <bits/stdc++.h>
using namespace std;

ll num_contestants, num_criteria;
v<ll> per_criteria;
v<v<ll>> criteria;
v<set<ll>> candidates;
v<ll> invited;
v<ll> filled;
ll total_sum;

void find_next(ll c) {
    while (c >= 1 && c <= num_criteria && filled[c] < per_criteria[c] && !candidates[c].empty()) {
        ll cand = *candidates[c].begin();
        ll old_criteria = invited[cand];
        
        if (old_criteria != -1 && old_criteria <= c) {
            candidates[c].erase(cand);
            continue;
        }
        
        if (old_criteria == -1) {
            invited[cand] = c;
            filled[c]++;
            total_sum += cand;
            return;
    
        } else {
            filled[old_criteria]--;
            filled[c]++;
            invited[cand] = c;
            c = old_criteria;
        }
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    
    cin >> num_contestants >> num_criteria;
    
    per_criteria.resize(num_criteria + 1);
    f0r(i, 1, num_criteria + 1) {
        cin >> per_criteria[i];
    }
    
    v<ll> decline(num_contestants);
    For(i, num_contestants) {
        cin >> decline[i];
    }
    
    criteria.resize(num_contestants + 1);
    f0r(i, 1, num_contestants + 1) {
        ll _n; cin >> _n;
        For(j, _n) {
            ll c; cin >> c;
            criteria[i].push_back(c);
        }
    }
    
    candidates.resize(num_criteria + 1);
    f0r(i, 1, num_contestants + 1) {
        for (ll c: criteria[i]) {
            candidates[c].insert(i);
        }
    }
    
    invited.assign(num_contestants + 1, -1);
    filled.assign(num_criteria + 1, 0);
    total_sum = 0;
    
    f0r (criteria, 1, num_criteria + 1) {
        for (ll contestant : candidates[criteria]) {
            if (filled[criteria] >= per_criteria[criteria]) {
                break;
            }
            if (invited[contestant] == -1) {
                invited[contestant] = criteria;
                filled[criteria]++;
                total_sum += contestant;
            }
        }
    }
    
    cout << total_sum << nl;
    
    For (q, num_contestants - 1) {
        ll r = decline[q];
        
        for (ll c2 : criteria[r]) {
            candidates[c2].erase(r);
        }
        
        if (invited[r] != -1) {
            ll c = invited[r];
            total_sum -= r;
            filled[c]--;
            invited[r] = -1;
            find_next(c);
        }
        cout << total_sum << nl;
    }
}