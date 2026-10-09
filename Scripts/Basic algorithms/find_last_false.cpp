li find_last_false(li l, li r) {
    li res = l - 1, m;
    while (l <= r) {
        m = l + (r - l) / 2;
        if (!check(m)) l = m + 1, res = m;
        else r = m - 1;
    }
    return res;
}
