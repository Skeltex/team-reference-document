// g = gcd(a, b) >= 0; a*x + b*y = g.
li egcd(li a, li b, li& x, li& y) {
    if (!b) {
        x = a < 0 ? -1 : 1;
        y = 0;
        return abs(a);
    }
    li g = egcd(b, a % b, y, x);
    y -= (a / b) * x;
    return g;
}
