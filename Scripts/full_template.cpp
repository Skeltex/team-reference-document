#define _CRT_SECURE_NO_WARNINGS
const int MOD = 998'244'353;
#pragma region template
#pragma region include
#include <iostream>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <iomanip>
#include <random>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <list>
#include <stack>
#include <queue>
#include <deque>
#include <array>
#include <bitset>
#include <cstring>
#include <fstream>
#include <cassert>

using namespace std;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
#pragma endregion

#pragma region define
#define see(x) cerr << (#x) << " = " << (x) << '\n';
#define forn(i, n) for (int i = 0; i < int(n); ++i)
#define forit(it, a) for (auto it = (a).begin(); it != (a).end(); ++it)
#define each(x, a) for (auto &x : (a))
#define sqr(a) ((a) * (a))
#define cube(a) ((a) * (a) * (a))
#define divup(a, b) ((a) ? ((a) - 1) / (b) + 1 : 0)
#define inc(a, b, c) ((a) <= (b) && (b) <= (c))
#define inc2(a, b, c) ((a) < (b) && (b) < (c))
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#pragma endregion

#pragma region typedef
typedef long long li;
typedef long double ld;
typedef string str;

typedef pair<int, int> pii;
typedef pair<char, char> pcc;
typedef pair<li, li> pli;
typedef pair<ld, ld> pld;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<char> vc;
typedef vector<vc> vvc;
typedef vector<li> vli;
typedef vector<vli> vvli;
typedef vector<ld> vld;
typedef vector<vld> vvld;
typedef vector<str> vs;
typedef vector<vs> vvs;
#pragma endregion

#pragma region const
const int INF = int(1e9) + 13;
const li INF64 = li(2e18) + 13ll;
const ld EPS = 1e-9l;
const ld PI = acosl(-1.0l);
const int N = 200'013;
#pragma endregion

#pragma region input/output operators
template<typename T, typename U>
istream& operator >> (istream& in, pair<T, U>& x) {
    return in >> x.f >> x.s;
}

template<typename T, typename U>
ostream& operator << (ostream& out, const pair<T, U>& x) {
    return out << x.f << ' ' << x.s << '\n';
}

template<typename T> istream& operator >> (istream& in, vector<T>& v) {
    each(x, v)
        in >> x;
    return in;
}

template <typename T> ostream& operator << (ostream& out, const vector<T>& v) {
    each(x, v)
        out << x << ' ';
    return out << '\n';
}

template <typename T> ostream& operator << (ostream& out, const vector<vector<T>>& v) {
    each(x, v)
        out << x;
    return out;
}
#pragma endregion

#pragma region yes/no functions
void YES(bool ok = true) {
    cout << (ok ? "YES" : "NO") << '\n';
}

void Yes(bool ok = true) {
    cout << (ok ? "Yes" : "No") << '\n';
}

void yes(bool ok = true) {
    cout << (ok ? "yes" : "no") << '\n';
}

void NO(bool ok = true) {
    YES(!ok);
}

void No(bool ok = true) {
    Yes(!ok);
}

void no(bool ok = true) {
    yes(!ok);
}
#pragma endregion

#pragma region number functions
bool is_int(ld x) {
    return abs(x - li(x)) < EPS;
}

bool is_sqr(li x) {
    return is_int(sqrtl(x));
}

bool is_pow2(li x) {
    return x && (x & -x) == x;
}

li mask(int i) {
    return (1ll << i) - 1;
}

