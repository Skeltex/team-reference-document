void update(int pos, int x, int lx, int rx) {
    if (rx - lx == 1) {
        treet[x] = 0;
        return;
    }
    int mid = (lx + rx) / 2;
    if (pos < mid) update(pos, 2 * x + 1, lx, mid);
    else update(pos, 2 * x + 2, mid, rx);
    treet[x] = treet[2 * x + 1] + treet[2 * x + 2];
}

int get(int cnt, int x, int lx, int rx) {
    if (rx - lx == 1) return lx;
    int mid = (lx + rx) / 2;
    if (treet[2 * x + 1] >= cnt) return get(cnt, 2 * x + 1, lx, mid);
    return get(cnt - treet[2 * x + 1], x * 2 + 2, mid, rx);
}