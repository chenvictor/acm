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

random_device rd;
mt19937 rng(rd());

template <class K, typename V, int MAXL>
struct skiplist {
  geometric_distribution<> geom;
  struct node;
  using ptr = node*;
  struct node {
    ptr l,r; // doubly linked list
    ptr up;  // entry in L_{i+1}
    ptr bot; // entry in L0 (could be self)
    union {
      ptr dn;       // entry in L_{i-1}
      pair<K,V> kv; // or pair<K,V> if L0 node
    };
    node(): l(this), r(this), bot(this) {}
    node(K k, V v, ptr p, ptr n): l(p), r(n), bot(this), kv(k,v) {}
    ~node() {}
    auto& operator*() { return bot->kv; }
    // insert after current node
    ptr append(K k, V v) {
      return r = r->l = new node(k, v, this, this->r);
    }
  };
  struct iter {
    node* p;
    iter& operator++() { p = p->r; return *this; }
    iter operator++(int) const { return ++iter(*this); }
    bool operator==(const iter& b) const { return p == b.p; }
    bool operator!=(const iter& b) const { return p != b.p; }
    auto& operator*() { return **p; }
    auto operator->() { return &**p; }
  };
  node head[MAXL]; int c=0; // current # levels
  skiplist() {
    rep(i,1,MAXL) {
      head[i].bot = &head[0];
      head[i].dn = &head[i-1];
      lb[i] = head[i-1].up = &head[i];
    }
  }
  ~skiplist() {}
  iter begin(int i=0) { return { head[i].r }; }
  iter end(int i=0)   { return { &head[i]  }; }

  ptr lb[MAXL];
  iter lower_bound(K k) {
    lb[c] = &head[c];
    for (int i=c; i >= 0; --i) {
      while (lb[i]->r != &head[i] && lb[i]->r->bot->kv.ff <= k) {
        lb[i] = lb[i]->r;
      }
      if (i > 0) {
        lb[i-1] = lb[i]->dn;
      }
    }
    return { lb[0] };
  }
  int count(K k) {
    iter it = lower_bound(k);
    return it->ff == k;
  }
  V& operator[](K k) {
    iter it = lower_bound(k);
    if (it == end() || it->ff != k) {
      const int level = min(geom(rng), MAXL-1);
      trace(level);
      for(int i=0; i <= level; ++i) {
        ptr nu = lb[i]->append(k, {});
        if (i > 0) {
          nu->bot = lb[0]->r;
          nu->dn = lb[i-1]->r;
          nu->dn->up = nu;
        }
      }
      c = max(c, level);
    }
    return it->ss;
  }
};

/* REAL CODE */

template <class K, class V, int SZ>
void verbose(skiplist<K,V,SZ>& list) {
  debug {
    const int levels = list.c+1;
    static char buffer[50];
    assert(levels >= 1);
    for (int i=0; i < levels; ++i) {
      auto l0 = list.begin();
      fprintf(stderr, "L%02d:", i);
      for (auto it = list.begin(i); it != list.end(i); ++it, ++l0) {
        while (it.p->bot != l0.p) {
          const int nspaces = sprintf(buffer, " %s", l0->ff.c_str());
          fprintf(stderr, "%*s", nspaces, "");
          ++l0;
        }
        fprintf(stderr, " %s", it->ff.c_str());
      }
      cerr << nl;
    }
  }
}

void code() {
  // testing on https://codeforces.com/contest/855/problem/A
  skiplist<string,bool,20> list;
  int n;
  cin >> n;
  for(int i=0; i < n; ++i) {
    string s; cin >> s;
    if (list.count(s)) {
      cout << "YES\n";
    } else {
      list[s] = 1;
      cout << "NO\n";
    }
    verbose(list);
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

