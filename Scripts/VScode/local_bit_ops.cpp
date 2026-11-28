// Вставить после using namespace std; и до #define int long long.
// В настройках Visual Studio включить /std:c++20 и /DLOCAL.
// Вызывать __lg(x) при x > 0, __builtin_ctzll(x) при x != 0.
#ifdef LOCAL
#include <bit>

template<class T>
constexpr T local_lg(T x) {
    return T(bit_width((unsigned long long)x) - 1);
}

#define __lg(x) local_lg(x)
#define __builtin_ctzll(x) countr_zero((unsigned long long)(x))
#endif
