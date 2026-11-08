// Выпуклая оболочка за O(n log n).
// Входной вектор заменяется вершинами оболочки против часовой стрелки.
// Для коллинеарного набора возвращаются две крайние точки;
// для пустого набора --- пустой вектор, для одной различной точки --- она сама.
// Координаты исходных точек должны быть по модулю не больше 10^9.

int orientation(const vec2d& a, const vec2d& b, const vec2d& c) {
    long long v = a.x * 1ll * (b.y - c.y)
        + b.x * 1ll * (c.y - a.y)
        + c.x * 1ll * (a.y - b.y);
    if (v < 0)
        return -1; // По часовой стрелке.
    if (v > 0)
        return 1; // Против часовой стрелки.
    return 0;
}

bool cw(const vec2d& a, const vec2d& b, const vec2d& c) {
    return orientation(a, b, c) < 0;
}

bool ccw(const vec2d& a, const vec2d& b, const vec2d& c) {
    return orientation(a, b, c) > 0;
}

void convex_hull(vector<vec2d>& a) {
    if (a.size() <= 1)
        return;

    sort(a.begin(), a.end(), [](const vec2d& p, const vec2d& q) {
        return make_pair(p.x, p.y) < make_pair(q.x, q.y);
    });
    a.erase(unique(a.begin(), a.end(), [](const vec2d& p, const vec2d& q) {
        return p.x == q.x && p.y == q.y;
    }), a.end());
    if (a.size() <= 1)
        return;

    vec2d p1 = a[0], p2 = a.back();
    vector<vec2d> up, down;
    up.push_back(p1);
    down.push_back(p1);
    int size = (int)a.size();
    for (int i = 1; i < size; i++) {
        if (i == size - 1 || cw(p1, a[i], p2)) {
            while (up.size() >= 2 && !cw(up[up.size() - 2], up.back(), a[i]))
                up.pop_back();
            up.push_back(a[i]);
        }
        if (i == size - 1 || ccw(p1, a[i], p2)) {
            while (down.size() >= 2 && !ccw(down[down.size() - 2], down.back(), a[i]))
                down.pop_back();
            down.push_back(a[i]);
        }
    }

    a.clear();
    for (const vec2d& point : down)
        a.push_back(point);
    for (int i = (int)up.size() - 2; i > 0; i--)
        a.push_back(up[i]);
}
