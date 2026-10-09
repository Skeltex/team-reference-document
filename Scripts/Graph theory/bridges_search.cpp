vvi g;
vc used;
vi up, d;

void dfs(int v, int p = -1) {
    up[v] = d[v];
    used[v] = true;
    bool parent_skipped = false;
    for (int u : g[v]) {
        if (u == p && !parent_skipped) {
            parent_skipped = true;
            continue;
        }
        if (!used[u]) {
            d[u] = d[v] + 1;
            dfs(u, v);
            if (up[u] > d[v]) cout << v + 1 << ' ' << u + 1 << '\n';
            up[v] = min(up[v], up[u]);
        } else up[v] = min(up[v], d[u]);
    }
}

void solve() {
    // Ввод графа
    used.assign(n, false);
    d.assign(n, 0);
    up.resize(n);
    for (int v = 0; v < n; ++v)
        if (!used[v]) dfs(v);
}
