li find_first_true(li l, li r) {
    li res = r + 1, m;
    while (l <= r) {
        m = l + (r - l) / 2;
        if (check(m)) r = m - 1, res = m;
        else l = m + 1;
    }
    return res;
}
