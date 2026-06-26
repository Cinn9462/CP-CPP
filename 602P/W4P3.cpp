#include <bits/stdc++.h>
using namespace std;

struct Friend {
    int popularity, cost, bribe;
    Friend() : popularity(0), cost(0), bribe(0) {}
};

bool x_sort(Friend f1, Friend f2) {
    return f1.bribe < f2.bribe;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int N, moonies, ice_cream; 
    cin >> N >> moonies >> ice_cream;
    vector<Friend> friends(N);
    for(int i = 0; i < N; i++) cin >> friends[i].popularity >> friends[i].cost >> friends[i].bribe;
    sort(friends.begin(), friends.end(), x_sort); // sort by lowest cost to bribe

    vector<long long> dp(moonies + ice_cream + 1, -1); // -1 represents unvisited
    dp[0] = 0;

    for (Friend f : friends) {
        for (int i = moonies + ice_cream - f.cost; i >= 0; i--) { // prevent out-of-bounds indexing
            // skip if unvisited
            if (dp[i] == -1) continue;

            // spending only moonies
            if (i >= ice_cream) dp[i + f.cost] = max(dp[i + f.cost], dp[i] + f.popularity);

            // spending only ice creams
            else if (ice_cream - i >= f.cost * f.bribe) dp[i + f.cost * f.bribe] = max(dp[i + f.cost * f.bribe], dp[i] + f.popularity); 
            
            // spending a mixed amount of moonies and ice creams
            else if (ice_cream + (f.cost - ((ice_cream - i) / f.bribe)) <= moonies + ice_cream) dp[ice_cream + (f.cost - ((ice_cream - i) / f.bribe))] = max(dp[ice_cream + (f.cost - ((ice_cream - i) / f.bribe))], dp[i] + f.popularity);
        }
    }

    cout << *max_element(dp.begin(), dp.end());
}