li gcd(li a, li b) {
    if (a < b)
        swap(a, b);
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

li lcm(li a, li b) {
    return a / gcd(a, b) * b;
}

bool is_prime(li x) {
    if (x < 5)
        return (x == 2) || (x == 3);
    if (!(x % 2) || !(x % 3))
        return false;
    for (li i = 6; sqr(i - 1) <= x; i += 6)
        if (!(x % (i - 1)) || !(x % (i + 1)))
            return false;
    return true;
}

str dec_to_bin(li x) {
    if (!x)
        return "0";
    str s;
    while (x) {
        s += (x & 1) + '0';
        x >>= 1;
    }
    reverse(all(s));
    return s;
}

li bin_to_dec(str s) {
    li x = 0;
    int n = sz(s);
    for (int i = n - 1; i >= 0; --i)
        x += (s[i] - '0') * (1ll << (n - 1 - i));
    return x;
}
#pragma endregion
#pragma region modular operations
li add(li a, li b) {
    a = (a + b) % MOD;
    return a >= 0 ? a : a + MOD;
}

li sub(li a, li b) {
    return add(a, -b);
}

li mul(li a, li b) {
    return a * b % MOD;
}

li binpow(li a, li b) {
    li res = 1;
    while (b) {
        if (b & 1)
            res = mul(res, a);
        a = mul(a, a);
        b >>= 1;
    }
    return res;
}

li inv(li x) {
    return binpow(x, MOD - 2);
}
#pragma endregion
#pragma region vector functions
template<typename T>
T min(const vector<T>& a) {
    return *min_element(all(a));
}

template<typename T>
T min_ind(const vector<T>& a) {
    return min_element(all(a)) - a.begin();
}

template<typename T>
T max(const vector<T>& a) {
    return *max_element(all(a));
}

template<typename T>
T max_ind(const vector<T>& a) {
    return max_element(all(a)) - a.begin();
}

template<typename T>
li sum(const vector<T>& a) {
    return accumulate(all(a), 0ll);
}

template<typename T>
int mex(const T& a) {
    vc used(sz(a) + 1, false);
    each(x, a)
        if (x <= sz(a))
            used[x] = true;
    for(int i = 0; i <= sz(a); ++i)
        if (!used[i])
            return i;
}

template<typename T>
li gcd(const vector<T>& a) {
    li gcd1 = 0;
    each(x, a)
        gcd1 = gcd(gcd1, x);
    return gcd1;
}

template<typename T>
li lcm(const vector<T>& a) {
    li lcm1 = 1;
    each(x, a)
        lcm1 = lcm(lcm1, x);
    return lcm1;
}

template<typename T>
int find(const vector<T>& a, T value) {
    return find(all(a), value) - a.begin();
}

template<typename T>
int rfind(const vector<T>& a, T value) {
    return a.rend() - find(rall(a), value) - 1;
}

template<typename T>
bool in(const vector<T>& a, T value) {
    return find(a, value) != sz(a);
}

template<typename T>
int bin_search(const vector<T>& a, T value) {
    int index = lower_bound(all(a), value) - a.begin();
    return (a[index] == value ? index : -1);
}

template<typename T>
vi get_cnt(const vector<T>& a) {
    vi cnt(max(a) + 1);
    each(x, a)
        ++cnt[x];
    return cnt;
}

template<typename T>
vc get_used(const vector<T>& a) {
    vc used(max(a) + 1);
    each(x, a)
        used[x] = true;
    return used;
}

template<typename T>
vi zip(const vector<T>& a) {
    vector<T> c = a;
    sort(all(c));
    unique(all(c));
    vi b;
    each(x, a)
        b.push_back(bin_search(c, x));
    return b;
}
#pragma endregion
#pragma region string functions
char min(const str& s) {
    return *min_element(all(s));
}

char max(const str& s) {
    return *max_element(all(s));
}

str low(const str& s) {
    str s1 = s;
    each(c, s1)
        c = tolower(c);
    return s1;
}

str up(const str& s) {
    str s1 = s;
    each(c, s1)
        c = toupper(c);
    return s1;
}

bool in(const str& s, char c) {
    return s.find(c) != str::npos;
}

bool in(const str& s, const str& s1) {
    return s.find(s1) != str::npos;
}

bool replace(str& s, const str& from, const str& to) {
    size_t start_pos = s.find(from);
    if (start_pos == str::npos)
        return false;
    s.replace(start_pos, sz(from), to);
    return true;
}

void replace_all(str& s, const str& from, const str& to) {
    while (replace(s, from, to));
}

void remove(str& s, const str& from) {
    replace(s, from, "");
}

void remove_all(str& s, const str& from) {
    replace_all(s, from, "");
}

void strip(str& s, char c = ' ') {
    if (empty(s))
        return;
    int l = 0, r = sz(s) - 1;
    while (s[l] == c && l < r)
        ++l;
    while (s[r] == c && l < r)
        --r;
    if (s[l] == c)
        s = "";
    else
        s = s.substr(l, r - l + 1);
}

void remove_extra_spaces(str& s, char c = ' ') {
    str s2;
    for (int i = 0; i < sz(s); ++i)
        if (!(s[i] == c && i >= 1 && s[i - 1] == c))
            s2.push_back(s[i]);
    s = s2;
}
#pragma endregion
#pragma endregion
//#define int long long
//#define MULTITEST

void solve() {
    
}

signed main() {
#ifdef _DEBUG
    (void)freopen("input.txt", "r", stdin);
    (void)freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(16);
    cerr.precision(16);
    cout << fixed;
    cerr << fixed;

    int tc = 1;
#ifdef MULTITEST
    cin >> tc;
#endif
    while (tc--)
        solve();
}