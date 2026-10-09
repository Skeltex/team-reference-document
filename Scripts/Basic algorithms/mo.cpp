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

// Пример: число значений x, встречающихся ровно x раз на отрезке.
void solve() {
    gp_hash_table<int, int> cnt;
    int n, q;
    cin >> n >> q;
    vi a(n);
    for (auto& i : a)
        cin >> i;
    vector<int> zp(q);
    for (int i = 0; i < q; ++i) {
        cin >> lg[i] >> rg[i];
        --lg[i];
        block[i] = lg[i] / M;
        zp[i] = i;
    }
    sort(all(zp), cmp);
    int l = 0, r = 0, cur = 0;
    auto update = [&](int pos, int delta) {
        int x = a[pos];
        if (x <= 0 || x > n) return;
        if (cnt[x] == x) --cur;
        cnt[x] += delta;
        if (cnt[x] == x) ++cur;
    };
    vector<int> ans(q);
    for (auto i : zp) {
        while (l > lg[i]) {
            --l;
            update(l, 1);
        }
        while (r < rg[i]) {
            update(r, 1);
            ++r;
        }
        while (l < lg[i]) {
            update(l, -1);
            ++l;
        }
        while (r > rg[i]) {
            --r;
            update(r, -1);
        }
        ans[i] = cur;
    }
    for (auto i : ans)
        cout << i << '\n';
}
