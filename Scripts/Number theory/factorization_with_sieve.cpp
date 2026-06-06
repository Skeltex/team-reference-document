vc prime(n + 1, true);
vi prdiv(n + 1);
iota(all(prdiv), 0);
prime[0] = prime[1] = false;
for (li i = 2; i * i <= n; ++i) {
    if (prime[i]) {
        for (li j = i * i; j <= n; j += i) {
            prime[j] = false;
            prdiv[j] = min(prdiv[j], i);
        }
    }
}

auto fact = [&](int x) {
    vector<pii> f;
    while (x > 1) {
        int p = prdiv[x];
        int cnt = 0;
        while (x % p == 0) {
            ++cnt;
            x /= p;
        }
        f.push_back({ p, cnt });
    }
    return f;
    };