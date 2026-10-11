//k = __lg(n)
//if ((1ll << k) < n) k++;
int tree[Ts];
int a[N];

void build(int n, int k) {
    k = 1ll << k;
    for (int i = 0; i < n; i++) tree[i + k] = a[i];
    for (int i = k - 1; i > 0; i--) {
        tree[i] = tree[2 * i] + tree[2 * i + 1];
    }
}

void update(int pos, int val, int k) {
    pos += (1ll << k);
    tree[pos] = val;
    pos >>= 1ll;
    while (pos) {
        tree[pos] = tree[2 * pos] + tree[2 * pos + 1];
        pos >>= 1ll;
    }
}

int get(int l, int r, int k) {
    l += (1ll << k);
    r += (1ll << k);
    int res = 0;
    while (l < r) {
        if (l & 1) res += tree[l++];
        if (r & 1) res += tree[--r];
        l >>= 1;
        r >>= 1;
    }
    return res;
}

