// Использует vec2d и line из integer_geometry.cpp.
// Для функций над прямыми требуется A != 0 || B != 0.

typedef pair<long double, long double> pt;

bool operator<(const vec2d& a, const vec2d& b) {
    return make_pair(a.x, a.y) < make_pair(b.x, b.y);
}

__int128 det(long long a, long long b, long long c, long long d) {
    return (__int128)a * d - (__int128)b * c;
}

line canonical_form(const line& a) {
    long long G = gcd(abs(a.A), gcd(abs(a.B), abs(a.C)));
    line b(a.A / G, a.B / G, a.C / G);
    if (b.A < 0 || (b.A == 0 && b.B < 0)) {
        b.A *= -1;
        b.B *= -1;
        b.C *= -1;
    }
    return b;
}

bool parallel_lines(const line& a, const line& b) {
    return det(a.A, a.B, b.A, b.B) == 0;
}

bool equal_lines(const line& a, const line& b) {
    // Проверка пропорциональности коэффициентов через точные определители.
    return det(a.A, a.B, b.A, b.B) == 0
        && det(a.A, a.C, b.A, b.C) == 0
        && det(a.B, a.C, b.B, b.C) == 0;
}

int intersect_lines(const line& a, const line& b, long double& x, long double& y) {
    // 1: единственная точка пересечения записана в (x, y).
    // 0: прямые параллельны и различны.
    // -1: прямые совпадают.
    // При результате 0 или -1 значения x и y не изменяются.
    __int128 d = det(a.A, a.B, b.A, b.B);
    if (d == 0)
        return equal_lines(a, b) ? -1 : 0;

    x = (long double)det(-a.C, a.B, -b.C, b.B) / (long double)d;
    y = (long double)det(a.A, -a.C, b.A, -b.C) / (long double)d;
    return 1;
}

bool bounding_box_check(long long a, long long b, long long c, long long d) {
    if (a > b)
        swap(a, b);
    if (c > d)
        swap(c, d);
    return max(a, c) <= min(b, d);
}

// Только для невырожденных отрезков: a != b и c != d.
// Если пересечение --- точка, она записывается и в ans1, и в ans2.
// Если пересечение --- отрезок, его концы записываются в ans1 и ans2
// в лексикографическом порядке. В обоих случаях возвращается true.
// Если пересечения нет, возвращается false; ans1 и ans2 не определены.
bool intersect_segments(const vec2d& a, const vec2d& b, const vec2d& c, const vec2d& d, pt& ans1, pt& ans2) {
    if (!bounding_box_check(a.x, b.x, c.x, d.x)
        || !bounding_box_check(a.y, b.y, c.y, d.y))
        return false;

    // Точная проверка сторон прямых.
    // Перемножаем только знаки определителей.
    auto sign = [](long long z) {
        return (z > 0) - (z < 0);
    };
    if (sign((b - a) % (c - a)) * sign((b - a) % (d - a)) > 0
        || sign((d - c) % (a - c)) * sign((d - c) % (b - c)) > 0)
        return false;

    line l1(a, b);
    line l2(c, d);
    if (parallel_lines(l1, l2)) {
        if (!equal_lines(l1, l2))
            return false;

        vec2d left = max(min(a, b), min(c, d));
        vec2d right = min(max(a, b), max(c, d));
        ans1 = pt(left.x, left.y);
        ans2 = pt(right.x, right.y);
        return true;
    }

    intersect_lines(l1, l2, ans1.x, ans1.y);
    ans2 = ans1;
    return true;
}
