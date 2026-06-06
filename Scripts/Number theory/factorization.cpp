vector<pii> fact;
for (li i = 2; i * i <= x; ++i) {
    if (x % i == 0) {
        int cnt = 0;
        while (x % i == 0) {
            x /= i;
            ++cnt;
        }
        fact.push_back({ i, cnt });
    }
}
if (x > 1)
    fact.push_back({ x, 1 });