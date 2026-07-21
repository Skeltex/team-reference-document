const int B[2] = { 10'128'551, 10'526'657 };
const int M[2] = { 1'009'456'381, 1'004'835'929 };
const int N = 3'000'013;
int p[2][N];

void precalc() {
    p[0][0] = p[1][0] = 1;
    for (int k : {0, 1})
        for (int i = 1; i < N; ++i)
            p[k][i] = (p[k][i - 1] * 1ll * B[k]) % M[k];
}

li create_hash(const string& s) {
    int hs[2] = { 0, 0 };
    for (char c : s)
        for (int k : {0, 1})
            hs[k] = (hs[k] * 1ll * B[k] + c + 1) % M[k];
    return (1ll * hs[0] << 32) | hs[1];
}

struct DoubleHash {
    vector<int> h[2];

    DoubleHash(const string& s) {
        h[0].assign(sz(s) + 1, 0);
        h[1].assign(sz(s) + 1, 0);

        for (int k : {0, 1})
            for (int i = 0; i < sz(s); ++i)
                h[k][i + 1] = (h[k][i] * 1ll * B[k] + s[i] + 1) % M[k];
    }

    li get(int l, int r) const {
        li res = 0;
        for (int k : {0, 1}) {
            int val = (h[k][r + 1] - h[k][l] * 1ll * p[k][r - l + 1] % M[k] + M[k]) % M[k];
            res = (res << 32) | val;
        }
        return res;
    }
};