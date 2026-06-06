const int N = 300'013, lg = 20;
int T[lg][N];

void build(const vector<int>& a) {
    int n = a.size();
    for (int i = 0; i < n; ++i)
        T[0][i] = a[i];
    for (int i = 1; i < lg; ++i) {
        int len = 1 << i;
        for (int j = 0; j + len <= n; ++j)
            T[i][j] = min(T[i - 1][j], T[i - 1][j + (len >> 1)]);
    }
}

int query(int l, int r) {
    ++r;
    int len = __lg(r - l);
    return min(T[len][l], T[len][r - (1 << len)]);
}