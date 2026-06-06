struct func {
    int k;
    int b;
    int eval(int x) {
        return k * x + b;
    }
    func(int k = 0, int b = 0) : k(k), b(b) {};
};

struct LiChaoTreeMin {
    vector<func> t;
    int n;

    LiChaoTreeMin(int n = 0) {
        this->n = n;
        t.resize(4 * n, func(0, INF64));
        // -INF64 для дерева на max
    }

    int get(int v, int l, int r, int pos) {
        int ans = t[v].eval(pos);
        if (l < r - 1) {
            int m = (l + r) / 2;
            if (pos < m)
                ans = min(ans, get(v * 2 + 1, l, m, pos));
            else
                ans = min(ans, get(v * 2 + 2, m, r, pos));
        }
        return ans;
    }

    void add(int v, int l, int r, func& f) {
        if (l == r - 1)
            return;
        int m = (l + r) / 2;
        if (t[v].eval(m) > f.eval(m)) // < для дерева на max
            swap(f, t[v]);
        if (f.eval(l) < t[v].eval(l)) // > для дерева на max
            add(v * 2 + 1, l, m, f);
        else
            add(v * 2 + 2, m, r, f);
    }

    int getMin(int x) {
        return get(0, 0, n, x);
    }

    void add(func f) {
        func f2 = f;
        add(0, 0, n, f2);
    }
};

void solve() {
    LiChaoTreeMin t(10);
    t.add(func(3, 2));
    t.add(func(5, 0));
    t.add(func(6, -5));
    cout << t.getMin(5) << '\n';
    cout << t.getMin(0) << '\n';
    cout << t.getMin(7) << '\n';
    // 17 -5 23
}