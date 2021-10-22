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

template <class K, typename T, int MAXL=20> // MAXL should be roughly lg(max elems)
struct skiplist {
  geometric_distribution<> geom;
  struct node;
  using ptr = node*;
  using value_type = pair<const K, T>;
  struct node {
    ptr l,r; // doubly linked list
    ptr up;  // entry in L_{i+1}
    ptr bot; // entry in L0 (could be self)
    union {
      ptr dn;       // entry in L_{i-1}
      pair<const K,T> kv; // or pair<K,T> if L0 node
    };
    node(): l(this), r(this), bot(this) {}
    node(ptr p, ptr n, ptr b, ptr d): l(p), r(n), bot(b), dn(d) { d->up = this; }
    node(ptr p, ptr n, const value_type& val): l(p), r(n), bot(this), kv(val) {}
    node(const K& k, T v, ptr p, ptr n): l(p), r(n), bot(this), kv(k,v) {}
    ~node() {}
    // insert after current node
    ptr append(const value_type& val) {
      assert(this == bot && "only append value at L0");
      return r = r->l = new node(this, this->r, val);
    }
    ptr append(ptr b, ptr d) {
      assert(this != b && "only append ptrs at L>0");
      return r = r->l = new node(this, this->r, b, d);
    }
  };
  struct iter {
    ptr p;
    iter(ptr x): p(x) {}
    iter& operator++() { p = p->r; return *this; }
    iter operator++(int) const { return ++iter(*this); }
    iter& operator--() { p = p->l; return *this; }
    iter operator--(int) const { return --iter(*this); }
    bool operator==(const iter& b) const { return p == b.p; }
    bool operator!=(const iter& b) const { return p != b.p; }
    auto& operator*() { return p->bot->kv; }
    auto operator->() { return &p->bot->kv; }
  };
  node head[MAXL]; int c=0; // current # levels
  ptr lb[MAXL]; // prev ptr from lower_bound
  size_t _size;
  skiplist(): _size(0) {
    rep(i,1,MAXL) {
      head[i].bot = &head[0];
      head[i].dn = &head[i-1];
      lb[i] = head[i-1].up = &head[i];
    }
  }
  ~skiplist() {}
  iter begin(int i=0) { return head[i].r; }
  iter end(int i=0)   { return &head[i]; }
  bool empty() const  { return size() == 0; }
  size_t size() const { return _size; }
  T& operator[](const K& k) {
    return insert(make_pair(k, T())).first->second;
  }
  pair<iter,bool> insert (const value_type& val) {
    iter it = lower_bound(val.first);
    if (it != end() && it->first == val.first) {
      return make_pair(it, false);
    }
    const int level = min(geom(rng), MAXL-1);
    c = max(c, level);
    const ptr n0 = lb[0]->append(val);
    ptr np = n0;
    for(int i=1; i <= level; ++i) {
      np = lb[i]->append(n0, np);
    }
    ++_size;
    return make_pair(iter(n0), true);
  }
  iter erase(iter pos) {
    throw "TODO";
  }
  size_t erase(const K& k) {
    throw "TODO";
  }
  void swap(skiplist& x) {
    throw "TODO";
  }
  void clear() {

  }
  iter find(const K& k) {

  }
  int count(const K& k) {
    iter it = lower_bound(k);
    return it->ff == k;
  }
  iter lower_bound(const K& k) {
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
  iter upper_bound(const K& k) {
    throw "TODO";
  }
};

/* REAL CODE */

template <class K, class T, int SZ>
void verbose(skiplist<K,T,SZ>& list) {
  debug {
    const int levels = list.c+1;
    assert(levels >= 1);
    for (int i=0; i < levels; ++i) {
      auto l0 = list.begin();
      cerr << "L" << i << '\t';
      for (auto it = list.begin(i); it != list.end(i); ++it, ++l0) {
        while (it.p->bot != l0.p) {
          stringstream ss;
          ss << " <" << l0->ff << "> ";
          string s = ss.str();
          fill(all(s), ' ');
          cerr << s;
          ++l0;
        }
        cerr << " <" << it->ff << "> ";
      }
      cerr << nl;
    }
  }
}

int num_reps;

void deal(auto& container, mt19937& gen) {
  uniform_int_distribution<> kv(int(-2e9), int(2e9));
  uniform_int_distribution<> op(0,1);
  const auto stime = clock();
  rep(i,0,num_reps){
    const int k = kv(gen);
    const int v = kv(gen);
    switch (op(gen)) {
      case 0:
        container[k] = v;
        break;
      case 1:
        container[k] += v;
        break;
    }
  }
  cerr << "time " << ld(clock() - stime) / CLOCKS_PER_SEC << nl;
}

int sd;

void fuzz() {
  cin >> sd >> num_reps;
  skiplist<int,int,40> l;
  map<int,ll> m;
  mt19937 gen;
  {
    cerr << "running map\n";
    gen.seed(sd);
    deal(m, gen);
  }
  {
    cerr << "running skiplist\n";
    gen.seed(sd);
    deal(l, gen);
  }
  assert(l.size() == m.size());
  auto it1 = l.begin();
  for (pii p : m) {
    assert(p.ff == it1->ff);
    assert(p.ss == it1->ss);
    ++it1;
  }
  assert(it1 == l.end());
  cerr << "all ok\n";
  exit(0);
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
  fuzz();
  code();
  return 0;
}

