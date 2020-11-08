struct bm {
  int v; bm(int val=0) : v(val) {}
  bool operator[](int i) const { return v & 1 << i; }
  bm set(int i) const { return bm(v | 1 << i); }
  int count() const { return __builtin_popcount(v); }
};
#define for_submasks(s, m) for (int s=m, l=1<<bm(m).count(); l--; s=(s-1)&m)

