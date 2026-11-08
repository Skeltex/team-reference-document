// Проверка принадлежности точки выпуклому многоугольнику за O(log n).
// Требования к многоугольнику перед вызовом prepare:
// - не менее трёх вершин, обход против часовой стрелки;
// - строгая выпуклость: нет промежуточных коллинеарных вершин;
// - нет повторяющихся вершин, первая вершина не повторяется в конце.
// Координаты вершин и точек запросов должны быть по модулю не больше 10^9.
// Граница считается принадлежащей многоугольнику.
// Сначала вызвать prepare за O(n), затем pointInConvexPolygon для запросов.

bool lexComp(const vec2d& l, const vec2d& r) {
    return l.x < r.x || (l.x == r.x && l.y < r.y);
}

int sgn(long long val) {
    return (val > 0) - (val < 0);
}

vector<vec2d> seq;
vec2d translation;
int n;

// Треугольник должен быть невырожденным. Граница включена.
bool pointInTriangle(const vec2d& a, const vec2d& b, const vec2d& c, const vec2d& p) {
    long long s1 = abs((b - a) % (c - a));
    __int128 s2 = (__int128)abs((a - p) % (b - p))
        + abs((b - p) % (c - p))
        + abs((c - p) % (a - p));
    return s1 == s2;
}

void prepare(vector<vec2d>& points) {
    n = (int)points.size();
    int pos = 0;
    for (int i = 1; i < n; i++) {
        if (lexComp(points[i], points[pos]))
            pos = i;
    }
    rotate(points.begin(), points.begin() + pos, points.end());

    n--;
    seq.resize(n);
    for (int i = 0; i < n; i++)
        seq[i] = points[i + 1] - points[0];
    translation = points[0];
}

bool pointInConvexPolygon(vec2d point) {
    point = point - translation;
    if (seq[0] % point != 0 &&
        sgn(seq[0] % point) != sgn(seq[0] % seq[n - 1]))
        return false;
    if (seq[n - 1] % point != 0 &&
        sgn(seq[n - 1] % point) != sgn(seq[n - 1] % seq[0]))
        return false;

    if (seq[0] % point == 0)
        return seq[0] * seq[0] >= point * point;

    int l = 0, r = n - 1;
    while (r - l > 1) {
        int mid = (l + r) / 2;
        if (seq[mid] % point >= 0)
            l = mid;
        else
            r = mid;
    }
    return pointInTriangle(seq[l], seq[l + 1], vec2d(0, 0), point);
}
