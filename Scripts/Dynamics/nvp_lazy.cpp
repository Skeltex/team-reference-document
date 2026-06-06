int calc(int i, const vi& a, vi& dp) {
    if (dp[i] != -1)
        return dp[i];

    dp[i] = 1;
    for (int j = 0; j < i; ++j)
        if (a[i] > a[j])
            dp[i] = max(dp[i], calc(j, a, dp) + 1);
    return dp[i];
}

vi dp(n, -1);
calc(n - 1, a, dp);
cout << *max_element(all(dp)) << '\n';