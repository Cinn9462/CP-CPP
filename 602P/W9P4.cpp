    #include <bits/stdc++.h>
    using namespace std;

    #define ll long long
    #define v vector
    #define pb push_back
    #define all(x) x.begin(), x.end()
    #define For(i, a) for(ll i = 0; i < a; i++)
    #define FOR(i, a, b) for(ll i = a; i < b; i++)
    #define roF(i, a) for(ll i = a; i >= 0; i--)
    #define ROF(i, a, b) fo (ll i = a; i >= b; i--)
    #define p pair
    #define F first
    #define S second
    #define ss " "
    #define nl "\n"

    int main() {
        ios::sync_with_stdio(0); cin.tie(0);
        ll N; cin >> N;
        v<ll> nums(N); For(i, N) cin >> nums[i];
        
        // minimum xor query with trie
        v<array<int, 2>> trie;
        auto min_xor = [&](v<ll> &v1, v<ll> &v2) -> ll {
            trie.clear();
            trie.pb({-1, -1});
            for (ll i : v1) {
                ll node = 0;
                roF(b, 29) {
                    if (trie[node][(i >> b) & 1] == -1) {
                        trie[node][(i >> b) & 1] = trie.size();
                        trie.pb({-1, -1});
                    }
                    node = trie[node][(i >> b) & 1];
                }
            }
            ll best = LLONG_MAX;
            for (ll i : v2) {
                ll node = 0; ll curr = 0;
                roF(b, 29) {
                    if (trie[node][(i >> b) & 1] != -1) {
                        node = trie[node][(i >> b) & 1];
                    } else {
                        node = trie[node][((i >> b) & 1) ^ 1];
                        curr |= 1 << b;
                    }
                }
                best = min(best, curr);
            }
            return best;
        };

        auto dfs = [&](auto&& dfs, v<ll>& curr, ll bit) -> ll {
            if (curr.size() == 2) return curr[0] ^ curr[1];
            if (curr.size() < 2) return 0;
            if (bit == -1) return 0;

            v<ll> zero, one;
            for(ll n : curr) {
                if ((n >> bit) & 1) one.pb(n);
                else zero.pb(n);
            }
            return dfs(dfs, one, bit - 1) + dfs(dfs, zero, bit - 1) + ((one.size() != 0 && zero.size() != 0) ? min_xor(one, zero) : 0);
        };

        cout << dfs(dfs, nums, 29) << nl;
    }