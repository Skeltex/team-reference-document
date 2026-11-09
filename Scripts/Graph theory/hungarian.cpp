// a[i][j]: стоимость задачи i у работника j.
// Матрица n x m, 1 <= n <= m. Все пары разрешены.
// Целые стоимости, в том числе отрицательные.
// Ответ: {минимальная сумма, worker для задач}.
// Индексы с 0. O(n^2 m), доп. память O(n + m).
pair<li, vi> hungarian(const vvi& a) {
    int n = sz(a), m = sz(a[0]);
    vli u(n + 1), v(m + 1);
    vi p(m + 1), way(m + 1);
    // Внутри индексы с 1; столбец 0 фиктивный.
    // p[j]: задача, назначенная работнику j.
    for (int i = 1; i <= n; ++i) {
        p[0] = i;
        int j0 = 0;
        vli minv(m + 1);
        vc used(m + 1);
        do {
            used[j0] = true;
            int i0 = p[j0], j1 = 0;
            li delta = 0;
            for (int j = 1; j <= m; ++j) {
                if (used[j]) continue;
                li cur = a[i0 - 1][j - 1]
                         - u[i0] - v[j];
                // Первый шаг инициализирует minv.
                if (!j0 || cur < minv[j]) {
                    minv[j] = cur;
                    way[j] = j0;
                }
                if (!j1 || minv[j] < delta) {
                    delta = minv[j];
                    j1 = j;
                }
            }
            for (int j = 0; j <= m; ++j) {
                if (used[j]) {
                    u[p[j]] += delta;
                    v[j] -= delta;
                } else {
                    minv[j] -= delta;
                }
            }
            j0 = j1;
        } while (p[j0]);
        // Увеличение паросочетания вдоль пути.
        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }
    vi worker(n);
    for (int j = 1; j <= m; ++j)
        if (p[j]) worker[p[j] - 1] = j - 1;
    return {-v[0], worker};
}
