#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <iomanip>
#include <random>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <list>
#include <stack>
#include <queue>
#include <deque>
#include <bitset>
#include <cstring>
#include <fstream>
#include <cassert>
#include <chrono>

using namespace std;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

#ifdef _DEBUG
#define see(x) cerr << (#x) << " = " << (x) << '\n'
#else
#define see(x) 42
#endif
#define sqr(a) ((a) * (a))
#define divup(a, b) ((a) ? ((a) - 1) / (b) + 1 : 0)
#define inc(a, b, c) ((a) <= (b) && (b) <= (c))
#define inc2(a, b, c) ((a) < (b) && (b) < (c))
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define int long long

typedef long long li;
typedef long double ld;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<char> vc;
typedef vector<li> vli;
typedef vector<vli> vvli;
typedef vector<ld> vld;

const li MOD = 998'244'353;
const li INF = li(2e18) + 13LL;
const ld EPS = 1e-9L;
const ld PI = acosl(-1.0L);
const char nl = '\n';

template <typename T>
istream& operator>>(istream& in, vector<T>& v) {
    for (auto& x : v)
        in >> x;
    return in;
}

template <typename T>
ostream& operator<<(ostream& out, const vector<T>& v) {
    for (auto& x : v)
        out << x << ' ';
    return out;
}

bool is_pow2(li x) {
    return x && (x & -x) == x;
}

string dec_to_bin(li x) {
    if (!x) return "0";
    string s;
    while (x) {
        s += (x & 1) + '0';
        x >>= 1;
    }
    reverse(all(s));
    return s;
}

li bin_to_dec(const string& s) {
    li x = 0;
    int n = sz(s);
    for (int i = n - 1; i >= 0; --i)
        x += (s[i] - '0') * (1LL << (n - 1 - i));
    return x;
}

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
        if (b & 1) res = mul(res, a);
        a = mul(a, a);
        b >>= 1;
    }
    return res;
}

li inv(li x) {
    return binpow(x, MOD - 2);
}

template <typename T>
li gcd(const vector<T>& a) {
    li gcd1 = 0;
    for (auto x : a)
        gcd1 = gcd(gcd1, x);
    return gcd1;
}

template <typename T>
li lcm(const vector<T>& a) {
    li lcm1 = 1;
    for (auto x : a)
        lcm1 = lcm(lcm1, x);
    return lcm1;
}

template <typename T>
vi zip(const vector<T>& a) {
    vector<T> c = a;
    sort(all(c));
    c.erase(unique(all(c)), c.end());
    vi b;
    for (auto& x : a)
        b.push_back(lower_bound(all(c), x) - c.begin());
    return b;
}

string low(const string& s) {
    string s1 = s;
    for (char& c : s1)
        c = tolower(c);
    return s1;
}

string up(const string& s) {
    string s1 = s;
    for (char& c : s1)
        c = toupper(c);
    return s1;
}

//#define MULTITEST

void solve() {}

signed main() {
#ifdef _DEBUG
    (void)freopen("input.txt", "r", stdin);
    (void)freopen("output.txt", "w", stdout);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
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
