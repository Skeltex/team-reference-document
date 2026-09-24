struct LazyAddMinSegmentTree {
    vector<li> T, lazy;
    int n;

    li get_val(int v) {
        return T[v] + lazy[v];
    }

    void push(int v) {
        if (lazy[v]) {
            T[v] += lazy[v];
            lazy[2 * v + 1] += lazy[v];
            lazy[2 * v + 2] += lazy[v];
            lazy[v] = 0;
        }
    }

    void recalc(int v) {
        T[v] = min(get_val(2 * v + 1), get_val(2 * v + 2));
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
        lazy.assign(4 * n, 0LL);
        T.assign(4 * n, 0LL);
        build(0, 0, n, a);
    }

    void add(int v, int l, int r, int L, int R, li val) {
        if (L >= R) return;
        if (L <= l && r <= R) {
            lazy[v] += val;
            return;
        }
        push(v);
        int m = (l + r) / 2;
        add(2 * v + 1, l, m, L, min(m, R), val);
        add(2 * v + 2, m, r, max(L, m), R, val);
        recalc(v);
    }

    void add(int L, int R, li val) {
        add(0, 0, n, L, R + 1, val);
    }

    li get_min(int v, int l, int r, int L, int R) {
        if (L <= l && r <= R) return get_val(v);
        if (R <= l || L >= r || L >= R) return INF;
        push(v);
        int m = (l + r) / 2;
        li x = get_min(2 * v + 1, l, m, L, R);
        li y = get_min(2 * v + 2, m, r, L, R);
        return min(x, y);
    }

    li get_min(int L, int R) {
        return get_min(0, 0, n, L, R + 1);
    }
};
