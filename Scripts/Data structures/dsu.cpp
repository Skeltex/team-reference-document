struct DSU {
    vi s; // Эвристика размера
    vi p;
    
    int get(int x) {
        if (p[x] == x)
            return x;
        //return get(p[x]); // Без эвристики сжатия пути
        return p[x] = get(p[x]); // Эвристика сжатия пути
    }

    bool merge(int x, int y) {
        x = get(x);
        y = get(y);
        if (x == y)
            return false;

        // Эвристика размера
        if (s[x] > s[y])
            swap(x, y);
        s[y] += s[x];
        //

        p[x] = y;
        return true;
    }

    DSU(int n = 0) {
        p = vi(n);
        iota(all(p), 0);
        s = vi(n, 1); // Эвристика размера
    }
};