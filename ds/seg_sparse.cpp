template <int Q, int N> struct seg_sparse {
#define IN  (l <= s && e <= r)
#define OUT (r <= s || e <= l)
#define MID ((s+e)/2)
#define POINT(x) (x),(x)+1
  struct T {
    int L,R;
    T& merge(const T& l, const T& r) {
      return SELF;
    }
    bool update(int v) {
      return 1;
    }
  } t[Q];
  int rt = 0, id=1;
#define L t[i].L
#define R t[i].R
  void update(int l, int r, int v, int& i, int s=0, int e=N) {
    if (OUT) return;
    if (!i) i = id++;
    if (IN && t[i].update(v)) return;
    update(l, r, v, L, s, MID);
    update(l, r, v, R, MID, e);
    t[i].merge(t[L], t[R]);
  }
  void update(int l, int r, int v) {
    update(l,r,v,rt);
  }
  T query(int l, int r, int& i, int s=0, int e=N) {
    if (OUT) return {};
    if (!i) i = id++;
    if (IN) return t[i];
    return T{}.merge(query(l, r, L, s, MID), query(l, r, R, MID, e));
  }
  T query(int l, int r) { return query(l,r,rt); }
};

