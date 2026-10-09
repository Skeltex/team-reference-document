// F — vli из Fsz нулей.
li sum(int pos) {
    li ans = 0;
    for (; pos >= 0; pos = (pos & (pos + 1)) - 1)
        ans += F[pos];
    return ans;
}

void inc_fenwick(int pos, li val) {
    for (; pos < Fsz; pos |= (pos + 1))
        F[pos] += val;
}
