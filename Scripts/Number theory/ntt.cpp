// MOD = 998'244'353 = 119 * 2^23 + 1, G = 3.
// Размер a: степень двойки <= 2^23. O(n log n).
const li NTT_G = 3;
void ntt(vli& a, bool inv_fft = false) {
    int n = sz(a);
    for (int i = 1, j = 0; i < n; ++i) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        li wlen = binpow(NTT_G, (MOD - 1) / len);
        if (inv_fft) wlen = inv(wlen);
        int half = len >> 1;
        for (int i = 0; i < n; i += len) {
            li w = 1;
            for (int j = 0; j < half; ++j) {
                li u = a[i + j];
                li v = a[i + j + half] * w % MOD;
                a[i + j] = u + v < MOD ? u + v : u + v - MOD;
                a[i + j + half] =
                    u - v >= 0 ? u - v : u - v + MOD;
                w = w * wlen % MOD;
            }
        }
    }
    if (inv_fft) {
        li n_inv = inv(n);
        for (li& x : a)
            x = x * n_inv % MOD;
    }
}
vli mul_ntt(vli a, vli b) {
    if (a.empty() || b.empty()) return {};
    int N = sz(a) + sz(b) - 1, n = 1;
    while (n < N)
        n <<= 1;
    a.resize(n);
    b.resize(n);
    for (li& x : a)
        x = add(x, 0);
    for (li& x : b)
        x = add(x, 0);
    ntt(a);
    ntt(b);
    for (int i = 0; i < n; ++i)
        a[i] = a[i] * b[i] % MOD;
    ntt(a, true);
    a.resize(N);
    return a;
}
