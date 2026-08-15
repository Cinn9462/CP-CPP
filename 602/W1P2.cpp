#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;

#define ll long long
#define v vector
#define pb push_back
#define all(x) x.begin(), x.end()
#define For(i, a) for(ll i = 0; i < a; i++)
#define FOR(i, a, b) for(ll i = a;i < b; i++)
#define nl "\n"
#define ss " "
#define MOD 998244353

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll t; cin >> t; 
    while(t--) {
        ll N, M; cin >> N >> M;
        v<string> grid(N); // char './*' for grid[i][j]
        v<v<ll>> adj(N * M); // x * N + y
        For(i, N) {
            cin >> grid[i];
        }

        v<ll> parent(N * M);
        For(i, N * M) parent[i] = i;
        v<ll> size(N * M, 1);
        v<ll> count(N * M, 0);
        v<bool> has_self(N * M);

        ll ans = 1;

        auto find = [&](auto&& find, ll v1) -> ll {
            if (v1 == parent[v1]) return v1;
            return parent[v1] = find(find, parent[v1]);
        };

        auto merge = [&](ll v1, ll v2) -> void {
            ll p_u = find(find, v1);
            ll p_v = find(find, v2);
            if (p_u == p_v) {
                if (v1 == v2) has_self[p_u] = true;
                count[p_u]++;
                return;
            }
            parent[p_v] = p_u;
            count[p_u] += count[p_v] + 1;
            size[p_u] += size[p_v];
            has_self[p_u] = has_self[p_u] || has_self[p_v];
        };

        For(i, N) {
            For(j, M) {
                if (grid[i][j] == '*') {
                    if (i > 0 && i < N - 1 && grid[i - 1][j] == '.' && grid[i + 1][j] == '.') {
                        merge((i - 1) * M + j, (i + 1) * M + j);
                    }
                    else if (i > 0 && grid[i - 1][j] == '.') {
                        merge((i - 1) * M + j, (i - 1) * M + j);
                    }
                    else if (i < N - 1 && grid[i + 1][j] == '.') {
                        merge((i + 1) * M + j, (i + 1) * M + j);
                    }
                    else ans = 0;
                    if (j > 0 && j < M - 1 && grid[i][j - 1] == '.' && grid[i][j + 1] == '.') {
                        merge(i * M + j - 1, i * M + j + 1);
                    }
                    else if (j > 0 && grid[i][j - 1] == '.') {
                        merge(i * M + j - 1, i * M + j - 1);
                    }
                    else if (j < M - 1 && grid[i][j + 1] == '.') {
                        merge(i * M + j + 1, i * M + j + 1);
                    }
                    else ans = 0;
                }
            }
        }

        For(i, N * M) {
            if (find(find, i) == i) {
                if (count[i] >= size[i] + 1) ans = 0;
                else if (count[i] == size[i] && has_self[i]) ans = ans;
                else if (count[i] == size[i]) ans = (ans + ans) % MOD;
                else ans = (ans * size[i]) % MOD;

            }
        }

        cout << ans << nl;
    }
}