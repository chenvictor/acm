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
  void push(int i, int len) {
    /* LAZY */
    t[i].prop(t[L], t[R], len);
  }
  void build(int i=1, int s=0, int e=SZ) {
    if (s+1 == e) return;
    build(L, s, MID);
    build(R, MID, e);
    t[i].merge(t[L], t[R]);
  }
  void update(int l, int r, typename T::V v, int i=1, int s=0, int e=SZ) {
    if (IN) {
      t[i].set(v,e-s);
      return;
    }
    if (OUT) return;
    push(i,e-s);
    update(l, r, v, L, s, MID);
    update(l, r, v, R, MID, e);
    t[i].merge(t[L], t[R]);
  }
  T query(int l, int r, int i=1, int s=0, int e=SZ) {
    if (IN) return t[i];
    T ans = {};
    if (OUT) return ans;
    push(i,e-s);
    ans.merge(query(l, r, L, s, MID), query(l, r, R, MID, e));
    return ans;
  }
  /* binary search on { r, val }
   * where non-empty range [l, r) has value >= lim */
  pair<int,T> find(int l, typename T::S lim, int i=1, int s=0, int e=SZ, T add={}) {
    if (e <= l) return make_pair(e, T());
    T cur; cur.merge(add, t[i]);
    if (s+1 == e || !(cur >= lim)) {
      return make_pair(e, cur);
    }
    push(i,e-s);
    auto left = find(l, lim, L, s, MID, add);
    if (left.ss >= lim) return left;
    return find(l, lim, R, MID, e, left.ss);
  }
};

struct Data {
  // TODO: define data, default value!!
  void merge(const Data& l, const Data& r) {
    throw "Not implemented";
  }
  /* Update */
  using V = int;
  void set(V val, int len) {
    throw "Not implemented";
  }
  /* Lazy Prop */
  void prop(Data& l, Data& r, int len) {
    // Optional
//    if (d == -1) return;
//    l.set(d,len/2);
//    r.set(d,len/2);
//    d = -1;
  }
  /* Binary Search */
  using S = int;
  bool operator>=(S lim) const {
    // Optional
    throw "Not implemented";
  }
};

