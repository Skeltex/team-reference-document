vector<int> pal(const string& s) {
    string t = "@#";
    for (char c : s) {
        t.push_back(c);
        t.push_back('#');
    }
    t.push_back('$');

    vector<int> p(sz(t));
    int l = 1, r = 1;
    for (int i = 1; i < sz(t) - 1; ++i) {
        if (i < r) p[i] = min(r - i, p[l + r - i]);
        while (t[i + p[i]] == t[i - p[i]])
            ++p[i];
        if (i + p[i] > r) {
            r = i + p[i];
            l = i - p[i];
        }
    }
    return p;
}
// len = p[i] - 1
// l = (i - p[i]) / 2
// r = (i + p[i]) / 2 - 2
// для нечётных center = i / 2 - 1
// для чётных center = [i / 2 - 1, i / 2]