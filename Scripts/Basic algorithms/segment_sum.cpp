vli pr(n + 1);
pr[0] = 0;
for (int i = 0; i < n; ++i)
    pr[i + 1] = pr[i] + a[i];
auto sum = [&pr, n](int l, int r) {
    if (l > n - 1 || r < 0 || l > r) return 0ll;
    return pr[min(r + 1, n)] - pr[max(l, 0ll)];
    };