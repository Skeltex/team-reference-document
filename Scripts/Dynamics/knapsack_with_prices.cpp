bool update(int& x, int y) {
    if (x >= y)
        return false;
    x = y;
    return true;
}

vvi dp(n + 1, vi(W + 1, -INF));
dp[0][0] = 0;

for (int i = 0; i < n; ++i) {
    for (int j = 0; j <= W; ++j) {
        if (dp[i][j] != -INF) {
            update(dp[i + 1][j], dp[i][j]);
            if (a[i] + j <= W)
                update(dp[i + 1][j + a[i]], dp[i][j] + b[i]);
        }
    }
}