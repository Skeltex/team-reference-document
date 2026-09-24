struct SumSegmentTree {
    vector<li> T;
    int n;

    void recalc(int v) {
        T[v] = T[2 * v + 1] + T[2 * v + 2];
    }

    void build(int v, int l, int r, const vector<int>& a) {
        if (r - l == 1) {
            T[v] = a[l];
            return;
        }
        int m = (l + r) / 2;
        build(2 * v + 1, l, m, a);
        build(2 * v + 2, m, r, a);
        recalc(v);
    }

    void build(const vector<int>& a) {
        n = sz(a);
        T.assign(4 * n, 0LL);
        build(0, 0, n, a);
    }

    void update(int v, int l, int r, int pos, int val) {
        if (r - l == 1) {
            T[v] = val;
            return;
        }
        int m = (l + r) / 2;
        if (pos < m) update(2 * v + 1, l, m, pos, val);
        else update(2 * v + 2, m, r, pos, val);
        recalc(v);
    }

    void update(int pos, int val) {
        update(0, 0, n, pos, val);
    }

    li get_sum(int v, int l, int r, int L, int R) {
        if (R <= l || L >= r || L >= R) return 0;
        if (L <= l && r <= R) return T[v];
        int m = (l + r) / 2;
        li x = get_sum(2 * v + 1, l, m, L, R);
        li y = get_sum(2 * v + 2, m, r, L, R);
        return x + y;
    }

    li get_sum(int L, int R) {
        return get_sum(0, 0, n, L, R + 1);
    }
};
