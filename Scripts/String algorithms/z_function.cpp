vi z_func(const string& s) {
    vi z(sz(s));
    int l = 0, r = 0;
    for (int i = 1; i < sz(s); ++i) {
        if (i < r)
            z[i] = min(z[i - l], r - i);
        while (i + z[i] < sz(s) && s[i + z[i]] == s[z[i]])
            ++z[i];
        if (i + z[i] > r)
            l = i, r = i + z[i];
    }
    return z;
}