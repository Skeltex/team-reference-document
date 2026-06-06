vvi g;
vc used;
vi ord;

void dfs(int v) {
    used[v] = true;
    for (int u : g[v])
        if (!used[u])
            dfs(u);
    ord.push_back(v);
}

void solve() {
    // Ввод графа
    for (int i = 0; i < n; ++i)
        if (!used[i])
            dfs(i);
    reverse(all(ord));

    vi pos(n);
    for (int i = 0; i < n; ++i)
        pos[ord[i]] = i;

    bool is_valid = true;
    for (int v = 0; v < n; ++v) {
        for (int u : g[v]) {
            if (pos[v] >= pos[u]) {
                is_valid = false;
                break;
            }
        }
    }
}