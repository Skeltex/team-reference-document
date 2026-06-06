int mx[N];
vector<int> m[N];

void per() {
    vector<int> els;
    for (int i = 0; i < N; i++) {
        for (auto j : m[i]) els.push_back(j);
        m[i] = {};
        mx[i] = 0;
    }
    int cur = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            mx[i] = max(mx[i], els[cur]);
            m[i].push_back(els[cur++]);
            if (cur == els.size()) return;
        }
    }
}

void solve() {
    int n; cin >> n;
    map<int, int> mp;
    vector<int> a(n), c(n);
    for (int i = 0; i < n; i++) cin >> a[i] >> c[i], mp[a[i]] = i + 1;
    for (int i = 0; i < n; i++) {
        int j = N - 1;
        for (; j >= 0; j--) {
            if (c[i] - (int)m[j].size() < 0 or mx[j] > a[i]) break;
            c[i] -= (int)m[j].size();
        }
        if (j == -1) {
            mx[0] = max(mx[0], a[i]);
            m[0].insert(m[0].begin(), a[i]);
            continue;
        }
        int k = m[j].size() - 1;
        for (; k >= 0; k--) {
            if (c[i] == 0 or m[j][k] > a[i]) break;
            c[i]--;
        }
        m[j].insert(m[j].begin() + k + 1, a[i]);
        mx[j] = max(mx[j], a[i]);
        if (i % N == 0) per();
    }
    for (int i = 0; i < N; i++) {
        for (auto j : m[i]) cout << mp[j] << ' ';
    }
}