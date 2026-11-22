// Статический массив, отрезки [L, R] включительно.
// get_kth даёт значение по рангу 0 <= k <= R - L.
// count_le считает элементы <= x.
// m — число различных значений. Построение O(n log n),
// запросы O(log m), память O(n log m).
struct PersSegmentTree {
private:
    struct Node {
        int lc = 0, rc = 0, cnt = 0;
    };
    vi vals;
    vi roots; // roots[i] хранит частоты на [0, i).
    vector<Node> buf;

    int insert(int v, int l, int r, int pos) {
        Node cur = buf[v];
        ++cur.cnt;
        if (r - l > 1) {
            int m = l + (r - l) / 2;
            if (pos < m) cur.lc = insert(cur.lc, l, m, pos);
            else cur.rc = insert(cur.rc, m, r, pos);
        }
        buf.push_back(cur);
        return sz(buf) - 1;
    }
    int count_pref(int u, int v, int l, int r, int p) const {
        if (u == v || p <= l) return 0;
        if (r <= p) return buf[v].cnt - buf[u].cnt;
        int m = l + (r - l) / 2;
        return count_pref(buf[u].lc, buf[v].lc, l, m, p)
             + count_pref(buf[u].rc, buf[v].rc, m, r, p);
    }
    int get_kth(int u, int v, int l, int r, int k) const {
        if (r - l == 1) return vals[l];
        int lu = buf[u].lc, lv = buf[v].lc;
        int cnt = buf[lv].cnt - buf[lu].cnt;
        int m = l + (r - l) / 2;
        if (k < cnt) return get_kth(lu, lv, l, m, k);
        return get_kth(buf[u].rc, buf[v].rc, m, r, k - cnt);
    }

public:
    explicit PersSegmentTree(const vi& a = {}) { build(a); }

    void build(const vi& a) {
        vals = a;
        sort(all(vals));
        vals.erase(unique(all(vals)), vals.end());
        int m = sz(vals), h = 1;
        for (int x = m - 1; x > 0; x >>= 1) ++h;
        buf.clear();
        buf.reserve(1 + a.size() * h);
        buf.emplace_back(); // узел 0 пуст во всех версиях
        roots.assign(a.size() + 1, 0);
        for (int i = 0; i < sz(a); ++i) {
            int pos = lower_bound(all(vals), a[i]) - vals.begin();
            roots[i + 1] = insert(roots[i], 0, m, pos);
        }
    }
    int count_le(int L, int R, int x) const {
        if (L > R) return 0;
        int p = upper_bound(all(vals), x) - vals.begin();
        return count_pref(roots[L], roots[R + 1], 0, sz(vals), p);
    }
    int get_kth(int L, int R, int k) const {
        return get_kth(roots[L], roots[R + 1], 0, sz(vals), k);
    }
};
