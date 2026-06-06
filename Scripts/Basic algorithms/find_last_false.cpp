int find_last_false(int l, int r) {
    int res = l - 1, m;
    while (l <= r) {
        m = (l + r) / 2;
        if (!check(m))
            l = m + 1, res = m;
        else
            r = m - 1;
    }
    return res;
}