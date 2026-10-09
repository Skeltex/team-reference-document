void get_divs(const vector<pair<li, li>>& f, li d = 1, int i = 0) {
    if (i == sz(f)) {
        cout << d << '\n';
        return;
    }
    for (int q = 0; q <= f[i].second; ++q) {
        get_divs(f, d, i + 1);
        if (q < f[i].second) d *= f[i].first;
    }
}
