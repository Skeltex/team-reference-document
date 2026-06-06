struct edge {
    int v, f, c;
    edge(int a, int b) : v(a), f(0), c(b) {}
};

struct network {
    int n, s, t;
    vvi g;
    vector<edge> edges;
    vi lx;
    vi d;
    network(int a, int b, int c) {
        n = a;
        s = b;
        t = c;
        g.resize(n);
    }

    void add(int u, int v, int c) {
        edges.push_back(edge(v, c));
        edges.push_back(edge(u, 0));
        g[u].push_back(sz(edges) - 2);
        g[v].push_back(sz(edges) - 1);
    }

    int dif(int i) {
        return edges[i].c - edges[i].f;
    }

    bool bfs(int m) {
        d = vi(n, INF);
        d[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (u == t) break;
            for (auto i : g[u]) {
                int v = edges[i].v;
                if (dif(i) < m or d[v] != INF) continue;
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
        return d[t] != INF;
    }

    int dfs(int x, int mx, int m) {
        if (x == t or mx == 0) return mx;
        int sm = 0;
        for (; lx[x] < g[x].size(); ++lx[x]) {
            int i = g[x][lx[x]];
            int v = edges[i].v;
            if (dif(i) < m or d[v] != d[x] + 1) continue;
            int push = dfs(v, min(mx - sm, dif(i)), m);
            edges[i].f += push;
            edges[i ^ 1].f -= push;
            sm += push;
            if (sm == mx) break;
        }
        return sm;
    }

    int maxflow() {
        int flow = 0, m = (1ll << 30);
        while (m > 0) {
            while (bfs(m)) {
                lx = vi(n, 0);
                while (true) {
                    int f = dfs(s, INF, m);
                    if (f == 0) break;
                    flow += f;
                }
            }
            m >>= 1;
        }
        return flow;
    }
};