// Эти #include ставить до макросов шаблона.
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag,
    tree_order_statistics_node_update>
    ordered_multiset;

const unsigned long long FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();

struct custom_hash {
    size_t operator()(unsigned long long x) const {
        x += FIXED_RANDOM;
        x = (x ^ (x >> 30)) * 0xBF58476D1CE4E5B9ULL;
        x = (x ^ (x >> 27)) * 0x94D049BB133111EBULL;
        x = x ^ (x >> 31);
        return x;
    }
};

// Более простой хеш без случайной соли.
struct simple_hash {
    size_t operator()(unsigned long long x) const {
        return x * 0x9e3779b97f4a7c15ULL;
    }
};

typedef gp_hash_table<int, null_type, custom_hash> fast_set;
typedef gp_hash_table<int, int, custom_hash> fast_map;

void example() {
    ordered_set s;
    s.insert(3);
    auto it = s.find_by_order(0);
    int x = *it; // Запрашиваем только существующий порядковый номер.
    s.order_of_key(x); // Число элементов, строго меньших x.

    ordered_multiset ms;
    int s_id = 0;
    ms.insert({3, ++s_id});
    ms.insert({5, ++s_id});
    ms.insert({5, ++s_id});

    auto one = ms.lower_bound({5, 0});
    if (one != ms.end() && one->first == 5) ms.erase(one);

    auto first = ms.lower_bound({5, 0});
    auto last = ms.upper_bound({5, s_id});
    while (first != last)
        first = ms.erase(first); // У PBDS нет erase(first, last).

    fast_map cnt;
    ++cnt[3];
}
