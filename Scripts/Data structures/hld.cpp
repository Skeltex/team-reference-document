int n;
vector<int> g[N];
int p[N], siz[N], d[N], nxt[N];
int tin[N], T;
void dfs_sz(int v) {
	if (p[v] != -1) {
		auto it = find(g[v].begin(), g[v].end(), p[v]);
		if (it != g[v].end())
			g[v].erase(it);
	}
	siz[v] = 1;
	for (int &u : g[v]) {
		p[u] = v;
		d[u] = d[v] + 1;
		dfs_sz(u);
		siz[v] += siz[u];
		if (siz[u] > siz[g[v][0]])
			swap(u, g[v][0]);
	}
}
void dfs_hld(int v) {
	tin[v] = T++;
	for (int u : g[v]) {
		nxt[u] = (u == g[v][0] ? nxt[v] : u);
		dfs_hld(u);
	}
}
void update(int l, int r, int val) { } // [l; r] inclusive
int get(int l, int r) { } // [l; r] inclusive
void update_path(int v, int u, int val) {
	for (; nxt[v] != nxt[u]; u = p[nxt[u]]) {
		if (d[nxt[v]] > d[nxt[u]]) swap(v, u);
		update(tin[nxt[u]], tin[u], val);
	}
	if (d[v] > d[u]) swap(v, u);
	update(tin[v], tin[u], val);
}
int get_path(int v, int u) {
	int res;
	for (; nxt[v] != nxt[u]; u = p[nxt[u]]) {
		if (d[nxt[v]] > d[nxt[u]]) swap(v, u);
		// update res with the result of get()
		get(tin[nxt[u]], tin[u]);
	}
	if (d[v] > d[u]) swap(v, u);
	get(tin[v], tin[u]);
	return res;
}
void update_subtree(int v, int val) {
	update(tin[v], tin[v] + siz[v] - 1, val);
}
int get_subtree(int v) {
	return get(tin[v], tin[v] + siz[v] - 1);
}
void init_hld(int root = 0) {
	d[root] = 0;
	nxt[root] = root;
	p[root] = -1;
	T = 0;
	dfs_sz(root);
	dfs_hld(root);
}
