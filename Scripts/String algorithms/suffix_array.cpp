// Суффиксный массив за O(n log n) и LCP (Касаи) за O(n).
// sa[i]: начало i-го суффикса (без служебного '\0').
// lcp[i]: LCP(s[sa[i]..], s[sa[i + 1]..]), размер n - 1.
pair<vi, vi> suffix_array(string s) {
    s.push_back('\0');
    int n = sz(s), alpha = 256;
    vi p(n), c(n), cnt(max(alpha, n));
    for (int i = 0; i < n; ++i)
        ++cnt[(unsigned char)s[i]];
    for (int i = 1; i < alpha; ++i)
        cnt[i] += cnt[i - 1];
    for (int i = n - 1; i >= 0; --i)
        p[--cnt[(unsigned char)s[i]]] = i;
    int cls = 1;
    c[p[0]] = 0;
    for (int i = 1; i < n; ++i) {
        if (s[p[i]] != s[p[i - 1]]) ++cls;
        c[p[i]] = cls - 1;
    }
    vi pn(n), cn(n);
    for (int h = 1; h < n && cls < n; h <<= 1) {
        for (int i = 0; i < n; ++i) {
            pn[i] = p[i] - h;
            if (pn[i] < 0) pn[i] += n;
        }
        fill(cnt.begin(), cnt.begin() + cls, 0);
        for (int i = 0; i < n; ++i)
            ++cnt[c[pn[i]]];
        for (int i = 1; i < cls; ++i)
            cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; --i)
            p[--cnt[c[pn[i]]]] = pn[i];
        cls = 1;
        cn[p[0]] = 0;
        for (int i = 1; i < n; ++i) {
            int cur1 = c[p[i]], cur2 = c[(p[i] + h) % n];
            int prv1 = c[p[i - 1]],
                prv2 = c[(p[i - 1] + h) % n];
            if (cur1 != prv1 || cur2 != prv2) ++cls;
            cn[p[i]] = cls - 1;
        }
        c.swap(cn);
    }
    p.erase(p.begin());
    int m = sz(p);
    vi rnk(m), lcp(max<int>(0, m - 1));
    for (int i = 0; i < m; ++i)
        rnk[p[i]] = i;
    for (int i = 0, k = 0; i < m; ++i) {
        if (rnk[i] == m - 1) {
            k = 0;
            continue;
        }
        int j = p[rnk[i] + 1];
        while (i + k < m && j + k < m && s[i + k] == s[j + k])
            ++k;
        lcp[rnk[i]] = k;
        if (k) --k;
    }
    return {p, lcp};
}
