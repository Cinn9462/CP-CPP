#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pb push_back 
#define v vector
#define p pair
#define F first
#define S second
#define For(i, end) for (ll i = 0; i < end; i++)
#define roF(i, begin) for (ll i = begin; i >= 0; i--)
#define FOR(i, begin, end) for (ll i = begin; i < end; i++) 
#define ROF(i, begin, end) for (ll i = begin; i > end; i--)
#define nl "\n"
#define ss " "
#define all(x) x.begin(), x.end()
#define popcount(x) __builtin_popcountll(x)
#define fileread(file) ifstream fin; fin.open((string)file + ".in"); ofstream fout; fout.open((string)file + ".out")

ostream& operator<<(ostream& os, v<ll>& arr) {
    for (ll ___a : arr) {
        os << ___a << " ";
    }
    return os;
}

int comp(ll a, ll b) {
    if (a > b) return 2;
    if (a == b) return 1;
    return 0;
}


int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    // fileread("4");
    ll N, A, B; cin >> N >> A >> B;
    // ll N, A, B; fin >> N >> A >> B;
    ll nums[N];
    For(i, N) cin >> nums[i];
    // For(i, N) fin >> nums[i];
    A--; 

    ll digitA[18]; // maximum digit allowed in each space
    memset(digitA, 0, sizeof(digitA));
    For(i, to_string(A).size()) {
        digitA[18 + i - to_string(A).size()] = to_string(A)[i] - '0';
    }
    ll digitB[18]; // maximum digit allowed in each space
    memset(digitB, 0, sizeof(digitB));
    For(i, to_string(B).size()) {
        digitB[18 + i - to_string(B).size()] = to_string(B)[i] - '0';
    }

    ll ansA[N][N];
    ll ansB[N][N];
    memset(ansA, 0, sizeof(ansA));
    memset(ansB, 0, sizeof(ansB));
    
    For (L, N) {
        ll dp[18][18][3];
        memset(dp, 0, sizeof(dp));
        FOR (R, L, N) {
            For(i, 18) {
                ROF(j, 17, i) {
                    // Rth digit is added to front
                    if (nums[R] > digitB[i]) For(flag, 3) dp[i][j][2] += dp[i + 1][j][flag]; // Rth digit is bigger, so result is bigger
                    if (nums[R] < digitB[i]) For(flag, 3) dp[i][j][0] += dp[i + 1][j][flag]; // Rth digit is smaller, so result is smaller
                    if (nums[R] == digitB[i]) For(flag, 3) dp[i][j][flag] += dp[i + 1][j][flag]; // Rth digit is equal, so prefix persists

                    // Rth digit is added to back
                    dp[i][j][2] += dp[i][j - 1][2]; // prefix is bigger , so Rth digit does not matter
                    dp[i][j][0] += dp[i][j - 1][0]; // prefix is smaller, so Rth digit does not matter
                    dp[i][j][comp(nums[R], digitB[j])] += dp[i][j - 1][1]; // prefix is equal, so Rth digit tiebreaks

                    // mod to keep values small
                    For(flag, 3) dp[i][j][flag] %= (1000000007);
                }
            }

            // add base cases
            For(i, 18) {
                dp[i][i][comp(nums[R], digitB[i])] += 2; // can add to top and bottom, but they are equivalent
            }

            // smaller in length
            FOR(i, 18 - to_string(B).size() + 1, 18) For(flag, 3) {
                ansB[L][R] += dp[i][17][flag];
                ansB[L][R] %= (1000000007);
            }
            // equal length, but smaller
            ansB[L][R] += dp[18 - to_string(B).size()][17][0];
            ansB[L][R] += dp[18 - to_string(B).size()][17][1];
            ansB[L][R] %= (1000000007);
        }
    }

    For (L, N) {
        ll dp[18][18][3];
        memset(dp, 0, sizeof(dp));
        FOR (R, L, N) {
            For(i, 18) {
                ROF(j, 17, i) {
                    // Rth digit is added to front
                    if (nums[R] > digitA[i]) For(flag, 3) dp[i][j][2] += dp[i + 1][j][flag]; // Rth digit is bigger, so result is bigger
                    if (nums[R] < digitA[i]) For(flag, 3) dp[i][j][0] += dp[i + 1][j][flag]; // Rth digit is smaller, so result is smaller
                    if (nums[R] == digitA[i]) For(flag, 3) dp[i][j][flag] += dp[i + 1][j][flag]; // Rth digit is equal, so prefix persists

                    // Rth digit is added to back
                    dp[i][j][2] += dp[i][j - 1][2]; // prefix is bigger , so Rth digit does not matter
                    dp[i][j][0] += dp[i][j - 1][0]; // prefix is smaller, so Rth digit does not matter
                    dp[i][j][comp(nums[R], digitA[j])] += dp[i][j - 1][1]; // prefix is equal, so Rth digit tiebreaks

                    // mod to keep values small
                    For(flag, 3) dp[i][j][flag] %= (1000000007);
                }
            }

            // add base cases
            For(i, 18) {
                dp[i][i][comp(nums[R], digitA[i])] += 2; // can add to top and bottom, but they are equivalent
            }

            // smaller in length
            FOR(i, 18 - to_string(A).size() + 1, 18) For(flag, 3) {
                ansA[L][R] += dp[i][17][flag];
                ansA[L][R] %= (1000000007);
            }
            // equal length, but smaller
            ansA[L][R] += dp[18 - to_string(A).size()][17][0];
            ansA[L][R] += dp[18 - to_string(A).size()][17][1];
            ansA[L][R] %= (1000000007);
        }
    }

    ll Q, l, r; cin >> Q;
    // ll Q, l, r; fin >> Q;
    For(i, Q) {
        cin >> l >> r;
        // fin >> l >> r;
        l--; r--;
        cout << ((ansB[l][r] + 1000000007) - ansA[l][r]) % 1000000007 << nl;
    }
}