#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
template <class K, class Hash> struct chash { const size_t RANDOM; const Hash hash; size_t operator()(K key) const { return hash(key) ^ RANDOM; }
  chash() : RANDOM(  (size_t)make_unique<char>().get() ^ (size_t)chrono::high_resolution_clock::now().time_since_epoch().count()  ), hash() { } };
namespace Hashes { struct hash_pii { size_t operator()(pii key) const { return ((size_t)key.ff << 32) | key.ss; } }; }
// HashMap = umap
template <class K, class V, class Hash=hash<K>>
using umap = __gnu_pbds::gp_hash_table<K,V,chash<K,Hash>>;
// HashSet = uset
template <class K, class Hash=hash<K>>
using uset = umap<K, __gnu_pbds::null_type, Hash>;
// oset<K[, Comp]> = Ordered Statistics Set tree
template <class K, class Comp=less<K>>
using oset = __gnu_pbds::tree<K, __gnu_pbds::null_type, Comp, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;
