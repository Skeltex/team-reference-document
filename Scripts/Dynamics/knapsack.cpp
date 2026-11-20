// Достижимость сумм 0..W и сертификат. O(nW), память O(W).
vc dp(W + 1, false);
vi pr(W + 1, -1);
dp[0] = true;
for (int i = 0; i < n; ++i) {
    for (int j = W; j >= a[i]; --j) {
        if (!dp[j] && dp[j - a[i]]) {
            dp[j] = true;
            pr[j] = i;
        }
    }
}
vi ans;
if (dp[W]) {
    for (int s = W; s > 0; s -= a[pr[s]])
        ans.push_back(pr[s]);
    reverse(all(ans));
}
