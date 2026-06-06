vvi dp(n + 1, vi(W + 1, false));
dp[0][0] = true;

for (int i = 0; i < n; ++i) {
    for (int j = 0; j <= W; ++j) {
        if (dp[i][j]) {
            dp[i + 1][j] = true;
            if (j + a[i] <= W)
                dp[i + 1][j + a[i]] = true;
        }
    }
}