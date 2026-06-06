int find_first_true(int l, int r) {
    int res = r + 1, m;
    while (l <= r) {
        m = (l + r) / 2;
        if (check(m))
            r = m - 1, res = m;
        else
            l = m + 1;
    }
    return res;
}