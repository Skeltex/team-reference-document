vvi dp(n + 1, vi(m + 1, -INF));
dp[0][0] = 0;

for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= m; ++j) {
        // Пропустить элемент в a
        if (i < n)
            dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);

        // Пропустить элемент в b
        if (j < m)
            dp[i][j + 1] = max(dp[i][j + 1], dp[i][j]);

        // Взять оба элемента
        if (i < n && j < m && a[i] == b[j])
            dp[i + 1][j + 1] = max(dp[i + 1][j + 1], dp[i][j] + 1);
    }
}
cout << dp[n][m] << '\n';