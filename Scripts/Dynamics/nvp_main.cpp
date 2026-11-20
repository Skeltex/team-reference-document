// Строго возрастающая НВП за O(n log n) + сертификат.
// Для неубывающей заменить lower_bound на upper_bound.
vli dp(n + 1, INF);
vi pos(n + 1, -1), prev(n, -1);
dp[0] = -INF;
int len = 0;
for (int i = 0; i < n; ++i) {
    int j = lower_bound(all(dp), a[i]) - dp.begin();
    dp[j] = a[i];
    pos[j] = i;
    prev[i] = pos[j - 1];
    len = max(len, j);
}
vi ans;
for (int cur = pos[len]; cur != -1; cur = prev[cur])
    ans.push_back(cur); // Индексы элементов НВП.
reverse(all(ans));
