#define ll long long
#define pb push_back 
#define v vector
#define p pair
#define INF 1000000000000000000
#define inf 1000000001
#define MP(x, y) make_pair(x, y)
#define F first
#define S second
#define For(i, end) for (ll i = 0; i < end; i++)
#define roF(i, start) for (ll i = start; i >= 0; i--)
#define FOR(i, begin, end) for (ll i = begin; i < end; i++) 
#define nl "\n"
#define ss " "
#define un_map unordered_map
#define un_set unordered_set

#include <bits/stdc++.h>
using namespace std;

// Maximum Independent Set for N <= 40 using meet-in-the-middle.
//
// Split vertices into left half L = [0, nL) and right half R = [nL, N).
// For each independent set S in L, the right vertices that can be added must
// avoid all neighbors of S in R. Precompute best_R[mask] = size of the
// largest independent set whose vertices are a subset of `mask` in R, then
// the answer is max over all IS S in L of |S| + best_R[allowed_R(S)].

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int N, M;
    cin >> N >> M;

    int nL = N / 2, nR = N - nL;

    // Full adjacency stored as bitmasks over all N vertices (fits in long long for N<=40)
    vector<long long> adj(N, 0);
    for (int i = 0; i < M; i++) {
        int u, w;
        cin >> u >> w;
        adj[u] |= (1LL << w);
        adj[w] |= (1LL << u);
    }

    // Left-to-left adjacency mask (bit j set => left vertex j is a neighbor)
    vector<int> ladj(nL, 0);
    // Left-to-right adjacency mask (bit j set => right vertex nL+j is a neighbor)
    vector<int> rcross(nL, 0);
    for (int i = 0; i < nL; i++) {
        for (int j = 0; j < nL; j++)
            if ((adj[i] >> j) & 1) ladj[i] |= (1 << j);
        for (int j = 0; j < nR; j++)
            if ((adj[i] >> (nL + j)) & 1) rcross[i] |= (1 << j);
    }

    // Right-to-right adjacency mask (bit k set => right vertex nL+k is a neighbor)
    vector<int> radj(nR, 0);
    for (int j = 0; j < nR; j++)
        for (int k = 0; k < nR; k++)
            if ((adj[nL + j] >> (nL + k)) & 1) radj[j] |= (1 << k);

    // Precompute best_R[mask]: max IS size using only vertices whose bit is set in mask.
    // Recurrence: pick the lowest set bit v in mask;
    //   either skip v: best_R[mask] = best_R[mask ^ (1<<v)]
    //   or take  v: best_R[mask] = 1 + best_R[(mask ^ (1<<v)) & ~radj[v]]
    int sz = 1 << nR;
    vector<int> best_R(sz, 0);
    for (int m = 1; m < sz; m++) {
        int vb = __builtin_ctz(m);           // index of lowest set bit
        best_R[m] = best_R[m ^ (1 << vb)];  // skip v
        int rem = (m ^ (1 << vb)) & ~radj[vb];
        best_R[m] = max(best_R[m], 1 + best_R[rem]);  // take v
    }

    int ans = 0;
    int fullR = sz - 1;  // all nR bits set

    // Enumerate all independent sets in the left half.
    for (int m = 0; m < (1 << nL); m++) {
        bool ok = true;
        int blocked = 0;
        for (int tmp = m; tmp; tmp &= tmp - 1) {
            int vb = __builtin_ctz(tmp);
            if (ladj[vb] & m) { ok = false; break; }
            blocked |= rcross[vb];
        }
        if (!ok) continue;
        int allowed = fullR & ~blocked;
        ans = max(ans, __builtin_popcount(m) + best_R[allowed]);
    }

    cout << ans << nl;
}
