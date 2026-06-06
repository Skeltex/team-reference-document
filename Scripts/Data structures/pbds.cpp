#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/hash_policy.hpp>
using namespace __gnu_pbds;

typedef tree<
    int,
    null_type,
    less<int>,
    rb_tree_tag,
    tree_order_statistics_node_update
> ordered_set;

ordered_set s;
auto it = s.find_by_order(0);
int x = *it;

s.order_of_key(3);


typedef tree<
    pair<int, int>,
    null_type,
    less<pair<int, int>>,
    rb_tree_tag,
    tree_order_statistics_node_update
> ordered_multiset;

ordered_multiset s;
int s_id = 0;
s.insert({3, ++s_id});

auto it = ms.lower_bound({5, -INF});
if (it != ms.end() && it->first == 5)
    ms.erase(it);

auto first = ms.lower_bound({5, -INF});
auto last = ms.upper_bound({5, INF});
ms.erase(first, last);


typedef gp_hash_table<int, null_type, custom_hash> fast_unordered_set;

const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();

struct custom_hash {
    size_t operator()(long long x) const {
        x += FIXED_RANDOM;
        x = (x ^ (x >> 30)) * 0xBF58476D1CE4E5B9ULL;
        x = (x ^ (x >> 27)) * 0x94D049BB133111EBULL;
        x = x ^ (x >> 31);
        return x;
    }
};

struct custom_hash {
    size_t operator()(long long x) const {
        return x * 0x9e3779b97f4a7c15ULL;
    }
};