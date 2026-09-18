struct TreeNode {
    li sum;
    int leftSon;
    int rightSon;
    TreeNode() : sum(0), leftSon(-1), rightSon(-1) {}
};

TreeNode buf[24'000'000];
int cur = 0;
int n;
vector<int> roots;

int makeLeaf(int val) {
    buf[cur].sum = val;
    buf[cur].leftSon = buf[cur].rightSon = -1;
    return cur++;
}

int makeInner(int lf, int rg) {
    buf[cur].sum = buf[lf].sum + buf[rg].sum;
    buf[cur].leftSon = lf;
    buf[cur].rightSon = rg;
    return cur++;
}

int build(const vector<int>& a, int l, int r) {
    if (r - l == 1)
        return makeLeaf(a[l]);
    int m = (l + r) / 2;
    int lf = build(a, l, m);
    int rg = build(a, m, r);
    return makeInner(lf, rg);
}

void build(const vector<int>& a) {
    n = sz(a);
    roots.push_back(build(a, 0, n));
}

li get_sum(int v, int l, int r, int L, int R) {
    if (R <= l || L >= r || L >= R) return 0;
    if (L <= l && r <= R) return buf[v].sum;
    int m = (l + r) / 2;
    return get_sum(buf[v].leftSon, l, m, L, R) + get_sum(buf[v].rightSon, m, r, L, R);
}

li get_sum(int L, int R, int v = sz(roots) - 1) {
    return get_sum(roots[v], 0, n, L, R + 1);
}

int update(int v, int l, int r, int pos, int val) {
    if (r - l == 1)
        return makeLeaf(val);
    int m = (l + r) / 2;
    int lf = buf[v].leftSon;
    int rg = buf[v].rightSon;
    if (pos < m)
        lf = update(lf, l, m, pos, val);
    else
        rg = update(rg, m, r, pos, val);
    return makeInner(lf, rg);
}

void update(int pos, int val, int v = sz(roots) - 1) {
    roots.push_back(update(roots[v], 0, n, pos, val));
}