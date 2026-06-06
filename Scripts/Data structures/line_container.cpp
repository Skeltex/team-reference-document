struct func {
    int k;
    int b;
    int eval(int x) {
        return k * x + b;
    }
    func(int k = 0, int b = 0) : k(k), b(b) {};
};

struct line {
    func f;
    ld l;

    line(func f, ld l = 0.0l) : f(f), l(l) {};
};

ld getX(const func& f1, const func& f2) {
    return (f2.b - f1.b) / (f1.k - f2.k);
}

struct LineContainer {
    deque<line> d;

    // Вызываем, если по убыванию k
    void addRight(const func& f) {
        while (!d.empty()) {
            ld newX = getX(f, d.back().f);
            if (newX <= d.back().l)
                d.pop_back();
            else
                break;
        }
        ld newX = (d.empty() ? -INF64 : getX(f, d.back().f));
        d.push_back(line(f, newX));
    }

    // Вызываем, если по возрастанию k
    void addLeft(const func& f) {
        while (!d.empty()) {
            ld newX = getX(f, d.front().f);
            ld r = (sz(d) > 1 ? d[1].l : INF64);
            if (newX >= r)
                d.pop_front();
            else
                break;
        }
        if (!d.empty()) {
            ld newX = getX(f, d.front().f);
            d.front().l = newX;
        }
        d.push_front(line(f, -INF64));
    }

    int getMin(int x) {
        if (d.empty())
            return INF64;
        int res = 0;
        int l = 1, r = sz(d) - 1;
        while (l <= r) {
            int m = (l + r) / 2;
            if (d[m].l <= x) {
                res = m;
                l = m + 1;
            }
            else
                r = m - 1;
        }
        return d[res].f.eval(x);
    }

    int getMin1(int x) {
        // x подаются в порядке неубывания
        if (d.empty())
            return INF64;
        while (d.size() > 1 && d[1].l <= x) {
            d.pop_front();
            d.front().l = -INF64;
        }
        return d.front().f.eval(x);
    }

    int getMin2(int x) {
        // x подаются в порядке невозрастания
        if (d.empty())
            return INF64;
        while (d.back().l > x)
            d.pop_back();
        return d.back().f.eval(x);
    }

    LineContainer() {};
};

void solve() {
    int n;
    cin >> n;
    vli a(n), b(n), dp(n, INF64);
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