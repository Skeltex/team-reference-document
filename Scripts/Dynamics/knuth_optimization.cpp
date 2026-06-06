vector<vector<int>> prs(n + 1, vector<int>(n + 1));
for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
        prs[i][j] = a[i - 1][j - 1] + prs[i - 1][j] + prs[i][j - 1] - prs[i - 1][j - 1];
    }
}
vector<vector<int>> dp(n + 1, vector<int>(k + 1, INF));
vector<vector<int>> opt(n + 2, vector<int>(k + 1, 1));
dp[0][0] = 0;
for (int j = 1; j <= k; j++) {
    opt[n + 1][j] = n;
    for (int i = n; i > 0; i--) {
        for (int l = opt[i][j - 1]; l <= opt[i + 1][j]; l++) {
            // dp[i][j] = min(dp[i][j], dp[l][j - 1] + (prs[i][i] + prs[l][l] - prs[i][l] - prs[l][i]) / 2);
            if (dp[i][j] > dp[l - 1][j - 1] + (prs[i][i] + prs[l - 1][l - 1] - prs[i][l - 1] - prs[l - 1][i]) / 2) {
                dp[i][j] = dp[l - 1][j - 1] + (prs[i][i] + prs[l - 1][l - 1] - prs[i][l - 1] - prs[l - 1][i]) / 2;
                opt[i][j] = l;
            }
        }
    }
}
cout << dp[n][k] << '\n';