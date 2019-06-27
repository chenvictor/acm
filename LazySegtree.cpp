template <typename T>
class LazySegtree {
  const int n, h;
  vector<T> t,d;
  VB lazy_bit;
  // merge function
  function<T(const T&, const T&)> pull;
  // update operation (eg. set, increment)
  function<void(T&, const T&, int)> updt;
  // update segment value using lazy value
  function<void(T&, const T&, int)> apply_lazy;
  void calc(int p, int seg_len) { t[p] = pull(t[p<<1], t[p<<1|1]); if (lazy_bit[p]) apply_lazy(t[p], d[p], seg_len); }
  void apply(int p, T value, int seg_len) { updt(t[p], value, seg_len); if (p < n) { d[p] = value; lazy_bit[p] = true; } }
  void build(int l, int r) { int k = 2; for (l += n, r += n-1; l > 1; k <<= 1) { l >>= 1, r >>= 1; for (int i = r; i >= l; --i) calc(i, k); } }
  void push(int l, int r) { int s = h, k = 1 << (h-1); for (l += n, r += n-1; s > 0; --s, k >>= 1) { for (int i = l >> s; i <= r >> s; ++i) {
        if (lazy_bit[i]) { apply(i<<1,   d[i], k); apply(i<<1|1, d[i], k); lazy_bit[i] = false; } } } }
  public:
    LazySegtree(int n, function<T(const T&, const T&)> pull, function<void(T&, const T&, int)> updt, function<void(T&, const T&, int)> apply_lazy) :
      n(n), h(sizeof(int) * 8 - __builtin_clz(n)), t(2*n), d(n), lazy_bit(n, false), pull(pull), updt(updt), apply_lazy(apply_lazy) {}
    // point update
    void update(int p, T value) { push(p, p+1); apply(p+n, value, 1); build(p, p+1); }
    // update range [l, r)
    void update(int l, int r, T value) { push(l, l+1); push(r-1, r); int l0 = l, r0 = r, k = 1; for (l += n, r += n; l < r; l >>= 1, r >>= 1, k <<= 1) {
        if (l & 1) { apply(l++, value, k); } if (r & 1) { apply(--r, value, k); } } build(l0, l0+1); build(r0-1, r0); }
    // point query
    T query(int p) { push(p, p+1); return t[p + n]; }
    // query range [l, r)
    T query(int l, int r) { push(l, l+1); push(r-1, r); T resl, resr; bool initl = false, initr = false; for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) { resl = initl ? pull(resl, t[l++]) : (initl=true, t[l++]); } if (r & 1) { resr = initr ? pull(resr, t[--r]) : (initr=true, t[--r]); } }
      return initl ? (initr ? (pull(resl, resr)) : resl) : resr; }
};
