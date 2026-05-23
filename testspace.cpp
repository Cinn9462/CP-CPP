v<v<ll>> dp(N + 1, v<ll>(S + 1, -1));
    dp[0][0] = 0;

    For(i, N) {
        For(j, S + 1) {
            dp[i + 1][j] = dp[i][j];
            if (dp[i] != -1 && j + max(app[i][0], app[i][1]) <= S && dp[i][j] + 1 > dp[i + 1][j + app[i][]])
        }
    }