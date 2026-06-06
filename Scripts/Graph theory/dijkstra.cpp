int s = 3;
vli d(n, INF64);
d[s] = 0;
priority_queue<pair<li, int>,
    vector<pair<li, int>>,
    greater<pair<li, int>>> q;
q.push({ d[s], s });
while (!q.empty()) {
    int v = q.top().second;
    bool need = d[v] == q.top().first;
    q.pop();
    if (need) {
        for (auto [u, w] : g[v]) {
            if (d[u] > d[v] + w) {
                d[u] = d[v] + w;
                q.push({ d[u], u });
            }
        }
    }
}