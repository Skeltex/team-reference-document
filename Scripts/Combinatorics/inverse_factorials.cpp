const int N = 300'013;
int fact[N], rfact[N];

int cnk(int n, int k) {
    if (k < 0 || n < k || n < 0)
        return 0ll;
    return mul(fact[n], mul(rfact[k], rfact[n - k]));
}

void calc() {
    fact[0] = 1;
    for (int i = 1; i < N; ++i)
        fact[i] = mul(fact[i - 1], i);

    rfact[N - 1] = binpow(fact[N - 1], MOD - 2);
    for (int i = N - 2; i >= 0; --i)
        rfact[i] = mul(rfact[i + 1], i + 1);
}