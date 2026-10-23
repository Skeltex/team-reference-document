vector<int> g[N]; // список смежности
vector<int> c[N]; // список детей
int siz[N]; // размеры поддеревьев
int p[N]; // родитель вершины
vector<int> order; // порядок вершин
int pos[N]; // позиция вершины в порядке
int path[N]; // путь, которому принадлежит вершина
int start[N]; // начало каждого пути
int n, depth[N]; // глубины вершин
void dfs1(int x, int par = -1) {
    p[x] = par; siz[x] = 1;
    if (par != -1) depth[x] = depth[par] + 1;
    for (auto y : g[x]) if (y != par) {
        c[x].push_back(y);
        dfs1(y, x); siz[x] += siz[y];
    }
    int max_child = 0;
    for (int i = 1; i < c[x].size(); i++)
        if (siz[c[x][i]] > siz[c[x][max_child]])
            max_child = i;
    if (!c[x].empty()) swap(c[x][0], c[x][max_child]);
}
void dfs2(int x, int& cur_path, bool is_start) {
    if (is_start) start[cur_path] = x;
    path[x] = cur_path; pos[x] = order.size();
    order.push_back(x);
    if (!c[x].empty()) dfs2(c[x][0], cur_path, false);
    for (int i = 1; i < c[x].size(); i++)
        dfs2(c[x][i], ++cur_path, true);
}
void build_hld() {
    int paths = 0; dfs1(0); dfs2(0, paths, true);
    build(0, 0, n); // строим дерево отрезков на массиве order
}
void upd(int v, int x) { upd(0, 0, n, pos[v], x); }
int get_max(int x, int y) {
    int ans = -1e9;
    while (path[x] != path[y]) {
        if (pos[x] > pos[y]) swap(x, y);
        int z = start[path[y]];
        ans = max(ans, get(0, 0, n, pos[z], pos[y] + 1));
        y = p[z];
    }
    if (depth[x] < depth[y]) swap(x, y);
    // если надо исключить LCA, вместо pos[y] исп. pos[y]+1
    return max(ans, get(0, 0, n, pos[y], pos[x] + 1));
}
