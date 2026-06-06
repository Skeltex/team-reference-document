int tree[Ts];
int p[Ts];
int a[N];

void push(int x, int lx, int rx) {
    tree[x] += p[x] * (rx - lx);
    if (rx - lx != 1) {
        p[2 * x + 1] += p[x];
        p[2 * x + 2] += p[x];
    }
    p[x] = 0;
}

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

void add(int l, int r, int val, int x, int lx, int rx) {
    push(x, lx, rx);
    if (lx >= l and rx <= r) {
        p[x] += val;
        push(x, lx, rx);
        return;
    }
    if (lx >= r or rx <= l) return;
    int mid = (lx + rx) / 2;
    add(l, r, val, 2 * x + 1, lx, mid);
    add(l, r, val, 2 * x + 2, mid, rx);
    tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
}

int get(int l, int r, int x, int lx, int rx) {
    push(x, lx, rx);
    if (lx >= l and rx <= r) return tree[x];
    if (lx >= r or rx <= l) return 0;
    int mid = (lx + rx) / 2;
    return get(l, r, 2 * x + 1, lx, mid) + get(l, r, 2 * x + 2, mid, rx);
}