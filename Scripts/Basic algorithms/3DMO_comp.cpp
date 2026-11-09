// Размер блока B для 3D Mo должен быть ≈ N^(2/3). Для N = 100'000 оптимально B ≈ 2150.
bool cmp(int i, int j) {
    int bLi = lg[i] / B, bLj = lg[j] / B;
    if (bLi != bLj) return bLi < bLj;
    int bRi = rg[i] / B, bRj = rg[j] / B;
    if (bRi != bRj) return (bLi & 1) ? bRi < bRj : bRi > bRj;
    return (bRi & 1) ? t[i] < t[j] : t[i] > t[j];
}