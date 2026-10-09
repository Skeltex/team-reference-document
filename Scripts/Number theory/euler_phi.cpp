li euler(li n) {
    li res = n;
    for (li p = 2; p * p <= n; ++p) {
        if (n % p == 0) {
            while (n % p == 0)
                n /= p;
            res -= res / p;
        }
    }
    if (n > 1) res -= res / n;
    return res;
}
