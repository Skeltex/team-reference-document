struct SparseTable {
    int n;
    int lg;
    vvi T;

    void build(const vi& a) {
        n = sz(a);
        lg = __lg(n) + 1;
        T.resize(lg);

        T[0] = a;
        for (int i = 1; i < lg; ++i) {
            T[i].resize(n - (1 << i) + 1);
            int len = 1 << i;
            for (int j = 0; j + len <= n; ++j)
                T[i][j] = min(T[i - 1][j], T[i - 1][j + (len >> 1)]);
        }
    }

    int query(int l, int r) const {
        ++r;
        int len = __lg(r - l);
        return min(T[len][l], T[len][r - (1 << len)]);
    }

    SparseTable(const vi& a) {
        build(a);
    }

    SparseTable(int n) : n(n) {
        vi a(n, 0LL);
        build(a);
    }
};
