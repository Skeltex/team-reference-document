// s[l..r] включительно, пустая подстрока задаётся [l, l-1].
// SA-IS, Касаи и блочный RMQ: O(n) времени и памяти.
// SuffixArray(s, true) строит полную SparseTable за O(n log n).
// В обоих режимах нужна SparseTable из раздела структур данных.
struct SuffixArray {
    vi sa, rank, adj; // adj[i] = LCP суффиксов sa[i], sa[i+1]
private:
    int n, width = 1;
    SparseTable blocks{1};
    vector<unsigned long long> mask;
    using Bounds = pair<int, int>;
    vector<Bounds> pos;

    // a заканчивается единственным нулём, символы в [0, alphabet).
    static vi sais(const vi& a, int alphabet) {
        int n = sz(a);
        if (n == 1) return {0};
        vc is_s(n);
        is_s.back() = 1;
        for (int i = n - 2; i >= 0; --i)
            is_s[i] = a[i] == a[i + 1] ? is_s[i + 1] : a[i] < a[i + 1];
        vi lms, id(n, -1), bucket(alphabet + 1), order(n);
        // LMS — позиция S-типа сразу после L-типа.
        for (int i = 1; i < n; ++i)
            if (is_s[i] && !is_s[i - 1]) {
                id[i] = sz(lms);
                lms.push_back(i);
            }
        for (int c : a) ++bucket[c + 1];
        partial_sum(all(bucket), bucket.begin());
        // По порядку LMS расставить L слева направо, затем S справа налево.
        auto induce = [&](const vi& starts) {
            fill(all(order), -1);
            vi ptr = bucket;
            for (auto it = starts.rbegin(); it != starts.rend(); ++it)
                order[--ptr[a[*it] + 1]] = *it;
            ptr = bucket;
            for (int i = 0; i < n; ++i) {
                int p = order[i] - 1;
                if (p >= 0 && !is_s[p]) order[ptr[a[p]]++] = p;
            }
            ptr = bucket;
            for (int i = n - 1; i >= 0; --i) {
                int p = order[i] - 1;
                if (p >= 0 && is_s[p]) order[--ptr[a[p] + 1]] = p;
            }
        };
        induce(lms);
        int m = sz(lms), classes = 0, prev = -1;
        vi names(m), sorted(m);
        // Блок включает символ в следующей LMS-позиции.
        auto end = [&](int p) {
            return id[p] + 1 < m ? lms[id[p] + 1] + 1 : n;
        };
        for (int p : order) if (id[p] >= 0) {
            int len = end(p) - p, j = 0;
            if (prev >= 0 && end(prev) - prev == len)
                while (j < len && a[p + j] == a[prev + j]
                       && is_s[p + j] == is_s[prev + j]) ++j;
            if (j < len) ++classes;
            names[id[p]] = classes - 1;
            prev = p;
        }
        if (classes == m) {
            for (int i = 0; i < m; ++i) sorted[names[i]] = i;
        } else sorted = sais(names, classes);
        for (int& i : sorted) i = lms[i];
        induce(sorted);
        return order;
    }
    void index_lcp(bool full) {
        if (adj.empty()) return;
        if (full) {
            blocks.build(adj);
            return;
        }
        width = __lg(sz(adj)) + 1; // таблица по минимумам блоков занимает O(n)
        vi minima;
        mask.resize(sz(adj));
        unsigned long long bits = 0;
        for (int i = 0; i < sz(adj); ++i) {
            if (i % width == 0) {
                minima.push_back(adj[i]);
                bits = 0;
            }
            minima.back() = min(minima.back(), adj[i]);
            // Бит d хранит кандидата на минимум в позиции i-d.
            bits <<= 1;
            while (bits && adj[i - __builtin_ctzll(bits)] >= adj[i])
                bits &= bits - 1;
            bits |= 1;
            mask[i] = bits;
        }
        blocks.build(minima);
    }
    int range_min(int l, int r) const {
        if (width == 1) return blocks.query(l, r);
        auto part = [&](int a, int b) {
            auto bits = mask[b] & ((1ULL << (b - a + 1)) - 1);
            return adj[b - __lg(bits)];
        };
        int x = l / width, y = r / width;
        if (x == y) return part(l, r);
        int ans = min(part(l, (x + 1) * width - 1), part(y * width, r));
        if (x + 1 < y) ans = min(ans, blocks.query(x + 1, y - 1));
        return ans;
    }
    int common(int a, int b) const { // ранги суффиксов, a <= b
        return a == b ? n - sa[a] : range_min(a, b - 1);
    }
    // Все суффиксы с непустым префиксом s[l..r] занимают [lo, hi].
    Bounds interval(int l, int r) const {
        int p = rank[l], len = r - l + 1, lo = 0, hi = p;
        while (lo < hi) {
            int m = lo + (hi - lo) / 2;
            if (common(m, p) >= len) hi = m;
            else lo = m + 1;
        }
        int left = lo;
        lo = p; hi = n - 1;
        while (lo < hi) {
            int m = lo + (hi - lo + 1) / 2;
            if (common(p, m) >= len) lo = m;
            else hi = m - 1;
        }
        return {left, lo};
    }
    static Bounds combine(Bounds a, Bounds b) {
        return {min(a.first, b.first), max(a.second, b.second)};
    }
    Bounds extremes(int l, int r) const {
        if (l > r) return {0, n};
        auto [a, b] = interval(l, r);
        Bounds ans{n, -1};
        for (a += n, b += n + 1; a < b; a /= 2, b /= 2) {
            if (a & 1) ans = combine(ans, pos[a++]);
            if (b & 1) ans = combine(ans, pos[--b]);
        }
        return ans;
    }
public:
    explicit SuffixArray(const string& s, bool full_sparse = false) : n(sz(s)) {
        vi a(n + 1);
        for (int i = 0; i < n; ++i) a[i] = (unsigned char)s[i] + 1;
        sa = sais(a, 257);
        sa.erase(sa.begin()); // убрать пустой суффикс
        rank.resize(n);
        if (n) adj.resize(n - 1);
        for (int i = 0; i < n; ++i) rank[sa[i]] = i;
        for (int i = 0, h = 0; i < n; ++i) {
            int p = rank[i];
            if (p == n - 1) { h = 0; continue; }
            int j = sa[p + 1];
            while (i + h < n && j + h < n && s[i + h] == s[j + h]) ++h;
            adj[p] = h;
            if (h) --h;
        }
        index_lcp(full_sparse);
        pos.resize(2 * n);
        for (int i = 0; i < n; ++i) pos[n + i] = {sa[i], sa[i]};
        for (int i = n - 1; i > 0; --i)
            pos[i] = combine(pos[2 * i], pos[2 * i + 1]);
    }
    int count_occurrences(int l, int r) const { // O(log n)
        if (l > r) return n + 1;
        auto [a, b] = interval(l, r);
        return b - a + 1;
    }
    int first_occurrence(int l, int r) const { return extremes(l, r).first; }
    int last_occurrence(int l, int r) const { return extremes(l, r).second; }
    vi occurrences(int l, int r) const { // O(log n + k), порядок SA
        if (l > r) {
            vi ans{n};
            ans.insert(ans.end(), all(sa));
            return ans;
        }
        auto [a, b] = interval(l, r);
        return vi(sa.begin() + a, sa.begin() + b + 1);
    }
    int lcp(int l, int r, int p, int q) const { // O(1)
        int len = min(r - l + 1, q - p + 1);
        if (!len) return 0;
        return min(len, common(min(rank[l], rank[p]), max(rank[l], rank[p])));
    }
    int compare(int l, int r, int p, int q) const { // -1, 0, 1 за O(1)
        int a = r - l + 1, b = q - p + 1;
        if (lcp(l, r, p, q) == min(a, b)) return (a > b) - (a < b);
        return rank[l] < rank[p] ? -1 : 1;
    }
    // Далее O(n). Ответ (начало, длина), при отсутствии (-1, 0).
    pair<int, int> longest_at_least(int k) const {
        pair<int, int> ans{-1, 0};
        if (!n || k > n) return ans;
        if (k <= 1) return {0, n};
        for (int i = 0; i <= n - k; ++i) {
            int len = common(i, i + k - 1);
            if (len > ans.second) ans = {sa[i], len};
        }
        return ans;
    }
    pair<int, int> shortest_at_most(int k) const {
        pair<int, int> ans{-1, 0};
        if (k < 1) return ans;
        for (int i = 0; i < n; ++i) {
            // Для первого ранга i исключаем суффиксы i-1 и i+k.
            int h = i ? adj[i - 1] : 0;
            if (i < n - k) h = max(h, common(i, i + k));
            if (h < n - sa[i] && (!ans.second || h + 1 < ans.second))
                ans = {sa[i], h + 1};
        }
        return ans;
    }
    li distinct_substrings() const {
        return (li)n * (n + 1LL) / 2 - accumulate(all(adj), 0LL);
    }
};
