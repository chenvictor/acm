#include <bits/extc++.h>
namespace fancy {
  using namespace __gnu_pbds;
  template <typename K, typename Cmp=less<K>>
  using set = tree<K, null_type, Cmp, rb_tree_tag, tree_order_statistics_node_update>;
  /** set with order statistics
   * set.order_of_key(k)   number of elements preceding
   * set.find_by_order(k)  get ith element
   **/

  template <typename T, typename Cmp=less<T>>
  using heap = __gnu_pbds::priority_queue<T,Cmp>;
  /** Heap with modifications
   * auto it = heap.push(x);
   * heap.modify(it, y);
   **/
}

