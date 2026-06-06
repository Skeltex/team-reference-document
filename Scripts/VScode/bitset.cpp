const int sz = 6250001;

void solve() {
    vi pr(sz);
    int n, w; cin >> n >> w;
    vi a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    bitset<sz> bt, dif;
    bt[0] = 1;
    for (int i = 0; i < n; i++) {
        dif = bt ^ (bt | bt << a[i]);
        bt |= bt << a[i];
        int ch = dif._Find_first();
        while (ch != sz) {
            pr[ch] = i + 1;
            ch = dif._Find_next(ch);
        }
    }
    if (!bt[w]) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    vi ans;
    int cur = pr[w], curs = w;
    while (cur) {
        ans.push_back(cur);
        curs -= a[cur - 1];
        cur = pr[curs];
    }
    cout << sz(ans) << nl;
    for (int i = sz(ans) - 1; i >= 0; i--) cout << ans[i] << ' ';
}