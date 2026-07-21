struct SQRT {
    int n;
    const int SZ = 2'500;
    vector<vector<int>> s;

    vector<int> get_a() {
        vector<int> a;
        a.reserve(n);
        for (const auto& block : s)
            a.insert(a.end(), all(block));
        return a;
    }

    void insert(int pos, int val) {
        int i = 0;
        while (pos > sz(s[i])) {
            pos -= sz(s[i]);
            ++i;
        }

        s[i].insert(s[i].begin() + pos, val);
        ++n;

        if (sz(s[i]) > 2 * SZ) {
            vector<int> new_block(s[i].begin() + SZ, s[i].end());
            new_block.reserve(2 * SZ + 10);
            s[i].resize(SZ);
            s.insert(s.begin() + i + 1, new_block);
        }
    }

    SQRT() : n(0) {
        s.reserve(600);
        s.push_back(vector<int>());
        s[0].reserve(2 * SZ + 10);
    }
};