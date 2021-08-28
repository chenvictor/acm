struct Segtree {
#define IN  (l <= s && e <= r)
#define OUT (r <= s || e <= l)
#define MID ((s+e)/2)
#define L (i*2)
#define R (i*2+1)
  using T = int;
  constexpr static T NUL = /* TODO */
  constexpr static int SZ = 1<<17;
  T t[SZ*2];
  T& operator[](int i) { return t[i+SZ]; }
  T merge(T l, T r) {
    /* TODO */
    return 
  }
  void set(T& cur, T val) {
    /* TODO */
    cur = 
  }
  void build(int i=1, int s=0, int e=SZ) {
    if (s+1 == e) return;
    build(L, s, MID);
    build(R, MID, e);
    t[i] = merge(t[L], t[R]);
  }
  void update(int l, int r, T v, int i=1, int s=0, int e=SZ) {
    if (OUT) return;
    if (IN) {
      set(t[i], v);
      return;
    }
    update(l, r, v, L, s, MID);
    update(l, r, v, R, MID, e);
    t[i] = merge(t[L], t[R]);
  }
  T query(int l, int r, int i=1, int s=0, int e=SZ) {
    if (IN) return t[i];
    if (OUT) return NUL;
    return merge(query(l, r, L, s, MID), query(l, r, R, MID, e));
  }
  /* binary search on { r, val }
   * where non-empty range [l, r) has value >= lim */
  pair<int,T> find_k(int l, T lim, int i=1, int s=0, int e=SZ, T add=NUL) {
    if (e <= l) return make_pair(e, NUL);
    T cur = merge(add, t[i]);
    if (s+1 == e || cur < lim) {
      return make_pair(e, cur);
    }
    auto left = find_k(l, lim, L, s, MID, add);
    if (left.ss >= lim) return left;
    return find_k(l, lim, R, MID, e, left.ss);
  }
};

