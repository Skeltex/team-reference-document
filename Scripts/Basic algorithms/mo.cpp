int lg[N], rg[N];
int64_t ord[N];
inline int64_t hilbertOrder(int x, int y) {
    int64_t d = 0;
    for (int s = 1 << 20; s > 0; s >>= 1) {
        int rx = (x & s) > 0, ry = (y & s) > 0;
        d = (d << 2) | ((rx * 3) ^ ry);
        if (!ry) {
            if (rx) { x = ~x; y = ~y; }
            swap(x, y);
        }
    }
    return d;
}
bool cmp(int i, int j) { return ord[i] < ord[j]; }
void solve() {
    unordered_map<int, int> cnt;
    int n, q;
    cin >> n >> q;
    vector<int> a(n), ans(q), zp(q);
    for (auto& i : a) cin >> i;
    for (int i = 0; i < q; ++i) {
        cin >> lg[i] >> rg[i];
        ord[i] = hilbertOrder(--lg[i], rg[i]);
        zp[i] = i;
    }
    sort(all(zp), cmp);
    int l = lg[zp[0]], r = l, cur = 0;
    for (auto i : zp) {
        while (l > lg[i]) { --l; if (++cnt[a[l]] == a[l]) ++cur; else if (cnt[a[l]] == a[l] + 1) --cur; }
        while (r < rg[i]) { if (++cnt[a[r]] == a[r]) ++cur; else if (cnt[a[r]] == a[r] + 1) --cur; ++r; }
        while (l < lg[i]) { if (cnt[a[l]]-- == a[l]) --cur; else if (cnt[a[l]] == a[l]) ++cur; ++l; }
        while (r > rg[i]) { --r; if (cnt[a[r]]-- == a[r]) --cur; else if (cnt[a[r]] == a[r]) ++cur; }
        ans[i] = cur;
    }
    for (auto i : ans) cout << i << '\n';
}