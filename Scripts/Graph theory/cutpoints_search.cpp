vvi g;
vc used;
vi up, d;

void dfs(int v, int p = -1) {
    up[v] = d[v];
    used[v] = true;
    bool is_cutpoint = false;
    int cnt = 0;
    for (int u : g[v]) {
        if (u != p) {
            if (!used[u]) {
                d[u] = d[v] + 1;
                dfs(u, v);
                if (up[u] >= d[v] && p != -1)
                    is_cutpoint = true;
                up[v] = min(up[v], up[u]);
                ++cnt;
            }
            else
                up[v] = min(up[v], d[u]);
        }
    }
    if (p == -1 && cnt > 1)
        is_cutpoint = true;
    if (is_cutpoint)
        cout << v + 1 << '\n';
}

void solve() {
    // Ввод графа
    d.resize(n);
    up.resize(n);
    d[0] = 0;
    dfs(0);
}