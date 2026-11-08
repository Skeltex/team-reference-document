// Целочисленная геометрия, C++17.
// Исходные точки должны иметь координаты по модулю не больше 10^9.

#define x first
#define y second

struct vec2d {
    long long x, y;

    vec2d(long long x = 0, long long y = 0) : x(x), y(y) {}
};

struct line {
    long long A, B, C;

    line(long long A = 0, long long B = 0, long long C = 0) : A(A), B(B), C(C) {}

    // Точки a и b должны быть различны.
    line(const vec2d& a, const vec2d& b) {
        A = b.y - a.y;
        B = a.x - b.x;
        C = -A * a.x - B * a.y;
    }
};

long long eval(const line& l, const vec2d& v) {
    return l.A * v.x + l.B * v.y + l.C;
}

bool isOnLine(const line& l, const vec2d& v) {
    return eval(l, v) == 0;
}

vec2d operator+(const vec2d& a, const vec2d& b) {
    return vec2d(a.x + b.x, a.y + b.y);
}

vec2d operator-(const vec2d& a, const vec2d& b) {
    return vec2d(a.x - b.x, a.y - b.y);
}

long long operator*(const vec2d& a, const vec2d& b) {
    // Скалярное произведение.
    return a.x * b.x + a.y * b.y;
}

long long operator%(const vec2d& a, const vec2d& b) {
    // Псевдоскалярное (косое) произведение.
    return a.x * b.y - a.y * b.x;
}
