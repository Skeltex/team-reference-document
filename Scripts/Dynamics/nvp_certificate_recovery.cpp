vi dp(n, 1), p(n, -1);
for (int i = 0; i < n; ++i)
    for (int j = i + 1; j < n; ++j)
        if (a[j] > a[i])
            if (dp[i] + 1 > dp[j]) {
                dp[j] = dp[i] + 1;
                p[j] = i;
            }
int pos = max_element(all(dp)) - dp.begin();
vi ans;
while (pos != -1) {
    ans.push_back(pos);
    pos = p[pos];
}
reverse(all(ans));
cout << ans;