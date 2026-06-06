vli d(n, INF64);
d[s] = 0;
for (int k = 0; k < n - 1; ++k) {
	bool changed = false;
	for (int v = 0; v < n; ++v) {
		if (d[v] == INF64)
			continue;
		for (auto [u, w] : g[v]) {
			if (d[v] + w < d[u]) {
				d[u] = d[v] + w;
				changed = true;
			}
		}
	}
	if (!changed)
		break;
}