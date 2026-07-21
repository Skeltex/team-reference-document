const int base = 10'128'551, N = 3'000'013, MOD = 1'009'456'381;
int p[N];

void precalc() {
    p[0] = 1;
    for (int i = 1; i < N; ++i)
        p[i] = (p[i - 1] * 1ll * base) % MOD;
}

int create_hash(const string& s) {
    int hs = 0;
    for (char c : s)
        hs = (hs * 1ll * base + c + 1) % MOD;
    return hs;
}

struct SingleHash {
    vector<int> h;

    SingleHash(const string& s) {
        h.assign(sz(s) + 1, 0);
        for (int i = 0; i < sz(s); ++i)
            h[i + 1] = (h[i] * 1ll * base + s[i] + 1) % MOD;
    }

    int get(int l, int r) const {
        return (h[r + 1] - h[l] * 1ll * p[r - l + 1] % MOD + MOD) % MOD;
    }
};