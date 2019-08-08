#include <bits/stdc++.h>
using namespace std; inline void fileio(const char* in, const char* out) { freopen(in, "r", stdin); freopen(out, "w", stdout); } 
#define TD typedef
#define forx(i,n) for(int i = 0; i < (n); ++i)
TD long long ll; TD long double ld; TD pair<int,int> pii; TD pair<ll, ll> pll; TD vector<int> VI; TD vector<bool> VB; TD vector<ll> VL;
const char nl = '\n'; const int INF = 0x3f3f3f3f; const ll LINF = 0x3f3f3f3f3f3f3f3fll; const ld EPS = 1e-9, PI = acos(-1);
#define ff first
#define ss second

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

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  // Emily <3
  
  
  cerr << "Time: " << (ld)clock() / CLOCKS_PER_SEC << nl;
  return 0;
}
