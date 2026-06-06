int binary_search(const vi& a, int val) {
    int l = 0, r = sz(a) - 1, m;
    while (l <= r) {
        m = (l + r) / 2;
        if (a[m] == val)
            return m;
        else if (a[m] > val)
            r = m - 1;
        else
            l = m + 1;
    }
    return -1;
}