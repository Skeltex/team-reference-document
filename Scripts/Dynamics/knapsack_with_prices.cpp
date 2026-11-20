// Веса w[i] >= 0, цены c[i]. 2 слоя + сертификат.
// Память O(W) на dp + n*W бит на take.
vli dp(W + 1, -INF), ndp(W + 1);
vector<vector<bool>> take(n, vector<bool>(W + 1));
dp[0] = 0;
for (int i = 0; i < n; ++i) {
    ndp = dp;
    for (int j = w[i]; j <= W; ++j) {
        if (dp[j - w[i]] == -INF) continue;
        li cand = dp[j - w[i]] + c[i];
        if (cand > ndp[j]) {
            ndp[j] = cand;
            take[i][j] = true;
        }
    }
    dp.swap(ndp);
}
int best = max_element(all(dp)) - dp.begin();
vi ans;
for (int i = n - 1, s = best; i >= 0; --i) {
    if (take[i][s]) {
        ans.push_back(i);
        s -= w[i];
    }
}
reverse(all(ans));
