// Индексы с 0, отрезки [l, r] включительно.
// argmin и argmax при равенстве возвращают левый индекс.
// ge означает >= x, le означает <= x. Если ответа нет, вернётся -1.
// Построение и память O(n), запросы и изменения O(log n).
struct MinMaxSegmentTree {
    struct Node {
        int mn = -1, mx = -1; // индексы минимума и максимума
    };
    int base = 1;
    vi a;
    vector<Node> t;

    Node merge(Node left, Node right) const {
        if (left.mn == -1) return right;
        if (right.mn == -1) return left;
        return {a[left.mn] <= a[right.mn] ? left.mn : right.mn,
                a[left.mx] >= a[right.mx] ? left.mx : right.mx};
    }
    void pull(int v) {
        t[v] = merge(t[2 * v], t[2 * v + 1]);
    }
    void build(const vi& values) {
        int n = sz(values);
        base = 1;
        while (base < n) base *= 2;
        t.assign(2 * base, {});
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            a[i] = values[i];
            t[base + i] = {i, i};
        }
        for (int v = base - 1; v > 0; --v) pull(v);
    }
    MinMaxSegmentTree() = default;
    explicit MinMaxSegmentTree(const vi& values) {
        build(values);
    }
    void set(int pos, int x) {
        a[pos] = x;
        for (int v = (base + pos) / 2; v > 0; v /= 2)
            pull(v);
    }
    void add(int pos, int x) {
        set(pos, a[pos] + x);
    }

    Node query(int l, int r) const {
        Node left, right;
        for (l += base, r += base + 1; l < r; l /= 2, r /= 2) {
            if (l & 1) left = merge(left, t[l++]);
            if (r & 1) right = merge(t[--r], right);
        }
        return merge(left, right);
    }
    int argmin(int l, int r) const {
        return query(l, r).mn;
    }
    int argmax(int l, int r) const {
        return query(l, r).mx;
    }

    int find(int v, int lo, int hi, int l, int r,
             int x, bool ge, bool last) const {
        if (hi < l || r < lo) return -1;
        auto [mn, mx] = t[v];
        if (mn == -1 || (ge ? a[mx] < x : a[mn] > x))
            return -1;
        if (lo == hi) return lo;
        int mid = (lo + hi) / 2;
        auto visit = [&](bool right) {
            if (right)
                return find(2 * v + 1, mid + 1, hi, l, r, x, ge, last);
            return find(2 * v, lo, mid, l, r, x, ge, last);
        };
        int pos = visit(last);
        return pos == -1 ? visit(!last) : pos;
    }
    int first_ge(int l, int r, int x) const {
        return find(1, 0, base - 1, l, r, x, true, false);
    }
    int first_le(int l, int r, int x) const {
        return find(1, 0, base - 1, l, r, x, false, false);
    }
    int last_ge(int l, int r, int x) const {
        return find(1, 0, base - 1, l, r, x, true, true);
    }
    int last_le(int l, int r, int x) const {
        return find(1, 0, base - 1, l, r, x, false, true);
    }
};
