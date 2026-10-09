struct func {
    int k;
    int b;
    int eval(int x) {
        return k * x + b;
    }
    func(int k = 0, int b = 0) : k(k), b(b) {}
};

struct line {
    func f;
    ld l;

    line(func f, ld l = 0.0L) : f(f), l(l) {}
};

ld getX(const func& f1, const func& f2) {
    return ld(f2.b - f1.b) / (f1.k - f2.k);
}

struct LineContainer {
    deque<line> d;

    // Вызываем, если по невозрастанию k
    void addRight(const func& f) {
        if (!d.empty() && d.back().f.k == f.k) {
            if (d.back().f.b <= f.b) return;
            d.pop_back();
        }
        while (!d.empty()) {
            ld newX = getX(f, d.back().f);
            if (newX <= d.back().l) d.pop_back();
            else break;
        }
        ld newX = (d.empty() ? -INF : getX(f, d.back().f));
        d.push_back(line(f, newX));
    }

    // Вызываем, если по неубыванию k
    void addLeft(const func& f) {
        if (!d.empty() && d.front().f.k == f.k) {
            if (d.front().f.b <= f.b) return;
            d.pop_front();
        }
        while (!d.empty()) {
            ld newX = getX(f, d.front().f);
            ld r = (sz(d) > 1 ? d[1].l : INF);
            if (newX >= r) d.pop_front();
            else break;
        }
        if (!d.empty()) {
            ld newX = getX(f, d.front().f);
            d.front().l = newX;
        }
        d.push_front(line(f, -INF));
    }

    int getMin(int x) {
        if (d.empty()) return INF;
        int res = 0;
        int l = 1, r = sz(d) - 1;
        while (l <= r) {
            int m = (l + r) / 2;
            if (d[m].l <= x) {
                res = m;
                l = m + 1;
            } else r = m - 1;
        }
        return d[res].f.eval(x);
    }

    int getMin1(int x) {
        // x подаются в порядке неубывания
        if (d.empty()) return INF;
        while (d.size() > 1 && d[1].l <= x) {
            d.pop_front();
            d.front().l = -INF;
        }
        return d.front().f.eval(x);
    }

    int getMin2(int x) {
        // x подаются в порядке невозрастания
        if (d.empty()) return INF;
        while (d.size() > 1 && d.back().l > x)
            d.pop_back();
        return d.back().f.eval(x);
    }

    LineContainer() {}
};

void solve() {
    int n;
    cin >> n;
    vli a(n), b(n), dp(n, INF);
    cin >> a >> b;

    dp[0] = 0;
    LineContainer cont;
    cont.addRight(func(b[0], dp[0]));
    for (int i = 1; i < n; ++i) {
        dp[i] = cont.getMin(a[i]);
        cont.addRight(func(b[i], dp[i]));
    }
    cout << dp[n - 1] << '\n';
}
