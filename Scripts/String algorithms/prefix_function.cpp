vi p_func(const string& s) {
    vi p(sz(s));
    for (int i = 1; i < sz(s); ++i) {
        int j = p[i - 1];
        while (j > 0 && s[i] != s[j])
            j = p[j - 1];
        if (s[i] == s[j])
            ++j;
        p[i] = j;
    }
    return p;
}