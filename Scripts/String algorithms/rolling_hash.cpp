const int mn = 1'063'831, N = 300'013, MOD = 1'000'752'847;
int p[N];

void calc() {
    p[0] = 1;
    for (int i = 1; i < N; ++i)
        p[i] = (p[i - 1] * mn) % MOD;
}

int create_hash(const string& s) {
    int hs = 0;
    for (char c : s)
        hs = (hs * mn + c + 1) % MOD;
    return hs;
}

vli create_all_hashes(const string& s) {
    vli hs(sz(s) + 1);
    for (int i = 0; i < sz(s); ++i)
        hs[i + 1] = (hs[i] * mn + s[i] + 1) % MOD;
    return hs;
}

int get_segment_hash(int l, int r, const vli& hs) {
    return (MOD + hs[r + 1] - (hs[l] * p[r - l + 1]) % MOD) % MOD;
}