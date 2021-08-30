template <typename T, int K=17>
struct Segtree {
#define IN  (l <= s && e <= r)
#define OUT (r <= s || e <= l)
#define MID ((s+e)/2)
#define L (i*2)
#define R (i*2+1)
  constexpr static int SZ = 1 << K;
  T t[SZ*2];
  T& operator[](int i) { return t[i+SZ]; }
  void push(int i, int s, int e) {
    /* LAZY */
//    if (t[i].lazy == 0) return;
//    t[i].val ...t[i].lazy;
//    if (i < SZ) {
//      set(L, t[i].lazy);
//      set(R, t[i].lazy);
//    }
//    t[i].lazy = 0;
  }
  void build(int i=1, int s=0, int e=SZ) {
    if (s+1 == e) return;
    build(L, s, MID);
    build(R, MID, e);
    t[i].merge(t[L], t[R]);
  }
  void update(int l, int r, typename T::V v, int i=1, int s=0, int e=SZ) {
    if (OUT) return;
    if (IN) {
      t[i].set(v);
      return;
    }
    push(i,s,e);
    update(l, r, v, L, s, MID);
    update(l, r, v, R, MID, e);
    t[i].merge(t[L], t[R]);
  }
  T query(int l, int r, int i=1, int s=0, int e=SZ) {
    T ans = {};
    if (OUT) return ans;
    push(i,s,e);
    if (IN) return t[i];
    ans.merge(query(l, r, L, s, MID), query(l, r, R, MID, e));
    return ans;
  }
  /* binary search on { r, val }
   * where non-empty range [l, r) has value >= lim */
  pair<int,T> find_k(int l, T lim, int i=1, int s=0, int e=SZ, T add={}) {
    if (e <= l) return make_pair(e, T());
    push(i,s,e);
    T cur; cur.merge(add, t[i]);
    if (s+1 == e || !(cur >= lim)) {
      return make_pair(e, cur);
    }
    auto left = find_k(l, lim, L, s, MID, add);
    if (left.ss >= lim) return left;
    return find_k(l, lim, R, MID, e, left.ss);
  }
};

struct Data {
  // TODO: define data, default value!!
  using V = int;
  void set(V val) {
    throw "Not implemented";
  }
  void merge(const Data& l, const Data& r) {
    throw "Not implemented";
  }
  bool operator>=(const Data& o) {
    throw "Not implemented";
  }
};

