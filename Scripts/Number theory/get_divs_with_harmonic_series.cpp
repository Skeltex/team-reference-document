vvi divs(n + 1);
for (int d = 2; d <= n; ++d)
    for (int x = d; x <= n; x += d)
        divs[x].push_back(d);