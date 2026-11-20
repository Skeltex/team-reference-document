// Min-Cost Max-Flow (потенциалы Джонсона + Дейкстра).
// Начальный граф без циклов отрицательного веса.
// O(F * m log n); при cost < 0 один запуск SPFA.
struct MCMF {
    struct Edge {
        int to;
        li cap, cost;
    };
    int n;
    bool has_neg = false;
    vector<Edge> ed;
    vvi g;
    vli pot, dist;
    vi pv, pe;
    MCMF(int n) : n(n), g(n), pot(n), dist(n), pv(n), pe(n) {}
    void add_edge(int u, int v, li cap, li cost) {
        if (cost < 0) has_neg = true;
        g[u].push_back(sz(ed));
        ed.push_back({v, cap, cost});
        g[v].push_back(sz(ed));
        ed.push_back({u, 0, -cost});
    }
    void init_pot(int s) {
        pot.assign(n, INF);
        vc inq(n);
        queue<int> q;
        pot[s] = 0;
        q.push(s);
        inq[s] = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            inq[u] = false;
            for (int e : g[u]) {
                int v = ed[e].to;
                if (ed[e].cap > 0 && pot[u] + ed[e].cost < pot[v]) {
                    pot[v] = pot[u] + ed[e].cost;
                    if (!inq[v]) q.push(v), inq[v] = true;
                }
            }
        }
        has_neg = false;
    }
    // Возвращает {поток, стоимость} для потока <= max_f.
    pair<li, li> min_cost_flow(int s, int t, li max_f = INF) {
        if (has_neg) init_pot(s);
        li flow = 0, cost = 0;
        using P = pair<li, int>;
        while (flow < max_f) {
            dist.assign(n, INF);
            priority_queue<P, vector<P>, greater<P>> pq;
            dist[s] = 0;
            pq.push({0, s});
            while (!pq.empty()) {
                auto [d, u] = pq.top();
                pq.pop();
                if (d != dist[u]) continue;
                for (int e : g[u]) {
                    if (ed[e].cap <= 0) continue;
                    int v = ed[e].to;
                    li nd = d + ed[e].cost + pot[u] - pot[v];
                    if (nd < dist[v]) {
                        dist[v] = nd;
                        pv[v] = u;
                        pe[v] = e;
                        pq.push({nd, v});
                    }
                }
            }
            if (dist[t] == INF) break;
            for (int i = 0; i < n; ++i)
                if (dist[i] < INF) pot[i] += dist[i];
            // Для мин. цены произвольного потока:
            // if (pot[t] >= 0) break;
            li push = max_f - flow;
            for (int v = t; v != s; v = pv[v])
                push = min(push, ed[pe[v]].cap);
            for (int v = t; v != s; v = pv[v]) {
                ed[pe[v]].cap -= push;
                ed[pe[v] ^ 1].cap += push;
            }
            flow += push;
            cost += push * pot[t];
        }
        return {flow, cost};
    }
};
