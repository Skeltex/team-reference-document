// Индексы с 0, отрезки [l, r] включительно.
// get_sorted возвращает весь отрезок по возрастанию.
// first_k выдаёт первые min(k, r - l + 1) значений
// в том же порядке, включая повторы.
// update(pos, x) присваивает a[pos] = x.
// Построение и память O(n log n), update O(log^2 n).
// Выдача s элементов O(log n + s log log n).
struct MergeSortTree {
private:
    struct Cursor {
        multiset<int>::const_iterator it, end;
        bool operator<(const Cursor& other) const {
            return *it > *other.it;
        }
    };
    int n = 0;
    vector<multiset<int>> t;

public:
    explicit MergeSortTree(const vi& a = {}) {
        build(a);
    }
    void build(const vi& a) {
        n = sz(a);
        t.assign(2 * n, {});
        for (int i = 0; i < n; ++i)
            t[n + i].insert(a[i]);
        vi buf;
        for (int v = n - 1; v > 0; --v) {
            const auto& left = t[2 * v];
            const auto& right = t[2 * v + 1];
            buf.resize(left.size() + right.size());
            merge(all(left), all(right), buf.begin());
            t[v] = multiset<int>(all(buf));
        }
    }
    int get(int pos) const {
        return *t[n + pos].begin();
    }
    void update(int pos, int val) {
        int old = get(pos);
        if (old == val) return;
        for (int v = n + pos; v > 0; v /= 2) {
            auto node = t[v].extract(old);
            node.value() = val;
            t[v].insert(move(node));
        }
    }

    vi first_k(int l, int r, int k) const {
        k = min(k, r - l + 1);
        if (k <= 0) return {};
        vector<Cursor> heap;
        auto take = [&](int v) {
            heap.push_back({t[v].begin(), t[v].end()});
        };
        for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
            if (l & 1) take(l++);
            if (r & 1) take(--r);
        }
        make_heap(all(heap));
        vi ans;
        ans.reserve(k);
        while (sz(ans) < k) {
            pop_heap(all(heap));
            auto& cur = heap.back();
            ans.push_back(*cur.it);
            if (++cur.it == cur.end) heap.pop_back();
            else push_heap(all(heap));
        }
        return ans;
    }
    vi get_sorted(int l, int r) const {
        return first_k(l, r, r - l + 1);
    }
};
