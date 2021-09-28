#include <bits/stdc++.h>
using namespace std;
#define rep(i,s,e) for(int i = s; i < (e); ++i)
using ll = long long; using ld = long double;
using pii = pair<int,int>; using pll = pair<ll, ll>;
using vi = vector<int>; using vl = vector<ll>;
const char nl = '\n';
const ll LINF = 0x3f3f3f3f3f3f3f3fll; const int INF = (int)LINF;
const ld EPS = 1e-9, PI = acos(-1.0L);
#define ff first
#define ss second
#define all(c) begin(c),end(c)
#define sz(c) int(c.size())

/* BOOK CODE */

template <typename K, typename V>
struct skiplist {
  struct node {
    using ptr = shared_ptr<node>;
    pair<K,V> kv;
    ptr l,r;
    node(pair<K,V> kv, ptr l = NULL, ptr r = NULL): kv(kv), l(l), r(r) {}
    pair<K,V>& operator*() {
      return kv;
    }
    // insert after current node
    void append(pair<K,V> v) {
      auto n = new node(v.kv);
      n->l = l; n->r = 
      l = l->r = new node(v);
    }
  } head[20];
  ptr lower_bound(K k): const {
    // smallest val >= k
  }
};

/* REAL CODE */

void code() {
  skiplist<int,int> list;
}

/* MAIN CODE */

int main() { // Emily <3
  atexit([]{ cerr << "Time: " << (ld)clock() / CLOCKS_PER_SEC << nl; });
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(12);
  code();
  return 0;
}

