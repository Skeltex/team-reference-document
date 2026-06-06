int s = 3;
vli d(n, INF64);
d[s] = 0;
vc used(n);
for (int i = 0; i < n; ++i) {
    int v = -1;
    for (int u = 0; u < n; ++u) {
        if (!used[u])
            if (v == -1 || d[v] > d[u])
                v = u;
    }
    if (d[v] == INF64)
        break;
    used[v] = true;
    for (auto [u, w] : g[v])
        d[u] = min(d[u], d[v] + w);
}