int max1 = -INF, max2 = -INF;
for (int x : a) {
    if (x > max1) {
        max2 = max1;
        max1 = x;
    }
    else if (x > max2)
        max2 = x;
}