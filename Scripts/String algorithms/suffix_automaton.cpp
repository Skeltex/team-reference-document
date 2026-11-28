// Фиксированный байтовый алфавит. Построение и память O(n).
// map хранит только имеющиеся переходы, поиск по ней O(log A), A <= 256.
// Запросы по внешнему шаблону O(m), выдача k вхождений O(m + k).
struct SuffixAutomaton {
    struct Node {
        int len = 0, link = -1;
        bool prefix = true;
        map<char, int> next;
    };
    vector<Node> st{1};
    int last = 0;
private:
    struct Hits {
        int begin, count, first, last; // начало в ends, число, крайние концы
    };
    mutable vector<Hits> info;
    mutable vi ends;

    int step(int v, char c) const {
        auto it = st[v].next.find(c);
        return it == st[v].next.end() ? -1 : it->second;
    }
    pair<int, int> match_prefix(const string& p) const {
        int v = 0, len = 0;
        for (char c : p) {
            int u = step(v, c);
            if (u == -1) break;
            v = u;
            ++len;
        }
        return {v, len};
    }
    Hits hits(const string& p) const {
        prepare();
        int v = find(p);
        return v == -1 ? Hits{0, 0, -1, -1} : info[v];
    }
public:
    explicit SuffixAutomaton(const string& s = {}) {
        st.reserve(2 * sz(s) + 1);
        for (char c : s) extend(c);
        prepare();
    }
    void extend(char c) {
        int p = last, cur = sz(st);
        st.emplace_back();
        st[cur].len = st[last].len + 1;
        while (p != -1 && st[p].next.emplace(c, cur).second)
            p = st[p].link;
        if (p == -1) st[cur].link = 0;
        else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) st[cur].link = q;
            else {
                int clone = sz(st);
                st.push_back(st[q]);
                st[clone].len = st[p].len + 1;
                st[clone].prefix = false;
                while (p != -1 && step(p, c) == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }
    // После серии extend первый запрос вхождений вызовет prepare за O(n).
    void prepare() const {
        int size = sz(st);
        if (sz(info) == size) return;
        info.assign(size, {0, 0, st[last].len, -1});
        vi child(size, -1), sibling(size);
        for (int v = 1; v < size; ++v) {
            int p = st[v].link;
            sibling[v] = child[p];
            child[p] = v;
        }
        vi order, todo{0};
        order.reserve(size);
        ends.clear();
        ends.reserve(st[last].len + 1);
        while (!todo.empty()) {
            int v = todo.back();
            todo.pop_back();
            order.push_back(v);
            info[v].begin = sz(ends);
            if (st[v].prefix) { // корень отмечает конец пустого префикса
                int e = st[v].len - 1;
                ends.push_back(e);
                info[v].count = 1;
                info[v].first = info[v].last = e;
            }
            for (int u = child[v]; u != -1; u = sibling[u]) todo.push_back(u);
        }
        // Концы вхождений состояния занимают всё его поддерево в порядке DFS.
        for (int i = size - 1; i > 0; --i) {
            int v = order[i];
            auto& p = info[st[v].link];
            p.count += info[v].count;
            p.first = min(p.first, info[v].first);
            p.last = max(p.last, info[v].last);
        }
    }
    int longest_prefix(const string& p) const { return match_prefix(p).second; }
    int find(const string& p) const {
        auto [v, len] = match_prefix(p);
        return len == sz(p) ? v : -1;
    }
    int count_occurrences(const string& p) const { return hits(p).count; }
    vli count_occurrences() const { // по всем состояниям за O(n)
        prepare();
        vli cnt;
        for (const auto& h : info) cnt.push_back(h.count);
        return cnt;
    }
    int first_occurrence(const string& p) const {
        auto h = hits(p);
        return h.count ? h.first - sz(p) + 1 : -1;
    }
    int last_occurrence(const string& p) const {
        auto h = hits(p);
        return h.count ? h.last - sz(p) + 1 : -1;
    }
    vi occurrences(const string& p) const { // индексы в порядке DFS
        auto h = hits(p);
        vi ans(h.count);
        for (int i = 0; i < h.count; ++i)
            ans[i] = ends[h.begin + i] - sz(p) + 1;
        return ans;
    }
    // (Начало в шаблоне, длина), при отсутствии (-1, 0).
    pair<int, int> longest_common_substring(const string& p) const {
        pair<int, int> ans{-1, 0};
        int v = 0, len = 0;
        for (int i = 0; i < sz(p); ++i) {
            int u = step(v, p[i]);
            while (v && u == -1) {
                v = st[v].link;
                len = st[v].len;
                u = step(v, p[i]);
            }
            if (u == -1) len = 0;
            else { v = u; ++len; }
            if (len > ans.second) ans = {i - len + 1, len};
        }
        return ans;
    }
    // Частота общая для всех длин от len(link) + 1 до len состояния.
    // Оба поиска за O(n), ответ (начало в тексте, длина) или (-1, 0).
    pair<int, int> longest_at_least(int k) const {
        prepare();
        pair<int, int> ans{-1, 0};
        for (int v = 1; v < sz(st); ++v) {
            int len = st[v].len;
            if (info[v].count >= k && len > ans.second)
                ans = {info[v].first - len + 1, len};
        }
        return ans;
    }
    pair<int, int> shortest_at_most(int k) const {
        prepare();
        pair<int, int> ans{-1, 0};
        for (int v = 1; v < sz(st); ++v) {
            int len = st[st[v].link].len + 1;
            if (info[v].count <= k && (!ans.second || len < ans.second))
                ans = {info[v].first - len + 1, len};
        }
        return ans;
    }
    li distinct_substrings() const {
        li ans = 0;
        for (int v = 1; v < sz(st); ++v)
            ans += st[v].len - st[st[v].link].len;
        return ans;
    }
};
