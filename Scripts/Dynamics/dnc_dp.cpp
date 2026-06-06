int n, k;
int dp[100013][22];
int a[100013];
int cnt[100013];
int sm = 0, lg = 1, rg = 1;

//recalc for CD 868F

void calc(int l, int r) {
    while (rg < r) sm += cnt[a[rg++]]++;
    while (lg > l) sm += cnt[a[--lg]]++;
    while (rg > r) sm -= --cnt[a[--rg]];
    while (lg < l) sm -= --cnt[a[lg++]];
}

void rec(int l, int r, int opt_l, int opt_r, int j) {
    if (l > r) return;
    int mid = (l + r) / 2;
    int opt = opt_l;
    for (int i = opt_l; i <= min(mid, opt_r); i++) {
        calc(i, mid + 1);
        if (dp[mid][j] > dp[i - 1][j - 1] + sm) {
            dp[mid][j] = dp[i - 1][j - 1] + sm;
            opt = i;
        }
    }
    rec(l, mid - 1, opt_l, opt, j);
    rec(mid + 1, r, opt, opt_r, j);
}

void solve() {
    cin >> n >> k;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= k; j++) dp[i][j] = INF;
    }
    dp[0][0] = 0;
    for (int i = 0; i < n; i++) cin >> a[i + 1];
    for (int i = 0; i < k; i++) {
        rec(1, n, 1, n, i + 1);
    }
    cout << dp[n][k];
}