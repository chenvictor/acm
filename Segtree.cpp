typedef int Data;
typedef int Update;
class Segtree { const int h, n; vector<Data> t; vector<Update> d; VB lazy_bit;
  void pull(Data& p, Data l, Data r) {
    (void) p;
    (void) l;
    (void) r;
  }
  void update(Data& cur, Update val, int k) {
    (void) cur;
    (void) val;
    (void) k;   // k is segment length
  }
  void apply_lazy(Data& cur, Update lazy, int k) {
    (void) cur;
    (void) val;
    (void) k;   // k is segment length
  }
  void calc(int p, int seg_len) { pull(t[p], t[p<<1], t[p<<1|1]); if (lazy_bit[p]) apply_lazy(t[p], d[p], seg_len); }
  void apply(int p, Update value, int seg_len) { update(t[p], value, seg_len); if (p < n) { d[p] = value; lazy_bit[p] = true; } }
  void build(int l, int r) { int k = 2; for (l += n, r += n-1; l > 1; k <<= 1) { l >>= 1, r >>= 1; for (int i = r; i >= l; --i) calc(i, k); } }
  void push(int l, int r) { int s = h, k = 1 << (h-1); for (l += n, r += n-1; s > 0; --s, k >>= 1) { for (int i = l >> s; i <= r >> s; ++i) {
    if (lazy_bit[i]) { apply(i<<1, d[i], k); apply(i<<1|1, d[i], k); lazy_bit[i] = false; } } } }
  bool built = false; public: Segtree(int x) : h(32 - __builtin_clz(x)), n(1<<h), t(2*n), d(n), lazy_bit(n) {}
  Data& operator[](int i) { assert(!built); return t[n+i]; }
  void init() { assert(!built); for(int i = n-1; i > 0; i--) { pull(t[i], t[i<<1], t[i<<1|1]); } built = true; }
  // point update
  void set(int p, Update value) { push(p, p+1); apply(p+n, value, 1); build(p, p+1); }
  // update range [l, r)
  void set_range(int l, int r, Update value) { push(l, l+1); push(r-1, r); int l0 = l, r0 = r, k = 1; for (l += n, r += n; l < r; l >>= 1, r >>= 1, k <<= 1) {
    if (l & 1) { apply(l++, value, k); } if (r & 1) { apply(--r, value, k); } } build(l0, l0+1); build(r0-1, r0); }
  // point query
  Data get(int p) { push(p, p+1); return t[p + n]; }
  // query range [l, r)
  Data get_range(int l, int r) { push(l, l+1); push(r-1, r); Data resl, resr; bool il = false, ir = false; for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) { if(il) { pull(resl, resl, t[l++]); } else { il=true, resl = t[l++]; } }
    if (r & 1) { if(ir) { pull(resr, t[--r], resr); } else { ir=true, resr = t[--r]; } } }
    if (!il) { return resr; } else if (ir) { pull(resl, resl, resr); } return resl; }
};
