// A faster version of unordered_map
// source: https://codeforces.com/blog/entry/60737?#comment-446357
// usage: same as unordered_map
#include <ext/pb_ds/assoc_container.hpp>
template <class K, class Hash>
struct chash {
  // Randomize the hash via XOR with a heap pointer and current time
  const size_t RANDOM; const Hash hash; size_t operator()(K key) const { return hash(key) ^ RANDOM; }
  chash() : RANDOM(  (size_t)make_unique<char>().get() ^ (size_t)chrono::high_resolution_clock::now().time_since_epoch().count()  ), hash() { } };
template <class K, class V, class Hash=hash<K>>
using FastMap = __gnu_pbds::gp_hash_table<K,V,chash<K,Hash>>;
// some hash functions
namespace Hashes {
  struct pii { size_t operator()(pii key) const { return ((size_t)key.ff << 32) | key.ss; } };
}
