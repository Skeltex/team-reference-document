vvi g;
vc used;
vi up, d;

void dfs(int v, int p = -1) {
    up[v] = d[v];
    used[v] = true;
    for (int u : g[v]) {
        if (u != p) {
            if (!used[u]) {
                d[u] = d[v] + 1;
                dfs(u, v);
                if (up[u] > d[v])
                    cout << "! " << v + 1 << ' ' << u + 1 << '\n';
                up[v] = min(up[v], up[u]);
            }
            else
                up[v] = min(up[v], d[u]);
        }
    }
}

void solve() {
    // Ввод графа
    d.resize(n);
    up.resize(n);
    d[0] = 0;
    dfs(0);
}