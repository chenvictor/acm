template <typename T, int K=17>
struct segtree {
#define IN  (l <= s && e <= r)
#define OUT (r <= s || e <= l)
#define MID ((s+e)/2)
#define L (i*2)
#define R (i*2+1)
  constexpr static int N = 1 << K;
  array<T,2*N> t;
  T& operator[](int i) { return t[i+N]; }
  void build(int i=1, int s=0, int e=N) {
    if (s+1==e) return;
    build(L, s, MID);
    build(R, MID, e);
    t[i].merge(t[L], t[R]);
  }
  T query(int l, int r, int i=1, int s=0, int e=N) {
    if (IN) return t[i];
    if (OUT) return T();
    t[i].prop(t[L], t[R], e-s);
    return T(query(l, r, L, s, MID), query(l, r, R, MID, e));
  }
  template<typename Op, typename...A>
  void upd(int l, int r, int i, int s, int e, A...args) {
    if (OUT) return;
    if (IN && Op::calc(t[i], args..., e-s)) return;
    t[i].prop(t[L], t[R], e-s);
    upd<Op>(l, r, L, s, MID, args...);
    upd<Op>(l, r, R, MID, e, args...);
    t[i].merge(t[L], t[R]);
  }
  template<typename Op, typename...A>
  void update(int l, int r, A...args){ upd<Op>(l,r,1,0,N,args...); }
  /* Binary search - first index r where range [l, r] has value >= lim */
  template<typename Find, typename...A>
  pair<int,T> find(int l, int i, int s, int e, T acc, A...args) {
    if (e <= l) return {N, T()};
    T cur(acc, t[i]);
    const bool ok = Find::ok(cur, args...);
    if (!ok || s+1==e) return {ok ? s : N, cur};
    t[i].prop(t[L], t[R], e-s);
    auto left = find<Find>(l, L, s, MID, acc, args...);
    if (Find::ok(left.ss, args...)) return left;
    return find<Find>(l, R, MID, e, left.ss, args...);
  }
  template<typename Find, typename...A>
  pair<int,T> find(int l, A...args) { return find<Find>(l,1,0,N,T(),args...); }
};

