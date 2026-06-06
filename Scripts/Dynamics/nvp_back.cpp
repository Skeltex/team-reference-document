vi dp(n, 1);
for (int i = 1; i < n; ++i)
    for (int j = 0; j < i; ++j)
        if (a[j] < a[i])
            dp[i] = max(dp[i], dp[j] + 1);
cout << *max_element(all(dp)) << '\n';