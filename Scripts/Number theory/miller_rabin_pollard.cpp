using u64 = uint64_t;
using u128 = __uint128_t;
u64 mul_mod(u64 a, u64 b, u64 m) {
    return (u128)a * b % m;
}
u64 pow_mod(u64 a, u64 e, u64 m) {
    u64 r = 1;
    for (a %= m; e; e >>= 1) {
        if (e & 1) r = mul_mod(r, a, m);
        a = mul_mod(a, a, m);
    }
    return r;
}
// Детерминированный Миллер–Рабин для всех u64 (< 2^64).
bool is_prime(u64 n) {
    if (n < 2) return false;
    if (n % 2 == 0) return n == 2;
    u64 d = n - 1;
    int s = 0;
    while ((d & 1) == 0) d >>= 1, ++s;
    for (u64 a : {2ULL, 325ULL, 9375ULL,
             28178ULL, 450775ULL,
             9780504ULL, 1795265022ULL}) {
        if (a % n == 0) continue;
        u64 x = pow_mod(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool ok = false;
        for (int r = 1; r < s; ++r) {
            x = mul_mod(x, x, n);
            if (x == n - 1) {
                ok = true;
                break;
            }
        }
        if (!ok) return false;
    }
    return true;
}
// Поллард-ро: нетривиальный делитель составного n.
u64 pollard(u64 n) {
    if (!(n & 1)) return 2;
    for (u64 c = 1;; ++c) {
        auto f = [&](u64 x) -> u64 {
            return ((u128)x * x + c) % n;
        };
        u64 x = 2, y = 2, prd = 1, q;
        for (int t = 1;; ++t) {
            x = f(x);
            y = f(f(y));
            if (x == y) break;
            u64 diff = x > y ? x - y : y - x;
            if ((q = mul_mod(prd, diff, n))) prd = q;
            if (t % 64 == 0) {
                u64 g = std::gcd(prd, n);
                if (g > 1) return g;
            }
        }
        u64 g = std::gcd(prd, n);
        if (g > 1) return g;
    }
}
void factor_rec(u64 n, vector<u64>& res) {
    if (n == 1) return;
    if (is_prime(n)) {
        res.push_back(n);
        return;
    }
    u64 d = pollard(n);
    factor_rec(d, res);
    factor_rec(n / d, res);
}
// Отсортированные простые делители (с кратностью). O(n^(1/4)).
vector<u64> factorize(u64 n) {
    vector<u64> res;
    factor_rec(n, res);
    sort(all(res));
    return res;
}
