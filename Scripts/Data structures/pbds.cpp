// Этот #include ставить до макросов шаблона.
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
const unsigned long long FIXED_RANDOM =
    chrono::steady_clock::now().time_since_epoch().count();
struct custom_hash {
    size_t operator()(unsigned long long x) const {
        x += FIXED_RANDOM;
        x = (x ^ (x >> 30)) * 0xBF58476D1CE4E5B9ULL;
        x = (x ^ (x >> 27)) * 0x94D049BB133111EBULL;
        return x ^ (x >> 31);
    }
};
typedef gp_hash_table<int, null_type, custom_hash> fast_set;
typedef gp_hash_table<int, int, custom_hash> fast_map;
