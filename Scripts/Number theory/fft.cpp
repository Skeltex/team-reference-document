typedef complex<ld> cd;

// Размер a: ненулевая степень двойки.
// inv = true: обратное преобразование.
void fft(vector<cd>& a, bool inv = false) {
    int n = sz(a);
    // Корни кэшируются и растут по необходимости.
    static vector<cd> w = {1, 1};
    for (int len = sz(w); len < n; len <<= 1) {
        w.resize(len << 1);
        ld ang = PI / len;
        cd step(cosl(ang), sinl(ang));
        for (int i = len; i < (len << 1); ++i)
            w[i] = (i & 1) ? w[i >> 1] * step
                           : w[i >> 1];
    }

    for (int i = 1, j = 0; i < n; ++i) {
        int bit = n >> 1;
        while (j & bit) {
            j ^= bit;
            bit >>= 1;
        }
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }

    for (int len = 1; len < n; len <<= 1) {
        for (int pos = 0; pos < n; pos += len << 1) {
            for (int i = 0; i < len; ++i) {
                cd x = a[pos + i];
                cd y = a[pos + i + len] * w[len + i];
                a[pos + i] = x + y;
                a[pos + i + len] = x - y;
            }
        }
    }
    if (inv) {
        reverse(a.begin() + 1, a.end());
        for (auto& x : a)
            x /= n;
    }
}

// a[i], b[i]: коэффициенты при x^i.
// O(N log N), где N = sz(a) + sz(b) - 1.
// Большие коэффициенты могут дать ошибку
// округления даже при результате в пределах li.
vli mul(const vi& a, const vi& b) {
    if (a.empty() || b.empty()) return {};
    int N = sz(a) + sz(b) - 1;
    int n = 1;
    while (n < N)
        n <<= 1;
    vector<cd> aa(n), bb(n);
    for (int i = 0; i < sz(a); ++i)
        aa[i] = (ld)a[i];
    for (int i = 0; i < sz(b); ++i)
        bb[i] = (ld)b[i];
    fft(aa);
    fft(bb);
    for (int i = 0; i < n; ++i)
        aa[i] *= bb[i];
    fft(aa, true);
    vli res(N);
    for (int i = 0; i < N; ++i)
        res[i] = llroundl(aa[i].real());
    return res;
}
