li sum(int pos) {
    li ans = 0;
    for (; pos >= 0; pos = (pos & (pos + 1)) - 1) ans += F[pos];
    return ans;
}
void inc_fenwick(int pos, li val) {
    for (; pos < Fsz; pos |= (pos + 1)) F[pos] += val;
}
// Возвращает минимальный индекс, префиксная сумма до которого >= x (или Fsz, если сумма всего массива < x)
int find_first_geq(li x) {
    int pos = 0, step = 1;
    while ((step << 1) <= Fsz) step <<= 1;
    for (; step > 0; step >>= 1)
        if (pos + step <= Fsz && F[pos + step - 1] < x)
            x -= F[pos + step - 1], pos += step;
    return pos;
}
