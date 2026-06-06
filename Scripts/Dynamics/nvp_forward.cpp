vi dp(n, 1);
for (int i = 1; i < n; ++i)
    for (int j = i + 1; j < n; ++j)
        if (a[j] > a[i])
            dp[j] = max(dp[j], dp[i] + 1);
cout << *max_element(all(dp)) << '\n';