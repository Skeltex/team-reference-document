int tree[Ts];
int a[N];

void build(int x, int lx, int rx) {
    if (rx - lx == 1) {
        tree[x] = a[lx];
        return;
    }
    int mid = (lx + rx) / 2;
    build(2 * x + 1, lx, mid);
    build(2 * x + 2, mid, rx);
    tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
}

void add(int pos, int val, int x, int lx, int rx) {
    if (rx - lx == 1) {
        tree[x] += val;
        return;
    }
    int mid = (lx + rx) / 2;
    if (mid < pos) add(pos, val, 2 * x + 1, lx, mid);
    else add(pos, val, 2 * x + 2, mid, rx);
    tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
}

int get(int l, int r, int x, int lx, int rx) {
    if (lx >= l and rx <= r) return tree[x];
    if (lx >= r or rx <= l) return 0;
    int mid = (lx + rx) / 2;
    return get(l, r, 2 * x + 1, lx, mid) + get(l, r, 2 * x + 2, mid, rx);
}