vi pal(int n, const string& s) {
    vi p(n);
    int l = 1, r = 1;
    for (int i = 1; i < n; ++i) {
        if (i < r) p[i] = min(r - i, p[l + r - i]);
        while (s[i + p[i]] == s[i - p[i]])
            ++p[i];
        if (i + p[i] > r) {
            r = i + p[i];
            l = i - p[i];
        }
    }
    return p;
}