template <int SZ>
struct Segtree {
#define IN  (l <= s && e <= r)
#define OUT (r <= s || e <= l)
#define MID ((s+e)/2)
#define L (i*2)
#define R (i*2+1)
  int t[SZ*2];
  void update(int l, int r, int v, int i=1, int s=0, int e=SZ) {
    if (OUT) return;
    if (IN) {
      t[i] = v;
      return;
    }
    update(l, r, v, L, s, MID);
    update(l, r, v, R, MID, e);
    t[i] = t[L] + t[R];
  }

  int query(int l, int r, int i=1, int s=0, int e=SZ) {
    if (IN) return t[i];
    if (OUT) return 0;
    return query(l, r, L, s, MID)
      + query(l, r, R, MID, e);
  }
};

