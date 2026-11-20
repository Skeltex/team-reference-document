struct DSU {
    vi p, s;
    DSU(int n = 0) : p(n), s(n, 1) {
        iota(all(p), 0);
    }
    int get(int x) {
        return p[x] == x ? x : p[x] = get(p[x]);
    }
    bool merge(int x, int y) {
        x = get(x), y = get(y);
        if (x == y) return false;
        if (s[x] > s[y]) swap(x, y);
        s[y] += s[x];
        p[x] = y;
        return true;
    }
};
