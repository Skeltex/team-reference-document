vli pr(n);
pr[0] = a[0];
for (int i = 1; i < n; ++i)
    pr[i] = a[i] - a[i - 1];

auto add = [&pr, n](int l, int r, int x) {
    if (l > n - 1 || r < 0 || l > r) return;
    pr[max(l, 0ll)] += x;
    if (r < n - 1) pr[r + 1] -= x;
    };

add(l, r, x);

a[0] = pr[0];
for (int i = 1; i < n; ++i) 
    a[i] = a[i - 1] + pr[i];