#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pb push_back 
#define v vector
#define p pair
#define F first
#define S second
#define For(i, end) for (ll i = 0; i < end; i++)
#define roF(i, start) for (ll i = start; i >= 0; i--)
#define FOR(i, begin, end) for (ll i = begin; i < end; i++) 
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

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    fileread("odometer");

    ll A, B; fin >> A >> B;

    auto solve = [&](ll N) -> ll { // returns query for [0, N]

        v<ll> max_digit(20, 0); // maximum digit allowed in each space
        For(i, to_string(N).size()) {
            max_digit[20 + i - to_string(N).size()] = to_string(N)[i] - '0';
        }

        ll ans = 0;
        
        For(i, 10) {
            // pos -> index we are changing [0,19]
            // start -> if all digits are leading zeros [0, 1]
            // count -> # of digits above and below 20 that are the same as selected digit[0, 40]
            // top -> if current number is at the limit of the selected N [0, 1]

            v<v<v<v<ll>>>> dp(20, v<v<v<ll>>>(2, v<v<ll>>(41, v<ll>(2, -1))));

            auto dfs = [&](auto&& self, ll pos, ll start, ll count, ll top, ll digit) -> ll {

                // base case
                if (pos == 20) return (count >= 20 && !start) ? 1 : 0;

                // memoization
                if (dp[pos][start][count][top] != -1) return dp[pos][start][count][top];

                ll curr_sum = 0;
                For(next_digit, 10) {
                    ll next_top, next_start, next_count = count;

                    if (top && next_digit > max_digit[pos]) continue;

                    next_top = top && (next_digit == max_digit[pos]);
                    next_start = start && (next_digit == 0);
                    if (!next_start) next_count += (next_digit == digit) ? 1 : -1;

                    curr_sum += self(self, pos + 1, next_start, next_count, next_top, digit);
                }

                return dp[pos][start][count][top] = curr_sum;
            };
            ans += dfs(dfs, 0, 1, 20, 1, i);
        }

        For(i, 10) {
            FOR (j, i + 1, 10) {
                // pos -> index we are changing [0,19]
                // start -> if all digits are leading zeros [0, 1]
                // count1 -> # of digits above and below 20 that are the same as 1st select digit[0, 40]
                // count2 -> # of digits above and below 20 that are the same as 2nd selec digit[0, 40]
                // top -> if current number is at the limit of the selected N [0, 1]

                v<v<v<v<v<ll>>>>> dp(20, v<v<v<v<ll>>>>(2, v<v<v<ll>>>(41, v<v<ll>>(41, v<ll>(2, -1)))));

                auto dfs2 = [&](auto&& self, ll pos, ll start, ll count1, ll count2, ll top, ll digit1, ll digit2) -> ll {

                    // base case
                    if (pos == 20) return (count1 >= 20 && count1 == count2 && !start) ? 1 : 0;

                    // memoization
                    if (dp[pos][start][count1][count2][top] != -1) return dp[pos][start][count1][count2][top];

                    ll curr_sum = 0;
                    For(next_digit, 10) {
                        ll next_top, next_start, next_count1 = count1, next_count2 = count2;

                        if (top && next_digit > max_digit[pos]) continue;

                        next_top = top && (next_digit == max_digit[pos]);
                        next_start = start && (next_digit == 0);
                        if (!next_start) next_count1 += (next_digit == digit1) ? 1 : -1;
                        if (!next_start) next_count2 += (next_digit == digit2) ? 1 : -1;

                        curr_sum += self(self, pos + 1, next_start, next_count1, next_count2, next_top, digit1, digit2);
                    }

                    return dp[pos][start][count1][count2][top] = curr_sum;
                };
                ans -= dfs2(dfs2, 0, 1, 20, 20, 1, i, j);
            }
        }   

        return ans;
    };

    fout << solve(B) - solve(A - 1) << nl;
}