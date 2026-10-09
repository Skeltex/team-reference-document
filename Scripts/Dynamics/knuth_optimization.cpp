// a — неотрицательная симметричная матрица с нулевой диагональю, 1 <= k <= n.
// Для этой стоимости opt[i][j - 1] <= opt[i][j] <= opt[i + 1][j].
vvli prs(n + 1, vli(n + 1));
for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
        prs[i][j] = a[i - 1][j - 1] + prs[i - 1][j] + prs[i][j - 1] - prs[i - 1][j - 1];
    }
}
vvli dp(n + 1, vli(k + 1, INF));
vector<vector<int>> opt(n + 2, vector<int>(k + 1, 1));
dp[0][0] = 0;
for (int j = 1; j <= k; ++j) {
    opt[n + 1][j] = n;
    for (int i = n; i >= j; --i) {
        for (int l = max(j, opt[i][j - 1]); l <= min(i, opt[i + 1][j]); ++l) {
            if (dp[l - 1][j - 1] == INF) continue;
            if (dp[i][j] > dp[l - 1][j - 1]
                    + (prs[i][i] + prs[l - 1][l - 1] - prs[i][l - 1] - prs[l - 1][i]) / 2) {
                dp[i][j] = dp[l - 1][j - 1]
                    + (prs[i][i] + prs[l - 1][l - 1] - prs[i][l - 1] - prs[l - 1][i]) / 2;
                opt[i][j] = l;
            }
        }
    }
}
cout << dp[n][k] << '\n';
