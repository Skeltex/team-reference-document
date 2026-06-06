queue<int> q;
vc used(n, false);
vi d(n, INF);
d[0] = 0;
used[0] = true;
q.push(0);
while (!q.empty()) {
    int v = q.front();
    q.pop();
    for (int u : g[v]) {
        if (!used[u]) {
            d[u] = d[v] + 1;
            used[u] = true;
            q.push(u);
        }
    }
}