// SOS DP: для каждой mask считает сумму f[sub]
// по всем sub <= mask (sub & mask == sub). O(B * 2^B).
vli sos_submasks(vli dp, int B) {
    int N = 1 << B;
    for (int i = 0; i < B; ++i)
        for (int m = 0; m < N; ++m)
            if (m & (1 << i)) dp[m] += dp[m ^ (1 << i)];
    return dp;
}
// Обратное (Мёбиус по подмаскам): заменить += на -=.
// Сумма по надмаскам (sup & mask == mask):
vli sos_supermasks(vli dp, int B) {
    int N = 1 << B;
    for (int i = 0; i < B; ++i)
        for (int m = 0; m < N; ++m)
            if (!(m & (1 << i))) dp[m] += dp[m | (1 << i)];
    return dp;
}
// Перебор всех подмасок маски mask (O(3^B) по всем mask):
// for (int s = mask;; s = (s - 1) & mask) {
//     ...
//     if (!s) break;
// }
