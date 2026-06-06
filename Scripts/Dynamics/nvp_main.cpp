vi dp(n + 1, INF);
dp[0] *= -1;
for (int i = 1; i <= n; i++)
    dp[lower_bound(all(dp), a[i - 1]) - dp.begin()] = a[i - 1];
cout << lower_bound(all(dp), INF) - dp.begin() - 1 << '\n';