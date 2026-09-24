// Простой неориентированный граф. O(n + m * sqrt(m)).
int count_triangles(const vvi& g) {
    int n = sz(g);
    vvi to(n);
    for (int v = 0; v < n; ++v) {
        for (int u : g[v]) {
            if (sz(g[v]) < sz(g[u]) || (sz(g[v]) == sz(g[u]) && v < u)) to[v].push_back(u);
        }
    }

    vector<char> used(n);
    int ans = 0;
    for (int v = 0; v < n; ++v) {
        for (int u : to[v])
            used[u] = true;
        for (int u : to[v]) {
            for (int w : to[u])
                ans += used[w];
        }
        for (int u : to[v])
            used[u] = false;
    }
    return ans;
}
