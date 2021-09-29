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

/* DEBUG */

#if (DEBUG && !defined(ONLINE_JUDGE))
template <class T> void _print(const T& t) { cerr << t << " "; }
template <class T> void _print(const vector<T>& t) {
  cerr << "[ "; for (auto it : t) cerr << it << " "; cerr << "]"; }
template <class TT, size_t... I>
void _print(const TT& tup, typename std::index_sequence<I...>) {
  (..., (cerr << get<I>(tup) << ", ")); }
template <class... T> void _print(tuple<T...>& t) {
  _print(t, index_sequence_for<T...>()); }
template <class F, class S>
void _print(pair<F,S>& p) {
  _print(p.ff); _print(p.ss);
}
#define trace(x)  { cerr << ">> Line " << __LINE__ << ": " #x " = "; _print(x); cerr << nl; }
#define debug if(1)
#else
#define trace(...)	{}
#define debug if(0)
#endif

/* BOOK CODE */

template <class K, typename V>
struct skiplist {
  struct node;
  using ptr = node*;
  struct node {
    ptr l,r,bot,up;
    pair<K,V> kv;
    node(): l(this), r(this) {}
    node(K k, V v, ptr p, ptr n): l(p), r(n), kv(k,v) {}
    auto& operator*() { return kv; }
    // insert after current node
    ptr append(K k, V v) {
      return r = r->l = new node(k, v, this, this->r);
    }
  };
  struct iter {
    node* p;
    iter& operator++() { p = p->r; return *this; }
    iter operator++(int) const { return ++iter(*this); }
    bool operator!=(const iter& b) const { return p != b.p; }
    auto& operator*() { return **p; }
  };
  vector<node> head;
  skiplist(): head(1) { }
  iter begin() { return { head[0].r }; }
  iter end()   { return { &head[0]  }; }
  ptr lower_bound(K k): const {
    // smallest val >= k
  }
};

/* REAL CODE */

void code() {
  skiplist<int,int> list;
  list.head[0].append(2,10);
  list.head[0].append(1,2);
  list.head[0].append(0,10);
  for (pii v : list) {
    trace(v);
  }
}

/* MAIN CODE */

int main() { // Emily <3
  atexit([]{ cerr << "Time: " << (ld)clock() / CLOCKS_PER_SEC << nl; });
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(12);
  code();
  return 0;
}

