void get_divs(const vector<pii>& f, int d = 1, int i = 0) {
    if (i == sz(f))) {
        cout << d << '\n';
        return;
    }
    for (int q = 0; q <= f[i].second; ++q) {
        get_divs(f, d, i + 1);
        d *= f[i].first;
    }
}