 // For(i, 10) {
        //     // pos -> index we are changing [0,19]
        //     // start -> if all digits are leading zeros [0, 1]
        //     // count -> # of digits above and below 20 that are the same as selected digit[0, 40]
        //     // top -> if current number is at the limit of the selected N [0, 1]

        //     v<v<v<v<ll>>>> dp(20, v<v<v<ll>>>(2, v<v<ll>>(41, v<ll>(2, -1))));

        //     auto dfs = [&](auto&& self, ll pos, ll start, ll count, ll top, ll digit) -> ll {

        //         // base case
        //         if (pos == 20) (count >= 20 && !start) ? 1 : 0;

        //         // memoization
        //         if (dp[pos][start][count][top] != -1) return dp[pos][start][count][top];

        //         ll curr_sum = 0;
        //         For(next_digit, 10) {
        //             ll next_top, next_start, next_count = count;

        //             if (top && next_digit > max_digit[pos]) continue;

        //             next_top = top && (next_digit == max_digit[pos]);
        //             next_start = start & (next_digit == 0);
        //             if (!next_start) next_count += (next_digit == digit) ? 1 : -1;

        //             curr_sum += self(self, pos + 1, next_start, next_count, next_top, digit);
        //         }

        //         return dp[pos][start][count][top] = curr_sum;
        //     };
        //     ans += dfs(dfs, 0, 1, 20, 1, i);
        // }