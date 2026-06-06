int sum(int pos) {
    int ans = 0;
    for (; pos >= 0; pos = (pos & (pos + 1)) - 1) ans += F[pos];
    return ans;
}

void inc(int pos, int val) {
    for (; pos < Fsz; pos |= (pos + 1)) F[pos] += val;
}