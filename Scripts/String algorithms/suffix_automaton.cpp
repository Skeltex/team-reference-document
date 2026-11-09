// A: размер алфавита, n: длина строки.
// Построение O(n log A), память O(n).
struct SuffixAutomaton {
    struct Node {
        // cnt: исходная метка конца префикса.
        int len = 0, link = -1, cnt = 0;
        map<char, int> next;
    };
    vector<Node> st;
    int last = 0;

    // Амортизированно O(log A) на символ.
    void extend(char c) {
        int cur = sz(st);
        st.emplace_back();
        st[cur].len = st[last].len + 1;
        st[cur].cnt = 1;
        int p = last;
        while (p != -1 && !st[p].next.count(c)) {
            st[p].next[c] = cur;
            p = st[p].link;
        }
        if (p == -1) {
            st[cur].link = 0;
        } else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } else {
                int clone = sz(st);
                st.push_back(st[q]);
                st[clone].len = st[p].len + 1;
                st[clone].cnt = 0;
                while (p != -1
                       && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }

    // Состояние подстроки s или -1. O(|s| log A).
    int find(const string& s) const {
        int v = 0;
        for (char c : s) {
            auto it = st[v].next.find(c);
            if (it == st[v].next.end()) return -1;
            v = it->second;
        }
        return v;
    }

    // Число различных непустых подстрок. O(n).
    li distinct_substrings() const {
        li ans = 0;
        for (int v = 1; v < sz(st); ++v)
            ans += st[v].len - st[st[v].link].len;
        return ans;
    }

    // Число вхождений для каждого состояния.
    // O(n). После extend пересчитать заново.
    // Для непустого s: v = find(s), ответ cnt[v]
    // при v != -1, иначе 0. С учётом пересечений.
    vli count_occurrences() const {
        int n = st[last].len;
        vi freq(n + 1), order(sz(st));
        vli cnt(sz(st));
        for (const auto& v : st)
            ++freq[v.len];
        for (int i = 1; i <= n; ++i)
            freq[i] += freq[i - 1];
        for (int v = 0; v < sz(st); ++v) {
            order[--freq[st[v].len]] = v;
            cnt[v] = st[v].cnt;
        }
        for (int i = sz(st) - 1; i > 0; --i) {
            int v = order[i];
            cnt[st[v].link] += cnt[v];
        }
        // Пустая строка встречается n + 1 раз.
        ++cnt[0];
        return cnt;
    }

    SuffixAutomaton(const string& s = "") : st(1) {
        st.reserve(2 * sz(s) + 1);
        for (char c : s)
            extend(c);
    }
};
