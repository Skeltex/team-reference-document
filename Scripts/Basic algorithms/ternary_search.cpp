int l = 0, r = n; // Обе границы включительно
while (l < r) {
    int m1 = (l + r) / 2, m2 = m1 + 1;
    if (check(m1) < check(m2)) r = m1;
    else l = m2;
}
cout << check(r) << '\n';