#include <bits/stdc++.h>
using namespace std;

// Brute-force Maximum Independent Set: try every subset in O(2^N * N).
// Only for small N (stress testing).

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<long long> adj(N, 0);
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        adj[u] |= (1LL << v);
        adj[v] |= (1LL << u);
    }

    int best = 0;
    int best_mask = 0;
    for (int mask = 0; mask < (1 << N); mask++) {
        bool ok = true;
        for (int i = 0; i < N && ok; i++) {
            if (!((mask >> i) & 1)) continue;
            // Check if any other vertex in mask is adjacent to i
            if (adj[i] & mask & ~(1LL << i)) ok = false;
        }
        if (ok && __builtin_popcount(mask) > best) {
            best = __builtin_popcount(mask);
            best_mask = mask;
        }
    }

    cout << best << "\n";
    for (int i = 0; i < N; i++)
        if ((best_mask >> i) & 1) cout << i << " ";
    cout << "\n";
}
