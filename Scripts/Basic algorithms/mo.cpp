const int M = 300;
const int N = 100'013;

int block[N];
int lg[N];
int rg[N];

bool cmp(int i, int j) {
    if (block[i] != block[j]) return block[i] < block[j];
    if (block[i] & 1) return rg[i] > rg[j];
    return rg[i] < rg[j];
}

void solve() {
    unordered_map<int, int> cnt;
    int n, q; cin >> n >> q;
    vector<int> a(n);
    for (auto& i : a) cin >> i;
    vector<int> zp(q);
    for (int i = 0; i < q; i++) {
        cin >> lg[i] >> rg[i];
        lg[i]--;
        block[i] = lg[i] / M;
        zp[i] = i;
    }
    sort(all(zp), cmp);
    int l = lg[zp[0]], r = l, cur = 0;
    vector<int> ans(q);
    for (auto i : zp) {
        while (l > lg[i]) {
            l--;
            if (++cnt[a[l]] == a[l]) cur++;
            else if (cnt[a[l]] == a[l] + 1) cur--;
        }
        while (r < rg[i]) {
            if (++cnt[a[r]] == a[r]) cur++;
            else if (cnt[a[r]] == a[r] + 1) cur--;
            r++;
        }
        while (l < lg[i]) {
            if (cnt[a[l]]-- == a[l]) cur--;
            else if (cnt[a[l]] == a[l]) cur++;
            l++;
        }
        while (r > rg[i]) {
            r--;
            if (cnt[a[r]]-- == a[r]) cur--;
            else if (cnt[a[r]] == a[r]) cur++;
        }
        ans[i] = cur;
    }
    for (auto i : ans) cout << i << '\n';
}